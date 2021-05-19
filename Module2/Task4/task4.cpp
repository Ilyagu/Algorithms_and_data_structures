// Copyright 2021 Ilyagu Nagdimaev

#include <iostream>
#include <vector>
#include <memory>
#include <stack>

template<class T>
struct DefaultComparator {
 public:
    bool operator()(const T &l, const T &r) const {
        return l < r;
    }
};

template<class Value, class Pos,
        class Comparator = DefaultComparator<Value>>
class AVLBinTree {
    struct Node {
        explicit Node(Value value) : _value(value), _position(1), _height(1) {}

        std::shared_ptr<Node> _left;
        std::shared_ptr<Node> _right;

        Value _value;
        Pos _position;

        uint8_t _height;

        Node(const Value &k, const Pos &v) :
                _left(nullptr), _right(nullptr),
                _value(k), _position(v), _height(1) {
        }
    };

 public:
    explicit AVLBinTree(Comparator comp = Comparator()) :
            _root(nullptr), _items_count(0), _comp(comp) {}

    ~AVLBinTree() {
        _root.reset();
    }

    void add(const Value &value, Pos &pos) {
        _root = add_aux(value, pos, _root);
    }

    void remove(const Value &value) {
        _root = remove_aux(_root, value);
    }

 private:
    std::shared_ptr<Node> _root;
    size_t _items_count;

    Comparator _comp;

    std::shared_ptr<Node> add_aux(const Value &value, Pos &pos, std::shared_ptr<Node> node) {
        if (!node) {
            _items_count++;
            return std::make_shared<Node>(value);
        }

        node->_position++;

        if (_comp(value, node->_value)) {
            pos += get_position(node->_right) + 1;
            node->_left = add_aux(value, pos, node->_left);
        } else {
            node->_right = add_aux(value, pos, node->_right);
        }
        return balance(node);
    }

    int get_position(std::shared_ptr<Node> node) {
        if (node == nullptr)
            return 0;
        return node->_position;
    }

    void fix_position(std::shared_ptr<Node> p) {
        int left_h = get_position(p->_left);
        int right_h = get_position(p->_right);

        p->_position = left_h + right_h + 1;
    }

    std::shared_ptr<Node> fix_positions(std::stack<std::shared_ptr<Node>> &nodes, std::shared_ptr<Node> cur_node) {
        while (!nodes.empty()) {
            std::shared_ptr<Node> node = nodes.top();
            node->_position--;

            if (node->_value > cur_node->_value)
                node->_left = cur_node;
            else
                node->_right = cur_node;

            cur_node = balance(node);
            nodes.pop();
        }
        return cur_node;
    }

    std::shared_ptr<Node> remove_aux(std::shared_ptr<Node> cur_node, int pos) {
        if (cur_node == nullptr)
            return nullptr;
        if (pos >= cur_node->_position)
            return cur_node;

        int current = 0;
        std::stack<std::shared_ptr<Node>> nodes;

        while (true) {
            int nodes_right = get_position(cur_node->_right);
            if (pos - current > nodes_right) {
                nodes.push(cur_node);
                cur_node = cur_node->_left;
                current += nodes_right + 1;
            } else if (pos - current < nodes_right) {
                if (cur_node->_right != nullptr) {
                    nodes.push(cur_node);
                    cur_node = cur_node->_right;
                } else {
                    break;
                }
            } else {
                std::shared_ptr<Node> cur_left = cur_node->_left;
                std::shared_ptr<Node> cur_right = cur_node->_right;
                int cur_value = cur_node->_value;

                cur_node.reset();

                if (cur_right == nullptr) {
                    if (cur_left == nullptr) {
                        if (!nodes.empty()) {
                            cur_node = nodes.top();
                            nodes.pop();
                            if (cur_node->_value > cur_value)
                                cur_node->_left = nullptr;
                            else
                                cur_node->_right = nullptr;
                            cur_node->_position--;
                        } else {
                            return nullptr;
                        }
                    } else {
                        cur_node = cur_left;
                    }
                } else {
                    std::shared_ptr<Node> min;
                    std::shared_ptr<Node> tree = find_and_remove_min(cur_right, min);
                    min->_left = cur_left;
                    min->_right = tree;
                    fix_position(min);
                    cur_node = balance(min);
                }
                break;
            }
        }

        return fix_positions(nodes, cur_node);
    }

    std::shared_ptr<Node> find_and_remove_min(std::shared_ptr<Node> node, std::shared_ptr<Node> &min) {
        if (!node->_left) {
            min = node;
            return node->_right;
        }
        node->_left = find_and_remove_min(node->_left, min);
        node->_position--;
        return balance(node);
    }

    uint8_t get_height(std::shared_ptr<Node> node) {
        if (!node)
            return 0;
        return node->_height;
    }

    void fix_height(std::shared_ptr<Node> node) {
        if (!node)
            return;
        node->_height = std::max(get_height(node->_left),
                                 get_height(node->_right)) + 1;
    }

    int b_factor(std::shared_ptr<Node> node) {
        return get_height(node->_right) - get_height(node->_left);
    }

    std::shared_ptr<Node> balance(std::shared_ptr<Node> node) {
        fix_height(node);

        int bf = b_factor(node);
        if (bf == 2) {
            if (b_factor(node->_right) < 0)
                node->_right = right_turn(node->_right);
            return left_turn(node);
        } else if (bf == -2) {
            if (b_factor(node->_left) > 0)
                node->_left = left_turn(node->_left);
            return right_turn(node);
        }
        return node;
    }

    std::shared_ptr<Node> left_turn(std::shared_ptr<Node> p) {
        std::shared_ptr<Node> q = p->_right;
        p->_right = q->_left;
        q->_left = p;

        fix_position(p);
        fix_position(q);

        fix_height(p);
        fix_height(q);
        return q;
    }

    std::shared_ptr<Node> right_turn(std::shared_ptr<Node> p) {
        std::shared_ptr<Node> q = p->_left;
        p->_left = q->_right;
        q->_right = p;

        fix_position(p);
        fix_position(q);

        fix_height(p);
        fix_height(q);
        return q;
    }
};


int main() {
    int n;
    std::cin >> n;

    AVLBinTree<int, int> tree;
    std::vector<int> result;
    int command, value, position;

    for (size_t i = 0; i < n; i++) {
        std::cin >> command;

        if (command == 1) {
            position = 0;
            std::cin >> value;
            tree.add(value, position);
            result.push_back(position);
        } else if (command == 2) {
            std::cin >> value;
            tree.remove(value);
        }
    }

    for (int i : result)
        std::cout << i << std::endl;

    return 0;
}
