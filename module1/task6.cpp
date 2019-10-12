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

int main(int argc, char const *argv[]) {

    return 0;
}