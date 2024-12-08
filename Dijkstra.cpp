#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Vector<int> dijkstra(const Graph &graph, const int start, const int end) {
    int n = graph.getSize();

    Vector<int> distances;
    for (int i = 0; i < n; ++i)
        distances.push_back(INT_MAX);

    distances[start] = 0;

    Vector<int> previous;
    for (int i = 0; i < n; ++i)
        previous.push_back(-1);

    Vector<bool> visited;
    for (int i = 0; i < n; ++i)
        visited.push_back(false);

    Queue<int> q;
    q.enqueue(start);

    while (!q.isEmpty()) {
        int current = q.front();
        q.dequeue();

        if (visited[current]) continue;
        visited[current] = true;

        const LinkedList &adjList = graph.getAdjacencyList(current);
        Node *edge = adjList.getHead();

        while (edge != nullptr) {
            int next = edge->data;
            int weight = edge->weight;
            int newDist = distances[current] + weight;

            if (newDist < distances[next]) {
                distances[next] = newDist;
                previous[next] = current;
                if (!visited[next]) {
                    q.enqueue(next);
                }
            }

            edge = edge->next;
        }
    }

    if (distances[end] == INT_MAX) {
        return {};
    }

    Vector<int> path;
    for (int at = end; at != -1; at = previous[at]) {
        path.push_back(at);
    }

    Vector<int> reversedPath;
    while (!path.isEmpty()) {
        reversedPath.push_back(path.pop());
    }

    return reversedPath;
}

void printPathAndDistance(const Graph &graph, const Vector<int> &path, const int start, const int end) {
    if (path.getSize() == 0) {
        cout << "No path exists from vertex " << start << " to vertex " << end << endl;
    } else {
        cout << "Shortest path from vertex " << start << " to vertex " << end << " is: ";

        for (int i = 0; i < path.getSize(); ++i) {
            cout << path[i];
            if (i != path.getSize() - 1) cout << " -> ";
        }

        int totalDistance = 0;
        for (int i = 0; i < path.getSize() - 1; ++i) {
            int from = path[i];
            int to = path[i + 1];
            Node *edge = graph.getAdjacencyList(from).getHead();

            while (edge != nullptr) {
                if (edge->data == to) {
                    totalDistance += edge->weight;
                    break;
                }
                edge = edge->next;
            }
        }

        cout << "\nTotal distance: " << totalDistance << endl;
    }
}
