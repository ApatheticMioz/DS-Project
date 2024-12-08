#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

template<typename T>
class Stack {
    Vector<T> data;
public:
    void push(const T& value) {
        data.push_back(value);
    }

    T pop() {
        if (data.isEmpty()) {
            cout << "Stack is empty!" << endl;
            exit(1);
        }
        T value = data.pop();
        return value;
    }

    bool isEmpty() const {
        return data.isEmpty();
    }

    int size() const {
        return data.getSize();
    }
};
