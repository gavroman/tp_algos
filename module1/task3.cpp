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
        // int deletedElem = data[--realSize];
        // int * newData = new int[realSize];

        // for (int i = 0; i != realSize; i++) {
        //     newData[i] = data[i];
        // }

        // delete[] data;
        // data = newData;
        // return deletedElem;
        return data[--realSize];
    }

    void addElem(const int elem) {
        if(realSize == size) {
            grow();
        }
        data[realSize++] = elem;
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

class Queue {
 public:
    Queue() :
    inputStack(),
    outputStack() {}
    ~Queue() {}

    bool isEmpty() {
        return (!inputStack.getSize() && !outputStack.getSize());
    }

    void pushBack(const int elem) {
        inputStack.addElem(elem);

        // std::cout << "inputStack Size " << inputStack.getSize() << std::endl;
        // inputStack.print();
        // std::cout << "outputStack Size " << outputStack.getSize() << std::endl;
        // outputStack.print();
    }

    int popFront() {
        if (!outputStack.getSize() && inputStack.getSize()) {
            stackExchange();
        }
        int retValue = outputStack.getElem();
        // std::cout << "inputStack Size " << inputStack.getSize() << std::endl;
        // inputStack.print();
        // std::cout << "outputStack Size " << outputStack.getSize() << std::endl;
        // outputStack.print();
        return retValue;
    }

 private:
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


int run(std::istream& input, std::ostream& output) {
    Queue queue;
    int commandsCount = 0;
    input >> commandsCount;
    assert(commandsCount >= 0 && commandsCount <= 1000000);
    int i = 0;
    for (i = 0; i != commandsCount; i++) {
        int command = 0;
        int value = 0;
        input >> command >> value;
        int deqValue = -1; // если очередь пустая, то значение должно быть -1
        switch (command) {
            case 2:
                if (!queue.isEmpty()) {
                    deqValue = queue.popFront();
                }
                if (deqValue != value) {
                    output << "NO" << std::endl;
                    return i;
                }
                break;
            case 3:
                queue.pushBack(value);
                break;
            default:
                output << "NO" << std::endl;
                return i;
        }
    }
    output << "YES" << std::endl;

    return i;
}

void test() {
    // {
    //     std::stringstream input;
    //     std::stringstream output;

    //     input << "3" << std::endl;
    //     input << "3 44" << std::endl;
    //     input << "3 50" << std::endl;
    //     input << "2 44" << std::endl;
    //     run(input, output);
    //     //std::string s = output.str();
    //     //for (int i = 0; i < s.size(); ++i) {
    //     //    std::cout << std::hex << (unsigned int)s[i] << std::endl;
    //     //}
    //     //std::cout << output.str() << std::endl;
    //     assert(output.str() == "YES\n");
    // }

    // // тестируем пустой ввод

    // // тестируем пукт условия "Если команда pop вызвана для пустой структуры данных, то ожидается “-1”."
    // {
    //     std::stringstream input;
    //     std::stringstream output;

    //     input << "1" << std::endl;
    //     input << "2 -1" << std::endl;
    //     run(input, output);

    //     assert(output.str() == "YES\n");
    // }
    // // тестируем на вставку, а потом извлечение большого кол-ва элементов
    // {
    //     std::stringstream input;
    //     std::stringstream output;
    //     int count = 10000; // можно даже больше взять
    //     int commands_count = count * 2 + 1 ;
    //     input << commands_count << std::endl;
    //     for (int i = 0; i < count; i++) {
    //         input << "3 " << i << std::endl;
    //     }
    //     for (int i = 0; i < count; i++) {
    //         input << "2 " << i << std::endl;
    //     }
    //     input << "2 -1" << std::endl;
    //     int res = run(input, output);

    //     assert(output.str() == "YES\n");

    //     // проверим, что обработали столько команд, сколько ожидали
    //     assert(res == commands_count );
    // }

    // // проверим на последовательную вставку/извлечение большого кол-ва элементов
    // {
    //     std::stringstream input;
    //     std::stringstream output;
    //     int count = 10000;
    //     input << count * 2 + 1 << std::endl;
    //     for (int i = 0; i < count; i++) {
    //         input << "3 " << i << std::endl;
    //         input << "2 " << i << std::endl;
    //     }
    //     input << "2 -1" << std::endl;
    //     run(input, output);

    //     assert(output.str() == "YES\n");
    // }

    // // проверим только извлечение
    // {
    //     std::stringstream input;
    //     std::stringstream output;
    //     int count = 10000;
    //     input << count << std::endl;
    //     for (int i = 0; i < count; i++) {
    //         input << "3 " << i << std::endl;
    //     }
    //     run(input, output);

    //     assert(output.str() == "YES\n");
    // }

    // // запрашиваем элементы из очереди в неправильном порядке
    // {
    //     std::stringstream input;
    //     std::stringstream output;
    //     int count = 10000;
    //     input << count * 2 << std::endl;
    //     for (int i = 0; i < count; i++) {
    //         input << "3 " << i << std::endl;
    //     }
    //     for (int i = count; i >= 0; i--) {
    //         input << "2 " << i << std::endl;
    //     }
    //     run(input, output);

    //     assert(output.str() == "NO\n");
    // }
    // {
    //     std::stringstream input;
    //     std::stringstream output;

    //     run(input, output);

    //     assert(output.str() == "YES\n");
    // }
    {
        std::stringstream input;
        std::stringstream output;

        input << "2" << std::endl;
        input << "3 1" << std::endl; // push
        input << "2 1" << std::endl;
        input << "3 3" << std::endl;
        input << "2 1" << std::endl;
        input << "2 2" << std::endl;
        input << "2 2" << std::endl;
        input << "2 2" << std::endl;
        input << "2 2" << std::endl;

        run(input, output);

        assert(output.str() == "YES\n");
    }
}

int main(int argc, char const *argv[]) {

    // test();

    run(std::cin, std::cout);

    return 0;
}