#include <iostream>
#include "List.cpp"
using namespace std;

class Graph {
    LinkedList *adjacencyList;
    int numVertices;

    void resizeGraph(const int newSize) {
        auto *newAdjList = new LinkedList[newSize]();

        for (int i = 0; i < numVertices; ++i) {
            newAdjList[i] = adjacencyList[i];
        }

        delete[] adjacencyList;
        adjacencyList = newAdjList;
        numVertices = newSize;
    }

public:
    explicit Graph(const int nVert) {
        adjacencyList = new LinkedList[nVert]();
        numVertices = nVert;
    }

    ~Graph() {
        delete[] adjacencyList;
    }

    Graph(const Graph &other) {
        numVertices = other.numVertices;
        adjacencyList = new LinkedList[numVertices]();

        for (int i = 0; i < numVertices; ++i) {
            adjacencyList[i] = other.adjacencyList[i];
        }
    }

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

    void addNode() {
        resizeGraph(numVertices + 1);
    }

    void deleteEdge(const int u, const int v) {
        if (u < 0 || v < 0 || u >= numVertices || v >= numVertices) {
            cerr << "Error: Vertices out of range." << endl;
            return;
        }

        adjacencyList[u].deleteByValue(v);
    }

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
