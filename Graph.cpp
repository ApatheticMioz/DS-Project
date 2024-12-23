#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

/**
 * Represents a graph using adjacency lists.
 */
class Graph {
    /**
     * Represents the adjacency list of a graph, where each index in the vector corresponds
     * to a vertex in the graph, and the linked list at each index stores the adjacent vertices.
     * Used to efficiently store and retrieve the graph's edges for operations like traversals and searches.
     */
    Vector<LinkedList> adjacencyList;
    /**
     * The number of vertices in the graph.
     * This variable indicates the total number of nodes present in the graph.
     */
    int numVertices;

    /**
     * Constructs a graph with the specified number of vertices.
     * Each vertex initializes an empty adjacency list.
     *
     * @param nVert The number of vertices in the graph.
     * @return A new Graph object with initialized adjacency lists.
     */
public:
    explicit Graph(const int nVert) : adjacencyList(nVert), numVertices(nVert) {}

    /**
     * Copy constructor for the Graph class.
     *
     * @param other The Graph object to be copied.
     * @return A new instance of the Graph class that is a copy of the provided Graph.
     */
    Graph(const Graph &other) : adjacencyList(other.adjacencyList), numVertices(other.numVertices) {}

    /**
     * Assignment operator for the Graph class.
     *
     * @param other The Graph instance to assign from.
     * @return A reference to this Graph instance.
     */
    Graph &operator=(const Graph &other) {
        if (this == &other) {
            return *this;
        }

        adjacencyList = other.adjacencyList;
        numVertices = other.numVertices;

        return *this;
    }

    /**
     * Retrieves the number of vertices in the graph.
     * @return The number of vertices in the graph.
     */
    int getSize() const {
        return numVertices;
    }

    /**
    * @brief Returns a const reference to the adjacency list of a specific vertex.
    *
    * This function provides access to the linked list of adjacent edges for the
    * specified vertex. It performs boundary checks to ensure the vertex index
    * is valid. If the vertex is out of range, an error message is displayed.
    *
    * @param vertex The index of the vertex whose adjacency list is to be returned.
    * @return A const reference to the linked list representing the adjacency list of the vertex.
    */
    const LinkedList &getAdjacencyList(const int vertex) const {
        if (vertex < 0 || vertex >= numVertices) {
            cout << "Error: Vertex out of range." << endl;
            return adjacencyList[0];
        }

        return adjacencyList[vertex];
    }

    /**
     * Adds an edge between two vertices in the graph with a specified weight.
     *
     * @param u The starting vertex of the edge. Must be within valid vertex range.
     * @param v The ending vertex of the edge. Must be within valid vertex range.
     * @param weight The weight of the edge to be added.
     */
    void addEdge(const int u, const int v, const float weight) {
        if (u < 0 || v < 0 || u >= numVertices || v >= numVertices) {
            cout << "Error: Vertices out of range." << endl;
            return;
        }

        adjacencyList[u].insertAtEnd(v, weight);
    }

    /**
     * @brief Adds a new node to the graph.
     *
     * This method appends an empty linked list to the adjacency list,
     * representing a new vertex in the graph. It also increments the
     * total number of vertices by one.
     */
    void addNode() {
        if (numVertices > 26) {
            cout << "Error: Too many vertices." << endl;
            return;
        }

        adjacencyList.push_back(LinkedList());
        numVertices++;
    }

    /**
     * Deletes the edge between two vertices u and v in the graph.
     * If either vertex u or v is out of range, an error message is displayed.
     *
     * @param u The starting vertex of the edge to be deleted.
     * @param v The ending vertex of the edge to be deleted.
     */
    void deleteEdge(const int u, const int v) {
        if (u < 0 || v < 0 || u >= numVertices || v >= numVertices) {
            cout << "Error: Vertices out of range." << endl;
            return;
        }

        adjacencyList[u].deleteByValue(v);
    }

    /**
     * Deletes a node from the graph and removes all associated edges.
     *
     * @param u The index of the node to be deleted. Must be within the range [0, numVertices).
     * If the index is out of range, an error message is displayed and no action is taken.
     */
    void deleteNode(const int u) {
        if (u < 0 || u >= numVertices) {
            cout << "Error: Vertices out of range." << endl;
            return;
        }

        adjacencyList[u].deleteList();

        for (int i = 0; i < numVertices; ++i) {
            if (i != u) {
                adjacencyList[i].deleteByValue(u);
            }
        }
    }

    void setEdgeWeight(const int u, const int v, const float weight) {
        Node* edge = adjacencyList[u].getHead();
        while (edge != nullptr) {
            if (edge->data == v) {
                edge->weight = weight;
                return;
            }
            edge = edge->next;
        }
        adjacencyList[u].insertAtEnd(v, weight);
    }

    /**
     * @brief Displays the adjacency list of each vertex in the graph.
     *
     * Iterates through each vertex in the graph and prints its adjacency list.
     * If a vertex has no edges, it is skipped and not displayed.
     */
    void display() const {
        for (int i = 0; i < numVertices; ++i) {
            if (adjacencyList[i].isEmpty()) {
                continue;
            }

            cout << "Vertex " << i << ": ";
            adjacencyList[i].display();
        }
    }

    void bfs() {
        Vector<bool> visited(numVertices, false);
        Queue<int> queue;

        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i]) {
                queue.enqueue(i);
                visited[i] = true;

                while (!queue.isEmpty()) {
                    int current = queue.dequeue();
                    cout << current << " ";

                    LinkedList& adjList = adjacencyList[current];
                    Node* temp = adjList.getHead();
                    while (temp != nullptr) {
                        int neighbor = temp->data;
                        if (!visited[neighbor]) {
                            queue.enqueue(neighbor);
                            visited[neighbor] = true;
                        }
                        temp = temp->next;
                    }
                }
            }
        }
        cout << endl;
    }

    void dfs() {
        Vector<bool> visited(numVertices, false);
        Stack<int> stack;

        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i]) {
                stack.push(i);
                visited[i] = true;

                while (!stack.isEmpty()) {
                    int current = stack.pop();
                    cout << current << " ";

                    LinkedList& adjList = adjacencyList[current];
                    Node* temp = adjList.getHead();
                    while (temp != nullptr) {
                        int neighbor = temp->data;
                        if (!visited[neighbor]) {
                            stack.push(neighbor);
                            visited[neighbor] = true;
                        }
                        temp = temp->next;
                    }
                }
            }
        }
        cout << endl;
    }
};

