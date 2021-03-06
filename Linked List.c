#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
if (!((p) = malloc(s))) {\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

typedef struct list * listPointer;
typedef struct list {
    int data;
    listPointer link;
} listNode;

listPointer createList();
listPointer createNode(int data, listPointer link);
void printList(listPointer h);
int insertNode(listPointer *head, listPointer node, int pos);
int insertList(listPointer *head1, listPointer head2, int pos);

int main(void)
{
    listPointer head1, head2;

    head1 = createNode(10, createNode(20, createNode(30, NULL)));
    head2 = createNode(1, createNode(2, createNode(3, NULL)));

    if (insertList(&head1, head2, 0) == -1) {
        fprintf(stderr, "Fail to insert.\n");
        exit(-1);
    }

    printList(head1);

}

listPointer createList()
{
    listPointer l1, l2;

    MALLOC(l1, sizeof(*l1));
    MALLOC(l2, sizeof(*l2));

    l1->data = 10;
    l2->data = 20;

    l1->link = l2;
    l2->link = NULL;

    return l1;
}

listPointer createNode(int data, listPointer link)
{
    listPointer ptr;

    MALLOC(ptr, sizeof(*ptr));
    ptr->data = data;
    ptr->link = link;

    return ptr;
}

void printList(listPointer h)
{
    while (h) {
        printf("%d->", h->data);
        h = h->link;
    }
    
}


int insertNode(listPointer *head, listPointer node, int pos)
{
    int i = 0;
    listPointer p;

    if (!pos) {
        node->link = *head;
        *head = node;

        return 0;
    } else {
        for (p = *head; p && i < pos - 1; p = p->link, i ++);

        if (!p) return -1;

        node->link = p->link;
        p->link = node;
        return 0;
    }
}
int insertList(listPointer *head1, listPointer head2, int pos)
{
    int i = 0;
    listPointer p, q;

    if (!pos) {
        for (p = head2; p->link; p = p->link);

        p->link = *head1;
        *head1 = head2;

        return 0;
    } else {
        for (p = *head1; p && i < pos - 1; p = p->link, i ++);
        if (!p) return -1;
        for (q = head2; q->link; q = q->link); 

        q->link = p->link;
        p->link = head2;
        return 0;
    }
}
