#include <iostream>

class Node
{
public:
    Node* next;
    char val;

    Node(char val)
    {
        this->val = val;
        this->next = nullptr;
    }
};

//void printLinkedList(Node* head)
//{
//    Node* current = head;
//    while (current) {
//        std::cout << current->val << std::endl;
//        current = current->next;
//    }
//}

void printLinkedList(Node* head)
{
    if(!head) return;
    std::cout << head->val << std::endl;
    printLinkedList(head->next);
}

int main()
{
    Node a('A');
    Node b('B');
    Node c('C');
    Node d('D');

    a.next = &b;
    b.next = &c;
    c.next = &d;

    printLinkedList(&a);

    return 0;
}
