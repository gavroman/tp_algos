/*  2_4. Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 *  Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего
 *  по значению к B[i].
 *  Требования: Время работы поиска для каждого элемента B[i]: O(log(k)).
 *  Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска
 *  размером порядка k, а потом уже в нем делать бинарный поиск.
 *  n ≤ 110000, m ≤ 1000.
 */

#include <sstream>
#include <iostream>
#include <assert.h>

class Buffer {
    struct Bounds {
        int left;
        int right;

        explicit Bounds(int leftBound, int rightBound) :
            left(leftBound),
            right(rightBound)  {}
    };

 public:
    Buffer(const int count) :
        size(count),
        realSize(0),
        data(new int[count]) {}

    ~Buffer() {
        delete[] data;
    }

    void addElem(int elem) {
        data[realSize++] = elem;
    }

    int getElem(const int index) {
        return data[index];
    }

    int getSize() {
        return realSize;
    }

    int getNearest(const int elem) {
        Bounds bounds = localizeSearch(elem);
        if (bounds.right == bounds.left) {
            return bounds.left - 1;
        }

        int idx = binarySearch(elem, bounds.left, bounds.right);

        return (idx == 0 || data[idx] - elem < elem - data[idx - 1]) ? idx : idx - 1;
    }

 private:
    int size;
    int realSize;
    int * data;

    int binarySearch(int elem, int left, int right) {
        while (left < right) {
            int mid = (left + right) / 2;
            if (data[mid] < elem) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return right;
    }

    Bounds localizeSearch(const int elem) {
        Bounds bounds = Bounds(0, 2);
        while (elem > data[bounds.right-1] && bounds.right != bounds.left) {
            int tmp = bounds.right;
            bounds.right = std::min(bounds.right * 2, realSize);
            bounds.left = tmp;
        }
        return bounds;
    }
};


int main(int argc, char const *argv[]) {
    int n = 0;
    std::cin >> n;
    assert(n > 0 && n <= 110000);
    Buffer * A = new Buffer(n);
    for (int i = 0; i != n; i++) {
        int elem = 0;
        std::cin >> elem;
        A->addElem(elem);
    }

    int m = 0;
    std::cin >> m;
    assert(m > 0 && m <= 1000);
    Buffer * B = new Buffer(m);
    for (int i = 0; i != m; i++) {
        int elem = 0;
        std::cin >> elem;
        B->addElem(elem);
    }

    for (int i = 0; i != B->getSize(); i++) {
        std::cout << A->getNearest(B->getElem(i)) << " ";
    }
    std::cout << std::endl;

    return 0;
}