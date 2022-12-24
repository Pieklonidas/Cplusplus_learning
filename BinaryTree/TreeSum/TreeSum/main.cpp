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



//int treeSum(Node* root) {
//    int sum = 0;
//    if(!root) return sum;
//    std::queue<Node> q;
//    q.push(*root);

//    while (!q.empty())
//    {
//        Node current = q.front();
//        q.pop();
//        sum += current.val;
//        if(current.left) q.push(*current.left);
//        if(current.right) q.push(*current.right);
//    }
//    return sum;
//}

int treeSum(Node* root) {
    if(!root) return 0;
    return root->val + treeSum(root->left) + treeSum(root->right);
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

    std::cout << treeSum(&a) << std::endl;
}

void test_01()
{
    Node a(1);
    Node b(6);
    Node c(0);
    Node d(3);
    Node e(-6);
    Node f(2);
    Node g(2);
    Node h(2);

    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;
    e.left = &g;
    f.right = &h;

    std::cout << treeSum(&a) << std::endl;
}

void test_02()
{
    std::cout << treeSum(nullptr) << std::endl;
}


int main()
{
    test_00();
    test_01();
    test_02();
    return 0;
}
