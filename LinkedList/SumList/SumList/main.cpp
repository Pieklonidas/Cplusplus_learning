#include <iostream>

class Node {
  public:
    int val;
    Node* next;

    Node(int initialVal) {
      val = initialVal;
      next = nullptr;
    }
};



//int sumList(Node* head) {
//    int answer = 0;
//    Node* current = head;
//    while (current)
//    {
//        answer += current->val;
//        current = current->next;
//    }
//    return answer;
//}

int sumList(Node* head) {
    if(!head) return 0;
    return head->val + sumList(head->next);
}

void test_00()
{
    Node a(2);
    Node b(8);
    Node c(3);
    Node d(-1);
    Node e(7);

    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;

    std::cout << sumList(&a) << std::endl;
}

void test_01()
{
    Node x(38);
    Node y(4);

    x.next = &y;

    std::cout << sumList(&x) << std::endl;
}

void test_02()
{
    Node z(100);

    std::cout << sumList(&z) << std::endl;
}

void test_03()
{
    std::cout << sumList(nullptr) << std::endl;
}


int main()
{
    test_00();
    test_01();
    test_02();
    test_03();
    return 0;
}
