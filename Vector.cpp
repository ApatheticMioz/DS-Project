#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

template<typename T>
/**
 * A dynamic array implementation for storing elements of type T.
 */
class Vector {
    /**
     * Pointer to the dynamic array holding the elements of the Vector.
     * Allows for flexible resizing and element access.
     */
    T *data;
    /**
     * Represents the current maximum number of elements that can be held in the vector
     * without requiring a resize operation.
     */
    int capacity;
    /**
     * Represents the current number of elements stored in the Vector.
     */
    int size;

    /**
     * Resizes the internal storage of the vector to the specified new capacity.
     *
     * @param newCapacity The new capacity for the vector's internal storage. Must be greater than or equal to the current size.
     */
    void resize(int newCapacity) {
        T *newData = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    /**
     * Constructs a Vector with default settings, initializing the data pointer to nullptr,
     * and both capacity and size to zero.
     *
     * @return An instance of the Vector class with no elements and zero capacity.
     */
public:
    Vector() : data(nullptr), capacity(0), size(0) {
    }

    /**
     * Constructs a Vector with the specified initial size.
     * Allocates memory for the elements and initializes each element to the default value of the type T.
     *
     * @param initialSize The initial size and capacity for the vector.
     *                    Determines how many elements the vector can initially hold.
     * @return A newly constructed Vector object with allocated storage.
     */
    explicit Vector(int initialSize) : capacity(initialSize), size(initialSize) {
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = T();
        }
    }

    /**
     * Destructor for the Vector class.
     *
     * This function is responsible for deallocating the dynamic array
     * used to store the elements of the Vector, thus preventing memory leaks.
     */
    ~Vector() {
        delete[] data;
    }

    /**
     * Copy constructor for the Vector class. Initializes a new Vector object
     * by copying data from another Vector object.
     *
     * @param other The Vector object to copy from.
     * @return A new instance of Vector initialized with values from the given Vector.
     */
    Vector(const Vector &other) : data(new T[other.capacity]), capacity(other.capacity), size(other.size) {
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    /**
     * Assigns the contents of another Vector object to this Vector object.
     *
     * This operator performs a deep copy of the data from the other Vector
     * to this Vector, reallocating memory as needed.
     *
     * @param other The Vector object to copy the data from.
     * @return A reference to this Vector object after assignment.
     */
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

    /**
     * Provides access to the element at the specified index.
     *
     * @param index The index of the element to be accessed. Must be within the range [0, size - 1].
     * @return A reference to the element at the given index.
     * @throws Exits the program with an error message if the index is out of range.
     */
    T &operator[](int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of range" << endl;
            exit(1);
        }
        return data[index];
    }

    /**
     * Returns a const reference to the element at the specified index.
     * If the index is out of range, prints an error message and exits.
     *
     * @param index The index of the element to retrieve. Must be in the range [0, size).
     * @return A const reference to the element at the specified index.
     */
    const T &operator[](int index) const {
        if (index < 0 || index >= size) {
            cout << "Index out of range" << endl;
            exit(1);
        }
        return data[index];
    }

    /**
     * Returns the current number of elements in the vector.
     * @return The size of the vector.
     */
    int getSize() const { return size; }

    /**
     * Returns the current capacity of the vector.
     *
     * @return The capacity of the vector.
     */
    int getCapacity() const { return capacity; }

    /**
     * Checks if the vector is empty.
     * @return True if the vector contains no elements, false otherwise.
     */
    bool isEmpty() const { return size == 0; }

    /**
     * Adds a new element to the end of the vector.
     * If the current size equals the capacity, the vector's capacity is doubled.
     *
     * @param value The element to be added to the end of the vector.
     */
    void push_back(const T &value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    /**
     * Removes the last element from the vector and returns it. If the vector is empty,
     * the operation results in termination of the program.
     * @return The last element in the vector.
     */
    T pop() {
        if (isEmpty()) {
            cout << "Pop from empty vector" << endl;
            exit(1);
        }
        return data[--size];
    }

    /**
     * Inserts a value at the specified index in a vector. The elements at the
     * specified index and beyond are shifted to the right.
     *
     * @param index Position at which the value should be inserted. Must be
     *        between 0 and the current size of the vector, inclusive.
     * @param value The value to insert into the vector.
     */
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

    /**
     * Removes the element at the specified index from the vector.
     *
     * @param index The index of the element to be removed.
     *              The index must be in the range [0, size-1].
     *              If the index is out of range, the program will terminate with an error message.
     */
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

    /**
     * Clears the contents of the vector, setting the size to zero.
     * The capacity remains unchanged.
     */
    void clear() {
        size = 0;
    }

    /**
     * Searches for the first occurrence of the specified value in the vector.
     * @param value The value to search for within the vector.
     * @return The index of the first occurrence of the value if found; otherwise, -1.
     */
    int find(const T &value) const {
        for (int i = 0; i < size; i++) {
            if (data[i] == value) return i;
        }
        return -1;
    }

    /**
     * Checks whether a specified value exists in the vector.
     *
     * @param value The value to search for within the vector.
     * @return True if the vector contains the value, false otherwise.
     */
    bool contains(const T &value) const {
        return find(value) != -1;
    }

    /**
     * Displays the elements of the vector in a comma-separated format enclosed in square brackets.
     *
     * This method outputs the contents of the vector to the standard output stream.
     * It iterates through the vector and prints each element followed by a comma,
     * except for the last element which is followed by a closing bracket.
     */
    void display() const {
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};
