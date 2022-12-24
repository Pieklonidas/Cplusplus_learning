#include <iostream>
#include <string>
#include <vector>
#include <queue>

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

std::vector<std::string> breadthFirstValues(Node* root) {
    std::queue<Node> q;
    std::vector<std::string> answer;
    if(root) q.push(*root);

    while (!q.empty())
    {
        Node current = q.front();
        q.pop();
        answer.push_back(current.val);
        if(current.left) q.push(*current.left);
        if(current.right) q.push(*current.right);
    }
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

    std::vector<std::string> answer = breadthFirstValues(&a);

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
    Node h("h");

    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;
    e.left = &g;
    f.right = &h;

    std::vector<std::string> answer = breadthFirstValues(&a);

    for(const auto& node : answer)
    {
        std::cout << node << " ";
    }
    std::cout << std::endl;
}

void test_02()
{
    Node a("a");

    std::vector<std::string> answer = breadthFirstValues(&a);

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
    Node x("x");

    a.right = &b;
    b.left = &c;
    c.left = &x;
    c.right = &d;
    d.right = &e;

    std::vector<std::string> answer = breadthFirstValues(&a);

    for(const auto& node : answer)
    {
        std::cout << node << " ";
    }
    std::cout << std::endl;
}

void test_04()
{
    std::vector<std::string> answer = breadthFirstValues(nullptr);
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
