#include <iostream>
#include "List.cpp"
using namespace std;

/**
 * Graph class implements an adjacency list representation of a graph.
 */
class Graph {
    /**
     * A pointer to an array of LinkedList objects representing the adjacency list
     * of the graph. Each LinkedList at a particular index contains the edges
     * originating from the vertex represented by that index. It is used to manage
     * the storage and manipulation of the graph's edges.
     */
    LinkedList *adjacencyList;
    /**
     * @brief Represents the number of vertices in the graph.
     *
     * This variable holds the current count of vertices in a graph structure.
     * It is initially set during the Graph's construction and may be updated
     * through various operations like resizing the graph.
     */
    int numVertices;

    /**
     * Resizes the graph to accommodate a new number of vertices.
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
     * Constructs a new Graph with a specified number of vertices.
     * Initializes an adjacency list for each vertex.
     *
     * @param nVert The number of vertices to be included in the graph.
     *              Must be a non-negative integer.
     * @return A Graph object with an initialized adjacency list.
     */
public:
    explicit Graph(const int nVert) {
        adjacencyList = new LinkedList[nVert]();
        numVertices = nVert;
    }

    /**
     * Destructor for the Graph class.
     *
     * This method is responsible for releasing the memory allocated
     * for the adjacency list of the graph, ensuring to delete the
     * dynamically allocated array of LinkedList objects.
     */
    ~Graph() {
        delete[] adjacencyList;
    }

    /**
     * Copy constructor for the Graph class.
     * Creates a deep copy of the given Graph object.
     *
     * @param other The Graph object to be copied.
     * @return A new Graph object that is a deep copy of 'other'.
     */
    Graph(const Graph &other) {
        numVertices = other.numVertices;
        adjacencyList = new LinkedList[numVertices]();

        for (int i = 0; i < numVertices; ++i) {
            adjacencyList[i] = other.adjacencyList[i];
        }
    }

    /**
     * Assigns the contents of one Graph object to another.
     * It performs a deep copy of the adjacency list from the source graph to the current graph.
     *
     * @param other The Graph object to be copied into the current graph.
     * @return A reference to the current Graph object after assignment.
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
     * Adds a directed edge from vertex u to vertex v with a given weight.
     * If necessary, resizes the graph to accommodate new vertices.
     *
     * @param u The starting vertex of the edge.
     * @param v The ending vertex of the edge.
     * @param weight The weight of the edge.
     */
    void addEdge(const int u, const int v, const int weight) {
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
     * Adds a new node to the graph by increasing the number of vertices by one.
     * The method resizes the internal adjacency list to accommodate an additional node.
     */
    void addNode() {
        resizeGraph(numVertices + 1);
    }

    /**
     * Removes the edge from vertex u to vertex v in the graph's adjacency list.
     * If the vertices u or v are out of range, an error message is displayed.
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
     * Deletes a node and its associated edges from the graph.
     *
     * Removes the node specified by vertex 'u' from the graph and all edges connected to it.
     * Updates the graph's adjacency list accordingly.
     *
     * @param u The index of the vertex to be deleted. It must be within the range of existing vertices.
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
};
