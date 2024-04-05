#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, string> productLinks;

void LoadProductLinks(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Unable to open file " << filePath << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            string productName = line.substr(0, commaPos);
            string productLink = line.substr(commaPos + 1);
            productLinks[productName] = productLink;
        }
    }
    file.close();
}

void ShowComputerSpecs(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Unable to open file " << filePath << endl;
        return;
    }

    cout << "Choose which specification to display:\n";
    cout << "1. CPU\n";
    cout << "2. Motherboard\n";
    cout << "3. Memory\n";
    cout << "4. Storage\n";
    cout << "5. Graphics\n";
    cout << "6. Cooler\n";
    cout << "7. Case\n";
    cout << "8. Fan\n";
    cout << "9. Power Supply\n";
    cout << "10. Return\n";
    cout << "Enter your choice:";

    int choice;
    cin >> choice;
    cin.ignore(); // Ignore newline character left in input buffer after cin

    string specification;
    switch (choice) {
    case 1:
        specification = "CPU";
        break;
    case 2:
        specification = "Motherboard";
        break;
    case 3:
        specification = "Memory";
        break;
    case 4:
        specification = "Storages";
        break;
    case 5:
        specification = "Graphics";
        break;
    case 6:
        specification = "Cooler";
        break;
    case 7:
        specification = "Case";
        break;
    case 8:
        specification = "Fan";
        break;
    case 9:
        specification = "Power Supply";
        break;
    case 10:
        file.close();
        return;
    default:
        cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.find(specification) != string::npos) {
            cout << line << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Specification not found." << endl;
    }

    file.close();
}

void UpdateProductLinks(const string& filePath) {
    string productName, productLink;
    cout << "Enter part name (e.g., CPU, GPU, RAM): ";
    getline(cin, productName);

    auto it = productLinks.find(productName);
    if (it != productLinks.end()) {
        cout << "Link to '" << productName << "': " << it->second << endl;
    }
    else {
        cout << "No link found for '" << productName << "'" << endl;
    }
}

void DisplayMenu() {
    cout << "\nMenu:" << endl;
    cout << "1. Computer Specification" << endl;
    cout << "2. Link to purchase" << endl;
    cout << "3. Exit" << endl;
}

int main() {
    LoadProductLinks("product_links.txt");

    int choice;
    do {
        DisplayMenu();
        cout << "\nEnter your choice (1-3): ";
        cin >> choice;
        cin.ignore(); // Ignore newline character left in input buffer after cin

        switch (choice) {
        case 1:
            ShowComputerSpecs("systemspec.txt");
            break;
        case 2:
            UpdateProductLinks("product_links.txt");
            break;
        case 3:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
            break;
        }
    } while (choice != 3);

    return 0;
}
