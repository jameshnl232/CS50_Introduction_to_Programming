#include <stdio.h>
#include <stdlib.h>

struct node
    {
        int number;
        struct node* next;
    };

typedef struct node node;

void print_linkedlist( node* head)
{
    //for(node* tmp = head; tmp != NULL; tmp = tmp->next)
    //{
    //    printf("%i\n", tmp->number);
    //}

    // this is nichts anderes als das hier

     node* tmp = head;
     while ( tmp != NULL)
     {
          printf("%i - ", tmp->number);
          tmp = tmp->next;
     }

}

node* make_new_node( int number)
{
    node* new_node = malloc(sizeof(node));
    if(new_node == NULL)
    return NULL;

    new_node->number = number;
    new_node->next = NULL;
    return new_node;

}

node* insert_new_node( node* head, node* n) //to the front
{
    n->next = head;
    return n;

}

node* find_value( node* head, int number)
{
    node* n = head;
    while(n != NULL)
    {
        if(n->number == number)
        return n;
        n = n->next;
    }
    return NULL;
}

void insert_node_middle(node* node_to_insert_after, node* new_node)
{
    new_node->next = node_to_insert_after->next;
    node_to_insert_after->next = new_node;
    return;
}

int main(void)
{
    //node* head = NULL;

    //node* n1 = make_new_node(34);

    //head = n1;

    //node* n2 = make_new_node(8);

    //n1->next = n2;

    //node* n3 = make_new_node(32);

    //n2->next = n3;
    node* n = NULL;
    node* head = NULL;
    for(int i = 9; i >= 0; i--)
    {
                n = make_new_node(i);  //make a new node
     //head = insert_new_node( head, n)
                n->next = head;        // link the node, by add the new node to the front of the list
                                           //that's why they are reversely printed
                head = n;              // update head, in the end head point to the last node
    }

    n = make_new_node(-1); // insert -1 to the front of the list

    n->next = head;

    head = n;

    node* m = find_value( head, 8);
    insert_node_middle(m, make_new_node(75));
    print_linkedlist(head);
    printf("\n");


    printf("found node with number: %i\n", m->number);


    return 0;
}