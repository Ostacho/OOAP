#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Resident {
public:
    string name;
    string birthDate;
    string faculty;
    string group;
    string educationForm;
    double rent;

    Resident(string name, string birthDate, string faculty, string group, string educationForm, double rent)
        : name(name), birthDate(birthDate), faculty(faculty), group(group), educationForm(educationForm), rent(rent) {}

    void displayInfo() const {
        cout << "Name: " << name << ", Birth date: " << birthDate
            << ", Faculty: " << faculty << ", Group: " << group
            << ", Education form: " << educationForm
            << ", Rent: " << rent << " UAH" << endl;
    }
};

class Room {
protected:
    string type;
    vector<Resident> residents;

public:
    Room(string type) : type(type) {}

    void addResident(const Resident& resident) {
        residents.push_back(resident);
    }

    size_t getResidentCount() const {
        return residents.size();
    }

    virtual Room* clone() const = 0;

    virtual void displayInfo() const {
        cout << "Room type: " << type << ", Number of residents: " << residents.size() << endl;
        for (const auto& resident : residents) {
            resident.displayInfo();
        }
    }

    virtual void generateReport(const string& filename) const {
        ofstream report(filename, ios::app);
        if (!report.is_open()) {
            cerr << "Failed to open file." << endl;
            return;
        }

        report << "Room type: " << type << "\n";
        report << "Number of residents: " << residents.size() << "\n";
        for (const auto& resident : residents) {
            report << "Name: " << resident.name
                << ", Birth date: " << resident.birthDate
                << ", Faculty: " << resident.faculty
                << ", Group: " << resident.group
                << ", Education form: " << resident.educationForm
                << ", Rent: " << resident.rent << " UAH\n";
        }
        report << "----------------------------------------\n";
        report.close();
    }

    virtual size_t maxCapacity() const = 0;

    virtual ~Room() {}
};


class DoubleRoom : public Room {
public:
    DoubleRoom() : Room("Double") {}

    Room* clone() const override {
        return new DoubleRoom(*this);
    }

    size_t maxCapacity() const override {
        return 2;
    }
};

class TripleRoom : public Room {
public:
    TripleRoom() : Room("Triple") {}

    Room* clone() const override {
        return new TripleRoom(*this);
    }

    size_t maxCapacity() const override {
        return 4;
    }
};

vector<Room*> rooms;

void initializeDefaultRooms() {
    DoubleRoom* doubleRoomPrototype = new DoubleRoom();
    TripleRoom* tripleRoomPrototype = new TripleRoom();

    Room* room1 = doubleRoomPrototype->clone();
    room1->addResident(Resident("Salvan Tomas", "01.01.2000", "FIT", "KNS-21", "State order", 1500));
    room1->addResident(Resident("Knauf Helan", "02.02.2001", "FIT", "ISTS-41", "Self-funded", 2000));

    Room* room2 = tripleRoomPrototype->clone();
    room2->addResident(Resident("Sidoriv", "03.03.1933", "FIT", "KNS-21", "State order", 1500));
    room2->addResident(Resident("Olgard Olmond", "04.04.2001", "FIT", "KNS-21", "State order", 1500));
    room2->addResident(Resident("Trush Oleg", "05.05.2001", "FIT", "KNS-21", "Self-funded", 2000));

    rooms.push_back(room1);
    rooms.push_back(room2);

    delete doubleRoomPrototype;
    delete tripleRoomPrototype;
}

void clearAllRooms() {
    for (auto room : rooms) {
        delete room;
    }
    rooms.clear();
    cout << "All records have been deleted." << endl;
}

void displayAllRooms() {
    if (rooms.empty()) {
        cout << "No rooms available." << endl;
    }
    else {
        for (size_t i = 0; i < rooms.size(); ++i) {
            cout << "Room " << i + 1 << ":" << endl;
            rooms[i]->displayInfo();
        }
    }
}

void addResidentToRoom() {
    if (rooms.empty()) {
        cout << "No rooms available. Add a room first." << endl;
        return;
    }

    size_t roomIndex;
    displayAllRooms();
    cout << "Enter the room number to add a resident to: ";
    cin >> roomIndex;

    if (roomIndex < 1 || roomIndex > rooms.size()) {
        cout << "Invalid room number." << endl;
        return;
    }

    Room* selectedRoom = rooms[roomIndex - 1];
    if (selectedRoom->maxCapacity() <= selectedRoom->getResidentCount()) {
        cout << "The room is already full." << endl;
        return;
    }

    string name, birthDate, faculty, group, educationForm;
    double rent;

    cout << "Enter resident details:" << endl;
    cout << "Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Birth date: ";
    getline(cin, birthDate);
    cout << "Faculty: ";
    getline(cin, faculty);
    cout << "Group: ";
    getline(cin, group);
    cout << "Education form (State order/Self-funded): ";
    getline(cin, educationForm);
    cout << "Rent: ";
    cin >> rent;

    selectedRoom->addResident(Resident(name, birthDate, faculty, group, educationForm, rent));
    cout << "Resident added successfully." << endl;
}


void displayMenu() {
    cout << "\nMenu:" << endl;
    cout << "1. Display all rooms" << endl;
    cout << "2. Add a resident to a room" << endl;
    cout << "3. Clear all records" << endl;
    cout << "4. Generate report" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    initializeDefaultRooms();

    string reportFile = "report.txt";
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            displayAllRooms();
            break;
        case 2:
            addResidentToRoom();
            break;
        case 3:
            clearAllRooms();
            break;
        case 4:
            for (const auto& room : rooms) {
                room->generateReport(reportFile);
            }
            cout << "Report successfully generated in file: " << reportFile << endl;
            break;
        case 5:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    clearAllRooms();
    return 0;
}
