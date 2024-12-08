#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Vector.cpp"
#include "List.cpp"
#include "Queue.cpp"
#include "Graph.cpp"
#include "ParseFiles.cpp"
#include "MinHeap.cpp"
using namespace std;

int main() {
    Graph graph(26);
    Vector<Vector<int>> vehicles;
    Vector<Vector<int>> trafficSignals;
    Vector<Vector<int>> roadClosures;
    Vector<Vector<int>> emergencyVehicles;

    string roadNetworkFile = "road_network.csv";
    string vehiclesFile = "vehicles.csv";
    string trafficSignalsFile = "traffic_signals.csv";
    string roadClosuresFile = "road_closures.csv";
    string emergencyVehiclesFile = "emergency_vehicles.csv";

    cout << "Loading road network from " << roadNetworkFile << "..." << endl;
    loadRoadNetwork(graph, roadNetworkFile);
    cout << "Road network loaded successfully.\n" << endl;

    int numVehicles = INT_MAX;
    cout << "Loading vehicles from " << vehiclesFile << "..." << endl;
    loadVehicles(vehicles, vehiclesFile, numVehicles);
    cout << "Vehicles loaded successfully.\n" << endl;

    cout << "Loading traffic signals from " << trafficSignalsFile << "..." << endl;
    loadTrafficSignals(trafficSignals, trafficSignalsFile);
    cout << "Traffic signals loaded successfully.\n" << endl;

    cout << "Loading road closures from " << roadClosuresFile << "..." << endl;
    loadRoadClosures(roadClosures, roadClosuresFile);
    cout << "Road closures loaded successfully.\n" << endl;

    int numEmergencyVehicles = INT_MAX;
    cout << "Loading emergency vehicles from " << emergencyVehiclesFile << "..." << endl;
    loadEmergencyVehicles(emergencyVehicles, emergencyVehiclesFile, numEmergencyVehicles);
    cout << "Emergency vehicles loaded successfully.\n" << endl;

    cout << "====== ROAD NETWORK ======" << endl;
    graph.display();

    cout << "\n====== VEHICLES ======" << endl;
    for (int i = 0; i < vehicles.getSize(); i++) {
        cout << "Vehicle " << i + 1 << ": ";
        for (int j = 0; j < vehicles[i].getSize(); j++) {
            cout << vehicles[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\n====== TRAFFIC SIGNALS ======" << endl;
    for (int i = 0; i < trafficSignals.getSize(); i++) {
        cout << "Intersection: " << trafficSignals[i][0]
             << ", Green Time: " << trafficSignals[i][1] << endl;
    }

    cout << "\n====== ROAD CLOSURES ======" << endl;
    for (int i = 0; i < roadClosures.getSize(); i++) {
        cout << "Intersection 1: " << roadClosures[i][0]
             << ", Intersection 2: " << roadClosures[i][1]
             << ", Status: " << roadClosures[i][2] << endl;
    }

    cout << "\n====== EMERGENCY VEHICLES ======" << endl;
    for (int i = 0; i < emergencyVehicles.getSize(); i++) {
        cout << "Vehicle ID: " << emergencyVehicles[i][0]
             << ", Start: " << emergencyVehicles[i][1]
             << ", End: " << emergencyVehicles[i][2]
             << ", Priority: " << emergencyVehicles[i][3] << endl;
    }

    cout << "\nAll tests completed successfully!" << endl;

    return 0;
}


// int main() {
//                                                                 // CSV file headers
//     string vehicleCSV = "vehicles.csv";                         // VehicleID        StartIntersection   EndIntersection
//     string traffic_signalsCSV = "traffic_signals.csv";          // Intersection     GreenTime(s)
//     string road_networkCSV = "road_network.csv";                // Intersection1    Intersection2       TravelTime
//     string road_closuresCSV = "road_closures.csv";              // Intersection1    Intersection2       Status
//     string emergency_vehiclesCSV = "emergency_vehicles.csv";    // VehicleID        StartIntersection   EndIntersection     PriorityLevel
//
//     constexpr int graphSize = 26;
//     Graph graph(graphSize);
//
//     loadRoadNetwork(graph, road_networkCSV);
//
//     graph.display();
//
//     return 0;
// }
