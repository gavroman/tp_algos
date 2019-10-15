/*
 *     Требование для всех вариантов Задачи 5
 * Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием.
 * Решение должно поддерживать передачу функции сравнения снаружи.
 * Общее время работы алгоритма O(n log n).
 * 5_1. Реклама.
 * В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода
 * покупателей (два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы.
 * Рекламу можно транслировать только в целочисленные моменты времени.
 * Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
 * В каждый момент времени может показываться только одна реклама. Считается,
 * что реклама показывается мгновенно. Если реклама показывается в момент ухода или прихода,
 * то считается, что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.
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

struct TimeSlot {
    int timeIn;
    int timeOut;
    explicit TimeSlot() : timeIn(0), timeOut(0)  {}
};

template <class T>
class timeComparator {
 public:
    bool operator() (const T & left, const T & right) {
        if (left.timeOut < right.timeOut) {
            return true;
        }
        if (left.timeOut > right.timeOut) {
            return false;
        }

        if (left.timeIn < right.timeIn) {
            return false;
        }
        if (left.timeIn > right.timeIn) {
            return true;
        }
        return true;
    }
};

template<class T, class Comparator = timeComparator<T>>
Buffer<T> * merge(Buffer<T> * leftArray, Buffer<T> * rightArray, Comparator comp = Comparator()) {
    Buffer<T> * resultArray = new Buffer<T>(leftArray->getSize() + rightArray->getSize());
    int i = 0;
    int j = 0;
    while (i != leftArray->getSize() && j != rightArray->getSize()) {
        if (comp(leftArray->getElem(i), rightArray->getElem(j))) {
            resultArray->addElem(leftArray->getElem(i));
            i++;
        } else {
            resultArray->addElem(rightArray->getElem(j));
            j++;
        }
    }
    if (i == leftArray->getSize()) {
        for (; j != rightArray->getSize(); j++) {
            resultArray->addElem(rightArray->getElem(j));
        }
    } else if (j == rightArray->getSize()) {
        for (; i != leftArray->getSize(); i++) {
            resultArray->addElem(leftArray->getElem(i));
        }
    }
    return resultArray;
}

template<class T>
void mergeSort(Buffer<T> * array) {
    if (array->getSize() == 1) {
        return;
    }

    int leftPartSize = array->getSize() / 2;
    Buffer<T> * leftArray = new Buffer<T>(leftPartSize);
    for (int i = 0; i != leftPartSize; i++) {
        leftArray->addElem(array->getElem(i));
    }
    int rightPartSize = array->getSize() - leftPartSize;
    Buffer<T> * rightArray = new Buffer<T>(rightPartSize);
    for (int i = leftPartSize; i != array->getSize(); i++) {
        rightArray->addElem(array->getElem(i));
    }

    mergeSort(leftArray);
    mergeSort(rightArray);

    Buffer<T> * tmpArray = merge(leftArray, rightArray);
    for (int i = 0; i != array->getSize(); i++) {
        array->setElem(i, tmpArray->getElem(i));
    }

    delete tmpArray;
    delete rightArray;
    delete leftArray;
}

int main(int argc, char const *argv[]) {
    int arraySize = 0;
    std::cin >> arraySize;
    Buffer<TimeSlot> array(arraySize);

    for (int i = 0; i != arraySize; i++) {
        TimeSlot tSlot;
        std::cin >> tSlot.timeIn >> tSlot.timeOut;
        array.addElem(tSlot);
    }

    mergeSort(&array);

    int advTime1 = array.getElem(0).timeOut - 1;
    int advTime2 = array.getElem(0).timeOut;
    int advertismentCounter = 2;
    for (int i = 1; i != array.getSize() ; i++) {
        TimeSlot current = array.getElem(i);
        if (current.timeIn > advTime2) {
            advertismentCounter += 2;
            advTime1 = array.getElem(i).timeOut - 1;
            advTime2 = array.getElem(i).timeOut;
        } else if (current.timeIn == advTime2) {
            advertismentCounter++;
            advTime1 = advTime2;
            advTime2 = array.getElem(i).timeOut;
        } else if (current.timeIn > advTime1) {
            advertismentCounter++;
            advTime1 = advTime2;
            advTime2 = current.timeOut;
        }
    }
    std::cout << advertismentCounter << std::endl;
    return 0;
}