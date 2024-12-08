#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

template<typename T>
class HeapNode {
public:
    T value;
    HeapNode *left;
    HeapNode *right;
    HeapNode *parent;

    explicit HeapNode(T val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {
    }
};

template<typename T>
class MinHeap {
    HeapNode<T> *root;
    int nodeCount = 0;

    void swap(HeapNode<T> *a, HeapNode<T> *b) {
        T temp = a->value;
        a->value = b->value;
        b->value = temp;
    }

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

    void heapifyUp(HeapNode<T> *node) {
        if (node->parent && node->value < node->parent->value) {
            swap(node, node->parent);
            heapifyUp(node->parent);
        }
    }

public:
    MinHeap() : root(nullptr) {}

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

    T getMin() const {
        if (!root) {
            cout << "Heap is empty!" << endl;
            exit(1);
        }

        return root->value;
    }

    bool isEmpty() const {
        return nodeCount == 0;
    }

    int size() const {
        return nodeCount;
    }

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
