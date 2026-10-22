
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
using namespace std;

// Class to manage grocery purchase information
class GroceryTracker {
private:
    map<string, int> itemCounts;

public:
    // Read grocery items from the input file
    bool LoadFile(string fileName) {
        ifstream inputFile(fileName);
        string item;

        if (!inputFile.is_open()) {
            cout << "Error: Could not open input file." << endl;
            return false;
        }

        while (inputFile >> item) {
            itemCounts[item]++;
        }

        inputFile.close();
        return true;
    }

    // Create a backup file with item frequencies
    void SaveBackup() {
        ofstream outputFile("frequency.dat");

        if (!outputFile.is_open()) {
            cout << "Error: Could not create backup file." << endl;
            return;
        }

        for (auto item : itemCounts) {
            outputFile << item.first << " "
                       << item.second << endl;
        }

        outputFile.close();
    }

    // Option 1: Search for an item
    void SearchItem() {
        string item;

        cout << "Enter the item to search for: ";
        cin >> item;

        cout << item << " was purchased "
             << itemCounts[item] << " times." << endl;
    }

    // Option 2: Display all item frequencies
    void DisplayFrequencies() {
        cout << endl << "ITEM FREQUENCIES" << endl;

        for (auto item : itemCounts) {
            cout << item.first << " "
                 << item.second << endl;
        }
    }

    // Option 3: Display a histogram
    void DisplayHistogram() {
        cout << endl << "PURCHASE HISTOGRAM" << endl;

        for (auto item : itemCounts) {
            cout << item.first << " ";

            for (int i = 0; i < item.second; i++) {
                cout << "*";
            }

            cout << endl;
        }
    }
};

int main() {
    GroceryTracker tracker;
    int choice = 0;

    // Load purchase records
    if (!tracker.LoadFile(
        "CS210_Project_Three_Input_File.txt")) {
        return 1;
    }

    // Automatically create the backup file
    tracker.SaveBackup();

    // Keep displaying the menu until user exits
    while (choice != 4) {
        cout << endl;
        cout << "*****************************" << endl;
        cout << "       CORNER GROCER" << endl;
        cout << "*****************************" << endl;
        cout << "1. Search for an item" << endl;
        cout << "2. Display item frequencies" << endl;
        cout << "3. Display histogram" << endl;
        cout << "4. Exit program" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter 1-4." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            tracker.SearchItem();
            break;

        case 2:
            tracker.DisplayFrequencies();
            break;

        case 3:
            tracker.DisplayHistogram();
            break;

        case 4:
            cout << "Thank you for using Corner Grocer!"
                 << endl;
            break;

        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
