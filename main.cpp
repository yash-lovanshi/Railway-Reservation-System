#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>   // malloc(), free()
using namespace std;

const int TOTAL_SEATS = 30;

struct Passenger {
    int seatNo;
    string name;
    int age;
    char gender;
    Passenger* next;
};

// Find the first available seat. Returns its array index, or -1 if full.
int findAvailableSeat(int* seats) {
    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (seats[i] == 0) {
            return i;
        }
    }
    return -1;
}

// Add a passenger node at the end of the linked list.
void addPassenger(Passenger*& head, int seatNo, const string& name,
                  int age, char gender) {
    Passenger* newNode = new Passenger;
    newNode->seatNo = seatNo;
    newNode->name = name;
    newNode->age = age;
    newNode->gender = gender;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Passenger* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
}

// Book the first available seat and save passenger details.
void bookTicket(int* seats, Passenger*& head) {
    int index = findAvailableSeat(seats);

    if (index == -1) {
        cout << "\nSorry, all seats are booked.\n";
        return;
    }

    string name;
    int age;
    char gender;

    cout << "\nEnter passenger name: ";
    getline(cin, name);

    if (name.empty()) {
        cout << "Name cannot be empty. Booking cancelled.\n";
        return;
    }

    cout << "Enter age: ";
    if (!(cin >> age) || age <= 0) {
        cout << "Invalid age. Booking cancelled.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter gender (M/F/O): ";
    cin >> gender;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    gender = static_cast<char>(toupper(static_cast<unsigned char>(gender)));
    if (gender != 'M' && gender != 'F' && gender != 'O') {
        cout << "Invalid gender. Please enter M, F, or O. Booking cancelled.\n";
        return;
    }

    int seatNo = index + 1;
    addPassenger(head, seatNo, name, age, gender);
    seats[index] = 1;

    cout << "\nTicket booked successfully! Seat No: " << seatNo << "\n";
}

// Remove the passenger record for a given seat and make the seat available.
void cancelTicket(int* seats, Passenger*& head) {
    int seatNo;

    cout << "\nEnter seat number to cancel (1-" << TOTAL_SEATS << "): ";
    if (!(cin >> seatNo)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (seatNo < 1 || seatNo > TOTAL_SEATS) {
        cout << "Seat number is out of range.\n";
        return;
    }

    if (seats[seatNo - 1] == 0) {
        cout << "This seat is already available.\n";
        return;
    }

    Passenger* current = head;
    Passenger* previous = nullptr;

    while (current != nullptr && current->seatNo != seatNo) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Passenger record not found.\n";
        return;
    }

    if (previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;
    seats[seatNo - 1] = 0;

    cout << "Ticket for seat " << seatNo << " cancelled successfully.\n";
}

// Display whether each seat is booked or available.
void viewTrainStatus(const int* seats) {
    cout << "\n--- Train Seat Status ---\n";
    for (int i = 0; i < TOTAL_SEATS; i++) {
        cout << "Seat " << i + 1 << ": "
             << (seats[i] == 1 ? "Booked" : "Available") << '\n';
    }
}

// Traverse and display all passenger nodes.
void viewPassengerList(const Passenger* head) {
    if (head == nullptr) {
        cout << "\nNo passengers have booked tickets yet.\n";
        return;
    }

    cout << "\n--- Passenger List ---\n";
    const Passenger* current = head;

    while (current != nullptr) {
        cout << "Seat No: " << current->seatNo
             << " | Name: " << current->name
             << " | Age: " << current->age
             << " | Gender: " << current->gender << '\n';

        current = current->next;
    }
}

// Release all linked-list nodes before the program exits.
void freePassengerList(Passenger*& head) {
    while (head != nullptr) {
        Passenger* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // Dynamically allocate an array for 30 seat statuses.
    int* seats = static_cast<int*>(malloc(TOTAL_SEATS * sizeof(int)));

    if (seats == nullptr) {
        cout << "Memory allocation failed. Program cannot continue.\n";
        return 1;
    }

    for (int i = 0; i < TOTAL_SEATS; i++) {
        seats[i] = 0; // 0 means Available
    }

    Passenger* head = nullptr;
    int choice;

    do {
        cout << "\n===== Railway Reservation System =====\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. View Train Status\n";
        cout << "4. View Passenger List\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number from 1 to 5.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                bookTicket(seats, head);
                break;
            case 2:
                cancelTicket(seats, head);
                break;
            case 3:
                viewTrainStatus(seats);
                break;
            case 4:
                viewPassengerList(head);
                break;
            case 5:
                freePassengerList(head);
                free(seats);
                cout << "All allocated memory released. Thank you!\n";
                break;
            default:
                cout << "Please select a valid option (1-5).\n";
        }
    } while (choice != 5);

    return 0;
}
