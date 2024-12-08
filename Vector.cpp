#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

template<typename T>
class Vector {
    T *data;
    int capacity;
    int size;

    void resize(int newCapacity) {
        T *newData = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Vector() : data(nullptr), capacity(0), size(0) {
    }

    explicit Vector(int initialSize) : capacity(initialSize), size(initialSize) {
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = T();
        }
    }

    ~Vector() {
        delete[] data;
    }

    Vector(const Vector &other) : data(new T[other.capacity]), capacity(other.capacity), size(other.size) {
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    Vector &operator=(const Vector &other) {
        if (this == &other) return *this;
        delete[] data;
        data = new T[other.capacity];
        capacity = other.capacity;
        size = other.size;
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }

    T &operator[](int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of range" << endl;
            exit(1);
        }
        return data[index];
    }

    const T &operator[](int index) const {
        if (index < 0 || index >= size) {
            cout << "Index out of range" << endl;
            exit(1);
        }
        return data[index];
    }

    int getSize() const { return size; }

    int getCapacity() const { return capacity; }

    bool isEmpty() const { return size == 0; }

    void push_back(const T &value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    T pop() {
        if (isEmpty()) {
            cout << "Pop from empty vector" << endl;
            exit(1);
        }
        return data[--size];
    }

    void insert(int index, const T &value) {
        if (index < 0 || index > size) {
            cout << "Index out of range" << endl;
            exit(1);
        }
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        for (int i = size; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }

    void erase(const int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of range" << endl;
            exit(1);
        }
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }

    void clear() {
        size = 0;
    }

    int find(const T &value) const {
        for (int i = 0; i < size; i++) {
            if (data[i] == value) return i;
        }
        return -1;
    }

    bool contains(const T &value) const {
        return find(value) != -1;
    }

    void display() const {
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};
