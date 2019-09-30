 /* 1_4. “Считалочка”.
  * В круг выстроено N человек, пронумерованных числами от 1 до N. Будем исключать каждого k-ого до тех пор,
  * пока не уцелеет только один человек. (Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й,
  * затем 9-й, затем 2-й, затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й.
  * Таким образом, уцелеет 4-й.) Необходимо определить номер уцелевшего.
  * N, k ≤ 10000.
  * Требования:  Решить перебором.
  */

#include <memory>
#include <iostream>
#include <assert.h>

class Buffer {

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

    int deleteElemOnIndex(const int index) {
        int deletedElem = data[index];
        int * newData = new int[--realSize];

        for (int i = 0; i != index; i++) {
            newData[i] = data[i];
        }
        for (int i = index; i != realSize; i++) {
            newData[i] = data[i+1];
        }

        delete[] data;
        data = newData;
        return deletedElem;
    }

    int getElem(const int index) {
        return data[index];
    }

    int getSize() {
        return realSize;
    }

 private:
    int size;
    int realSize;
    int * data;
};

int getLastAlive(const int count, const int step) {
    Buffer * buf = new Buffer(count);

    for (int i = 0; i != count; i++) {
        buf->addElem(i + 1);
    }

    int counter = 0;
    int i = 0;
    while (buf->getSize() != 1) {
        if (i == buf->getSize()) {
            i = 0;
        }
        if (counter == step - 1) {
            buf->deleteElemOnIndex(i);
            if (i == buf->getSize()) {
                i = 0;
            }
            counter = 0;
        }

        counter++;
        i++;
    }

    int lastElem = buf->getElem(0);
    delete buf;
    return lastElem;
}


int main(int argc, char const *argv[]) {
    int N = 0, k = 0;
    std::cin >> N;
    std::cin >> k;

    assert(N > 0 && N <= 10000);
    assert(k > 0 && k <= 10000);

    std::cout << getLastAlive(N, k) << std::endl;
}
