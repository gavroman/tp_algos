#include <memory>
#include <iostream>

class Buffer {

 public:
    Buffer(const int count) :
        size(count),
        data(new int[count]),
        realSize(0) {}

    ~Buffer() {}

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
            //std::cout << "BACK" << std::endl;
            i = 0;
        }
        if (counter == step - 1) {
            //std::cout << "realSize " << buf->getSize();
            //std::cout << "          deleting " << i << "  =  " << buf->getElem(i) << "  counter  "<< counter<<std::endl;
            buf->deleteElemOnIndex(i);
            if (i == buf->getSize()) {
                //std::cout << "BACK" << std::endl;
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
    // int N = 0, k = 0;
    // std::cin >> N;
    // std::cin >> k;

    // std::cout << getLastAlive(N, k) << std::endl;
    std::cout << getLastAlive(10000, 3) << std::endl;
    std::cout << getLastAlive(10000, 345) << std::endl;
    std::cout << getLastAlive(10000, 343) << std::endl;
    std::cout << getLastAlive(10000, 38) << std::endl;
    std::cout << getLastAlive(10000, 4) << std::endl;
    std::cout << getLastAlive(10000, 5) << std::endl;
    std::cout << getLastAlive(10000, 6) << std::endl;
    std::cout << getLastAlive(10000, 7) << std::endl;
    std::cout << getLastAlive(10000, 8) << std::endl;
    std::cout << getLastAlive(10000, 9) << std::endl;
    std::cout << getLastAlive(10000, 111) << std::endl;
    std::cout << getLastAlive(10000, 323) << std::endl;
    std::cout << getLastAlive(10000, 783) << std::endl;
    std::cout << getLastAlive(10000, 3888) << std::endl;
    std::cout << getLastAlive(10000, 3876) << std::endl;
    std::cout << getLastAlive(10000, 38) << std::endl;
    std::cout << getLastAlive(10000, 18) << std::endl;
    std::cout << getLastAlive(10000, 63) << std::endl;
    std::cout << getLastAlive(10000, 100000) << std::endl;


/*    Buffer * buf = new Buffer(10);
    for (int i = 0; i != 10; i++) {
        buf->addElem(i);
    }

    buf->deleteElemOnIndex(8);
    for (int i = 0; i != 9; i++) {
        std::cout << buf->getElem(i) << std::endl;
    }*/

}
