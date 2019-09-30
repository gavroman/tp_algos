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
        data(new int[count]),
        realSize(0) {}

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

    int getNearest(const int elem) {
        Bounds bounds = localizeSearch(elem);
        if (bounds.right == bounds.left) {
            std::cout << "ZALUPA1    " ;
            return bounds.left - 1;
        }

        int idx = binarySearch(elem, bounds.left, bounds.right);
        if (idx == 0) {
            std::cout << "ZALUPA2    " ;
            return idx;
        }

        if (data[idx] - elem >= elem - data[idx - 1]) {
            std::cout << "ZALUPA3    " ;
            return idx - 1;
        } else {
            std::cout << "ZALUPA3    " ;
            return idx;
        }


    }

    void print() {
        for (int i = 0; i != realSize; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

 private:
    int size;
    int realSize;
    int * data;
};

int run(std::istream& input) {
    int n = 0;
    input >> n;
    assert(n > 0 && n <= 110000);
    Buffer * A = new Buffer(n);
    for (int i = 0; i != n; i++) {
        int elem = 0;
        input >> elem;
        A->addElem(elem);
    }

    int m = 0;
    input >> m;
    assert(m > 0 && m <= 1000);
    Buffer * B = new Buffer(m);
    for (int i = 0; i != m; i++) {
        int elem = 0;
        input >> elem;
        B->addElem(elem);
    }

    // std::cout << A->getNearest(401) << std::endl;

    for (int i = 0; i != B->getSize(); i++) {
        std::cout << i << ")   elem = " << B->getElem(i);
        std::cout << "     idx = " << A->getNearest(B->getElem(i)) << std::endl;
    }

    delete A;
    return 0;
}

int test() {
    // {
    //     std::stringstream input;
    //     input << "20" << std::endl;
    //     input << "2 4 24 40 70 78 90 91 92 93 94 95 96 97 132 156 192 198 290 400" << std::endl;
    //     input << "16" << std::endl;
    //     input << "0 1 2 3 4 13 14 45 56 77 78 76 87 291 399 500" << std::endl;
    //     run(input);
    // }
    // {
    //     std::stringstream input;
    //     input << "3" << std::endl;
    //     input << "10 20 30" << std::endl;
    //     input << "3" << std::endl;
    //     input << "9 15 35" << std::endl;
    //     run(input);
    // }
    {
        std::stringstream input;
        input << "3" << std::endl;
        input << "10 20 30" << std::endl;
        input << "4" << std::endl;
        input << "8 9 10 32" << std::endl;
        run(input);
    }
}

int main(int argc, char const *argv[]) {
    // int n = 0;
    // std::cin >> n;
    // assert(n > 0 && n <= 110000);
    // Buffer * A = new Buffer(n);
    // for (int i = 0; i != n; i++) {
    //     int elem = 0;
    //     std::cin >> elem;
    //     A->addElem(elem);
    // }

    // int m = 0;
    // std::cin >> m;
    // assert(m > 0 && m <= 1000);
    // Buffer * B = new Buffer(m);
    // for (int i = 0; i != m; i++) {
    //     int elem = 0;
    //     std::cin >> elem;
    //     B->addElem(elem);
    // }

    // A->print();
    // B->print();

    // delete A;
    // delete B;

    // run(std::cin; std::cout);
    test();

    return 0;
}