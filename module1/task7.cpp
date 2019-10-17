/*   7_3. Binary MSD для long long.
 *   Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 106.
 *   Отсортировать массив методом MSD по битам (бинарный QuickSort).
 */

#include <sstream>
#include <iostream>
#include <assert.h>
#include <bitset>

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

int getBitOnPosition(long long number, int bitNumber) {
    long long bitMask = 1;
    bitMask = bitMask << bitNumber;
    if (number & bitMask) {
        return 1;
    }
    return 0;
}

template<class T>
int partition(Buffer<T> * arr, int left, int right, int bitNumber) {
    int i = left;
    int j = right - 1;
    while (i != j) {
        for (; getBitOnPosition(arr->getElem(i), bitNumber) == 0 && (i < j); i++);
        for (; getBitOnPosition(arr->getElem(j), bitNumber) == 1 && (i < j); j--);
        arr->swap(i, j);
    }
    return i;
}


template <class T>
void binaryQuickSort(Buffer<T> * array, int left, int right, int bitNumber) {
    if (right - left < 2 || bitNumber == -1) {
        return;
    }

    int divisionIndex = partition(array, left, right, bitNumber);

    if (getBitOnPosition(array->getElem(left), bitNumber) == 1
        || getBitOnPosition(array->getElem(right - 1), bitNumber) == 0) {
        binaryQuickSort(array, left, right, bitNumber - 1);
    } else {
        binaryQuickSort(array, left, divisionIndex, bitNumber - 1);
        binaryQuickSort(array, divisionIndex, right, bitNumber - 1);
    }
}

int main(int argc, char const *argv[]) {
    int arraySize = 0;
    std::cin >> arraySize;
    assert(arraySize <= 1000000);
    Buffer<long long> * array = new Buffer<long long>(arraySize);
    for (int i = 0; i != arraySize; i++) {
        long long elem = 0;
        std::cin >> elem;
        array->addElem(elem);
    }

    binaryQuickSort(array, 0, arraySize, 62);

    for (int i = 0; i != arraySize; i++) {
        std::cout << array->getElem(i) << " ";
    }
    std::cout << std::endl;
    return 0;
}