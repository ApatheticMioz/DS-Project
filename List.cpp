#include <iostream>
using namespace std;

/**
 * Represents a node in a singly linked list containing an integer data and a float weight.
 */
class Node {
    /**
     * Represents an integer data value stored in a node of a linked list.
     */
public:
    int data;
    /**
     * Represents the weight associated with a node in the linked list.
     */
    float weight;
    /**
     * Pointer to the next node in a linked list.
     * This member variable is used to navigate through the linked list by linking
     * nodes together, with each node pointing to the subsequent node in the list.
     */
    Node *next;

    /**
     * Constructs a new Node object with given data and weight.
     * Initializes the next pointer to nullptr.
     *
     * @param d The integer data to be stored in the node.
     * @param w The float weight associated with the node.
     * @return An instance of a Node object with specified data and weight.
     */
    Node(const int d, const float w) : data(d), weight(w), next(nullptr) {
    }
};

/**
 * Represents a singly linked list.
 */
class LinkedList {
    /**
     * A pointer to the first node in a linked list.
     * Initially set to nullptr, it serves as the entry point to the list.
     */
    Node *head;

    /**
     * @brief Constructs an empty LinkedList.
     *
     * Initializes the head of the list to nullptr, indicating that the list is initially empty.
     *
     * @return An instance of LinkedList with no nodes.
     */
public:
    LinkedList() : head(nullptr) {
    }

    /**
     * @brief Destructor for the LinkedList class.
     *
     * This destructor ensures that all dynamically allocated nodes in the linked list
     * are properly deleted, preventing memory leaks by calling the deleteList() method.
     */
    ~LinkedList() {
        deleteList();
    }

    /**
     * Deletes all nodes in the linked list, freeing their memory.
     * Sets the head pointer to nullptr after deletion to indicate
     * that the list is empty.
     */
    void deleteList() {
        Node *current = head;
        while (current) {
            Node *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    /**
     * Inserts a new node with the specified value and weight at the beginning of the linked list.
     *
     * @param value The integer value to be stored in the new node.
     * @param weight The float weight to be stored in the new node.
     */
    void insertAtBeginning(const int value, const float weight) {
        auto newNode = new Node(value, weight);
        newNode->next = head;
        head = newNode;
    }

    /**
     * Inserts a new node with the given value and weight at the end of the linked list.
     *
     * @param value The integer value to be stored in the new node.
     * @param weight The floating-point weight to be associated with the new node.
     */
    void insertAtEnd(const int value, const float weight) {
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

    /**
     * Inserts a new node with given value and weight at the specified position in the linked list.
     *
     * @param value The integer value to be stored in the new node.
     * @param weight The float weight to be stored in the new node.
     * @param position The position at which to insert the new node. Indexing starts from 0.
     */
    void insertAtPosition(const int value, const float weight, const int position) {
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

    /**
     * Removes the first node from the beginning of the linked list.
     * Prints an error message if the list is empty.
     */
    void deleteFromBeginning() {
        if (!head) {
            cerr << "Error: List is empty." << endl;
            return;
        }

        Node *temp = head;
        head = head->next;
        delete temp;
    }

    /**
     * Deletes the last node from the linked list.
     * If the list is empty, an error message is displayed.
     * If the list has only one node, it deletes that node and sets the head to nullptr.
     */
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

    /**
     * Deletes a node from the linked list at the specified position.
     * If the position is invalid, an error message is output.
     *
     * @param position The index of the node to be deleted, where the first node is at position 0.
     */
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

    /**
     * Deletes the first occurrence of a node with the specified value from the linked list.
     * If the list is empty or the value is not found, an error message is displayed.
     *
     * @param value The integer value of the node to be deleted from the list.
     */
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

    /**
     * @brief Displays the contents of the linked list.
     *
     * Prints each node's data and weight followed by an arrow.
     * Outputs an error message if the list is empty.
     */
    void display() const {
        if (!head) {
            cerr << "Error: List is empty." << endl;
            return;
        }

        Node *temp = head;
        while (temp) {
            cout << "(" << temp->data << ", " << temp->weight << ") -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};
