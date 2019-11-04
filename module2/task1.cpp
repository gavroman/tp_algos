/*
 * Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
 * Хранимые строки непустые и состоят из строчных латинских букв. Хеш-функция строки должна быть реализована с
 * помощью вычисления значения многочлена методом Горнера. Начальный размер таблицы должен быть равным 8-ми.
 * Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
 * Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и
 * проверки принадлежности данной строки множеству. Для разрешения коллизий используйте двойное хеширование.
 */

#include <iostream>
#include <vector>
#include <assert.h>
#include <string>
#include <sstream>

template<class T, class H1, class H2>
class HashTable {
public:
    HashTable(const H1& hasher, const H2& hasherProbe, const T& emptyValue ,const T& deletedValue ) :
        hasher(hasher),
        hasherProbe(hasherProbe),
        table(8, emptyValue),
        emptyValue(emptyValue),
        deletedValue(deletedValue),
        keysCount(0) {
    }

    bool add(const T& key) {
        if (table.size() / 4 <= keysCount / 3 ) {
            growTable();
        }
        int hash1 = hasher(key) % table.size();
        if (table[hash1] == emptyValue || table[hash1] == deletedValue) {
            table[hash1] = key;
            keysCount++;
            return true;
        }
        if (table[hash1] == key) {
            return false;
        }
        //  if (table[hash1] != key)
        int hash2 = hasherProbe(key) % table.size();
        for (int i = 1; i != table.size(); i++) {
            int probeIndex = (hash1 + i * hash2 ) % table.size();
            if (table[probeIndex] == key) {
                return false;
            }
            if (table[probeIndex] == emptyValue || table[probeIndex] == deletedValue) {
                table[probeIndex] = key;
                keysCount++;
                return true;
            }
        }
        return false;
    }

    bool has(const T& key) {
        int hash1 = hasher(key) % table.size();
        if (table[hash1] == key) {
            return true;
        }
        if (table[hash1] == emptyValue) {
            return false;
        }
        //  if (table[hash1] == deletedValue && table[hash1] != key)
        int hash2 = hasherProbe(key) % table.size();
        for (int i = 1; i != table.size(); i++) {
            int probeIndex = (hash1 + i * hash2 ) % table.size();
            if (table[probeIndex] == key) {
                return true;
            }
            if (table[probeIndex] == emptyValue) {
                return false;
            }
        }
        return false;
    }

    bool remove(const T& key) {
        int hash1 = hasher(key) % table.size();
        if (table[hash1] == key) {
            table[hash1] = deletedValue;
            return true;
        }
        if (table[hash1] == emptyValue) {
            return false;
        }
        //  if (table[hash1] == deletedValue && table[hash1] != key)
        int hash2 = hasherProbe(key) % table.size();
        for (int i = 1; i != table.size(); i++) {
            int probeIndex = (hash1 + i * hash2 ) % table.size();
            if (table[probeIndex] == key) {
                table[probeIndex] = deletedValue;
                return true;
            }
            if (table[probeIndex] == emptyValue) {
                return false;
            }
        }
        return false;
    }

    void print() {
        std::cout << "+++++++++++++++++++++++" << std::endl;
        for (int i = 0; i != table.size(); i++) {
            std::cout << i << "   " << table[i] << std::endl;
        }
        std::cout << "+++++++++++++++++++++++" << std::endl;
    }

private:
    H1 hasher;
    H2 hasherProbe;
    std::vector<T> table;
    T emptyValue;
    T deletedValue;
    int keysCount;

    void growTable() {
        std::vector<T> newTable(table.size() * 2, emptyValue);
        for (int i = 0; i != table.size(); i++) {
            if (table[i] != emptyValue && table[i] != deletedValue) {
                int newHash1 = hasher(table[i]) % newTable.size();
                if (newTable[newHash1] == emptyValue) {
                    newTable[newHash1] = table[i];
                } else {
                    int newHash2 = hasherProbe(table[i]) % newTable.size();
                    for (int j = 1; j != newTable.size(); j++) {
                        int probeIndex = (newHash1 + j * newHash2 ) % newTable.size();
                        if (newTable[probeIndex] == emptyValue) {
                            newTable[probeIndex] = table[i];
                            break;
                        }
                    }
                }
            }
        }
        table = std::move(newTable);
    }
};

struct Hasher {
    int operator()(const std::string& key) const {
        int hash = 0;
        for (int i = 0; i < key.length(); i++)
            hash = hash * 7 + key[i];
        return hash;
    }
};

struct HasherProbe {
    int operator()(const std::string& key) const {
        int hash = 0;
        for (int i = 0; i < key.length(); i++)
            hash = hash * 5 + key[i];
        return hash * 2 + 1;
    }
};


void run(std::istream & input) {
    Hasher h1;
    HasherProbe h2;

    std::string emptyValue = "";
    std::string deletedValue = "_-_-_";
    HashTable<std::string, Hasher, HasherProbe> table(h1, h2, emptyValue, deletedValue);

    char operation = 0;
    std::string key;
    while (input >> operation >> key) {
        if (operation == '+') {
            std::cout << (table.add(key) ? "OK" : "FAIL") << std::endl;
        }
        if (operation == '?') {
            std::cout << (table.has(key) ? "OK" : "FAIL") << std::endl;
        }
        if (operation == '-') {
            std::cout << (table.remove(key) ? "OK " : "FAIL ") << key << std::endl;
        }
        if (operation == 'p') {
            table.print();
        }
    }
}

void test() {
    {
        std::stringstream input;

        input << "+ 1" << std::endl;
        input << "+ 2" << std::endl;
        input << "+ 3" << std::endl;
        input << "+ 4" << std::endl;
        input << "+ 5" << std::endl;
        input << "+ 6" << std::endl;
        input << "+ 7" << std::endl;
        input << "+ 8" << std::endl;
        input << "+ 9" << std::endl;
        input << "+ qwer" << std::endl;
        input << "+ fsedgg1" << std::endl;
        input << "+ fsedgg2" << std::endl;
        input << "+ fsedgg3" << std::endl;
        input << "+ fsedgg4" << std::endl;
        input << "+ fsedgg5" << std::endl;
        input << "+ fsedgg6" << std::endl;
        input << "+ fsedgg7" << std::endl;
        input << "+ fsedgg8" << std::endl;
        input << "+ fsg9" << std::endl;
        input << "+ 1ofr" << std::endl;
        input << "+ 2ofr" << std::endl;
        input << "+ 3ofr" << std::endl;
        input << "+ 4ofr" << std::endl;
        input << "+ 5ofr" << std::endl;
        input << "+ 6ofr" << std::endl;
        input << "+ 7ofr" << std::endl;
        input << "+ 8ofr" << std::endl;
        input << "+ 9ofr" << std::endl;
        input << "+ qw" << std::endl;
        input << "+ fsgg1" << std::endl;
        input << "+ fsgg2" << std::endl;
        input << "+ fsgg3" << std::endl;
        input << "+ fsgg4" << std::endl;
        input << "+ fsgg5" << std::endl;
        input << "+ fsgg6" << std::endl;
        input << "+ fsgg7" << std::endl;
        input << "+ fsgg8" << std::endl;
        input << "+ fg9" << std::endl;
        input << "p d" << std::endl;
        input << "? 7" << std::endl;

        input << "- 1" << std::endl;
        input << "- 2" << std::endl;
        input << "- 3" << std::endl;
        input << "- 4" << std::endl;
        input << "- 5" << std::endl;
        input << "- 6" << std::endl;
        input << "- 7" << std::endl;
        input << "- 8" << std::endl;
        input << "- 9" << std::endl;
        input << "- qwer" << std::endl;
        input << "- fsedgg1" << std::endl;
        input << "- fsedgg2" << std::endl;
        input << "- fsedgg3" << std::endl;
        input << "- fsedgg4" << std::endl;
        input << "- fsedgg5" << std::endl;
        input << "- fsedgg6" << std::endl;
        input << "- fsedgg7" << std::endl;
        input << "- fsedgg8" << std::endl;
        input << "- fsg9" << std::endl;
        input << "- 1ofr" << std::endl;
        input << "- 2ofr" << std::endl;
        input << "- 3ofr" << std::endl;
        input << "- 4ofr" << std::endl;
        input << "- 5ofr" << std::endl;
        input << "- 6ofr" << std::endl;
        input << "- 7ofr" << std::endl;
        input << "- 8ofr" << std::endl;
        input << "- 9ofr" << std::endl;
        input << "- qw" << std::endl;
        input << "- fsgg1" << std::endl;
        input << "- fsgg2" << std::endl;
        input << "- fsgg3" << std::endl;
        input << "- fsgg4" << std::endl;
        input << "- fsgg5" << std::endl;
        input << "- fsgg6" << std::endl;
        input << "- fsgg7" << std::endl;
        input << "- fsgg8" << std::endl;
        input << "- fg9" << std::endl;
        input << "p d" << std::endl;
        run(input);
    }
}

int main(int argc, char const *argv[]) {
    test();
    return 0;
}
