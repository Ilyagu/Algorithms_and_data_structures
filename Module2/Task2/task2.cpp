// Copyright 2021 Ilyagu Nagdimaev

#include <iostream>
#include <stack>
#include <vector>

template <class T>
class IsLess {
 public:
  bool operator()(const T& lhs, const T& rhs) { return lhs < rhs; }
};

template <class T, class Comparator = IsLess<T>>
class BinTree {
 public:
  BinTree() : root(nullptr) {}
  explicit BinTree(Comparator _comp) : root(nullptr), comp(IsLess<T>()) {}
  ~BinTree();
  void Add(const T& key);
  void PostOrder(void visit(T));
  bool Equal();

 private:
  struct Node {
    Node() : left(nullptr), right(nullptr), key(NULL) {}
    explicit Node(T _key) : left(nullptr), right(nullptr), key(_key) {}
    Node* left;
    Node* right;
    T key;
  };
  Node* root;
  Comparator comp;
};

template <class T, class Comparator>
BinTree<T, Comparator>::~BinTree() {
  std::stack<Node*> stack1;
  std::stack<Node*> stack2;
  stack1.push(root);
  while (!stack1.empty()) {
    Node* node = stack1.top();
    stack2.push(node);
    stack1.pop();
    if (node->left) {
      stack1.push(node->left);
    }
    if (node->right) {
      stack1.push(node->right);
    }
  }
  while (!stack2.empty()) {
    Node* node = stack2.top();
    delete node;
    stack2.pop();
  }
}

template <class T, class Comparator>
void BinTree<T, Comparator>::Add(const T& key) {
  if (root == nullptr) {
    root = new Node(key);
    return;
  }
  Node* node = root;
  Node* prev = root;
  while (node != nullptr) {
    prev = node;
    if (comp(node->key, key)) {
      node = prev->right;
    } else {
      node = prev->left;
    }
  }
  node = new Node(key);
  if (comp(prev->key, key)) {
    prev->right = node;
  } else {
    prev->left = node;
  }
}

template <class T, class Comparator>
bool BinTree<T, Comparator>::Equal() {
  if (root == nullptr) return false;

  std::stack<Node*> stack1; 
  std::stack<Node*> stack2;
  stack1.push(root);
  while (!stack1.empty()) {
    Node* node = stack1.top();
    stack2.push(node);
    stack1.pop();
    if (node->left) {
      stack1.push(node->left);
    }
    if (node->right) {
      stack1.push(node->right);
    }
  }
  while (!stack2.empty()) {
    Node* node = stack2.top();
    // visit(node->key);
    if (node->key == root->key) return false;
    stack2.pop();
  }
  return true;
}

template <class T, class Comparator>
void BinTree<T, Comparator>::PostOrder(void visit(T)) {
  if (root == nullptr) return;

  std::stack<Node*> stack1;
  std::stack<Node*> stack2;
  stack1.push(root);
  while (!stack1.empty()) {
    Node* node = stack1.top();
    stack2.push(node);
    stack1.pop();
    if (node->left) {
      stack1.push(node->left);
    }
    if (node->right) {
      stack1.push(node->right);
    }
  }
  while (!stack2.empty()) {
    Node* node = stack2.top();
    visit(node->key);
    stack2.pop();
  }
}

int main() {
  BinTree<int, IsLess<int>> tree;
  size_t n = 0;
  std::cin >> n;
  for (size_t i = 0; i < n; ++i) {
    int elem = 0;
    std::cin >> elem;
    tree.Add(elem);
  }
  tree.PostOrder([](int val) { std::cout << val << ' '; });
  std::cout << tree.Equal() << std::endl;
  return 0;
}
