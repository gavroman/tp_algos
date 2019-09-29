#include <iostream>
#include <sstream>
#include <iomanip>
#include <assert.h>

class Queue {
    struct Node {
        int data;
        Node* next;

        explicit Node(int d) : data(d), next(nullptr)  {}
    };
public:
    Queue() : head(nullptr), tail(nullptr) { }
    ~Queue() {
        while (!IsEmpty()) {
            Dequeue();
        }
    }

    Queue(const Queue&) = delete;
    Queue& operator= (const Queue&) = delete;

    bool IsEmpty() const {
        return head == tail && head == nullptr;
    }

    void Enqueue(int value) {
        Node* node = new Node(value);

        if (tail == nullptr) {
            tail = head = node;
            return;
        }
        tail->next = node;
        tail = node;

    }

    int Dequeue() {
        int result = head->data;

        Node* tmp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }

        delete tmp;

        return result;
    }
private:
    Node* head;
    Node* tail;
};

// тестируем саму очередб
void testQueue() {
    Queue queue;

    // после создания должна быть пустой
    assert(queue.IsEmpty());
    // кладем в очередь 1000 элементов
    for (int i = 0; i < 1000; i++) {
        queue.Enqueue(i);
    }
    // после предыдущего шага очередь должнать быть НЕ пустой
    assert(!queue.IsEmpty());
    // проверяем, что достаем элементы в том же порядке, в каком клали
    for (int i = 0; i < 1000; i++) {
        int res = queue.Dequeue();
        assert(i == res);
    }
    // должны были все достать
    assert(queue.IsEmpty());

    // снова положим элементы в очередь. При выходе из функции сработает деструктор
    for (int i = 0; i < 1000; i++) {
        queue.Enqueue(i);
    }
}

int run(std::istream& input, std::ostream& output) {
    Queue queue;

    int commands_count = 0;
    // считываем количество команд
    input >> commands_count;
    int i = 0;
    for (i = 0; i < commands_count; i++) {
        int command = 0;
        int value = 0;
        // считываем команду
        input >> command >> value;
        int deq_value = -1; // если очередь пустая, то значение должно быть -1
        switch (command) {
            case 2:
                if (!queue.IsEmpty()) {
                    deq_value = queue.Dequeue();
                }
                if (deq_value != value) {
                    output << "NO" << std::endl;
                    return i;
                }
                break;
            case 3:
                queue.Enqueue(value);
                break;
            default:
                output << "NO" << std::endl;
                return i;
        }
    }
    output << "YES" << std::endl;
    return i;
}

// тестируем основную логику
void testLogic() {

    // пример из условия задачи
    {
        std::stringstream input;
        std::stringstream output;

        input << "3" << std::endl;
        input << "3 44" << std::endl;
        input << "3 50" << std::endl;
        input << "2 44" << std::endl;
        run(input, output);
        //std::string s = output.str();
        //for (int i = 0; i < s.size(); ++i) {
        //    std::cout << std::hex << (unsigned int)s[i] << std::endl;
        //}
        //std::cout << output.str() << std::endl;
        assert(output.str() == "YES\n");
    }

    // тестируем пустой ввод
    {
        std::stringstream input;
        std::stringstream output;

        run(input, output);

        assert(output.str() == "YES\n");
    }

    // тестируем пукт условия "Если команда pop вызвана для пустой структуры данных, то ожидается “-1”."
    {
        std::stringstream input;
        std::stringstream output;

        input << "1" << std::endl;
        input << "2 -1" << std::endl;
        run(input, output);

        assert(output.str() == "YES\n");
    }
    // тестируем на вставку, а потом извлечение большого кол-ва элементов
    {
        std::stringstream input;
        std::stringstream output;
        int count = 10000; // можно даже больше взять
        int commands_count = count * 2 + 1 ;
        input << commands_count << std::endl;
        for (int i = 0; i < count; i++) {
            input << "3 " << i << std::endl;
        }
        for (int i = 0; i < count; i++) {
            input << "2 " << i << std::endl;
        }
        input << "2 -1" << std::endl;
        int res = run(input, output);

        assert(output.str() == "YES\n");

        // проверим, что обработали столько команд, сколько ожидали
        assert(res == commands_count );
    }

    // проверим на последовательную вставку/извлечение большого кол-ва элементов
    {
        std::stringstream input;
        std::stringstream output;
        int count = 10000;
        input << count * 2 + 1 << std::endl;
        for (int i = 0; i < count; i++) {
            input << "3 " << i << std::endl;
            input << "2 " << i << std::endl;
        }
        input << "2 -1" << std::endl;
        run(input, output);

        assert(output.str() == "YES\n");
    }

    // проверим только извлечение
    {
        std::stringstream input;
        std::stringstream output;
        int count = 10000;
        input << count << std::endl;
        for (int i = 0; i < count; i++) {
            input << "3 " << i << std::endl;
        }
        run(input, output);

        assert(output.str() == "YES\n");
    }

    // запрашиваем элементы из очереди в неправильном порядке
    {
        std::stringstream input;
        std::stringstream output;
        int count = 10000;
        input << count * 2 << std::endl;
        for (int i = 0; i < count; i++) {
            input << "3 " << i << std::endl;
        }
        for (int i = count; i >= 0; i--) {
            input << "2 " << i << std::endl;
        }
        run(input, output);

        assert(output.str() == "NO\n");
    }

}

int main(int argc, const char * argv[]) {
    //testQueue();
    //testLogic();
    //std::cout << "OK" << std::endl;
    //return 0;
    run(std::cin, std::cout);
    return 0;
}