#include<stdio.h>
#include<stdlib.h>
typedef struct node

{

    float p; //系数

    int e; //指数

    struct node *next;

}*Linklist,Lnode;

 

Linklist create_link()

{

    int n;

    scanf("%d",&n);

    Linklist head,r;

    Lnode *s;

   

    head=(Linklist)malloc(sizeof(Lnode));

    r = head;

 

  getchar();

    while(n--)

    {

        s=(Linklist)malloc(sizeof(Lnode));

        scanf("(%f,%d)",&s->p,&s->e);

        r->next = s;

        r = s;   

    }

    r->next = NULL;

    return head;

}

 

void print_link(Linklist head)

{

    Linklist q;

    int flag=1;

    q = head->next;

 

    if(!q)

    {

        putchar('0');

        printf("\n");

        return;

    }

    while(q)

    {

        if(q->p>0 && flag != 1)

            putchar('+');

        if(q->p != 1 && q->p != -1)

        {

            printf("%g",q->p);

            if(q->e == 1)

                printf("X");

            else if(q->e) //过滤掉0

                printf("X^%d",q->e);

        }

        else

        {

            if(q->p == 1)

            {

                if(!q->e)

                    putchar('1');

                else if(q->e == 1)

                    putchar('X');

                else

                    printf("X^%d",q->e);              

            }

        }

            q =q ->next;

            flag++;

 

    }

    printf("\n");

}

//2.首先两个一元多项式的加法：从头起扫描两个链表，并创建一个新链表，因为相加的两个链表都是已按顺序排列好的线性表，所以用指针扫描若指数谁小谁加到新链表中，若指数相同进行系数运算后加到新链表中。



Linklist add_link(Linklist head_1, Linklist head_2)

{

    Linklist qa = head_1->next;

    Linklist qb = head_2->next;

    Linklist head_3,pc;

    Lnode *qc;

     

    head_3 = (Linklist)malloc(sizeof(Lnode));

    head_3->next = NULL;

    pc = head_3;

 

    while(qa!=NULL && qb!=NULL)/*当两个多项式均未扫描到结束时*/

    {

        qc = (Linklist)malloc(sizeof(Lnode));

        if(qa->e <qb->e)

        {

            qc->p = qa->p;

            qc->e = qa->e;

            qa = qa->next;

        }

        else if(qa->e == qb->e)

        {

            qc->p = qa->p+qb->p;

            qc->e = qa->e;

            qa = qa->next;

            qb = qb->next;

 

        }

        else

        {

            qc->p = qb->p;

            qc->e = qb->e;

            qb = qb->next;

        }

 

        if(qc->p !=0 )

        {

            qc->next = pc->next;

            pc->next = qc;

            pc = qc;

        }

        else

            free(qc);

    }

    while(qa != NULL)

    {

        qc = (Linklist)malloc(sizeof(Lnode));

        qc->p = qa->p;

        qc->e = qa->e;

        qa = qa->next;

        qc->next =  pc->next;

        pc->next = qc;

        pc = qc;

    }

        while(qb != NULL)

    {

        qc = (Linklist)malloc(sizeof(Lnode));

        qc->p = qb->p;

        qc->e = qb->e;

        qb = qb->next;

        qc->next =  pc->next;

        pc->next = qc;

        pc = qc;

    }

    return head_3;

 

 

}

//3.减法运算同加法运算原理

Linklist derivative_link(Linklist head_1)

{

    Linklist pc = head_1;

    Linklist dc;

    while(pc->next!=NULL)

    {

         

        if(pc->next->e == 0)

        {

            dc = pc->next;

            pc->next = dc->next;

            free(dc);

        }

         if(pc->next->p == 0)

        {

            dc = pc->next;

            pc->next = dc->next;

            free(dc);

        }

         if(pc->next->e == 1)

        {

            pc->next->e = 0;

            pc = pc->next;

        }

        else

        {

            pc->next->p *= pc->next->e;

            pc->next->e = pc->next->e - 1;

            pc = pc->next;

        }

    }

    return head_1;

}

void print_link(Linklist head)

{

    Linklist q;

    int flag=1;

    q = head->next;

 

    if(!q)

    {

        putchar('0');

        printf("\n");

        return;

    }

    while(q)

    {

        if(q->p>0 && flag != 1)

            putchar('+');

        if(q->p != 1 && q->p != -1)

        {

            printf("%g",q->p);

            if(q->e == 1)

                printf("X");

            else if(q->e) //过滤掉0

                printf("X^%d",q->e);

        }

        else

        {

            if(q->p == 1)

            {

                if(!q->e)

                    putchar('1');

                else if(q->e == 1)

                    putchar('X');

                else

                    printf("X^%d",q->e);              

            }

        }

            q =q ->next;

            flag++;

 

    }

    printf("\n");

}



//4.乘法运算同加法运算原理

 Lnode *mult_link(Lnode *head_1, Lnode *head_2)

{  

   Lnode *p1,*p2,*p3,*s,*r,*p4,*p5;

       

   int flag=0; 

   p1=head_1->next;

   p2=head_2->next; 

       

   p3=(Lnode*)malloc(sizeof(Lnode));

   p3->next=NULL;

       

   p4=(Lnode*)malloc(sizeof(Lnode));

   p4->next=NULL;

   r=p3;

       

   while(p2!=NULL)

   {

    while(p1!=NULL)

    {

    s=(Lnode*)malloc(sizeof(Lnode));    

    s->p=p1->p*p2->p;

    s->e=p1->e+p2->e;

    r->next=s;

    r=s;

    p1=p1->next;

    flag++;

    }

    r->next=NULL; 

    p2=p2->next;

    p4=p3;

    p1=head_1->next;

   }

   return  p4;

}

    

Lnode *add_link(Lnode *Head)

{

    Lnode *r,*q,*p,*Q;

    int t;

    for(q=Head->next;q->next !=NULL;q=q->next)

    {

        for(p=q->next,r=q;p->next !=NULL;)

        {

            if(q->e==p->e)

        { 

            q->p=q->p+p->p;

            r->next=p->next;

            Q=p;

            p=p->next;

            free(Q);

        }

        else

        {

            r=r->next;

            p=p->next;

        }

        if(q->e > q->next ->e )

        {

            t=q->p ;q->p =q->next ->p ;q->next ->p =t;

            t=q->e ;q->e =q->next ->e ;q->next->e =t;

        }

        }

           

    }

    return Head;

}

//5.除法运算同加法运算原理

 Linklist evaluate_link(Linklist head_1)

{

    int sum = 0;

    int ex = 1;

    int t;

    int n;

    Linklist pc = head_1->next;

 

    scanf("%d",&n);

    while(pc!=NULL)

    {

        ex = 1;

        t = pc->e;

        while(t !=0 )

        {

            ex *= n;

            t--;

        }

        if(pc->e == 0)

            sum += pc->p;

        else

            sum += pc->p*ex;

        pc = pc->next;

 

    }

    printf("%d\n",sum);

}

//6.求导运算遍历链表，除去几个特殊情况如指数或系数为0直接删除该节点，其余新系数等于指数乘系数，再将指数减一。



Linklist derivative_link(Linklist head_1)

{

    Linklist pc = head_1;

    Linklist dc;

    while(pc->next!=NULL)

    {

        

        if(pc->next->e == 0)

        {

            dc = pc->next;

            pc->next = dc->next;

            free(dc);

        }

         if(pc->next->p == 0)

        {

            dc = pc->next;

            pc->next = dc->next;

            free(dc);

        }

         if(pc->next->e == 1)

        {

            pc->next->e = 0;

            pc = pc->next;

        }

        else

        {

            pc->next->p *= pc->next->e;

            pc->next->e = pc->next->e - 1;

            pc = pc->next;

        }

    }

    return head_1;

}

int main()
{
	linklist A, B, C;
	A = create_link();
	B = create_link();
	C = add_link(A,B);
    print_link(C);
    C = derivative_link(A,B);
    print_link(C);
    C = mult_link();
    print_link(C);
    C = evaluate_link(A,B);
    print_link(C);
    
}
