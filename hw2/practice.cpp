#include <iostream>

using namespace std;
struct Node {
    Node(int v, Node* n) { value = v; next = n; }
    int value;
    Node *next;
};

Node* funcB(Node* in) {
    if (!in) 
    {
        return NULL;
    }

    Node *p = funcB(in->next);
    if (p) 
    {
        p->next = in;
    }
    return in;
}

Node* funcA(Node* in) {
    if (!in) 
        {
            return NULL;
        } 

    Node *r = in;

    while (r->next) 
        {
            r = r->next;
        }
    Node *l = funcB(in);
    l->next = NULL;
    return r;
}

void printAll (Node* result)
{
    Node* temp = result;
    while (temp!=NULL)
    {
        cout << temp->value << endl;
        temp = temp->next;
    }
}

int main()
{
    Node* head = new Node(1, new Node(2, new Node(3, new Node(4, 
        new Node(5, NULL)))));

    Node* result = funcA(head);
    printAll(result);

    return 0;
}