#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

template<typename T>
class Queue {
    Vector<T> data;
    int frontIdx;

public:
    Queue() : frontIdx(0) {}

    void enqueue(const T &value) {
        data.push_back(value);
    }

    T dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            exit(1);
        }

        T frontElement = data[frontIdx];
        frontIdx++;
        if (frontIdx > data.getSize() / 2) {
            Vector<T> newData;
            for (int i = frontIdx; i < data.getSize(); i++) {
                newData.push_back(data[i]);
            }
            data = newData;
            frontIdx = 0;
        }

        return frontElement;
    }

    T front() const {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            exit(1);
        }

        return data[frontIdx];
    }

    bool isEmpty() const {
        return frontIdx >= data.getSize();
    }

    int size() const {
        return data.getSize() - frontIdx;
    }

    void display() const {
        cout << "[";
        for (int i = frontIdx; i < data.getSize(); i++) {
            cout << data[i];
            if (i < data.getSize() - 1) cout << ", ";
        }

        cout << "]" << endl;
    }
};
