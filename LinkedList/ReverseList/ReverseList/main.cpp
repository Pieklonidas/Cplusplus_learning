#include <iostream>
#include <string>

class Node {
  public:
    std::string val;
    Node* next;

    Node(std::string initialVal) {
      val = initialVal;
      next = nullptr;
    }
};

void printLinkedList(Node* head)
{
    if(!head) return;
    std::cout << head->val << "->";
    printLinkedList(head->next);
}

//Node* reverseList(Node* head) {
//    Node* prev = nullptr;
//    Node* current = head;
//    while(current)
//    {
//        Node* next = current->next;
//        current->next = prev;
//        prev = current;
//        current = next;
//    }
//    return prev;
//}

Node* reverseList(Node* head, Node* prev = nullptr) {
    if(!head) return prev;
    Node* next = head->next;
    head->next = prev;
    return reverseList(next, head);
}

void test_00()
{
    Node a("a");
    Node b("b");
    Node c("c");
    Node d("d");
    Node e("e");
    Node f("f");

    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = &f;

    printLinkedList(reverseList(&a));
    std::cout << std::endl;
}

void test_01()
{
    Node x("x");
    Node y("y");

    x.next = &y;

    printLinkedList(reverseList(&x));
    std::cout << std::endl;
}

void test_02()
{
    Node p("p");

    printLinkedList(reverseList(&p));
    std::cout << std::endl;
}

int main()
{
    test_00();
    test_01();
    test_02();
    return 0;
}
