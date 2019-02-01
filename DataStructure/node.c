#include <stdio.h>
#include<stdlib.h>
typedef struct node 

{

    int data;

    struct node *next;

}LNode,*Linklist;

//2. 创建单链表

Linklist creat_link()

{

    Linklist Head;

    Linklist r;

    LNode *s;

    Head = (Linklist)malloc(sizeof(LNode));

    Head->next = NULL;

    r = Head;

    int x;

    scanf("%d",&x);

    while(x!= -1)

    {

        s = (Linklist)malloc(sizeof(LNode));

        s->data = x;

        r->next = s;

        r = s;

        scanf("%d",&x);

    }

    r->next = NULL;

    return Head;

}



//3.拆分单链表

void apart_link(Linklist Head)

{

    Linklist r,q,s;

    int flag;



    r = Head;

    q = Head->next;

    flag = q->data;

//printf("%d\n",flag);

    while(q->next != NULL)

    {

     //   printf("1q为:%d",q->data);

        if(q->next->data < flag)

        {

            s = q->next;

            q->next = q->next->next;

            s->next = r->next;

            r->next = s; 

      //      printf("q为 %d q->next为 %d \n",q->data,q->next->data);

        }

        else

            q = q->next;

    }

  //  printf("\n拆分后为: ");

    while(r->next != NULL)

    {

        printf(" %d ",r->next->data);

        r = r->next;

    }

    printf("\n");

}



int main()

{

    Linklist Head;

    Head = creat_link();

    apart_link(Head);

}
