#include <iostream>
using namespace std;

/**
 * Represents a single node in a linked list.
 */
class Node {
    /**
     * Stores the value of the node in a linked list.
     */
public:
    int data;
    /**
     * Represents the weight of a node in the linked list.
     * Used to store additional information associated with the node's data.
     */
    int weight;
    /**
     * Pointer to the next node in the linked list.
     * It facilitates traversing the list by pointing to the subsequent node.
     * Initialized to nullptr by default, indicating the end of the list when no next node is available.
     */
    Node *next;

    /**
     * Constructor for the Node class.
     *
     * Initializes a new Node object with the provided data and weight values.
     *
     * @param d The data value for the node.
     * @param w The weight value associated with the node.
     * @return A new instance of the Node class with data and weight initialized. The `next` pointer is set to nullptr.
     */
    Node(const int d, const int w) : data(d), weight(w), next(nullptr) {
    }
};

/**
 * A class representing a singly linked list.
 */
class LinkedList {
    /**
     * @brief A pointer to the first node in a linked list.
     *
     * This variable serves as a reference to the head of a singly linked list,
     * enabling traversal, insertion, and deletion operations. If the linked list
     * is empty, this pointer will be null.
     */
    Node *head;

    /**
     * Constructs an empty LinkedList with the head initialized to nullptr.
     * @return A new instance of LinkedList with no elements.
     */
public:
    LinkedList() : head(nullptr) {
    }

    /**
     * Destructor for the LinkedList class.
     * Cleans up allocated memory by deleting all the nodes in the linked list.
     */
    ~LinkedList() {
        deleteList();
    }

    /**
     * Deletes all nodes in the linked list, freeing the allocated memory.
     *
     * This method traverses the linked list starting from the head, deleting each node to
     * ensure that all dynamically allocated memory is properly freed. After the list is
     * deleted, the head pointer is set to nullptr to indicate that the list is empty.
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
     * Inserts a new node with specified value and weight at the beginning of the linked list.
     *
     * @param value The integer value to be stored in the new node.
     * @param weight The integer weight to be associated with the new node.
     */
    void insertAtBeginning(const int value, const int weight) {
        auto newNode = new Node(value, weight);
        newNode->next = head;
        head = newNode;
    }

    /**
     * Inserts a new node with the specified value and weight at the end of the linked list.
     *
     * @param value The data value to be stored in the new node.
     * @param weight The weight associated with the new node.
     */
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

    /**
     * Inserts a new node with a specified value and weight at the given position in the list.
     * If the position is less than 0, an error message is displayed.
     * If the position is greater than the length of the list, an error message is displayed.
     *
     * @param value The integer value to be stored in the new node.
     * @param weight The integer weight to be stored in the new node.
     * @param position The zero-based position at which to insert the new node.
     */
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

    /**
     * Deletes the node at the beginning of the linked list.
     *
     * If the list is empty, an error message is logged and no action is taken.
     *
     * Note: The function assumes that Node objects are dynamically allocated and
     * need to be deallocated using `delete`.
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
     *
     * If the list is empty, an error message is displayed.
     * If the list contains only one node, that node is deleted and the list becomes empty.
     * For a list with multiple nodes, the last node is removed by traversing to the node before the last.
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
     * Deletes the node at a specific position in the linked list.
     *
     * @param position The zero-based index of the node to be deleted.
     *                 If negative, an error message is displayed.
     *                 If out of range, an error message is displayed.
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
     * Deletes the first occurrence of a node containing the specified value from the linked list.
     * It prints an error message if the list is empty or if the value is not found.
     *
     * @param value The value to be deleted from the linked list.
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
     * The method will iterate through the linked list and print the data and weight
     * of each node in the format "data weight ->", followed by a terminating "NULL".
     * If the list is empty, an error message is displayed.
     */
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
