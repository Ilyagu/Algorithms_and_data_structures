// Copyright 2021 Ilyagu Nagdimaev

#include <iostream>
#include <memory>
#include <queue>
#include <stack>

template <typename T>
class IsLess{
 public:
    bool operator()(const T &l, const T &r) const {
        return l < r;
    }
};

template <typename Value, typename Comparator = IsLess<Value>>
class BinaryTree {
    struct Node {
        Node() = default;
        explicit Node(Value value) : _value(value) {}

        std::shared_ptr<Node> _left = nullptr;
        std::shared_ptr<Node> _right = nullptr;
        Value _value;
    };

 public:
    BinaryTree() = default;

    void insert(Value value) {
        if (_root == nullptr) {
            _root = std::make_shared<Node>(value);
            return;
        }

        std::shared_ptr<Node> cur_node = _root;
        std::shared_ptr<Node> parent;
        bool right_or_left = false;
        while (cur_node != nullptr) {
            if (_comp(value, cur_node->_value)) {
                parent = cur_node;
                cur_node = cur_node->_left;
                right_or_left = false;
            } else {
                parent = cur_node;
                cur_node = cur_node->_right;
                right_or_left = true;
            }
        }
        cur_node = std::make_shared<Node>(value);
        if (right_or_left)
            parent->_right = cur_node;
        else
            parent->_left = cur_node;
    }

    [[nodiscard]] int max_width() const {
        int max_width = 0;
        std::queue<std::shared_ptr<Node>> layer;

        layer.push(_root);
        while (!layer.empty()) {
            int cur_width = layer.size();
            if (cur_width > max_width)
                max_width = cur_width;

            for (size_t i = 0; i != cur_width; ++i) {
                std::shared_ptr<Node> tmp_node = layer.front();
                layer.pop();
                if (tmp_node->_left)
                    layer.push(tmp_node->_left);
                if (tmp_node->_right)
                    layer.push(tmp_node->_right);
            }
        }
        return max_width;
    }

    ~BinaryTree() {
        if (_root == nullptr)
            return;

        std::stack<std::shared_ptr<Node>> queue;

        queue.push(_root);
        std::shared_ptr<Node> node;

        while (!queue.empty()) {
            node = queue.top();
            queue.pop();

            if (node->_left) {
                queue.push(node->_left);
                node->_left = nullptr;
            }

            if (node->_right) {
                queue.push(node->_right);
                node->_right = nullptr;
            }
        }
        if (node->_left == nullptr && node->_right == nullptr)
            node.reset();
        else
            queue.push(node);
    }

 private:
    std::shared_ptr<Node> _root;
    Comparator _comp;
};

template <typename Value>
class Treap {
    struct TreapNode {
        TreapNode() : _value(0), _priority(0) {}

        explicit TreapNode(Value& value, size_t priority) : _value(value),
                                                   _priority(priority) {}

        Value _value;
        size_t _priority;
        std::shared_ptr<TreapNode> _left;
        std::shared_ptr<TreapNode> _right;
    };

 public:
    void insert(Value& value, size_t priority) {
        auto node = std::make_shared<TreapNode>(TreapNode(value, priority));

        if (_root == nullptr) {
            _root = node;
            return;
        }
        std::shared_ptr<TreapNode> cur_node = _root, prev_node = _root;

        while (cur_node != nullptr && priority <= cur_node->_priority) {
            prev_node = cur_node;
            if (value <= cur_node->_value)
                cur_node = cur_node->_left;
            else
                cur_node = cur_node->_right;
        }

        split(cur_node, value, node->_left, node->_right);
        if (cur_node == _root)
            _root = node;
        else if (value <= prev_node->_value)
            prev_node->_left = node;
        else
            prev_node->_right = node;
    }

    [[nodiscard]] int max_width() const {
        int max_width = 0;
        std::queue<std::shared_ptr<TreapNode>> layer;

        layer.push(_root);
        while (!layer.empty()) {
            int cur_width = layer.size();
            if (cur_width > max_width)
                max_width = cur_width;

            for (size_t i = 0; i != cur_width; ++i) {
                std::shared_ptr<TreapNode> tmp_node = layer.front();
                layer.pop();
                if (tmp_node->_left)
                    layer.push(tmp_node->_left);
                if (tmp_node->_right)
                    layer.push(tmp_node->_right);
            }
        }
        return max_width;
    }

    void print(std::shared_ptr<TreapNode> node) {
        if (node != nullptr) {
            std::cout << node->_value << " " << node->_priority << std::endl;
            print(node->_left);
            print(node->_right);
        }
    }


 private:
    std::shared_ptr<TreapNode> _root;

    void split(std::shared_ptr<TreapNode> cur_node, int key,
               std::shared_ptr<TreapNode>& left, std::shared_ptr<TreapNode>& right) {
        if (cur_node == nullptr) {
            left = nullptr;
            right = nullptr;
        } else if (cur_node->_value <= key) {
            split(cur_node->_right, key, cur_node->_right, right);
            left = cur_node;
        } else {
            split(cur_node->_left, key, left, cur_node->_left);
            right = cur_node;
        }
    }

    std::shared_ptr<TreapNode> merge(std::shared_ptr<TreapNode>& left, std::shared_ptr<TreapNode>& right) {
        if (left == nullptr || right == nullptr)
            return left == nullptr ? right : left;

        if (left->_priority > right->_priority) {
            left->_right = merge(left->_right, right);
            return left;
        } else {
            right->_left = merge(left, right->_left);
            return right;
        }
    }
};


int main(int argc, char **argv) {
    Treap<int> treap;
    BinaryTree<int> binary_tree;
    int n, priority;
    int number;

    std::cin >> n;
    for (size_t i = 0; i != n; ++i) {
        std::cin >> number >> priority;
        treap.insert(number, priority);
        binary_tree.insert(number);
    }

    std::cout << treap.max_width() - binary_tree.max_width();
    return 0;
}
