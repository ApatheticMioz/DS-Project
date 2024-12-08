#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

template<typename T>
/**
 * A generic stack implementation using a vector as the underlying container.
 */
class Stack {
    /**
     * Internal storage for elements in the stack.
     * Utilizes a dynamic array to support stack operations like push and pop.
     */
    Vector<T> data;
    /**
     * Adds an element to the top of the stack.
     *
     * @param value The value to be added to the stack.
     */
public:
    void push(const T& value) {
        data.push_back(value);
    }

    /**
     * Removes and returns the top element from the stack.
     *
     * If the stack is empty, an error message is displayed and the program exits.
     *
     * @return The top element of the stack.
     */
    T pop() {
        if (data.isEmpty()) {
            cout << "Stack is empty!" << endl;
            exit(1);
        }
        T value = data.pop();
        return value;
    }

    /**
     * @brief Checks if the stack is empty.
     *
     * This method provides a way to verify whether there are any elements
     * currently stored in the stack. It utilizes the underlying data container's
     * isEmpty method to determine the emptiness condition.
     *
     * @return True if the stack has no elements, false otherwise.
     */
    bool isEmpty() const {
        return data.isEmpty();
    }

    /**
     * Returns the number of elements in the stack.
     *
     * @return The current size of the stack.
     */
    int size() const {
        return data.getSize();
    }
};
