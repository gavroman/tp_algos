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

class Array {

 public:
    Array(const int count) :
        initialSize(count),
        size(initialSize),
        realSize(0),
        data(new int[size]) {}

    Array(const int count, const int fill) :
        initialSize(count),
        size(count),
        realSize(count),
        data(new int[count]) {
            for (int i = 0; i != size; i++) {
                data[i] = fill;
            }
        }


    ~Array() {
        delete[] data;
    }

    void addElem(const int elem) {
        if(realSize == size) {
            grow();
        }
        data[realSize++] = elem;
    }

    int deleteLast() {
        return data[--realSize];
    }

    int getElem(const int index) {
        return data[index];
    }

    void setElem(const int index, const int elem) {
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
    int * data;

    void grow() {
        int newSize = size * 2;
        int * newData = new int[newSize];
        for (int i = 0; i != realSize; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
    }
};

class Tree {
public:
    Tree();
    ~Tree();

};

double makePower( double a, int n ) {
    double result = 1;
    double aInPowerOf2 = a;
    while( n > 0 ) {
        if( ( n & 1 ) == 1 ) {
            result *= aInPowerOf2;
        }
        aInPowerOf2 *= aInPowerOf2;
        n = n >> 1;
    }
    return result;
}


void run(std::istream & input, std::ostream & output) {
    int arraySize = 0;
    input >> arraySize;
    assert(arraySize >= 0 && arraySize < 100000000);

    int a = arraySize - 1;
    int power = 0;
    while(a != 0) {
      a = a >> 1;
      power++;
    }
    std::cout << "Old arraySize " << arraySize<< std::endl;
    std::cout << "Old power " << power << std::endl;

    int newArraySize = makePower(2, power + 1) - 1 ;
    std::cout << "new size " << newArraySize << std::endl;

    Array array(newArraySize, 0);

    for (int i = 0; i != arraySize; i++) {
            int elem = 0;
            input >> elem;
            array.setElem(newArraySize / 2 + i, elem);
    }

    for (int i = newArraySize / 2; i != -1; i--) {
        array.setElem(i, std::max(array.getElem(2 * i + 1), array.getElem(2 * i + 2)));
    }



    int l = 4;
    int r = 7;


    int ans = 0;
    int n = newArraySize / 2;
    l += n ;//- 1;
    r += n ;//- 1;
    while (l <= r)
    {
        std::cout << "l = " << l << "  data[l] = " << array.getElem(l) << std::endl;
        std::cout << "r = " << r << "  data[r] = " << array.getElem(r) << std::endl;
        if (l % 1 == 0) {
            std::cout << "l" << std::endl;
            ans = std::max(ans, array.getElem(l));
            std::cout << "ans = " << ans << std::endl;
            l = l / 2;
        } else {
            l = (l - 2) / 2;
        }

        if (r % 2 != 0) {
            std::cout << "r " << std::endl;
            ans = std::max(ans, array.getarray.getElem(r)Elem(r));
            std::cout << "ans = " << ans << std::endl;
            std::cout << "ODD "<< r << std::endl;
            r = (r - 3) / 2;
        } else {
            r = (r - 2) / 2;
            std::cout << "NODD "<< r << std::endl;
        }
        // сдвигаем указатели на уровень выше
    }

    std::cout << "l = " << l << "  data[l] = " << array.getElem(l) << std::endl;
    std::cout << "r = " << r << "  data[r] = " << array.getElem(r) << std::endl;

    array.print();
    std::cout << "ans = " << ans << std::endl;



    //heap.print();
}

void test() {
    // {
    //     std::stringstream input;
    //     std::stringstream output;

    //     input << "10 ";
    //     input << "1 2 3 4 5 6 7 8 9 10 ";
    //     input << "6 ";

    //     run(input, output);

    //     std::cout << output.str() << std::endl;
    // }
    {
        std::stringstream input;
        std::stringstream output;

        input << "9" << std::endl;
        input << "0 7 3 8 4 5 10 4 6" << std::endl;
        input << "1" << std::endl;

        run(input, output);

        std::cout << output.str() << std::endl;
    }
    // {
    //     std::stringstream input;
    //     std::stringstream output;

    //     input << "4 ";
    //     input << "5 10 4 6";
    //     // input << "1 ";

    //     run(input, output);

    //     std::cout << output.str() << std::endl;
    // }

}

int main(int argc, char const *argv[]) {
    // run(std::cin, std::cout);
    test();

    return 0;
}