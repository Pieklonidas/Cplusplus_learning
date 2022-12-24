#include <iostream>
#include <vector>
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



//std::vector<std::string> linkedListValues(Node* head) {
//    std::vector<std::string> answer;
//    Node* current = head;
//    while (current)
//    {
//        answer.push_back(current->val);
//        current = current->next;
//    }
//    return answer;
//}

std::vector<std::string> linkedListValues(Node* head) {
    if(!head) return {};
    std::vector<std::string> answer;
    answer.push_back(head->val);
    std::vector<std::string> temp = linkedListValues(head->next);
    answer.insert(answer.end(), temp.begin(), temp.end());
    return answer;
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

    std::vector<std::string> answer = linkedListValues(&a);

    for(const auto& node : answer)
    {
        std::cout << node << " -> ";
    }
    std::cout << std::endl;
}

void test_01()
{
    Node x("x");
    Node y("y");

    x.next = &y;


    std::vector<std::string> answer = linkedListValues(&x);

    for(const auto& node : answer)
    {
        std::cout << node << " -> ";
    }
    std::cout << std::endl;
}

void test_02()
{
    Node q("q");

    std::vector<std::string> answer = linkedListValues(&q);

    for(const auto& node : answer)
    {
        std::cout << node << " -> ";
    }
    std::cout << std::endl;
}

void test_03()
{
    std::vector<std::string> answer = linkedListValues(nullptr);

    for(const auto& node : answer)
    {
        std::cout << node << " -> ";
    }
    std::cout << std::endl;
}

int main()
{
    test_00();
    test_01();
    test_02();
    test_03();
    return 0;
}
