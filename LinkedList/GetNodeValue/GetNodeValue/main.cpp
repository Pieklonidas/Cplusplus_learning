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

std::string getNodeValue(Node* head, int idx) {
    Node* current = head;
    while (current)
    {
        if(idx == 0) return current->val;
        current = current->next;
        idx--;
    }
    return "";
}

//std::string getNodeValue(Node* head, int idx) {
//    if(!head) return "";
//    if(idx == 0) return head->val;
//    return getNodeValue(head->next, idx-1);
//}

void test_00()
{
    Node a("a");
    Node b("b");
    Node c("c");
    Node d("d");

    a.next = &b;
    b.next = &c;
    c.next = &d;

    std::cout << getNodeValue(&a, 2) << std::endl;
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

    std::cout << getNodeValue(&a, 3) << std::endl;
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

    std::cout << getNodeValue(&a, 7) << std::endl;
}

void test_03()
{
    Node node1("banana");
    Node node2("mango");

    node1.next = &node2;

    std::cout << getNodeValue(&node1, 0) << std::endl;
}

void test_04()
{
    Node node1("banana");
    Node node2("mango");

    node1.next = &node2;

    std::cout << getNodeValue(&node1, 1) << std::endl;
}

int main()
{
    test_00();
    test_01();
    test_02();
    test_03();
    test_04();
    return 0;
}
