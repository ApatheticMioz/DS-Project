#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/**
 * Loads a road network from a CSV file into a given graph.
 *
 * The CSV file is expected to have a header and subsequent rows
 * that define edges in the form of: Intersection1, Intersection2, TravelTime.
 * Each edge is added to the graph with an associated weight (TravelTime).
 * The intersections are internally represented by integers derived from their respective
 * first character's alphabetical index (e.g., 'A' -> 0, 'B' -> 1, ...).
 *
 * @param graph The graph object where the road network will be loaded.
 * @param fileName The name of the CSV file containing the road network data.
 */
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

/**
 * Loads vehicle data from a CSV file into a vector of vectors.
 *
 * The function reads entries from a specified file, parsing each line into
 * vehicle data that includes an identifier and two location indices. It
 * continues to parse lines until the specified number of vehicles is reached
 * or the file has no more lines. Each vehicle's data consists of three
 * integers: ID, start location, and end location.
 *
 * @param vehicles A reference to a vector where parsed vehicle data will be stored.
 * @param fileName The name of the file containing vehicle data in CSV format.
 * @param numVehicles The maximum number of vehicles to load.
 */
void loadVehicles(Vector<Vector<int>> &vehicles, const string &fileName, int numVehicles = INT_MAX) {
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

/**
 * Loads traffic signal data from a file into a vector.
 *
 * This function reads a specified file containing traffic signal information.
 * The file is expected to have data in a comma-separated format with a header.
 * Each line after the header should contain an intersection identifier and a green time value.
 *
 * @param trafficSignals A vector of vectors where the traffic signal data will be stored.
 *                       Each inner vector contains two integers: the first is the intersection index (starting from 'A'),
 *                       and the second is the green time for that intersection.
 * @param fileName The name of the file containing the traffic signal data.
 *
 * If the file cannot be opened, a message will be printed to the standard output.
 */
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

/**
 * Loads road closure data from a specified file and stores it in a provided vector.
 *
 * Reads and parses a CSV file to extract road closure information between intersections.
 * Each line in the file should contain data in the format: intersection1,intersection2,status.
 * Intersections are represented as uppercase letters, and the status can be one of:
 * "Under Repair", "Blocked", or default to "Clear".
 *
 * @param roadClosures A reference to a Vector of Vectors storing road closure data.
 *                     Each inner vector contains three integers: two intersection indices
 *                     and one status code.
 * @param fileName The path to the CSV file containing road closure information.
 */
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

/**
 * Loads emergency vehicle data from a specified file into a vector of vectors.
 * Each vehicle's data includes an ID, start point, end point, and priority level.
 *
 * @param emergencyVehicles A reference to a vector where emergency vehicle data will be stored.
 * @param fileName The name of the file containing emergency vehicle data.
 * @param numVehicles The maximum number of vehicle records to load.
 */
void loadEmergencyVehicles(Vector<Vector<int>> &emergencyVehicles, const string &fileName, int numVehicles = INT_MAX) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Unable to open file: " << fileName << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line) && emergencyVehicles.getSize() < numVehicles) {
        if (line == ",,,") continue;
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
