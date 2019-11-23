/*     4_2. Порядковые статистики.
 *     Дано число N и N строк. Каждая строка содержит команду добавления или удаления натуральных чисел, а также запрос
 * на получение k-ой порядковой статистики. Команда добавления числа A задается положительным числом A, команда удаления
 * числа A задается отрицательным числом “-A”. Запрос на получение k-ой порядковой статистики задается числом k.
 * Требования: скорость выполнения запроса - O(log n).
 */

#include <iostream>
#include <vector>
#include <assert.h>
#include <sstream>

template <class T>
struct DefaultComparator {
    int operator()(const T& l, const T& r) const {
        if (l < r) {
            return -1;
        }
        if (l > r) {
            return 1;
        }
        return 0;
    }
};

template <class Key, class Comparator = DefaultComparator<Key>>
class AVLTree {
    struct Node {
        Key key;
        uint8_t height;
        Node* left;
        Node* right;
        Node(const Key& key) : key(key), height(1), left(nullptr), right(nullptr) {}
    };

 public:
    AVLTree(Comparator comp = Comparator()) : root(nullptr), tree_size(0), comp(comp) {}

    AVLTree(const AVLTree&) = delete;
    AVLTree(AVLTree&&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    AVLTree& operator=(AVLTree&&) = delete;

    ~AVLTree() {
        kill_node_family(root);
    }

    void kill_node_family(Node * node) {
        if(!node) {
            return;
        }
        kill_node_family(node->left);
        kill_node_family(node->right);
        delete node;
        return;
    }

    bool find(const Key& key) {
        return _find(root, key);
    }

    void insert(const Key& key) {
        root = _insert(root, key);
    }

    void erase(const Key& key) {
        root = _erase(root, key);
    }

    Key get_elem_on_index(size_t index) {
        return get_elem_on_index(root, index);
    }

 private:
    Node* root;
    size_t tree_size;
    Comparator comp;

    bool _find(Node* node, const Key& key) {
        if (!node) {
            return false;
        }
        int comp_res = comp(key, node->key);
        if (comp_res == -1) {
            return _find(node->left, key);
        }
        else if (comp_res == 1) {
            return _find(node->right, key);
        }
        return true;
    }

    Node* _insert(Node* node, const Key& key) {
        if (!node) {
            tree_size++;
            return new Node(key);
        }
        int comp_res  = comp(key, node->key);
        if (comp_res == -1) {
            node->left = _insert(node->left, key);
        } else {
            node->right = _insert(node->right, key);
        }
        return balance(node);
    }

    Node* _erase(Node* node, const Key& key) {
        if (!node) {
            return nullptr;
        }

        int comp_res = comp(key, node->key);
        if (comp_res == -1) {
            node->left = _erase(node->left, key);
        } else if (comp_res == 1) {
            node->right = _erase(node->right, key);
        } else {
            Node* left = node->left;
            Node* right = node->right;

            delete node;

            if (!right) {
                return left;
            }

            Node* min_node = find_and_remove_min(right);
            min_node->right = right;
            min_node->left = left;

            return balance(min_node);
        }
        return balance(node);
    }

    Key get_elem_on_index(Node* current_node, size_t index) const {
        assert(current_node);
        size_t elem = 0;
        size_t left_children_number = count_children(current_node->left);
        if (left_children_number > index) {
            elem = get_elem_on_index(current_node->left, index);
        } else if (left_children_number < index) {
            elem = get_elem_on_index(current_node->right, index - left_children_number - 1);
        } else {
            elem = current_node->key;
        }
        return elem;
    }

    Node* find_and_remove_min(Node*& node) {
        Node * min_node = nullptr;
        if (!node->left) {
            min_node = node;
            node = node->right;
            min_node->right = nullptr;
            return min_node;
        }
        min_node = find_and_remove_min(node->left);
        node = balance(node);
        return min_node;
    }

    uint8_t height(Node* node) const {
        return node ? node->height : 0;
    }

    void fix_height(Node* node) {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    int bfactor(Node* node) const {
        return height(node->right) - height(node->left);
    }

    Node* rotate_left(Node* node) {
        Node* top_node = node->right;
        node->right = top_node->left;
        top_node->left = node;
        fix_height(node);
        fix_height(top_node);
        return top_node;
    }

    Node* rotate_right(Node* node) {
        Node* top_node = node->left;
        node->left = top_node->right;
        top_node->right = node;
        fix_height(node);
        fix_height(top_node);
        return top_node;
    }

    Node* balance(Node* node) {
        fix_height(node);
        int bf = bfactor(node);

        if (bf == 2) {
            if (bfactor(node->right) < 0) {
                node->right  = rotate_right(node->right);
            }
            return rotate_left(node);
        } else if (bf == -2) {
            if (bfactor(node->left) > 0) {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }
        return node;
    }

    size_t count_children(Node* father) const {
        if (!father) {
            return 0;
        }
        size_t children_number = 1;
        children_number += count_children(father->left);
        children_number += count_children(father->right);
        return children_number;
    }
};

int main(int argc, char const *argv[]) {
    size_t commands = 0;
    std::cin >> commands;
    assert(commands > 0);

    AVLTree<int> tree;
    for (int i = 0; i != commands; i++) {
        int key = 0, k = 0;
        std::cin >> key >> k;
        if (key > 0) {
            tree.insert(key);
        } else if (key < 0) {
            tree.erase(key * -1);
        }
        std::cout << tree.get_elem_on_index(k) << std::endl;
    }

    return 0;
}
