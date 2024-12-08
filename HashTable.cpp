#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

/**
 * HashTable class provides a structure for storing and managing entries with unique keys,
 * which represent roads between two nodes identified by integers.
 */
class HashTable {
    static constexpr int HT_SIZE = 653; /**
     * Represents a constant or sentinel value that is used as a placeholder
     * for an empty or null key in data structures or algorithms where
     * differentiation between a null key and an absent key is necessary.
     *
     * Typically used in hashmap or hashtable implementations to indicate
     * a slot that has been previously occupied but is currently empty,
     * distinguishing it from a never-occupied slot.
     */
    static constexpr int EMPTY_KEY = -1;
    /**
     * Represents a special marker key indicating a deleted entry within the hash table.
     * This is used to distinguish between empty and previously used slots that can be re-used.
     */
    static constexpr int DELETED_KEY = -2;

    /**
     * @struct HashEntry
     * @brief Represents an entry in a hash table.
     *
     * This structure is used to store key-value pairs in a hash table,
     * where the key is an integer and the values are counts for regular
     * and emergency entries*/
    struct HashEntry {
        /**
         * Represents the key value used in the hash table entry.
         * This key is a unique identifier for each entry in the hash table.
         */
        int key;
        /**
         * Stores the count of regular events or accesses associated with a specific hash entry.
         * This variable helps track the frequency or usage of an entry under non-emergency conditions.
         */
        int regularCount;
        /**
         * @brief Tracks the number of times a road segment is marked as an emergency.
         *
         * Used within a hash table entry to record the count of emergency events
         * associated with a particular key, representing a road segment.
         */
        int emergencyCount;
    };

    /**
     * A 2D array used for storing data in a tabular format.
     * The 'table' variable represents a matrix where each entry can hold a specific type of data.
     * This structure is often used for various computations or data organization tasks.
     *
     * Common use cases include:
     * - Performing mathematical operations on a matrix.
     * - Organizing and accessing data in rows and columns.
     * - Implementing algorithms that require a grid or matrix form.
     *
     * It's important to ensure that all operations on this variable maintain its integrity,
     * respecting its dimensions and data type consistency.
     */
    HashEntry table[HT_SIZE];
    /**
     * @brief Tracks the number of occupied slots in the hash table.
     *
     * This variable is incremented whenever a new entry is successfully inserted
     * into the hash table and decremented when an entry is removed. It acts as
     * a counter to keep track of how many slots are occupied at any given time,
     * providing a way to monitor the hash table's load factor.
     */
    int occupied;
    /**
     * @brief Represents the number of random probes to be executed.
     *
     * The `randomProbes` variable is utilized to determine how many times
     * a certain operation or function should be randomly invoked or tested.
     * This is commonly used in scenarios where random sampling or stochastic
     * testing is performed to verify functionality, ascertain performance,
     * or gather statistical data.
     */
    int randomProbes[HT_SIZE];

    /**
     * Computes the hash value for a given key using the modulo operation.
     *
     * @param key The integer key that requires hashing.
     * @return The hash value calculated as the remainder of the division of
     *         the key by HT_SIZE, which determines the index in the hash table.
     */
    int hashFunction(int key) const {
        return key % HT_SIZE;
    }

    /**
     * Generates a random index within the bounds of the hash table size.
     *
     * @return A random index between 0 and HT_SIZE - 1 inclusive.
     */
    int getRandomIndex() const {
        return rand() % HT_SIZE;
    }

    /**
     * Constructs a new HashTable object and initializes its entries and probes.
     * Each entry in the table is set with an EMPTY_KEY and count values are initialized to zero.
     * Random probes are initialized with random values within the table size range.
     * The number of occupied entries is initialized to zero.
     *
     * @return A newly constructed instance of the HashTable class.
     */
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

    /**
     * Inserts a road connection between nodes u and v into the hash table.
     * Utilizes random probing to handle collisions.
     *
     * @param u The first node identifier.
     * @param v The second node identifier.
     */
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

    /**
     * Removes a road from the hash table based on given endpoints.
     * If the road exists in the hash table, it will be marked as deleted.
     * If the road does not exist, an appropriate message will be printed.
     *
     * @param u The first endpoint of the road (integer representation of node).
     * @param v The second endpoint of the road (integer representation of node).
     */
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

    /**
     * Searches for a road defined by endpoints 'u' and 'v' in the hash table and retrieves the count based on the emergency flag.
     *
     * @param u The first endpoint of the road.
     * @param v The second endpoint of the road.
     * @param isEmergency A boolean flag to specify if the search is for an emergency count.
     * @return The number of counts for the specified road: emergency if isEmergency is true, otherwise regular. Returns -1 if the road is not found.
     */
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

    /**
     * Increments the current count value by a specified amount.
     *
     * @param currentCount The current value of the count before incrementation.
     * @param incrementValue The value to add to the current count.
     * @return The new count value after incrementation.
     */
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

    /**
     * Decrements the current count by a specified value.
     *
     * @param decrementValue The value by which the count should be decreased.
     *                       Must be a positive integer.
     */
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

    /**
     * @brief Displays a given message or output.
     *
     * This function is responsible for presenting information to the user
     * or logging system. The specific implementation of how the display
     * occurs (e.g., console output, GUI, log file) is dependent on the
     * context in which this function is used.
     *
     * @param message The content or information to be displayed.
     */
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

    /**
     * Calculates the density of traffic for a given road identified by coordinates.
     *
     * This function searches for a road in the hash table using the provided
     * coordinates and calculates the density as the sum of regular and emergency
     * vehicle counts associated with the road.
     *
     * @param u The first coordinate value representing part of the road identifier.
     * @param v The second coordinate value representing part of the road identifier.
     * @return The density as a float, calculated as the sum of regular and emergency
     *         counts if the road is found. Returns -1 if the road is not found.
     */
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

    /**
     * Computes the load factor of the data structure, which is a measure
     * of how full it is. The load factor is typically defined as the ratio
     * of the number of elements stored in the structure to the total
     * capacity of the structure.
     *
     * @return The load factor as a double.
     */
    float loadFactor() const {
        return static_cast<float>(occupied) / HT_SIZE;
    }
};
