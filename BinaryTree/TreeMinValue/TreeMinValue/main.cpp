#include <iostream>
#include <queue>

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



//int treeMinValue(Node* root) {
//    std::queue<Node> q;
//    if(root) q.push(*root);
//    int min = 9999;

//    while (!q.empty())
//    {
//        Node current = q.front();
//        q.pop();
//        if(current.val < min) min = current.val;
//        if(current.left) q.push(*current.left);
//        if(current.right) q.push(*current.right);
//    }

//    return min;
//}

int treeMinValue(Node* root) {
    if(!root) return 9999;
    int leftVal = treeMinValue(root->left);
    int rightVal = treeMinValue(root->right);
    if(leftVal < root->val)
    {
        if(rightVal < leftVal)
        {
            return rightVal;
        }
        return leftVal;
    }
    return root->val;
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

    std::cout << treeMinValue(&a) << std::endl;
}

void test_01()
{
    Node a(5);
    Node b(11);
    Node c(3);
    Node d(4);
    Node e(14);
    Node f(12);

    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;

    std::cout << treeMinValue(&a) << std::endl;
}

void test_02()
{
    Node a(-1);
    Node b(-6);
    Node c(-5);
    Node d(-3);
    Node e(-4);
    Node f(-13);
    Node g(-2);
    Node h(-2);

    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;
    e.left = &g;
    f.right = &h;

    std::cout << treeMinValue(&a) << std::endl;
}

void test_03()
{
    Node a(42);

    std::cout << treeMinValue(&a) << std::endl;
}


int main()
{
    test_00();
    test_01();
    test_02();
    test_03();
    return 0;
}
