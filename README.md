# DS-Project

# Smart Traffic Management System Simulator

## Introduction

The Smart Traffic Management System Simulator is designed to replicate and optimize real-world urban traffic flow using advanced data structures and algorithms. This system focuses on efficient traffic management, incorporating features such as dynamic vehicle routing, real-time traffic signal control, congestion management, and emergency vehicle handling. The goal is to simulate and improve traffic conditions in a city, ensuring smoother traffic flow and better management of road disruptions.

Key features of the system include:

- A **City Traffic Network** represented as a weighted, directed graph, modeling intersections and roads.
- A **Vehicle Routing System** powered by Dijkstra's Algorithm to find optimal routes dynamically.
- **Traffic Signal Management** using priority queues for adjusting signal timings based on congestion.
- **Congestion Monitoring** and rerouting using BFS/DFS to alleviate traffic jams.
- **Emergency Vehicle Handling** with special routing to clear paths for urgent vehicles.
- **Accident and Road Closure Simulation** to handle disruptions in the road network.
- A **Simulation Dashboard** to visualize and control the system in real-time.

This simulator is built using C++ and leverages various data structures like graphs, priority queues, and heaps for efficient traffic management and optimization.

## Features

### 1. **City Traffic Network**
- Represented as a weighted, directed graph where:
  - **Nodes**: Intersections.
  - **Edges**: Roads between intersections, with weights representing travel times or congestion levels.
- Supports dynamic addition and removal of roads or intersections.
- Can visualize the graph structure in a text-based or graphical form.

### 2. **Vehicle Routing System**
- Calculates the shortest or fastest route for vehicles dynamically.
- Uses **Dijkstra’s Algorithm** to find the optimal path.
- Recalculates routes dynamically based on changes in traffic conditions.
- Tracks vehicle movement across the network.

### 3. **Traffic Signal Management**
- Controls traffic lights at intersections to minimize congestion.
- Uses a **priority queue** to manage incoming roads based on vehicle density.
- Dynamically adjusts green signal durations to reduce wait times.
- Includes an emergency override system for critical situations.

### 4. **Congestion Monitoring**
- Monitors vehicle counts on each road segment.
- Identifies congested roads and reroutes traffic using **BFS** or **DFS**.
- Displays congestion levels for analysis.

### 5. **Emergency Vehicle Handling**
- Provides special routing for emergency vehicles to minimize delays.
- Overrides normal traffic signal operations to clear paths.
- Uses an **A* Algorithm** to find the fastest possible route.
- Restores normal traffic flow once the emergency vehicle has passed.

### 6. **Accident and Road Closure Simulation**
- Simulates disruptions such as road closures or accidents.
- Blocks specific roads or intersections dynamically.
- Recalculates affected vehicle routes and updates the traffic network.
- Monitors system performance during disruptions.

### 7. **Simulation Dashboard**
- Provides an interactive interface to visualize and control the simulation.
- Displays traffic flow, congestion levels, and signal statuses.
- Allows manual addition or removal of vehicles.
- Generates logs for all system actions, including rerouting and signal changes.

## Data Structures and Algorithms

- **Graph**: Represents the city's road network with adjacency lists.
- **Priority Queue**: Manages road order for signal adjustments.
- **Min-Heap**: Efficiently identifies roads with the highest congestion.
- **Hash Table**: Tracks real-time vehicle counts on roads.
- **Dijkstra’s Algorithm**: Finds shortest paths for vehicles.
- **A* Algorithm**: Handles emergency vehicle routing.
- **BFS/DFS**: Detects congestion or inaccessible paths.


### 1. Graph.cpp: 
#### Graph Class Overview:

Represents a graph using an adjacency list to efficiently store and retrieve edges.
Provides methods for adding and removing nodes and edges, as well as retrieving adjacency lists for specific vertices.
Key Components:

- Attributes:
    adjacencyList: A vector of linked lists representing the adjacency list of each vertex.
    numVertices: The total number of vertices in the graph.
    Constructor and Methods:
        - Graph(int nVert): Initializes a graph with nVert vertices.
        - addEdge(int u, int v, float weight): Adds an edge from vertex u to vertex v with a given weight.
        - deleteEdge(int u, int v): Deletes the edge between vertices u and v.
        - bfs(): Performs a breadth-first search traversal starting from unvisited vertices.
        - dfs(): Performs a depth-first search traversal starting from unvisited vertices.
        - display(): Displays the adjacency list of each vertex.
        - setEdgeWeight(int u, int v, float weight): Sets the weight of an edge between u and v.

### 2. Dijkstra.cpp
#### Dijkstra Algorithm Overview:

Implements Dijkstra's algorithm to compute the shortest path between nodes in a graph, with the added functionality of avoiding blocked edges.
Key Components:

Functions:
    dijkstraPath(): Computes the shortest path from a start node to an end node, while avoiding specified blocked edges.
    isBlockedEdge(): Checks if an edge between two nodes is blocked.
    populateCongestionHashTable(): Populates a hash table with congestion data, considering road closures and vehicle paths, and increments counts for regular and emergency vehicles.
    
  - Algorithm Details:
        The function dijkstraPath() uses Dijkstra's algorithm but avoids blocked edges, returning the shortest path.
populateCongestionHashTable() simulates traffic conditions by applying road closures and calculating traffic congestion for regular and emergency vehicles.
Traffic Management and Congestion Handling:

The method considers the dynamic nature of road conditions by incorporating real-time traffic data and emergencies. Road closures are accounted for before computing vehicle paths, and congestion data is incremented accordingly.


3. HashTable.cpp:

The HashTable class implements a hash table for managing roads between nodes, identified by integer keys. Each road entry is stored as a HashEntry with a unique key, regular count, and emergency count. The table uses random probing to resolve collisions.

Key Features:
  HashTable Size: Fixed at 653.
  Collision Handling: Uses random probing.
  Insert: Adds roads (u, v) with counts initialized to zero.
  Remove: Deletes roads, marking them as DELETED_KEY.
  Search: Retrieves regular or emergency counts for a road.
  Increment/Decrement: Adjusts counts for regular or emergency events.
  Density: Calculates the sum of regular and emergency counts.
  Load Factor: Provides the load factor, indicating how full the table is.

4. List.cpp:
   Contains a the LinkedList Data Structure Class

5. Minheap.cpp:
   The MinHeap class is a generic implementation of a Min-Heap data structure, designed to efficiently store and retrieve the minimum element. It provides methods for insertion, extraction, and maintaining the heap property through heapify operations. The heap is structured as a binary tree, with each node containing a value, and pointers to left, right, and parent nodes.

Key Features:
  - HeapNode:
      Represents a node in the heap with a generic value, and pointers to its left child, right child, and parent.
  - MinHeap:
      Manages the heap with methods to insert new elements, extract the minimum element, and perform necessary heap operations like heapify up and heapify down.
  - Insert: Adds a new value to the heap, maintaining the heap property.
  - ExtractMin: Removes and returns the minimum value (root), adjusting the heap to maintain the heap property.
  - GetMin: Returns the minimum value without removing it.
  - Display: Displays the heap elements in level-order traversal.
  - Size and Empty Check: Methods to check the number of nodes in the heap and whether the heap is empty.

6. ParseFiles.cpp:
    - Loads the datasets

7. PriorityQueue.cpp, Queue.cpp, Stack.cpp, Vector.cpp:
    - Has their respective data structure implementation


## Requirements

- **Programming Language**: C++
