/*      Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
 *   Требуется найти k-ю порядковую статистику, т.е. напечатать число,
 *   которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
 *   Требования: к дополнительной памяти: O(n). Среднее время работы: O(n).
 *   Должна быть отдельно выделенная функция partition.
 *   Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
 *
 *      6_1. Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 *   Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
 */
#include <sstream>
#include <iostream>
#include <assert.h>

template <class T>
class Buffer {

public:
    Buffer(int initSize) :
    initialSize(initSize),
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

    void print() {
        for (int i = 0; i != realSize; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
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

template<class T, class Comparator = std::less<T>>
int middleOfThree(Buffer<T> * array, int left, int right, Comparator comp = Comparator()) {
    int mid = (right + left) / 2;
    right--;

    if (array->getElem(right) < array->getElem(left)) {
        if (array->getElem(mid) >= array->getElem(left)) {
            mid = left;
        } else if (array->getElem(mid) < array->getElem(right)) {  // left > all
            mid = right;
        }
    } else {  // left <= right
        if (array->getElem(left) >= array->getElem(mid)) {
            mid = left;
        } else if (array->getElem(right) < array->getElem(mid)) {
            mid = right;
        }
    }

    return mid;
}

template<class T, class Comparator = std::less<T>>
int partition(Buffer<T> * arr, int left, int right, Comparator comp = Comparator()) {

std::cout << "Left = " << left << std::endl;
std::cout << "right = " << right << std::endl;
    int pivotIdx = middleOfThree(arr, left, right, comp);
    std::cout << "PIVOT = " << arr->getElem(pivotIdx) << std::endl;
    arr->swap(pivotIdx, right - 1);
    int i = left;
    int j = left;
    int last = right - 1;
    T pivot = arr->getElem(last);
    while (j != right) {
        while (arr->getElem(i) < pivot) {
            i++;
        }
        for (j = i; j != right && arr->getElem(j) >= pivot; j++);
        // j = i;
        // while (j != last && arr->getElem(j) >= pivot) {
        //     j++;
        // }
        if (j != right) {
            arr->swap(j, i);
            i++;
        }
        std::cout << "i =  " << i<< std::endl;
        std::cout << "j =  " << j<< std::endl;
        arr->print();
    }
    arr->swap(i, last);
    return i;
}

template<class T, class Comparator = std::less<T>>
void kStatistics(Buffer<T> * arr, int size, int k, Comparator comp = Comparator()) {
    int left = 0;
    int right = size;

    while (left < right) {
        int m = partition(arr, left, right, comp);
        if (m < k) {
            left = m + 1;
        } else {
            right = m;
        }
    }
}

void run(std::istream & input, std::ostream & output) {
    int arrSize = 0;
    input >> arrSize;
    assert(arrSize >= 0 && arrSize < 100000000);

    int k = 0;
    input >> k;

    Buffer<int> array(arrSize);
    for (int i = 0; i != arrSize; i++) {
        int elem = 0;
        input >> elem;
        array.addElem(elem);
    }

    array.print();
    kStatistics(&array, array.getSize(), k);
    // partition(&array, 0, arrSize);
    array.print();
    std::cout << "K = " << k << "  elem = " << array.getElem(k) << std::endl;
    // std::cout << middleOfThree(&array, 0, arrSize) << std::endl;
}

void test() {
    // {
    //     std::stringstream input;
    //     std::stringstream output;

    //     input << "10 0" << std::endl;
    //     input << "3 6 5 7 2 9 8 10 4 1" << std::endl;

    //     run(input, output);

    //     std::cout << output.str() << std::endl;
    // }
    // {
    //     std::stringstream input;
    //     std::stringstream output;

    //     input << "10 8" << std::endl;
    //     input << "10 9 8 7 6 5 4 3 2 1 " << std::endl;

    //     run(input, output);

    //     std::cout << output.str() << std::endl;
    // }
    // {
    //     std::stringstream input;
    //     std::stringstream output;

    //     input << "10 3" << std::endl;
    //     input << "0 0 0 0 0 0 0 0 0 1 " << std::endl;

    //     run(input, output);

    //     std::cout << output.str() << std::endl;
    // }
    {
        std::stringstream input;
        std::stringstream output;

        input << "9 7" << std::endl;
        input << "0 7 3 8 4 5 10 4 6" << std::endl;

        run(input, output);

        std::cout << output.str() << std::endl;
    }
    // {
    //     std::stringstream input;
    //     std::stringstream output;

    //     input << "4 4" << std::endl;
    //     input << "5 10 4 6 " << std::endl;

    //     run(input, output);

    //     std::cout << output.str() << std::endl;
    // }


}

int main(int argc, char const *argv[]) {
    test();
    //run(std::cin, std::cout);
    return 0;
}
