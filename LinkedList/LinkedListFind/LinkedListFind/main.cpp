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



//bool linkedListFind(Node* head, std::string target) {
//    Node* current = head;
//    while (current)
//    {
//        if(current->val == target) return true;
//        current = current->next;
//    }
//    return false;
//}

bool linkedListFind(Node* head, std::string target) {
    if(!head) return false;
    if(head->val == target) return true;
    return linkedListFind(head->next, target);
}

void test_00()
{
    Node a("a");
    Node b("b");
    Node c("c");
    Node d("d");

    a.next = &b;
    b.next = &c;
    c.next = &d;

    if(linkedListFind(&a, "c"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }
}

void test_01()
{
    Node a("a");
    Node b("b");
    Node c("c");
    Node d("d");

    a.next = &b;
    b.next = &c;
    c.next = &d;

    if(linkedListFind(&a, "d"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }
}

void test_02()
{
    Node a("a");
    Node b("b");
    Node c("c");
    Node d("d");

    a.next = &b;
    b.next = &c;
    c.next = &d;

    if(linkedListFind(&a, "q"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }
}

void test_03()
{
    Node node1("jason");
    Node node2("leneli");

    node1.next = &node2;

    if(linkedListFind(&node1, "jason"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }
}

void test_04()
{
    Node node1("potato");

    if(linkedListFind(&node1, "potato"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }
}

void test_05()
{
    Node node1("potato");

    if(linkedListFind(&node1, "apple"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }
}

int main()
{
    test_00();
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    return 0;
}
