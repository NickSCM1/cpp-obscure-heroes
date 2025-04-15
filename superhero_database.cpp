#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <limits> // Required for numeric_limits

using namespace std;

// Function to convert a string to uppercase
string toUpper(string str) {
    string result = "";
    for (char c : str) {
        result += toupper(c);
    }
    return result;
}

// Function to convert a string to lowercase
string toLower(string str) {
    string result = "";
    for (char c : str) {
        result += tolower(c);
    }
    return result;
}

// Function to display all superheroes
void displaySuperheroes(const vector<string>& names, const vector<string>& superpowers,
                        const vector<string>& weaknesses, const vector<int>& years,
                        const vector<string>& universes, bool uppercase) {
    cout << "\n--- Superhero Database ---" << endl;
    cout << "Name         | Superpower         | Weakness   | Year | Universe  " << endl;
    cout << "------------------------------------------------------" << endl;

    for (size_t i = 0; i < names.size(); ++i) {
        string name = names[i];
        string superpower = superpowers[i];
        string weakness = weaknesses[i];
        int year = years[i];
        string universe = universes[i];

        if (uppercase) {
            name = toUpper(name);
            superpower = toUpper(superpower);
            weakness = toUpper(weakness);
            universe = toUpper(universe);
        } else {
            name = toLower(name);
            superpower = toLower(superpower);
            weakness = toLower(weakness);
            universe = toLower(universe);
        }

        cout << name << " | " << superpower << " | " << weakness << " | "
             << year << " | " << universe << endl;
    }
    cout << endl;
}

// Function to search for a superhero by name (case-insensitive)
void searchByName(const vector<string>& names, const vector<string>& superpowers,
                  const vector<string>& weaknesses, const vector<int>& years,
                  const vector<string>& universes, const string& searchName) {
    string lowerSearchName = toLower(searchName);
    bool found = false;

    for (size_t i = 0; i < names.size(); ++i) {
        if (toLower(names[i]).find(lowerSearchName) != string::npos) {
            cout << "\nSuperhero Found:" << endl;
            cout << "Name: " << names[i] << endl;
            cout << "Superpower: " << superpowers[i] << endl;
            cout << "Weakness: " << weaknesses[i] << endl;
            cout << "Year Introduced: " << years[i] << endl;
            cout << "Comic Universe: " << universes[i] << endl;
            found = true;
            break; // Stop after the first match
        }
    }

    if (!found) {
        cout << "Superhero '" << searchName << "' not found." << endl;
    }
}

// Function to find superheroes by their superpower (substring search)
void findBySuperpower(const vector<string>& names, const vector<string>& superpowers,
                      const vector<string>& weaknesses, const vector<int>& years,
                      const vector<string>& universes, const string& searchPower) {
    string lowerSearchPower = toLower(searchPower);
    bool found = false;

    cout << "\nSuperheroes with superpower '" << searchPower << "':" << endl;
    for (size_t i = 0; i < superpowers.size(); ++i) {
        if (toLower(superpowers[i]).find(lowerSearchPower) != string::npos) {
            cout << "Name: " << names[i] << endl;
            cout << "Superpower: " << superpowers[i] << endl;
            cout << "Weakness: " << weaknesses[i] << endl;
            cout << "Year Introduced: " << years[i] << endl;
            cout << "Comic Universe: " << universes[i] << endl;
            cout << "------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No superheroes found with superpower '" << searchPower << "'." << endl;
    }
}

// Function to sort superheroes alphabetically by name
void sortAlphabetically(vector<string>& names, vector<string>& superpowers,
                        vector<string>& weaknesses, vector<int>& years,
                        vector<string>& universes) {
    vector<size_t> indices(names.size());
    for (size_t i = 0; i < names.size(); ++i) {
        indices[i] = i;
    }

    sort(indices.begin(), indices.end(), [&](size_t a, size_t b) {
        return names[a] < names[b];
    });

    // Create temporary vectors to store the sorted data
    vector<string> sortedNames(names.size());
    vector<string> sortedSuperpowers(superpowers.size());
    vector<string> sortedWeaknesses(weaknesses.size());
    vector<int> sortedYears(years.size());
    vector<string> sortedUniverses(universes.size());

    // Populate the sorted vectors
    for (size_t i = 0; i < names.size(); ++i) {
        sortedNames[i] = names[indices[i]];
        sortedSuperpowers[i] = superpowers[indices[i]];
        sortedWeaknesses[i] = weaknesses[indices[i]];
        sortedYears[i] = years[indices[i]];
        sortedUniverses[i] = universes[indices[i]];
    }

    // Copy the sorted data back to the original arrays
    names = sortedNames;
    superpowers = sortedSuperpowers;
    weaknesses = sortedWeaknesses;
    years = sortedYears;
    universes = sortedUniverses;

    cout << "Superheroes sorted alphabetically." << endl;
}

// Function to add a new superhero
void addSuperhero(vector<string>& names, vector<string>& superpowers,
                   vector<string>& weaknesses, vector<int>& years,
                   vector<string>& universes) {
    string name, superpower, weakness, universe;
    int year;

    cout << "\nEnter the name of the new superhero: ";
    getline(cin, name);

    cout << "Enter the superpower of the new superhero: ";
    getline(cin, superpower);

    cout << "Enter the weakness of the new superhero: ";
    getline(cin, weakness);

    cout << "Enter the year the superhero was introduced: ";
    cin >> year;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Consume the newline character

    cout << "Enter the comic universe (Marvel, DC, or Other): ";
    getline(cin, universe);

    // Add the new superhero's data
    names.push_back(name);
    superpowers.push_back(superpower);
    weaknesses.push_back(weakness);
    years.push_back(year);
    universes.push_back(universe);

    cout << "Superhero '" << name << "' added successfully!" << endl;
}

// Function to load superhero data from file
bool loadSuperheroData(vector<string>& names, vector<string>& superpowers,
                       vector<string>& weaknesses, vector<int>& years,
                       vector<string>& universes, const string& filename) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file '" << filename << "' for reading." << endl;
        return false;
    }

    names.clear();
    superpowers.clear();
    weaknesses.clear();
    years.clear();
    universes.clear();

    string line;
    while (getline(inputFile, line)) {
        names.push_back(line);
        getline(inputFile, line);
        superpowers.push_back(line);
        getline(inputFile, line);
        weaknesses.push_back(line);
        getline(inputFile, line);
        years.push_back(stoi(line));
        getline(inputFile, line);
        universes.push_back(line);
    }

    inputFile.close();
    return true;
}

// Function to save superhero data to file
bool saveSuperheroData(const vector<string>& names, const vector<string>& superpowers,
                       const vector<string>& weaknesses, const vector<int>& years,
                       const vector<string>& universes, const string& filename) {
    ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        cerr << "Error: Could not open file '" << filename << "' for writing." << endl;
        return false;
    }

    for (size_t i = 0; i < names.size(); ++i) {
        outputFile << names[i] << endl;
        outputFile << superpowers[i] << endl;
        outputFile << weaknesses[i] << endl;
        outputFile << years[i] << endl;
        outputFile << universes[i] << endl;
    }

    outputFile.close();
    return true;
}

// Function to clear the input buffer
void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    // Declare the data structures
    vector<string> names;
    vector<string> superpowers;
    vector<string> weaknesses;
    vector<int> years;
    vector<string> universes;

    const string dataFilename = "SuperheroData.txt";

    // Load the superhero data from the file
    if (!loadSuperheroData(names, superpowers, weaknesses, years, universes, dataFilename)) {
        cout << "Failed to load superhero data.  Creating a new data file." << endl;

        // Save the default data to the file
        if (!saveSuperheroData(names, superpowers, weaknesses, years, universes, dataFilename)) {
            cout << "Failed to save initial data.  Exiting." << endl;
            return 1;
        }
    }

    int choice;
    string searchName, searchPower;

    do {
        cout << "\n--- Superhero Database Menu ---" << endl;
        cout << "1. Display All Superheroes" << endl;
        cout << "2. Search by Name" << endl;
        cout << "3. Find by Superpower" << endl;
        cout << "4. Sort Alphabetically" << endl;
        cout << "5. Display in Uppercase" << endl;
        cout << "6. Display in Lowercase" << endl;
        cout << "7. Add New Superhero" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer(); // Consume the newline character

        switch (choice) {
            case 1:
                displaySuperheroes(names, superpowers, weaknesses, years, universes, false);
                break;
            case 2:
                cout << "Enter the name to search for: ";
                getline(cin, searchName);
                searchByName(names, superpowers, weaknesses, years, universes, searchName);
                break;
            case 3:
                cout << "Enter the superpower to search for: ";
                getline(cin, searchPower);
                findBySuperpower(names, superpowers, weaknesses, years, universes, searchPower);
                break;
            case 4:
                sortAlphabetically(names, superpowers, weaknesses, years, universes);
                break;
            case 5:
                displaySuperheroes(names, superpowers, weaknesses, years, universes, true);
                break;
            case 6:
                displaySuperheroes(names, superpowers, weaknesses, years, universes, false);
                break;
            case 7:           
                addSuperhero(names, superpowers, weaknesses, years, universes);
                break;
        case 0:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }

    // Save data after each modification
    if (choice >= 4 && choice <= 7) {
        if (!saveSuperheroData(names, superpowers, weaknesses, years, universes, dataFilename)) {
            cout << "Error saving data to file!" << endl;
        }
    }

} while (choice != 0);

return 0;
}