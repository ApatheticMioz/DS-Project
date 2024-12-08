#include <iostream>
#include "List.cpp"
using namespace std;

/**
 * @class Graph
 * @brief Represents a graph structure using adjacency lists.
 */
class Graph {
    /**
     * @brief An array of linked lists representing the adjacency list of a graph.
     *
     * Each element of the array is a linked list that maintains the vertices
     * adjacent to a vertex in the graph. This data structure efficiently supports
     * graph operations, such as adding or removing edges. It dynamically resizes
     * during the graph modifications.
     */
    LinkedList *adjacencyList;
    /**
     * Represents the number of vertices currently in the graph.
     */
    int numVertices;

    /**
     * Resizes the graph to the specified number of vertices.
     *
     * The method creates a new adjacency list of the specified size,
     * copies existing vertices to the new list, and updates the internal
     * state of the graph to reflect the new number of vertices.
     *
     * @param newSize The new number of vertices for the graph.
     */
    void resizeGraph(const int newSize) {
        auto *newAdjList = new LinkedList[newSize]();

        for (int i = 0; i < numVertices; ++i) {
            newAdjList[i] = adjacencyList[i];
        }

        delete[] adjacencyList;
        adjacencyList = newAdjList;
        numVertices = newSize;
    }

    /**
     * Constructs a graph with a specified number of vertices.
     * Initializes the adjacency list for each vertex.
     *
     * @param nVert The number of vertices in the graph.
     * @return An instance of the Graph class with initialized vertices.
     */
public:
    explicit Graph(const int nVert) {
        adjacencyList = new LinkedList[nVert]();
        numVertices = nVert;
    }

    /**
     * @brief Destructor for the Graph class.
     *
     * This destructor deallocates the memory allocated for the adjacency list
     * of the graph, ensuring that all resources are properly released.
     */
    ~Graph() {
        delete[] adjacencyList;
    }

    /**
     * @brief Copy constructor for the Graph class.
     *
     * Creates a new Graph instance by copying data from another Graph object.
     * It replicates the number of vertices and duplicates the adjacency list.
     *
     * @param other A constant reference to the Graph object to be copied.
     * @return A new Graph instance that is a copy of the provided Graph.
     */
    Graph(const Graph &other) {
        numVertices = other.numVertices;
        adjacencyList = new LinkedList[numVertices]();

        for (int i = 0; i < numVertices; ++i) {
            adjacencyList[i] = other.adjacencyList[i];
        }
    }

    /**
     * @brief Assignment operator for the Graph class.
     *
     * Copies the contents of another Graph object to this Graph object,
     * clearing any existing data in the destination Graph.
     *
     * @param other The Graph object to be copied.
     * @return A reference to this Graph object after assignment.
     */
    Graph &operator=(const Graph &other) {
        if (this == &other) {
            return *this;
        }

        delete[] adjacencyList;

        numVertices = other.numVertices;
        adjacencyList = new LinkedList[numVertices]();

        for (int i = 0; i < numVertices; ++i) {
            adjacencyList[i] = other.adjacencyList[i];
        }

        return *this;
    }

    /**
     * Adds an edge to the graph with a specified weight between two vertices.
     * If either vertex is out of range, the function outputs an error message.
     * The graph is resized if necessary to accommodate the new vertices.
     *
     * @param u The starting vertex of the edge. Must be within the range of existing vertices.
     * @param v The ending vertex of the edge. Must be within the range of existing vertices.
     * @param weight The weight of the edge between vertex u and vertex v.
     */
    void addEdge(const int u, const int v, const float weight) {
        if (u < 0 || v < 0 || u > numVertices || v > numVertices) {
            cerr << "Error: Vertices out of range." << endl;
            return;
        }

        if (u == numVertices || v == numVertices) {
            const int newSize = max(u, v) + 1;
            resizeGraph(newSize);
        }

        adjacencyList[u].insertAtEnd(v, weight);
    }

    /**
     * @brief Adds a new node to the graph by increasing the number of vertices.
     *
     * This function increments the count of vertices in the graph and adjusts the
     * adjacency list to accommodate the new vertex. The adjacency list is resized
     * to hold an additional empty list for the new node, preserving existing edges.
     */
    void addNode() {
        resizeGraph(numVertices + 1);
    }

    /**
     * @brief Deletes an edge between two vertices in the graph.
     *
     * Removes the edge from vertex u to vertex v by deleting v from
     * the adjacency list of u. If the vertices are out of range,
     * an error message is printed.
     *
     * @param u The starting vertex of the edge to be deleted.
     * @param v The ending vertex of the edge to be deleted.
     */
    void deleteEdge(const int u, const int v) {
        if (u < 0 || v < 0 || u >= numVertices || v >= numVertices) {
            cerr << "Error: Vertices out of range." << endl;
            return;
        }

        adjacencyList[u].deleteByValue(v);
    }

    /**
     * @brief Deletes a node from the graph.
     *
     * Removes node `u` and all associated edges from the graph.
     * If `u` is out of the range of valid vertices, an error message is displayed.
     *
     * @param u The index of the node to be deleted. Must be within the valid range of vertices.
     */
    void deleteNode(const int u) {
        if (u < 0 || u >= numVertices) {
            cerr << "Error: Vertices out of range." << endl;
            return;
        }

        adjacencyList[u].deleteList();

        for (int i = 0; i < numVertices; ++i) {
            if (i != u) {
                adjacencyList[i].deleteByValue(u);
            }
        }
    }


    /**
     * @brief Prints the adjacency list representation of the graph.
     *
     * Iterates through each vertex in the graph and displays its adjacent vertices
     * as stored in the corresponding linked list. Outputs the list for each vertex
     * to the console, showing the vertex index followed by a colon and its adjacency list.
     */
    void display() const {
        for (int i = 0; i < numVertices; ++i) {
            cout << "Vertex " << i << ": ";
            adjacencyList[i].display();
        }
    }
};
