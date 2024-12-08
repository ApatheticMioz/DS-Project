#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>
using namespace std;

/**
 * Represents an infinite distance used in the Dijkstra algorithm.
 * Initialized to the maximum possible integer value defined by INT_MAX.
 * Used as the initial distance for vertices to signify they are unvisited or unreachable.
 */
constexpr float INF = INT_MAX;

// Dijkstra's algorithm to find the shortest path
// Vector<int> dijkstraPath(const Graph &graph, const int start, const int end) {
//     auto *distance = new float[graph.getSize()];
//     auto visited = new bool[graph.getSize()];
//     auto *parent = new int[graph.getSize()];
//
//     for (int i = 0; i < graph.getSize(); i++) {
//         distance[i] = INF;
//         visited[i] = false;
//         parent[i] = -1;
//     }
//
//     distance[start] = 0;
//
//     for (int count = 0; count < graph.getSize(); count++) {
//         int u = -1;
//         float minDistance = INF;
//         for (int i = 0; i < graph.getSize(); i++) {
//             if (!visited[i] && distance[i] < minDistance) {
//                 minDistance = distance[i];
//                 u = i;
//             }
//         }
//
//         if (u == -1) break;
//         if (u == end) break;
//
//         visited[u] = true;
//
//         Node *neighbor = graph.getAdjacencyList(u).getHead();
//         while (neighbor != nullptr) {
//             int v = neighbor->data;
//             float weight = neighbor->weight;
//             if (!visited[v] && distance[u] + weight < distance[v]) {
//                 distance[v] = distance[u] + weight;
//                 parent[v] = u;
//             }
//             neighbor = neighbor->next;
//         }
//     }
//
//     Vector<int> path;
//     int current = end;
//     while (current != -1) {
//         path.push_back(current);
//         current = parent[current];
//     }
//     path.reverse();
//
//     delete[] distance;
//     delete[] visited;
//     delete[] parent;
//
//     if (path.isEmpty() || path[0] != start || path[path.getSize() - 1] != end) {
//         // cout << "No path found from (" << static_cast<char>(start + 65) << ", " << static_cast<char>(end + 65) << ")" << endl;
//         return Vector<int>();
//     }
//
//     return path;
// }

/**
 * Determines if there is a blocked edge between two nodes.
 *
 * @param blockedEdges A vector of vectors containing pairs of integers representing blocked edges.
 * @param u The first node to check for a blocked edge.
 * @param v The second node to check for a blocked edge.
 * @return True if an edge between node u and node v is blocked, false otherwise.
 */
bool isBlockedEdge(const Vector<Vector<int>> &blockedEdges, int u, int v) {
    for (int i = 0; i < blockedEdges.getSize(); i++) {
        // Access each closure using the index i
        Vector<int> closure = blockedEdges[i];
        if ((closure[0] == u && closure[1] == v) || (closure[0] == v && closure[1] == u)) {
            return true;  // The road is blocked
        }
    }
    return false;   // The road is not blocked
}

/**
 * Computes the shortest path in a graph from a start node to an end node while avoiding specified blocked edges.
 *
 * @param graph The graph to search, represented as an adjacency list.
 * @param start The starting node of the path search.
 * @param end The destination node of the path search.
 * @param blockedEdges A vector of pairs representing edges that should be avoided in the path.
 * @return A vector of integers representing the shortest path from start to end node, avoiding blocked edges.
 *         If no path is found, an empty vector is returned.
 */
Vector<int> dijkstraPath(const Graph &graph, const int start, const int end, const Vector<Vector<int>> &blockedEdges) {
    auto *distance = new float[graph.getSize()];
    auto visited = new bool[graph.getSize()];
    auto *parent = new int[graph.getSize()];

    for (int i = 0; i < graph.getSize(); i++) {
        distance[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    distance[start] = 0;

    for (int count = 0; count < graph.getSize(); count++) {
        int u = -1;
        float minDistance = INF;
        for (int i = 0; i < graph.getSize(); i++) {
            if (!visited[i] && distance[i] < minDistance) {
                minDistance = distance[i];
                u = i;
            }
        }

        if (u == -1) break;
        if (u == end) break;

        visited[u] = true;

        Node *neighbor = graph.getAdjacencyList(u).getHead();
        while (neighbor != nullptr) {
            int v = neighbor->data;
            float weight = neighbor->weight;

            // Skip the edge if it's blocked
            if (isBlockedEdge(blockedEdges, u, v)) {
                neighbor = neighbor->next;
                continue;  // Skip blocked edge
            }

            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
            }

            neighbor = neighbor->next;
        }
    }

    Vector<int> path;
    int current = end;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    path.reverse();

    delete[] distance;
    delete[] visited;
    delete[] parent;

    if (path.isEmpty() || path[0] != start || path[path.getSize() - 1] != end) {
        return Vector<int>();  // No path found
    }

    return path;
}


/**
 * Populates the hash table with congestion data derived from the graph, taking into account road closures and vehicle paths.
 *
 * @param graph The graph representing the network of roads between various nodes.
 * @param vehicles A 2D vector where each sub-vector contains vehicle data including start and end nodes.
 * @param emergencyVehicles A 2D vector where each sub-vector contains emergency vehicle data including start and end nodes.
 * @param roadClosures A 2D vector where each sub-vector represents a road closure with starting and ending nodes and closure status.
 * @param trafficSignals A 2D vector representing traffic signal data (currently unused in the function).
 * @param hashTable The hash table used to store and display congestion data including regular and emergency vehicle counts.
 */
void populateCongestionHashTable(Graph &graph, Vector<Vector<int>> &vehicles, Vector<Vector<int>> &emergencyVehicles, Vector<Vector<int>> &roadClosures, Vector<Vector<int>> &trafficSignals, HashTable &hashTable) {

    // Step 2: Apply road closures
    for (int i = 0; i < roadClosures.getSize(); i++) {
        Vector<int> closureData = roadClosures[i];
        int u = closureData[0];
        int v = closureData[1];
        int status = closureData[2];
        if (status == 1 || status == 2) { // Under Repair or Blocked
            //cout << "Deletions." << endl;
            graph.deleteEdge(u, v);
            graph.deleteEdge(v, u);
        }
    }

    // Step 3: Insert all remaining roads into the hash table
    for (int u = 0; u < graph.getSize(); u++) {
        Node *neighbor = graph.getAdjacencyList(u).getHead();
        while (neighbor != nullptr) {
            int v = neighbor->data;
            hashTable.insert(u, v);
            neighbor = neighbor->next;
        }
    }

    // Step 4: For each vehicle, find the shortest path and increment regularCount
    for (int i = 0; i < vehicles.getSize(); i++) {
        Vector<int> vehicleData = vehicles[i];
        int start = vehicleData[1];
        int end = vehicleData[2];
        Vector<int> path = dijkstraPath(graph, start, end, roadClosures);
        // for (int v = 0; v<path.getSize(); v++) {
        //     cout << path[v] << "  ";
        // }
        // cout << endl;
        if (path.getSize() < 2) continue;
        for (int j = 0; j < path.getSize() - 1; j++) {
            int u = path[j];
            int v = path[j+1];
            hashTable.incrementCount(u, v, false);
        }
    }

    // Step 5: For each emergency vehicle, find the shortest path and increment emergencyCount
    for (int i = 0; i < emergencyVehicles.getSize(); i++) {
        Vector<int> emVehicleData = emergencyVehicles[i];
        int start = emVehicleData[1];
        int end = emVehicleData[2];
        Vector<int> path = dijkstraPath(graph, start, end, roadClosures);
        if (path.getSize() < 2) continue;
        for (int j = 0; j < path.getSize() - 1; j++) {
            int u = path[j];
            int v = path[j+1];
            hashTable.incrementCount(u, v, true);
        }
    }

    // Step 6: Display the hash table
    hashTable.display();
}
