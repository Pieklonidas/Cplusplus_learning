#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

class Node {
  public:
    std::string val;
    Node* left;
    Node* right;


    Node(std::string initialVal) {
      val = initialVal;
      left = nullptr;
      right = nullptr;
    }
};

//std::vector<std::string> depthFirstValues(Node* root) {
//    std::stack<Node> sta;
//    std::vector<std::string> answer;
//    if(root) sta.push(*root);
//    while (!sta.empty())
//    {
//        Node top = sta.top();
//        answer.push_back(top.val);
//        sta.pop();
//        if(top.right) sta.push(*top.right);
//        if(top.left) sta.push(*top.left);
//    }


//    return answer;
//}

std::vector<std::string> depthFirstValues(Node* root) {
    if(root == nullptr) return {};
    std::vector<std::string> leftValues = depthFirstValues(root->left);
    std::vector<std::string> rightValues = depthFirstValues(root-> right);
    std::vector<std::string> answer = {root->val};
    answer.insert(answer.end(), leftValues.begin(), leftValues.end());
    answer.insert(answer.end(), rightValues.begin(), rightValues.end());
    return answer;
}

void test_00()
{
    Node a("a");
    Node b("b");
    Node c("c");
    Node d("d");
    Node e("e");
    Node f("f");

    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;

    std::vector<std::string> answer = depthFirstValues(&a);

    for(const auto& node : answer)
    {
        std::cout << node << " ";
    }
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
    Node g("g");

    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;
    e.left = &g;

    std::vector<std::string> answer = depthFirstValues(&a);

    for(const auto& node : answer)
    {
        std::cout << node << " ";
    }
    std::cout << std::endl;
}

void test_02()
{
    Node a("a");

    std::vector<std::string> answer = depthFirstValues(&a);

    for(const auto& node : answer)
    {
        std::cout << node << " ";
    }
    std::cout << std::endl;
}

void test_03()
{
    Node a("a");
    Node b("b");
    Node c("c");
    Node d("d");
    Node e("e");

    a.right = &b;
    b.left = &c;
    c.right = &d;
    d.right = &e;

    std::vector<std::string> answer = depthFirstValues(&a);

    for(const auto& node : answer)
    {
        std::cout << node << " ";
    }
    std::cout << std::endl;
}

void test_04()
{
    std::vector<std::string> answer = depthFirstValues(nullptr);
    std::cout << "Test_04:" << std::endl;
    for(const auto& node : answer)
    {
        std::cout << node << " ";
    }
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
