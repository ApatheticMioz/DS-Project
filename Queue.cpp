#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

template<typename T>
/**
 * @class Queue
 * @brief A template class implementing a queue data structure using a vector as storage.
 *
 * @tparam T The type of the elements stored in the queue.
 */
class Queue {
    /**
     * A vector container to store elements of the queue.
     * Utilizes a dynamic array for efficient element management.
     */
    Vector<T> data;
    /**
     * @brief Index indicating the front element in the queue.
     * @details Used to track the position of the first element in the queue for dequeuing.
     * Automatically adjusted when elements are dequeued to maintain efficient access.
     */
    int frontIdx;

    /**
     * Constructs a Queue object and initializes the front index to zero.
     *
     * @return A new instance of a Queue with an initialized front index.
     */
public:
    Queue() : frontIdx(0) {}

    /**
     * Adds a new element to the end of the queue.
     *
     * @param value The element to be added to the queue.
     */
    void enqueue(const T &value) {
        data.push_back(value);
    }

    /**
     * Removes and returns the element at the front of the queue.
     * If the queue is empty, the program will terminate with an error message.
     *
     * @return The element at the front of the queue.
     */
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

    /**
     * Retrieves the front element of the queue without removing it.
     * If the queue is empty, an error message is displayed and the program exits.
     *
     * @return The element at the front of the queue.
     */
    T front() const {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            exit(1);
        }

        return data[frontIdx];
    }

    /**
     * Checks if the queue is empty.
     * @return True if the queue is empty, false otherwise.
     */
    bool isEmpty() const {
        return frontIdx >= data.getSize();
    }

    /**
     * Calculates the number of elements currently in the queue.
     *
     * @return The number of elements in the queue from the front index to the end.
     */
    int size() const {
        return data.getSize() - frontIdx;
    }

    /**
     * Displays the content of the queue starting from frontIdx to the end in a comma-separated format enclosed in brackets.
     * The output is printed to the standard console.
     */
    void display() const {
        cout << "[";
        for (int i = frontIdx; i < data.getSize(); i++) {
            cout << data[i];
            if (i < data.getSize() - 1) cout << ", ";
        }

        cout << "]" << endl;
    }
};
