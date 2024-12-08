#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class HashTable {
    static constexpr int HT_SIZE = 653;       // Prime number larger than max possible roads
    static constexpr int EMPTY_KEY = -1;
    static constexpr int DELETED_KEY = -2;

    struct HashEntry {
        int key;
        int regularCount;
        int emergencyCount;
    };

    HashEntry table[HT_SIZE];
    int occupied;
    int randomProbes[HT_SIZE];

    int hashFunction(int key) const {
        return key % HT_SIZE;
    }

    int getRandomIndex() const {
        return rand() % HT_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < HT_SIZE; i++) {
            table[i].key = EMPTY_KEY;
            table[i].regularCount = 0;
            table[i].emergencyCount = 0;
            randomProbes[i] = rand() % HT_SIZE;
        }
        occupied = 0;
    }

    void insert(int u, int v) {
        int key = u * 100 + v;
        int index = hashFunction(key);
        if (table[index].key == EMPTY_KEY || table[index].key == DELETED_KEY) {
            table[index].key = key;
            table[index].regularCount = 0;
            table[index].emergencyCount = 0;
            occupied++;
            return;
        }
        if (table[index].key == key) {
            // Key already exists, no action needed
            return;
        }
        // Collision occurred, start random probing
        int attempts = 0;
        const int MAX_ATTEMPTS = HT_SIZE;
        while (attempts < MAX_ATTEMPTS) {
            int randIndex = randomProbes[attempts] % HT_SIZE;
            if (table[randIndex].key == EMPTY_KEY || table[randIndex].key == DELETED_KEY) {
                table[randIndex].key = key;
                table[randIndex].regularCount = 0;
                table[randIndex].emergencyCount = 0;
                occupied++;
                return;
            }
            attempts++;
        }
        cout << "Hash table is full, cannot insert road (" << static_cast<char>(u + 65) << ", " << static_cast<char>(v + 65) << ")" << endl;
    }

    void remove(int u, int v) {
        int key = u * 100 + v;
        int index = hashFunction(key);
        if (table[index].key == key) {
            table[index].key = DELETED_KEY;
            table[index].regularCount = 0;
            table[index].emergencyCount = 0;
            occupied--;
            return;
        }
        if (table[index].key == EMPTY_KEY) {
            cout << "Road (" << static_cast<char>(u + 65) << ", " << static_cast<char>(v + 65) << ") not found in hash table." << endl;
            return;
        }
        // Start random probing to find the key
        int attempts = 0;
        const int MAX_ATTEMPTS = HT_SIZE;
        while (attempts < MAX_ATTEMPTS) {
            int randIndex = randomProbes[attempts] % HT_SIZE;
            if (table[randIndex].key == key) {
                table[randIndex].key = DELETED_KEY;
                table[randIndex].regularCount = 0;
                table[randIndex].emergencyCount = 0;
                occupied--;
                return;
            }
            attempts++;
        }
        cout << "Road (" << static_cast<char>(u + 65) << ", " << static_cast<char>(v + 65) << ") not found in hash table." << endl;
    }

    int search(int u, int v, bool isEmergency) const {
        int key = u * 100 + v;
        int index = hashFunction(key);
        if (table[index].key == key) {
            return (isEmergency) ? table[index].emergencyCount : table[index].regularCount;
        }
        if (table[index].key == EMPTY_KEY) {
            cout << "Road (" << static_cast<char>(u + 65) << ", " << static_cast<char>(v + 65) << ") not found in hash table." << endl;
            return -1; // Indicate not found
        }
        // Start random probing to find the key
        int attempts = 0;
        const int MAX_ATTEMPTS = HT_SIZE;
        while (attempts < MAX_ATTEMPTS) {
            int randIndex = randomProbes[attempts] % HT_SIZE;
            if (table[randIndex].key == key) {
                return (isEmergency) ? table[randIndex].emergencyCount : table[randIndex].regularCount;
            }
            attempts++;
        }
        cout << "Road (" << static_cast<char>(u + 65) << ", " << static_cast<char>(v + 65) << ") not found in hash table." << endl;
        return -1; // Indicate not found
    }

    void incrementCount(int u, int v, bool isEmergency) {
        int key = u * 100 + v;
        int index = hashFunction(key);
        if (table[index].key == key) {
            if (isEmergency) {
                table[index].emergencyCount++;
            } else {
                table[index].regularCount++;
            }
            return;
        }
        if (table[index].key == EMPTY_KEY) {
            cout << "Road (" << static_cast<char>(u + 65) << ", " << static_cast<char>(v + 65) << ") not found in hash table." << endl;
            return;
        }
        // Start random probing to find the key
        int attempts = 0;
        const int MAX_ATTEMPTS = HT_SIZE;
        while (attempts < MAX_ATTEMPTS) {
            int randIndex = randomProbes[attempts] % HT_SIZE;
            if (table[randIndex].key == key) {
                if (isEmergency) {
                    table[randIndex].emergencyCount++;
                } else {
                    table[randIndex].regularCount++;
                }
                return;
            }
            attempts++;
        }
        cout << "Road (" << static_cast<char>(u + 65) << ", " << static_cast<char>(v + 65) << ") not found in hash table." << endl;
    }

    void decrementCount(int u, int v, bool isEmergency) {
        int key = u * 100 + v;
        int index = hashFunction(key);
        if (table[index].key == key) {
            if (isEmergency) {
                if (table[index].emergencyCount > 0) {
                    table[index].emergencyCount--;
                }
            } else {
                if (table[index].regularCount > 0) {
                    table[index].regularCount--;
                }
            }
            return;
        }
        if (table[index].key == EMPTY_KEY) {
            cout << "Road (" << static_cast<char>(u + 65) << ", " << static_cast<char>(v + 65) << ") not found in hash table." << endl;
            return;
        }
        // Start random probing to find the key
        int attempts = 0;
        const int MAX_ATTEMPTS = HT_SIZE;
        while (attempts < MAX_ATTEMPTS) {
            int randIndex = randomProbes[attempts] % HT_SIZE;
            if (table[randIndex].key == key) {
                if (isEmergency) {
                    if (table[randIndex].emergencyCount > 0) {
                        table[randIndex].emergencyCount--;
                    }
                } else {
                    if (table[randIndex].regularCount > 0) {
                        table[randIndex].regularCount--;
                    }
                }
                return;
            }
            attempts++;
        }
        cout << "Road (" << static_cast<char>(u + 65) << ", " << static_cast<char>(v + 65) << ") not found in hash table." << endl;
    }

    void display() const {
        for (int i = 0; i < HT_SIZE; i++) {
            if (table[i].key != EMPTY_KEY && table[i].key != DELETED_KEY) {
                int u = table[i].key / 100;
                int v = table[i].key % 100;
                cout << "Road (" << static_cast<char>(u + 65) << ", " << static_cast<char>(v + 65) << ") - Regular Count: " << table[i].regularCount
                     << " - Emergency Count: " << table[i].emergencyCount << endl;
            }
        }
    }

    float calculateDensity(int u, int v) const {
        int key = u * 100 + v;
        int index = hashFunction(key);
        if (table[index].key == key) {
            // Calculate density as the sum of regular and emergency counts
            return table[index].regularCount + table[index].emergencyCount;
        }
        if (table[index].key == EMPTY_KEY) {
            cout << "Road (" << static_cast<char>(u + 65) << ", " << static_cast<char>(v + 65) << ") not found in hash table." << endl;
            return -1; // Indicate not found
        }
        // Start random probing to find the key
        int attempts = 0;
        const int MAX_ATTEMPTS = HT_SIZE;
        while (attempts < MAX_ATTEMPTS) {
            int randIndex = randomProbes[attempts] % HT_SIZE;
            if (table[randIndex].key == key) {
                return table[randIndex].regularCount + table[randIndex].emergencyCount;
            }
            attempts++;
        }
        cout << "Road (" << static_cast<char>(u + 65) << ", " << static_cast<char>(v + 65) << ") not found in hash table." << endl;
        return -1; // Indicate not found
    }

    float loadFactor() const {
        return static_cast<float>(occupied) / HT_SIZE;
    }
};
