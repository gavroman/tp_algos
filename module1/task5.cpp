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
#include <string.h>
#include <algorithm>

template <class T>
class Buffer {

 public:
    Buffer(int initSize) :
        initialSize(initSize),
        size(0),
        realSize(0),
        data(nullptr) {}

    // Buffer(Buffer const& copy) :
    //     initialSize(copy.initialSize),
    //     size(copy.size),
    //     realSize(copy.realSize) {

    //     std::cout << "ZALUPA copy" << std::endl;
    //     for (int i = 0; i != realSize; i++) {
    //         data[i] = copy.data[i];
    //     }
    // }

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
    // std::cout << "_________________________________________" << std::endl;
    // std::cout << "leftArray = ";
    // leftArray->print();
    // std::cout << "rightArray = ";
    // rightArray->print();
    Buffer<T> * returnArray = new Buffer<T>(leftArray->getSize() + rightArray->getSize());
    int i = 0;
    int j = 0;
    while (i != leftArray->getSize() && j != rightArray->getSize()) {
        // std::cout << "i = " << i << std::endl;
        // std::cout << "j = " << j << std::endl;
        if (comp(leftArray->getElem(i), rightArray->getElem(j))) {
            returnArray->addElem(leftArray->getElem(i));
            i++;
        } else {
            returnArray->addElem(rightArray->getElem(j));
            j++;
        }
    }

    if (i == leftArray->getSize()) {
        for (; j != rightArray->getSize(); j++) {
            returnArray->addElem(rightArray->getElem(j));
        }
    } else if (j == rightArray->getSize()) {
        for (; i != leftArray->getSize(); i++) {
            returnArray->addElem(leftArray->getElem(i));
        }
    }
    // std::cout << "returnArray = ";
    // returnArray->print();
    // std::cout << "_________________________________________" << std::endl;
    return returnArray;
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
    // array->print();
}

int run(std::istream& input, std::ostream& output) {
    int arraySize = 0;
    input >> arraySize;

    // Buffer<int> array = Buffer<int>(arraySize);
    // for (int i = 0; i != arraySize; i++) {
    //     int elem = 0;
    //     input >> elem;
    //     array.addElem(elem);
    // }

    Buffer<TimeSlot> array(arraySize);
    for (int i = 0; i != arraySize; i++) {
        TimeSlot tSlot;
        input >> tSlot.timeIn >> tSlot.timeOut;
        array.addElem(tSlot);
    }

    // for (int i = 0; i != array.getSize(); i++) {
    //     std::cout << "{" << array.getElem(i).timeIn << "," << array.getElem(i).timeOut << "}, ";
    // }
    // std::cout << std::endl << std::endl;

    mergeSort(&array);

    for (int i = 0; i != array.getSize(); i++) {
        std::cout << "{" << array.getElem(i).timeIn << "," << array.getElem(i).timeOut << "}, ";
    }
    std::cout << std::endl;

    // int advertismentCounter = 2;
    // TimeSlot base = array.getElem(0);
    // bool afterBase = false;
    // for (int i = 1; i != array.getSize(); i++) {
    //     int timeIn = array.getElem(i).timeIn;
    //     if (timeIn > base.timeOut) {
    //         std::cout << i << " " << advertismentCounter << std::endl;
    //         advertismentCounter += 2;
    //         base = array.getElem(i);
    //     } else if (timeIn == base.timeOut) {
    //         std::cout << i << " " << advertismentCounter << std::endl;
    //         advertismentCounter++;
    //         base = array.getElem(i);
    //         afterBase = true;
    //     } else if (afterBase && timeIn > base.timeIn) {
    //         std::cout << i << " " << advertismentCounter << std::endl;
    //         advertismentCounter++;
    //         afterBase = false;
    //     }
    // }
    // std::cout << std::endl << advertismentCounter << std::endl;

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

        // std::cout << "Time 1 = " << advTime1<< std::endl;
        // std::cout << "Time 2 = " << advTime2<< std::endl;
        // std::cout << "Counter = " <<advertismentCounter << std::endl;
        // std::cout << "_________________________________________" << std::endl;
    }
    std::cout << advertismentCounter << std::endl;
}

void test() {
    {
        std::stringstream input;
        std::stringstream output;

        input << "5" << std::endl;
        input << "1 10" << std::endl;
        input << "10 12" << std::endl;
        input << "1 10" << std::endl;
        input << "1 10" << std::endl;
        input << "23 24" << std::endl;

        run(input, output);
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "9" << std::endl;
        input << "3 5" << std::endl;
        input << "4 8" << std::endl;
        input << "1 19" << std::endl;
        input << "13 14" << std::endl;
        input << "1 8" << std::endl;
        input << "5 16" << std::endl;
        input << "3 10" << std::endl;
        input << "4 10" << std::endl;
        input << "5 10" << std::endl;

        run(input, output);
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "5" << std::endl;
        input << "1 4" << std::endl;
        input << "2 5" << std::endl;
        input << "3 6" << std::endl;
        input << "4 7" << std::endl;
        input << "5 8" << std::endl;

        run(input, output);
    }
    /*{
        std::stringstream input;
        std::stringstream output;

        input << "8" << std::endl;
        input << "1 6 4 3 2 5 7 0" << std::endl;

        run(input, output);
    }*/
    /*{
        std::stringstream input;
        std::stringstream output;

        input << "16" << std::endl;
        input << "1 3 5 7 9 11 13 15" << std::endl;
        input << "2 4 6 8 10 12 14 16" << std::endl;

        run(input, output);
    }*/
}

int main(int argc, char const *argv[]) {
    test();
    return 0;
}