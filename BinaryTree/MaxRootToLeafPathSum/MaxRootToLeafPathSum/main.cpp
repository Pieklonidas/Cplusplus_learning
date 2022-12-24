#include <iostream>

class Node {
  public:
    int val;
    Node* left;
    Node* right;


    Node(int initialVal) {
      val = initialVal;
      left = nullptr;
      right = nullptr;
    }
};



int maxPathSum(Node* root) {
    if(!root) return -9999;
    if(!root->left && !root->right) return root->val;
    int leftVal = maxPathSum(root->left);
    int rightVal = maxPathSum(root->right);
    if(leftVal > rightVal)
    {
        return root->val + leftVal;
    }

    return root->val + rightVal;
}

void test_00()
{
    Node a(3);
    Node b(11);
    Node c(4);
    Node d(4);
    Node e(-2);
    Node f(1);

    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;

    std::cout << maxPathSum(&a) << std::endl;
}

void test_01()
{
    Node a(5);
    Node b(11);
    Node c(54);
    Node d(20);
    Node e(15);
    Node f(1);
    Node g(3);

    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    e.left = &f;
    e.right = &g;

    std::cout << maxPathSum(&a) << std::endl;
}

void test_02()
{
    Node a(-1);
    Node b(-6);
    Node c(-5);
    Node d(-3);
    Node e(0);
    Node f(-13);
    Node g(-1);
    Node h(-2);

    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;
    e.left = &g;
    f.right = &h;

    std::cout << maxPathSum(&a) << std::endl;
}

void test_03()
{
    Node a(42);

    std::cout << maxPathSum(&a) << std::endl;
}


int main()
{
    test_00();
    test_01();
    test_02();
    test_03();
    return 0;
}
