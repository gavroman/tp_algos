/* 3_3. Реализовать очередь с помощью двух стеков.
 * Использовать стек, реализованный с помощью динамического буфера.
 * Требования: Очередь должна быть реализована в виде класса.
 * Стек тоже должен быть реализован в виде класса.
 */

#include <sstream>
#include <iostream>
#include <assert.h>

class Stack {
 public:
    Stack() :
        initialSize(4),
        size(initialSize),
        realSize(0),
        data(new int[size]) {}

    ~Stack() {
        delete[] data;
    }

    int getSize() {
        return realSize;
    }

    int getElem() {
        return data[--realSize];
    }

    void addElem(const int elem) {
        if(realSize == size) {
            grow();
        }
        data[realSize++] = elem;
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

class Queue {
 public:
    Queue() :
    inputStack(),
    outputStack() {}
    ~Queue() {}

    bool runCommand(int command, int value) {
        int deqValue = -1; // если очередь пустая, то значение должно быть -1
        switch (command) {
            case 2: // pop front
                if (!isEmpty()) {
                    deqValue = popFront();
                }
                if (deqValue != value) {
                    return false;
                }
                break;
            case 3: // push back
                pushBack(value);
                break;
            default:
                return false;
        }
        return true;
    }

 private:
    bool isEmpty() {
        return (inputStack.getSize() == 0 && outputStack.getSize() == 0);
    }

    void pushBack(const int elem) {
        inputStack.addElem(elem);
    }

    int popFront() {
        if (!outputStack.getSize() && inputStack.getSize()) {
            stackExchange();
        }
        return outputStack.getElem();
    }

    void stackExchange() {
        int stackSize = inputStack.getSize();
        for (int i = 0; i != stackSize; i++) {
            // Удаляем последний элемент из inputStack, и добавляем его в outputStack
            outputStack.addElem(inputStack.getElem());
        }
    }

    Stack inputStack;
    Stack outputStack;
};

int main(int argc, char const *argv[]) {
    int commandsCount = 0;
    std::cin >> commandsCount;
    assert(commandsCount >= 0 && commandsCount <= 1000000);
    Queue queue;
    for (int i = 0; i != commandsCount; i++) {
        int command = 0;
        int value = 0;
        std::cin >> command >> value;
        if (!queue.runCommand(command, value)) {
            std::cout << "NO" << std::endl;
            return 0;
        }
    }
    std::cout << "YES" << std::endl;
    return 0;
}