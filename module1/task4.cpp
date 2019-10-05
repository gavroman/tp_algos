/*
 * 4_4. Скользящий максимум.
 * Дан массив натуральных чисел A[0..n), n не превосходит 10^8. Так же задан размер некоторого окна
 * (последовательно расположенных элементов массива) в этом массиве k, k<=n. Требуется для каждого
 * положения окна (от 0 и до n-k) вывести значение максимума в окне.
 * Требования: Скорость работы O(n log n), память O(n).
 * Формат входных данных. Вначале вводится n - количество элементов массива. Затем вводится n строк
 * со значением каждого элемента. Затем вводится k  - размер окна.
 * Формат выходных данных. Разделенные пробелом значения максимумов для каждого положения окна.
 */

#include <sstream>
#include <iostream>
#include <assert.h>

template <typename T>
class Buffer {

 public:
    Buffer() :
        initialSize(4),
        size(0),
        realSize(0),
        data(nullptr) {}

    ~Buffer() {
        delete[] data;
    }

    void addElem(T elem) {
        if(realSize == size) {
            grow();
        }
        data[realSize++] = elem;
    }

    T deleteLast() {
        return data[--realSize];
    }

    T getElem(const int index) {
        return data[index];
    }

    void setElem(const int index, const T elem) {
        data[index] = elem;
    }

    int getSize() {
        return realSize;
    }

    void swap(const int index1, const int index2) {
        std::swap(data[index1], data[index2]);
    }

    bool isEmpty() {
        return (realSize == 0);
    }

 private:
    int initialSize;
    int size;
    int realSize;
    T * data;

    void grow() {
        int newSize = std::max(size * 2, initialSize);
        T * newData = new T[newSize];
        for (int i = 0; i != realSize; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
    }
};

template <typename T>
class MaxHeap {
 public:
    MaxHeap() : arr() {}

    void insert(T elem) {
        arr.addElem(elem);
        siftUp(arr.getSize() - 1);
    }

    T extraxtMax() {
        assert(!arr.isEmpty());
        T result = arr.getElem(0);
        arr.setElem(0, arr.getElem(arr.getSize() - 1));
        arr.deleteLast();
        if (!arr.isEmpty()) {
            siftDown(0);
        }
        return result;
    }

    T getMax() {
        return arr.getElem(0);
    }

    void print() {
        for (int i = 0; i != arr.getSize(); i++) {
            std::cout << "{"<< arr.getElem(i).index << "," << arr.getElem(i).value << "}, ";
        }
        std::cout << std::endl;
    }

 private:
    Buffer<T> arr;

    void siftDown(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if (left < arr.getSize() && arr.getElem(i) < arr.getElem(left)) {
            largest = left;
        }
        if (right < arr.getSize() && arr.getElem(largest) < arr.getElem(right)) {
            largest = right;
        }
        if (largest != i) {
            arr.swap(i, largest);
            siftDown(largest);
        }
    }

    void siftUp (int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (! (arr.getElem(parent) < arr.getElem(index))) {
                return;
            }
            arr.swap(index, parent);
            index = parent;
        }
    }

    void buildHeap() {
        for (int i = arr.getSize() / 2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    }
};

// структура для работы с кучей (реализована передача сравнения снаружи)
struct Node {
    int value;
    int index;
    explicit Node() : value(0), index(0)  {}
    constexpr bool operator<(const Node &rhs) const {
        return value < rhs.value;
    }
};


int main(int argc, char const *argv[]) {
    int heapSize = 0;
    std::cin >> heapSize;
    assert(heapSize >= 0 && heapSize < 100000000);

    Buffer<Node> buf;
    for (int i = 0; i != heapSize; i++) {
        Node node;
        std::cin >> node.value;
        node.index = i;
        buf.addElem(node);
    }

    int windowSize = 0;
    std::cin >> windowSize;
    assert(windowSize >= 1 && heapSize <= heapSize);

    MaxHeap<Node> heap;
    for (int i = 0; i != windowSize; i++) {
        heap.insert(buf.getElem(i));
    }
    int left = 0;
    int right = windowSize - 1;
    while (right != heapSize) {
        Node node = heap.getMax();
        if (node.index >= left && node.index <= right) {
            std::cout << node.value << " ";
            left++;
            right++;
            heap.insert(buf.getElem(right));
        } else {
            heap.extraxtMax();
        }
    }
    std::cout << std::endl;
    return 0;
}