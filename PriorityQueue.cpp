#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct TrafficSignal {
    int intersection;  // Intersection represented by a number (0-25 for 'A' to 'Z')
    int vehicleDensity;  // Vehicle density at the intersection
    int greenTime;  // Duration for which the light stays green

    // Constructor to initialize the signal
    TrafficSignal(int intersection, int vehicleDensity, int greenTime)
        : intersection(intersection), vehicleDensity(vehicleDensity), greenTime(greenTime) {}

    // Comparator for the priority queue to prioritize higher vehicle density
    bool operator<(const TrafficSignal& other) const {
        return vehicleDensity < other.vehicleDensity;  // Max heap: More vehicles = higher priority
    }
};

void adjustGreenDuration(TrafficSignal& signal) {
    if (signal.vehicleDensity > 10) {
        signal.greenTime = 40;  // Longer green for higher density
    } else if (signal.vehicleDensity > 5) {
        signal.greenTime = 20;  // Moderate green for medium density
    } else {
        signal.greenTime = 5;  // Shorter green for low density
    }
}

template<typename T>
class PriorityQueue {
private:
    // Custom struct to store value and priority
    struct Element {
        T value;
        int priority;

        Element(const T &val, int pri) : value(val), priority(pri) {}
    };

    // Vector to store elements
    Vector<Element> data;

    // Method to reorder the priority queue based on priority values
    void reorder() {
        // Simple selection sort to reorder based on priority (highest priority first)
        for (int i = 0; i < data.getSize(); i++) {
            for (int j = i + 1; j < data.getSize(); j++) {
                if (data[i].priority < data[j].priority) {
                    // Swap if current element has lower priority
                    Element temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
            }
        }
    }

public:
    // Enqueue method to add an element with a priority
    void enqueue(const T &value, int priority) {
        // Create an Element object and push it into the vector
        Element newElement(value, priority);
        data.push_back(newElement);
        reorder();  // Reorder elements after insertion
    }

    // Dequeue method to remove and return the element with the highest priority
    T dequeue() {
        if (data.getSize() == 0) {
            cout << "Priority queue is empty!";
        }
        T highestPriorityValue = data[0].value;
        data.removeAt(0);  // Remove the element with the highest priority
        return highestPriorityValue;
    }

    // Check if the priority queue is empty
    bool isEmpty() const {
        return data.getSize() == 0;
    }

    // Peek at the element with the highest priority without removing it
    T peek() const {
        if (data.getSize() == 0) {
            cout << "Priority queue is empty!";
        }
        return data[0].value;
    }

    // Get the size of the priority queue
    int size() const {
        return data.getSize();
    }
};

void emergencyOverride(PriorityQueue<TrafficSignal>& pq, const TrafficSignal& emergencySignal) {
    pq.enqueue(emergencySignal, 1000);
}

PriorityQueue<int> TrafficSignals;

