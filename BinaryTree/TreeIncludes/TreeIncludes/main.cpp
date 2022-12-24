#include <iostream>
#include <string>
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

//bool treeIncludes(Node* root, std::string targetVal) {
//    if(root && root->val == targetVal) return true;
//    if(!root) return false;
//    if((treeIncludes(root->left, targetVal) || treeIncludes(root->right, targetVal)))
//    {
//        return true;
//    }
//    return false;
//}

bool treeIncludes(Node* root, std::string targetVal) {
    std::queue<Node> q;
    if(root) q.push(*root);
    while (!q.empty())
    {
        Node current = q.front();
        q.pop();
        if(current.val == targetVal)
        {
            return true;
        }
        if(current.left) q.push(*current.left);
        if(current.right) q.push(*current.right);
    }
    return false;
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

    if(treeIncludes(&a, "e"))
    {
        std::cout << "True" << std::endl;
    }
    else
    {
        std::cout << "False" << std::endl;
    }
}

void test_01()
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

    if(treeIncludes(&a, "a"))
    {
        std::cout << "True" << std::endl;
    }
    else
    {
        std::cout << "False" << std::endl;
    }
}

void test_02()
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

    if(treeIncludes(&a, "n"))
    {
        std::cout << "True" << std::endl;
    }
    else
    {
        std::cout << "False" << std::endl;
    }
}

void test_03()
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

    if(treeIncludes(&a, "f"))
    {
        std::cout << "True" << std::endl;
    }
    else
    {
        std::cout << "False" << std::endl;
    }
}

void test_04()
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

    if(treeIncludes(&a, "p"))
    {
        std::cout << "True" << std::endl;
    }
    else
    {
        std::cout << "False" << std::endl;
    }

}

void test_05()
{
    if(treeIncludes(nullptr, "b"))
    {
        std::cout << "True" << std::endl;
    }
    else
    {
        std::cout << "False" << std::endl;
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
