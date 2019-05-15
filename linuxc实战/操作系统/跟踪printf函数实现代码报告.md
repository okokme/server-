# 跟踪printf函数实现代码报告

##### 首先我们先写一个关于printf的简单输出函数

```c
#include <stdio.h>
int main()

{
	printf("hello");
	return 0;
}

```

##### 然后我们通过gdb的debuginfo调试来进入printf函数追踪一下有关printf的历程。

* 首先我们输入`l`，看看printf函数在何方（第几行），然后使用`b`在这一行打断点，打断点的目的是为了我们等会使用debug进入这个函数。

* 接下来，我们在gdb 中输入`run`来运行整个程序，它会在我们打断点的地方停止，接下来输入`s`，进入printf函数，debug输出 ：

  ```c
  _IO_puts (str=0x4005d0 "hello") at ioputs.c:33
  ```

  我们进入了ioputs.c文件.

* 再往深层次进入：

  ```c
  35	  _IO_size_t len = strlen (str);
  ```

  如果再往深层次进入就会进入strlen函数了、汇编代码了，我们就没有研究的必要了。

* 那么我们的深度够了就接着往下执行吧。

```c
_IO_puts (str=0x4005d0 "hello") at ioputs.c:36
36	  IO_acquire_lock (IO_stdout);
(gdb) 
35	  _IO_size_t len = strlen (str);
(gdb)
36	  IO_acquire_lock (IO_stdout);
(gdb) 
39	       || IO_fwide (IO_stdout, -1) == -1)

```

获取长度和IO输出锁，让我们再进入IO_fwide进去一探究竟

```c
40	      && _IO_sputn (_IO_stdout, str, len) == len
(gdb) s
IO_validate_vtable (vtable=0x7ffff7bcb3a0 <__GI__IO_file_jumps>) at libioP.h:959
959	  uintptr_t section_length = __stop___libc_IO_vtables - __start___libc_IO_vtables;
(gdb) 
961	  uintptr_t offset = ptr - __start___libc_IO_vtables;
(gdb) 
962	  if (__glibc_unlikely (offset >= section_length))
(gdb) 
_IO_puts (str=0x4005d0 "hello") at ioputs.c:40
40	      && _IO_sputn (_IO_stdout, str, len) == len
```

原来是为了判断字符串长度大小，我们之前的已有知识了解到

```c
printf("hello");和 printf("hello\n");是不同的
```

我们要知道，printf函数是一个有缓存i/o底层系统调用函数是write无缓冲函数，是系统调用函数。而printf和write的调用关系是 调用printf中缓冲区已满或使用‘\n’将调用一次底层系统调用函数进入内核执行一次。所以这个判断字符串长度大小就是为了判断是否要进入一次内核。

根据如上分析，所以有这一段;

```c
39	       || _IO_fwide (_IO_stdout, -1) == -1)
(gdb) 
40	      && _IO_sputn (_IO_stdout, str, len) == len
(gdb) 
41	      && _IO_putc_unlocked ('\n', _IO_stdout) != EOF)
(宏观整体分析)
```

往细了分析，就是如下代码：

```
  if ((f->_flags & _IO_LINE_BUF) && (f->_flags & _IO_CURRENTLY_PUTTING))
(gdb) n
1305	  else if (f->_IO_write_end > f->_IO_write_ptr)
(gdb) 
1322	  if (to_do + must_flush > 0)
(gdb) 
1326	      if (_IO_OVERFLOW (f, EOF) == EOF)
(gdb) 
1332	      block_size = f->_IO_buf_end - f->_IO_buf_base;
(gdb) 
1333	      do_write = to_do - (block_size >= 128 ? to_do % block_size : 0);
(gdb) 
1335	      if (do_write)
(gdb) 
1346	      if (to_do)
(gdb) 
1347		to_do -= _IO_default_xsputn (f, s+do_write, to_do);
(gdb) 
1349	  return n - to_do;
(gdb) 
1350	}
(gdb) 
_IO_puts (str=0x4005d0 "hello") at ioputs.c:41
41	      && _IO_putc_unlocked ('\n', _IO_stdout) != EOF)
(gdb) 
hello
42	    result = MIN (INT_MAX, len + 1);
(gdb) 
36	  _IO_acquire_lock (_IO_stdout);

```

把最简单的printf输出字符串通过debug扒了一下，理解的还不是很深，那么我们接下来来分析分析printf的源码。

首先我们在stdio.c里找到printf的实现代码

```c
int printf(const char*cntrl_string,...)
```

```c

#include "boot.h"

static int skip_atoi(const char **s)
{
    int i = 0;

    while (isdigit(**s))
        i = i * 10 + *((*s)++) - '0';
    return i;
}

#define ZEROPAD    1        /* pad with zero */
#define SIGN    2        /* unsigned/signed long */
#define PLUS    4        /* show plus */
#define SPACE    8        /* space if plus */
#define LEFT    16        /* left justified */
#define SMALL    32        /* Must be 32 == 0x20 */
#define SPECIAL    64        /* 0x */

#define __do_div(n, base) ({ \
int __res; \
__res = ((unsigned long) n) % (unsigned) base; \
n = ((unsigned long) n) / (unsigned) base; \
__res; })

static char *number(char *str, long num, int base, int size, int precision,
         int type)
{
    /* we are called with base 8, 10 or 16, only, thus don't need "G..." */
    static const char digits[16] = "0123456789ABCDEF"; /* "GHIJKLMNOPQRSTUVWXYZ"; */

    char tmp[66];
    char c, sign, locase;
    int i;

    /* locase = 0 or 0x20. ORing digits or letters with 'locase'
     * produces same digits or (maybe lowercased) letters */
    locase = (type & SMALL);
    if (type & LEFT)
        type &= ~ZEROPAD;
    if (base < 2 || base > 36)
        return NULL;
    c = (type & ZEROPAD) ? '0' : ' ';
    sign = 0;
    if (type & SIGN) {
        if (num < 0) {
            sign = '-';
            num = -num;
            size--;
        } else if (type & PLUS) {
            sign = '+';
            size--;
        } else if (type & SPACE) {
            sign = ' ';
            size--;
        }
    }
    if (type & SPECIAL) {
        if (base == 16)
            size -= 2;
        else if (base == 8)
            size--;
    }
    i = 0;
    if (num == 0)
        tmp[i++] = '0';
    else
        while (num != 0)
            tmp[i++] = (digits[__do_div(num, base)] | locase);
    if (i > precision)
        precision = i;
    size -= precision;
    if (!(type & (ZEROPAD + LEFT)))
        while (size-- > 0)
            *str++ = ' ';
    if (sign)
        *str++ = sign;
    if (type & SPECIAL) {
        if (base == 8)
            *str++ = '0';
        else if (base == 16) {
            *str++ = '0';
            *str++ = ('X' | locase);
        }
    }
    if (!(type & LEFT))
        while (size-- > 0)
            *str++ = c;
    while (i < precision--)
        *str++ = '0';
    while (i-- > 0)
        *str++ = tmp[i];
    while (size-- > 0)
        *str++ = ' ';
    return str;
}

int vsprintf(char *buf, const char *fmt, va_list args)
{
    int len;
    unsigned long num;
    int i, base;
    char *str;
    const char *s;

    int flags;        /* flags to number() */

    int field_width;    /* width of output field */
    int precision;        /* min. # of digits for integers; max
                 number of chars for from string */
    int qualifier;        /* 'h', 'l', or 'L' for integer fields */

    for (str = buf; *fmt; ++fmt) {
        if (*fmt != '%') {
            *str++ = *fmt;
            continue;
        }

        /* process flags */
        flags = 0;
     repeat:
        ++fmt;        /* this also skips first '%' */
        switch (*fmt) {
        case '-':
            flags |= LEFT;
            goto repeat;
        case '+':
            flags |= PLUS;
            goto repeat;
        case ' ':
            flags |= SPACE;
            goto repeat;
        case '#':
            flags |= SPECIAL;
            goto repeat;
        case '0':
            flags |= ZEROPAD;
            goto repeat;
        }

        /* get field width */
        field_width = -1;
        if (isdigit(*fmt))
            field_width = skip_atoi(&fmt);
        else if (*fmt == '*') {
            ++fmt;
            /* it's the next argument */
            field_width = va_arg(args, int);
            if (field_width < 0) {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

        /* get the precision */
        precision = -1;
        if (*fmt == '.') {
            ++fmt;
            if (isdigit(*fmt))
                precision = skip_atoi(&fmt);
            else if (*fmt == '*') {
                ++fmt;
                /* it's the next argument */
                precision = va_arg(args, int);
            }
            if (precision < 0)
                precision = 0;
        }

        /* get the conversion qualifier */
        qualifier = -1;
        if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L') {
            qualifier = *fmt;
            ++fmt;
        }

        /* default base */
        base = 10;

        switch (*fmt) {
        case 'c':
            if (!(flags & LEFT))
                while (--field_width > 0)
                    *str++ = ' ';
            *str++ = (unsigned char)va_arg(args, int);
            while (--field_width > 0)
                *str++ = ' ';
            continue;

        case 's':
            s = va_arg(args, char *);
            len = strnlen(s, precision);

            if (!(flags & LEFT))
                while (len < field_width--)
                    *str++ = ' ';
            for (i = 0; i < len; ++i)
                *str++ = *s++;
            while (len < field_width--)
                *str++ = ' ';
            continue;

        case 'p':
            if (field_width == -1) {
                field_width = 2 * sizeof(void *);
                flags |= ZEROPAD;
            }
            str = number(str,
                 (unsigned long)va_arg(args, void *), 16,
                 field_width, precision, flags);
            continue;

        case 'n':
            if (qualifier == 'l') {
                long *ip = va_arg(args, long *);
                *ip = (str - buf);
            } else {
                int *ip = va_arg(args, int *);
                *ip = (str - buf);
            }
            continue;

        case '%':
            *str++ = '%';
            continue;

            /* integer number formats - set up the flags and "break" */
        case 'o':
            base = 8;
            break;

        case 'x':
            flags |= SMALL;
        case 'X':
            base = 16;
            break;

        case 'd':
        case 'i':
            flags |= SIGN;
        case 'u':
            break;

        default:
            *str++ = '%';
            if (*fmt)
                *str++ = *fmt;
            else
                --fmt;
            continue;
        }
        if (qualifier == 'l')
            num = va_arg(args, unsigned long);
        else if (qualifier == 'h') {
            num = (unsigned short)va_arg(args, int);
            if (flags & SIGN)
                num = (short)num;
        } else if (flags & SIGN)
            num = va_arg(args, int);
        else
            num = va_arg(args, unsigned int);
        str = number(str, num, base, field_width, precision, flags);
    }
    *str = '\0';
    return str - buf;
}

int sprintf(char *buf, const char *fmt, ...)
{
    va_list args;
    int i;

    va_start(args, fmt);
    i = vsprintf(buf, fmt, args);
    va_end(args);
    return i;
}

int printf(const char *fmt, ...)
{
    char printf_buf[1024];
    va_list args;
    int printed;

    va_start(args, fmt);
    printed = vsprintf(printf_buf, fmt, args);
    va_end(args);

    puts(printf_buf);

    return printed;
}
```

* 1.从含有可选参数函数中获得可选参数，以及操作这些参数 

  ```c
  ypedef char *va_list;
  void va_start( va_list arg_ptr, prev_param );  
  type va_arg( va_list arg_ptr, type ); 
  void va_end( va_list arg_ptr );
  ```

假设函数有一个必选参数和多个可选参数，必选参数声明为普通数据类型，且能通过参数名vim 来获得该变量的值。

可选参数通过宏va_start、va_arg和va_end（定义在stdarg.h或varargs.h中）来进行操作，即通过设置指向第一个可选参数指针、返回当前参数、在返回参数后重新设置指针来操作所有的可选参数。

* va_start:为获取可变数目参数的函数的参数提供一种便捷手段。设置arg_ptr为指向传给函数参数列表中的第一个可选参数的指针，且该参数必须是va_list类型。prev_param是在参数列表中第一个可选参数前的必选参数。

* va_arg：返回由arg_ptr所指向的参数的值，且自增指向下一个参数的地址。type为当前参数的类型，用来计算该参数的长度，确定下一个参数的起始位置。它可以在函数中应用多次，直到得到函数的所有参数为止，但必须在宏va_start后面调用。

* va_end:在获取所有的参数后，设置指针arg_ptr为NULL。

* 2. 锁定字符串及输出字符串到屏幕

     ```c
     2、锁定字符串及输出字符串到屏幕
     #define _lock_str2(i,s) _lock_file2(i,s)
     void __cdecl _lock_file2(int, void *);
     #define _unlock_str2(i,s) _unlock_file2(i,s)
     void __cdecl _unlock_file2(int, void *);
     int __cdecl _stbuf(FILE *);
     void __cdecl _ftbuf(int, FILE *);
     int __cdecl _output(FILE *, const char *, va_list);
     ```

     在output函数中，读取格式字符串中的每一个字符，然后对其进行处理，处理方式根据每一个字符所代表的意义来进行，如：普通字符直接利用函数WRITE_CHAR(ch, &charsout);输出到控制台。

  * 下面是函数output()(output.c)部分源代码：

  ```c
  case ST_TYPE:
  //表示当前处理的字符的类型为转换说明符。
  ...
  switch (ch) {
  //下面对参数的获取都是利用宏va_arg( va_list arg_ptr, type );来进行的。
  case ''c'': {
  //从参数表中获取单个字符，输出到缓冲字符串中，此时，type=int 
  buffer[0] = (char) get_int_arg(&argptr); /* get char to print */
  text = buffer;
  textlen = 1; /* print just a single character */
  }
  break;
  
  case ''s'': {
  //从参数表中获取字符串，输出到缓冲字符串中，此时，type=char*
  int i;
  char *p; /* temps */
  text = get_ptr_arg(&argptr);
  ...
  }
  break;
  
  case ''w'': {
  //对宽字符进行处理
  ...
  } /* case ''w'' */
  break;
  ...
  case ''e'':
  case ''f'':
  case ''g'': {
  //对浮点数进行操作
  ...
  #if !LONGDOUBLE_IS_DOUBLE
  /* do the conversion */
  if (flags & FL_LONGDOUBLE) {
  _cldcvt((LONGDOUBLE*)argptr, text, ch, precision, capexp);
  va_arg(argptr, LONGDOUBLE);
  //对长双精度型进行处理，此时，type=long double
  }
  else
  #endif /* !LONGDOUBLE_IS_DOUBLE */
  {
  
  //对双精度型进行处理，此时，type=double
  _cfltcvt((DOUBLE*)argptr, text, ch, precision, capexp);
  va_arg(argptr, DOUBLE);
  }
  ...
  break;
  //对整型变量处理
  case ''d'':
  case ''i'':
  ...
  goto COMMON_INT;
  
  case ''u'':
  radix = 10;
  goto COMMON_INT;
  
  case ''p'':
  ...
  goto COMMON_INT;
  
  case ''o'':
  ...
  ```

  注：对于浮点型double和long double，有相应的转换说明符，但是float却没有。其中的原因是：在K&RC下，float值用于表达式或用作参数前，会自动转换成double型。而ANSI C一般不会自动把float转换成double。有些程序已假定其中的float参数会被转换成double,为了保护大量这样的程序，所有printf()函数的float参数还是被自动转换成double型。因此，在K&RC或ANSI C下，都无需用特定的转换说明符来显示float型。

  如果转换说明与类型不匹配，将会出现意想不到的结果。为什么呢？问题就在于C向函数传递信息的方式。 这个失败的根本细节与具体实现相关。它决定了系统中的参数以何方式传递。

  比如

  ```c
  float a;
  double b;
  long c;
  long d;
  ...
  printf("%ld,%ld,%ld,%ld",a,b,c,d);
  ```

  这个调用告诉计算机，要把a,b,c,d的值交给计算机，它把这些变量放进栈来完成这一任务。计算机把这些值放入栈中，其根据是变量类型而不是转换说明符，这就关系到了我们的字节对齐。

#### 接下来我们再看看printf函数的背后的处理

##### 预处理、编译、汇编、链接

`gcc -E printf.c -o printf.i`  预处理，完成宏定义的替换

`gcc -S printf.i -o printf.S` 生成汇编代码

` gcc -c printf.S -o printf.o` 汇编，将汇编代码转化为机器可以执行的机器指令

`objdump -h printf.o`  查看.o目标文件的内容

汇编代码如下：（图1）

![1556417466264](/home/k/Pictures/操作系统/call_puts.png)



从中我们可以发现printf函数调用被转化为call puts指令，而不是call printf指令。这是编译器对printf的一种优化。

对于printf上的参数如果是以'\n'为结尾的纯字符串，printf通常会被优化为puts函数，而字符串结尾的'\n'会被消除。除此之外，都会正常生成为call printf指令。

当我printf输出为一字符串时（无\n'情况）测试案例：（图2）

![1556417073499](/home/k/Pictures/操作系统/call_printf.png)

 接下来，汇编器开始工作。将汇编文件转化为我们不能直接阅读的二进制格式——可重定位目标文件，这里我们需要gcc工具包的objdump命令查看它的二进制信息。

使用 `objdump -sd printf`进行反汇编。找到链接方式---静态连接方式。（图3）

![1556426261612](/home/k/Pictures/操作系统/main.png)

静态链接时，链接器将C语言的运行库链接到可执行文件。由于我们使用了库函数puts，因此需要库文件libc.a 。而libc.a与libgcc.a和libgcc_eh.a有相互依赖关系，因此需要使用-strat-group和-end-group将他们包含起来。

链接后，call puts的地址被修正，但是反汇编显示的符号是puts@plt而不是puts。

我们使用`readelf a.out -S`查看main的函数表，发现等价关系。（图4）

![1556427958624](/home/k/Pictures/操作系统/readelf.png)



### printf的调用轨迹

我们知道了对于一个字符串+‘\n’的printf调用是被转化称puts函数，而且我们知道了puts函数的实现代码是在库文件libc.a内的，还知道它是以二进制的形式存储在文件ioputs.o内的。

那么我们到底怎么样才能知道printf函数是如何一步步执行，最终使用Linux的int 0x80软中断进行陷入内核？

这就又回到了我们最开始的gdb追踪了。

那么我们再来一次。

* 在main函数内下断点 `break main`

* 然后调试执行 `run`

* 接着不断用stepi指令执行代码  `stepi`

* 直到看到hello world输出为止

  （图5）

  ![1556431984251](/home/k/Pictures/操作系统/gdb.png)

  果真能验证上述printf的背后。

  一层层跳转中，其中追踪到了puts（图6）

  ![1556432144533](/home/k/Pictures/操作系统/puts.png)

  下来就是很多系统调用（图7）

  ![1556432729492](/home/k/Pictures/操作系统/IO_write.png)

  我们可以从中分析出肯定是经过了系统调用函数write的调用。

但是我stepi很久也没有没有看到 "hello world"的输出

所以在本来要找到“hello world”后执行`disassemble`反汇编是无意义的

找不到相应指令的位置。

最后回调一下函数调用关系`backtrace`（图8）

![1556433075624](/home/k/Pictures/操作系统/backtrace.png)

本身应该是回调到main的，但是它并没有达到我们的预期。

但是也可以从中验证出确实是执行了系统调用函数write的。

### 接下来我们分析glbc的源代码实现轨迹

* **puts** **调用 _IO_new_file_xsputn**

  具体的符号转化关系为：_IO_puts => _IO_sputn => _IO_XSPUTN => __xsputn => _IO_file_xsputn => _IO_new_file_xsputn

* **_IO_new_file_xsputn** **调用 _IO_new_file_overflow**

  具体的符号转化关系为：_IO_new_file_xsputn => _IO_OVERFLOW => __overflow => _IO_new_file_overflow

* **_IO_new_file_overflow** **调用 _IO_new_do_write**

  具体的符号转化关系为：_IO_new_file_overflow =>_IO_do_write =>_IO_new_do_write

* **. _IO_new_do_write** **调用 new_do_write**

  具体的符号转化关系为：_IO_new_do_write => new_do_write

* **new_do_write****调用 _IO_new_file_write**

  具体的符号转化关系为：new_do_write =>_IO_SYSWRITE => __write() => write() => _IO_new_file_write

* **_IO_new_file_write ** **调用 write_nocancel**

  具体的符号转化关系为：_IO_new_file_write=>write_not_cancel => write_nocancel

* **_IO_new_file_write**  **调用 write_nocancel**

  具体的符号转化关系为：_IO_new_file_write=>write_not_cancel => write_nocancel

*  **write_nocancel** **调用 linux-gate.so::__kernel_vsyscall**

  具体的符号转化关系为：write_nocancel => INLINE_SYSCALL  => INTERNAL_SYSCALL =>__kernel_vsyscall

  注意 linux-gate.so在磁盘上并不存在，它是内核镜像中的特定页，由内核编译生成。

  

### 总结

本文从通过编写一个简单的printf代码写起，通过gdb进行调试追踪，再通过执行printf背后的预处理、编译、汇编、链接来一步步推演，再通过分析printf的源码，最终找到了printf函数的调用轨迹，通过这次追踪，我对printf有了新的认识。





<https://www.cnblogs.com/fanzhidongyzby/p/3519838.html>！！！！！！！！！！！！

<https://www.cnblogs.com/XiaoHDeBlog/p/3232367.html>

<https://www.cnblogs.com/fanzhidongyzby/p/3519838.html>

