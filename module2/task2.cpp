/*
 * Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N. Требуется построить
 * бинарное дерево, заданное наивным порядком вставки. Т.е., при добавлении очередного числа K в
 * дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе
 * в левое поддерево root.
 * Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
 * Вариант 2_4. Выведите элементы в порядке level-order (по слоям, “в ширину”).
 */

#include <sstream>
#include <iostream>
#include <assert.h>
#include <vector>
#include <queue>
#include <functional>

template < class T, class Comparator = std::less<T> >
class BinaryTree {
 public:
    BinaryTree() : bigFather(nullptr), realSize(0) {}

    struct Node {
        T data;
        Node * left;
        Node * right;
        explicit Node(T data) : data(data), left(nullptr), right(nullptr) {}
    };

    void addElem(const T& data) {
        if (bigFather == nullptr) {
            bigFather = new Node(data);

            realSize++;
            return;
        }
        Node * currentNode = bigFather;
        while (true) {
            if (!comp(currentNode->data, data)) {
                if (currentNode->left) {
                    currentNode = currentNode->left;
                } else {
                    currentNode->left = new Node(data);
                    break;
                }
            } else {
                if (currentNode->right) {
                    currentNode = currentNode->right;
                } else {
                    currentNode->right = new Node(data);
                    break;
                }
            }
        }
        return;
    }

    void printDataInLevelOrder() {
        levelOrder([](const Node * node) {
            std::cout << node->data << " ";
            delete node;
        });
        std::cout << std::endl;
    }

    ~BinaryTree() {
        levelOrder([](Node * node) {
            delete node;
        });
    }

 private:
    Node * bigFather;
    unsigned realSize;
    Comparator comp;

    void levelOrder(std::function<void(Node*)> visitor) {
        std::queue<Node *> queue;
        Node * currentNode = bigFather;
        queue.push(bigFather);
        size_t needToPopNumber = 0;
        size_t newNeedToPopNumber = 1;
        while (!queue.empty()) {
            needToPopNumber = newNeedToPopNumber;
            newNeedToPopNumber = 0;
            for (int i = 0; i != needToPopNumber; i++) {
                if (queue.front() != nullptr) {
                    Node * currentFather = queue.front();
                    queue.pop();
                    if (currentFather->left) {
                        queue.push(currentFather->left);
                        newNeedToPopNumber++;
                    }
                    if (currentFather->right) {
                        queue.push(currentFather->right);
                        newNeedToPopNumber++;
                    }

                    visitor(currentFather);
                }
            }
        }
    }
};

int main(int argc, char const *argv[]) {
    size_t N = 0;
    std::cin >> N;
    assert(N > 0 && N <= 1000000);

    BinaryTree<int> bt;
    for (size_t i = 0; i != N; i++) {
        int elem = 0;
        std::cin >> elem;
        bt.addElem(elem);
    }

    bt.printDataInLevelOrder();
    return 0;
}
