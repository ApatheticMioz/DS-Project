#include <iostream>
using namespace std;

class Node {
public:
    int data;
    int weight;
    Node *next;

    Node(const int d, const int w) : data(d), weight(w), next(nullptr) {
    }
};

class LinkedList {
    Node *head;

public:
    LinkedList() : head(nullptr) {
    }

    ~LinkedList() {
        deleteList();
    }

    void deleteList() {
        Node *current = head;
        while (current) {
            Node *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    void insertAtBeginning(const int value, const int weight) {
        auto newNode = new Node(value, weight);
        newNode->next = head;
        head = newNode;
    }

    void insertAtEnd(const int value, const int weight) {
        auto newNode = new Node(value, weight);

        if (!head) {
            head = newNode;
            return;
        }

        Node *temp = head;
        while (temp->next) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    void insertAtPosition(const int value, const int weight, const int position) {
        if (position < 0) {
            cerr << "Error: Position should be >= 0." << endl;
            return;
        }

        if (position == 0) {
            insertAtBeginning(value, weight);
            return;
        }

        Node *newNode = new Node(value, weight);

        Node *temp = head;
        for (int i = 0; i < position - 1 && temp; ++i) {
            temp = temp->next;
        }

        if (!temp) {
            cerr << "Error: Position out of range." << endl;
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    void deleteFromBeginning() {
        if (!head) {
            cerr << "Error: List is empty." << endl;
            return;
        }

        Node *temp = head;
        head = head->next;
        delete temp;
    }

    void deleteFromEnd() {
        if (!head) {
            cerr << "Error: List is empty." << endl;
            return;
        }

        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }

        Node *temp = head;
        while (temp->next->next) {
            temp = temp->next;
        }

        delete temp->next;
        temp->next = nullptr;
    }

    void deleteFromPosition(const int position) {
        if (position < 0) {
            cerr << "Error: Position should be >= 0." << endl;
            return;
        }

        if (position == 0) {
            deleteFromBeginning();
            return;
        }

        Node *temp = head;
        for (int i = 0; i < position - 1 && temp; ++i) {
            temp = temp->next;
        }

        if (!temp || !temp->next) {
            cerr << "Error: Position out of range." << endl;
            return;
        }
        Node *nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
    }

    void deleteByValue(const int value) {
        if (!head) {
            cerr << "Error: List is empty." << endl;
            return;
        }

        if (head->data == value) {
            deleteFromBeginning();
            return;
        }

        Node *temp = head;
        while (temp->next && temp->next->data != value) {
            temp = temp->next;
        }

        if (!temp->next) {
            cerr << "Error: Value not found." << endl;
            return;
        }

        Node *nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
    }

    void display() const {
        if (!head) {
            cerr << "Error: List is empty." << endl;
            return;
        }

        Node *temp = head;
        while (temp) {
            cout << temp->data << ' ' << temp->weight << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};
