#include <memory>
#include <iostream>

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

    std::cout << getLastAlive(N, k) << std::endl;
}
