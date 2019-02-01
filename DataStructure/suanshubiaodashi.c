#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

struct OPTR

{

	char data[MAXSIZE];

	int top;

}OPTR;



struct OPRD

{

	int data[MAXSIZE];

	int top;

}OPRD;



//将算数表达式转化为后缀表达式

void postfix_exp_trans(char exp[], char postfix_exp[])

{

	char ch;

	int i = 0, j = 0;

	OPTR.top = -1;

	ch = exp[i];

	i++;

	while(ch != '\0')

	{

		switch(ch)

		{

			

		case '(':    //左括号

            OPTR.top++; OPTR.data[OPTR.top]=ch;

            break;

        case ')':   //右括号

            while(OPTR.data[OPTR.top]!='(')

            {

                postfix_exp[j]=OPTR.data[OPTR.top]; 

				j++;

                OPTR.top--;

            }

            OPTR.top--;

            break;



			case '+'://+-优先级不大于栈顶任何运算符直到‘）’

			case '-':

				while(OPTR.top != -1 && OPTR.data[OPTR.top]!='(')

				{

					postfix_exp[j] = OPTR.data[OPTR.top]; j++;

					OPTR.top--;

				}

				OPTR.top++;

				OPTR.data[OPTR.top] = ch;

				break;



			case '*': //*或/时，其优先级不大于栈顶为‘*’'/'的优先级直到）

			case '/':

		//		printf("%s\n",postfix_exp);

				while(OPTR.top != -1 && OPTR.data[OPTR.top] != '(' && (OPTR.data[OPTR.top] == '*' || OPTR.data[OPTR.top] == '/'))

				{

					postfix_exp[j] = OPTR.data[OPTR.top];

					j++;

					OPTR.top--;

				}

				OPTR.top++;

				OPTR.data[OPTR.top] = ch;

				break;

			

			case ' ':

				break;

			

			default:

			while (ch>='0' && ch<='9')

            {

                postfix_exp[j]=ch; j++;

                ch=exp[i]; i++;

            }

            i--;

            postfix_exp[j]='#'; j++;

		}

		ch = exp[i];

		i++;

	}

	while(OPTR.top != -1) //exp扫描完毕，栈不空时出栈并存放到postexp中

	{

		postfix_exp[j] = OPTR.data[OPTR.top];

		j++;

		OPTR.top--;

	}

	postfix_exp[j]='\0'; //给后缀表达式添加结束标识符*/

}





int cale_exp(char postfix_exp[])

{

	int d;

	char ch;

	int i = 0;

	OPRD.top = -1;

	ch = postfix_exp[i];

	i++;

	while(ch != '\0')

	{

		switch(ch)

		{

			case '+':

				OPRD.data[OPRD.top-1] = OPRD.data[OPRD.top]+OPRD.data[OPRD.top-1];

				OPRD.top--;

				break;

			case '-':

				OPRD.data[OPRD.top-1] = OPRD.data[OPRD.top-1]-OPRD.data[OPRD.top];

				OPRD.top--;

				break;

			case '*':

				OPRD.data[OPRD.top-1] = OPRD.data[OPRD.top]*OPRD.data[OPRD.top-1];

				OPRD.top--;

				break;

			case '/':

				if(OPRD.data[OPRD.top]!=0)

					OPRD.data[OPRD.top-1] = OPRD.data[OPRD.top-1]/OPRD.data[OPRD.top];

				else

				{

					printf("\t\t不能除零！\n");

					exit(0);

				}

				OPRD.top--;

				break;

			default:

				d = 0;

				while(ch >= '0' && ch <= '9')

				{

					d = 10*d + ch-'0';

					ch = postfix_exp[i];

					i++;

				}

				OPRD.top++;

				OPRD.data[OPRD.top] = d;

		}

		ch = postfix_exp[i];

		i++;

	}

	return OPRD.data[OPRD.top];

}

int main()

{

	char exp[100];

	char postfix_exp[100];

	scanf("%s",exp);

	postfix_exp_trans(exp, postfix_exp);

	printf("%d\n",cale_exp(postfix_exp));

	return 0;

}
