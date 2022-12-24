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

//Node* zipperLists(Node* head1, Node* head2) {
//  Node* current1 = head1;
//  Node* current2 = head2;
//  while (current1 && current2)
//  {
//      Node* next1 = current1->next;
//      Node* next2 = current2->next;
//      current1->next = current2;
//      current1 = next1;
//      if(current1) current2->next = current1;
//      current2 = next2;
//  }
//  return head1;
//}

//Node* zipperLists(Node* head1, Node* head2) {
//    if(!head1 || !head2) return nullptr;
//    Node* next1 = head1->next;
//    Node* next2 = head2->next;
//    head1->next = head2;
//    if(next1) head2->next = next1;
//    zipperLists(next1, next2);
//    return head1;
//}

Node* zipperLists(Node* head1, Node* head2) {
    if(!head1 && !head2) return nullptr;
    if(!head1) return head2;
    if(!head2) return head1;
    Node* next1 = head1->next;
    Node* next2 = head2->next;
    head1->next = head2;
    head2->next = zipperLists(next1, next2);
    return head1;
}

void test_00()
{
    Node a("a");
    Node b("b");
    Node c("c");
    a.next = &b;
    b.next = &c;

    //-----------------------------------

    Node x("x");
    Node y("y");
    Node z("z");
    x.next = &y;
    y.next = &z;

    printLinkedList(zipperLists(&a, &x));
    std::cout << std::endl;
}

void test_01()
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

    //-------------------------------------

    Node x("x");
    Node y("y");
    Node z("z");
    x.next = &y;
    y.next = &z;

    printLinkedList(zipperLists(&a, &x));
    std::cout << std::endl;
}

void test_02()
{
    Node s("s");
    Node t("t");
    s.next = &t;

    //------------------------------------

    Node one("1");
    Node two("2");
    Node three("3");
    Node four("4");
    one.next = &two;
    two.next = &three;
    three.next = &four;

    printLinkedList(zipperLists(&s, &one));
    std::cout << std::endl;
}

void test_03()
{
    Node w("w");

    //------------------------------------

    Node one("1");
    Node two("2");
    Node three("3");
    one.next = &two;
    two.next = &three;

    printLinkedList(zipperLists(&w, &one));
    std::cout << std::endl;
}

void test_04()
{
    Node one("1");
    Node two("2");
    Node three("3");
    one.next = &two;
    two.next = &three;

    //------------------------------------

    Node w("w");

    printLinkedList(zipperLists(&one, &w));
    std::cout << std::endl;
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
