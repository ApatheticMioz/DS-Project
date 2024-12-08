#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Graph.cpp"
using namespace std;

void loadRoadNetwork(Graph &graph, const string &fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Could not open the file: " << fileName << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string part;

        getline(ss, part, ',');
        char intersection1 = part[0];

        getline(ss, part, ',');
        char intersection2 = part[0];

        getline(ss, part, ',');
        float travelTime = stof(part);

        graph.addEdge(intersection1 - 'A', intersection2 - 'A', travelTime);
    }

    file.close();
}

int main() {
                                                                // CSV file headers
    string vehicleCSV = "vehicles.csv";                         // VehicleID        StartIntersection   EndIntersection
    string traffic_signalsCSV = "traffic_signals.csv";          // Intersection     GreenTime(s)
    string road_networkCSV = "road_network.csv";                // Intersection1    Intersection2       TravelTime
    string road_closuresCSV = "road_closures.csv";              // Intersection1    Intersection2       Status
    string emergency_vehiclesCSV = "emergency_vehicles.csv";    // VehicleID        StartIntersection   EndIntersection     PriorityLevel

    constexpr int graphSize = 26;
    Graph graph(graphSize);

    loadRoadNetwork(graph, road_networkCSV);

    graph.display();

    return 0;
}
