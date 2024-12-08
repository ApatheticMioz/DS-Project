#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

template<typename T>
/**
 * Represents a node in a heap data structure.
 *
 * @tparam T Type of the value contained in the node.
 */
class HeapNode {
    /**
     * Represents the value stored in a node of the heap.
     * It is of a generic type `T` and can hold any comparable value.
     */
public:
    T value;
    /**
     * @brief Pointer to the left child node.
     * @details Represents the left child in the binary heap structure, used for navigation and manipulation within the heap.
     */
    HeapNode *left;
    /**
     * Pointer to the right child node in a binary heap structure.
     * Used to represent and navigate the right subtree of the current node.
     */
    HeapNode *right;
    /**
     * Pointer to the parent node in the heap.
     * Used to navigate from a child node to its parent.
     */
    HeapNode *parent;

    /**
     * Constructs a new HeapNode with the given value and initializes all pointers to nullptr.
     *
     * @param val The value to be stored in the newly created heap node.
     * @return An instance of HeapNode with specified value and null child and parent pointers.
     */
    explicit HeapNode(T val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {
    }
};

template<typename T>
/**
 * Represents a generic MinHeap data structure.
 * Provides methods to insert elements, extract the minimum element,
 * and perform heap operations such as heapify up and heapify down.
 */
class MinHeap {
    /**
     * Pointer to the root node of the MinHeap.
     * Represents the smallest element in the heap.
     * Used as the starting point for all heap operations.
     */
    HeapNode<T> *root;
    /**
     * Represents the total number of nodes currently present in the MinHeap.
     * Used to manage heap operations such as insertions and removals.
     */
    int nodeCount = 0;

    /**
     * Swaps the values of two heap nodes.
     *
     * @param a Pointer to the first heap node to be swapped.
     * @param b Pointer to the second heap node to be swapped.
     */
    void swap(HeapNode<T> *a, HeapNode<T> *b) {
        T temp = a->value;
        a->value = b->value;
        b->value = temp;
    }

    /**
     * Restores the min-heap property by moving the specified node down the tree.
     * Compares the node with its children and swaps it with the smallest if necessary.
     * Continues the process recursively until the node is in the correct position.
     *
     * @param node A pointer to the heap node that needs to be heapified down.
     */
    void heapifyDown(HeapNode<T> *node) {
        if (!node) return;
        HeapNode<T> *smallest = node;

        if (node->left && node->left->value < smallest->value) {
            smallest = node->left;
        }

        if (node->right && node->right->value < smallest->value) {
            smallest = node->right;
        }

        if (smallest != node) {
            swap(node, smallest);
            heapifyDown(smallest);
        }
    }

    /**
     * Restores the heap property by moving a node up the tree as long as it is smaller than its parent.
     *
     * @param node The heap node to be adjusted upwards.
     */
    void heapifyUp(HeapNode<T> *node) {
        if (node->parent && node->value < node->parent->value) {
            swap(node, node->parent);
            heapifyUp(node->parent);
        }
    }

    /**
     * Constructs an empty MinHeap.
     * @return A new MinHeap object with an initialized empty root.
     */
public:
    MinHeap() : root(nullptr) {}

    /**
     * Inserts a new element into the heap while maintaining the heap property.
     *
     * @param value The value to be inserted into the min-heap.
     */
    void insert(const T &value) {
        auto *newNode = new HeapNode<T>(value);

        if (!root) {
            root = newNode;
        } else {
            Queue<HeapNode<T> *> nodeQueue;
            nodeQueue.enqueue(root);
            while (!nodeQueue.isEmpty()) {
                HeapNode<T> *current = nodeQueue.front();
                nodeQueue.dequeue();

                if (!current->left) {
                    current->left = newNode;
                    newNode->parent = current;
                    break;
                }

                if (!current->right) {
                    current->right = newNode;
                    newNode->parent = current;
                    break;
                }

                nodeQueue.enqueue(current->left);
                nodeQueue.enqueue(current->right);
            }
        }

        heapifyUp(newNode);
        nodeCount++;
    }

    /**
     * Extracts and returns the minimum element from the heap.
     * Removes the root of the heap and restructures the heap to maintain the min-heap property.
     *
     * @return The minimum element in the heap.
     * @throws std::runtime_error if the heap is empty.
     */
    T extractMin() {
        if (!root) {
            cout << "Heap is empty!" << endl;
            exit(1);
        }

        T minValue = root->value;
        if (nodeCount == 1) {
            delete root;
            root = nullptr;
            nodeCount--;
            return minValue;
        }

        HeapNode<T> *lastNode = getLastNode();
        root->value = lastNode->value;
        if (lastNode->parent->left == lastNode) {
            lastNode->parent->left = nullptr;
        } else {
            lastNode->parent->right = nullptr;
        }

        delete lastNode;
        heapifyDown(root);
        nodeCount--;

        return minValue;
    }

    /**
     * Retrieves the last node in a binary heap using level order traversal.
     *
     * @return A pointer to the last node in the heap, or nullptr if the heap is empty.
     */
    HeapNode<T> *getLastNode() {
        Queue<HeapNode<T> *> nodeQueue;
        nodeQueue.enqueue(root);
        HeapNode<T> *lastNode = nullptr;

        while (!nodeQueue.isEmpty()) {
            lastNode = nodeQueue.front();
            nodeQueue.dequeue();
            if (lastNode->left) nodeQueue.enqueue(lastNode->left);
            if (lastNode->right) nodeQueue.enqueue(lastNode->right);
        }

        return lastNode;
    }

    /**
     * Retrieves the minimum value from the heap without removing it.
     * @return The minimum value stored in the heap.
     * @throws If the heap is empty, the program will exit with a status of 1.
     */
    T getMin() const {
        if (!root) {
            cout << "Heap is empty!" << endl;
            exit(1);
        }

        return root->value;
    }

    /**
     * Checks if the heap is empty.
     * @return True if the heap contains no nodes, false otherwise.
     */
    bool isEmpty() const {
        return nodeCount == 0;
    }

    /**
     * Returns the number of nodes in the MinHeap.
     *
     * @return The total count of nodes currently present in the MinHeap.
     */
    int size() const {
        return nodeCount;
    }

    /**
     * Displays the values of the heap nodes in level-order traversal.
     * If the heap is empty, outputs an appropriate message indicating so.
     * Uses a queue to facilitate breadth-first traversal from root to leaves.
     */
    void display() const {
        if (!root) {
            cout << "Heap is empty!" << endl;
            return;
        }

        Queue<HeapNode<T> *> nodeQueue;
        nodeQueue.enqueue(root);
        while (!nodeQueue.isEmpty()) {
            HeapNode<T> *current = nodeQueue.front();
            nodeQueue.dequeue();
            cout << current->value << " ";

            if (current->left) nodeQueue.enqueue(current->left);
            if (current->right) nodeQueue.enqueue(current->right);
        }

        cout << endl;
    }
};
