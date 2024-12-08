#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void loadRoadNetwork(Graph &graph, const string &fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Unable to open file: " << fileName << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        istringstream iss(line);

        string temp;

        getline(iss, temp, ',');
        int u = temp[0] - 'A';

        getline(iss, temp, ',');
        int v = temp[0] - 'A';

        getline(iss, temp, ',');
        float weight = stof(temp);

        graph.addEdge(u, v, weight);
    }

    file.close();
}

void loadVehicles(Vector<Vector<int>> &vehicles, const string &fileName, int numVehicles) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Unable to open file: " << fileName << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line) && vehicles.getSize() < numVehicles) {
        istringstream iss(line);

        string temp;

        getline(iss, temp, ',');
        int id = stoi(temp.substr(1));

        getline(iss, temp, ',');
        int start = temp[0] - 'A';

        getline(iss, temp, ',');
        int end = temp[0] - 'A';

        Vector<int> vehicleData;
        vehicleData.push_back(id);
        vehicleData.push_back(start);
        vehicleData.push_back(end);
        vehicles.push_back(vehicleData);
    }

    file.close();
}

void loadTrafficSignals(Vector<Vector<int>> &trafficSignals, const string &fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Unable to open file: " << fileName << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        istringstream iss(line);

        string temp;

        getline(iss, temp, ',');
        int intersection = temp[0] - 'A';

        getline(iss, temp, ',');
        int greenTime = stoi(temp);

        Vector<int> signalData;
        signalData.push_back(intersection);
        signalData.push_back(greenTime);
        trafficSignals.push_back(signalData);
    }

    file.close();
}

void loadRoadClosures(Vector<Vector<int> > &roadClosures, const string &fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Unable to open file: " << fileName << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        if (line == ",,") continue;

        istringstream iss(line);

        string temp;

        getline(iss, temp, ',');
        int intersection1 = temp[0] - 'A';

        getline(iss, temp, ',');
        int intersection2 = temp[0] - 'A';

        getline(iss, temp, ',');

        int status;
        if (temp == "Under Repair") {
            status = 1;
        } else if (temp == "Blocked") {
            status = 2;
        } else {
            status = 0; // Default to "Clear"
        }

        Vector<int> closureData;
        closureData.push_back(intersection1);
        closureData.push_back(intersection2);
        closureData.push_back(status);
        roadClosures.push_back(closureData);
    }

    file.close();
}

void loadEmergencyVehicles(Vector<Vector<int>> &emergencyVehicles, const string &fileName, int numVehicles) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Unable to open file: " << fileName << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line) && emergencyVehicles.getSize() < numVehicles) {
        if (line == ",,") continue;
        istringstream iss(line);
        cout << line << endl;
        string temp;

        getline(iss, temp, ',');
        int id = stoi(temp.substr(2));

        getline(iss, temp, ',');
        int start = temp[0] - 'A';

        getline(iss, temp, ',');
        int end = temp[0] - 'A';

        getline(iss, temp, ',');

        int priority;
        if (temp == "Medium") {
            priority = 1;
        } else if (temp == "High") {
            priority = 2;
        } else {
            priority = 0; // Default, none
        }

        Vector<int> emVehicleData;
        emVehicleData.push_back(id);
        emVehicleData.push_back(start);
        emVehicleData.push_back(end);
        emVehicleData.push_back(priority);

        emergencyVehicles.push_back(emVehicleData);
    }

    file.close();
}
