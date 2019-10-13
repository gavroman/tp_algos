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
    explicit Node() : timeIn(0), timeOut(0)  {}
};


int run(std::istream& input, std::ostream& output) {
    int arraySize = 0;
    input >>
}

void test() {

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

int main(int argc, char const *argv[]) {
    test();
    return 0;
}