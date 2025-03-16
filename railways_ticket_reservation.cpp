#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Passenger {
public:
    string name, train, source, destination, berth;
    int age, seat, pnr;

    void inputDetails() {
        cout << "\nEnter Name: ";
        cin.ignore();
        getline(cin, name);
        
        cout << "Enter Age: ";
        cin >> age;

        cin.ignore();
        cout << "Enter Train Number: ";
        getline(cin, train);
        
        cout << "Enter Source: ";
        getline(cin, source);

        cout << "Enter Destination: ";
        getline(cin, destination);

        cout << "Enter Berth Preference (Lower, Middle, Upper, SideLower, SideUpper): ";
        cin >> berth;

        seat = rand() % 100 + 1;
        pnr = rand() % 900000 + 100000; 
    }

    void saveToFile() {
        ofstream file("tickets.txt", ios::app);
        file << pnr << " | " << name << " | " << age << " | " << train << " | " << source << " | " 
             << destination << " | " << seat << " | " << berth << "\n";
        file.close();
        cout << "Ticket Booked Successfully! PNR: " << pnr << ", Seat Number: " << seat << ", Berth: " << berth << "\n";
    }
};

class TicketManager {
public:
    void bookTicket() {
        Passenger p;
        p.inputDetails();
        p.saveToFile();
    }

    void viewTickets() {
        ifstream file("tickets.txt");
        if (!file) {
            cout << "No tickets booked yet!\n";
            return;
        }

        string line;
        cout << "\nBooked Tickets:\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }

    void searchByPNR() {
        int searchPNR;
        cout << "Enter PNR to search: ";
        cin >> searchPNR;

        ifstream file("tickets.txt");
        if (!file) {
            cout << "No tickets booked yet!\n";
            return;
        }

        string line;
        bool found = false;
        while (getline(file, line)) {
            if (line.find(to_string(searchPNR)) != string::npos) {
                cout << "Ticket Found: " << line << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "PNR not found!\n";
        }
        
        file.close();
    }

    void searchByTrainNumber() {
        string searchTrain;
        cout << "Enter Train Number to search: ";
        cin.ignore();
        getline(cin, searchTrain);

        ifstream file("tickets.txt");
        if (!file) {
            cout << "No tickets booked yet!\n";
            return;
        }

        string line;
        bool found = false;
        cout << "\nTickets for Train " << searchTrain << ":\n";
        while (getline(file, line)) {
            if (line.find(searchTrain) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }
        
        if (!found) {
            cout << "No tickets found for the given train number!\n";
        }
        
        file.close();
    }

    void cancelTicket() {
        int cancelPNR, journeyTime;
        cout << "Enter PNR to cancel ticket: ";
        cin >> cancelPNR;
        cout << "Enter Journey Time (in hours from now): ";
        cin >> journeyTime;

        ifstream file("tickets.txt");
        if (!file) {
            cout << "No tickets booked yet!\n";
            return;
        }

        ofstream temp("temp.txt");
        string line;
        bool found = false;
        while (getline(file, line)) {
            if (line.find(to_string(cancelPNR)) != string::npos) {
                if (journeyTime <= 6) {
                    cout << "Ticket cannot be canceled within 6 hours of journey time.\n";
                    temp << line << "\n";
                } else {
                    cout << "Ticket with PNR " << cancelPNR << " has been canceled.\n";
                    cout << "Cancellation fee: 50 units\n";
                    found = true;
                }
            } else {
                temp << line << "\n";
            }
        }
        
        file.close();
        temp.close();

        remove("tickets.txt");
        rename("temp.txt", "tickets.txt");

        if (!found) {
            cout << "PNR not found or cannot be canceled!\n";
        }
    }
};

int main() {
    srand(time(0));
    TicketManager manager;
    int choice;
    do {
        cout << "\n1. Book Ticket\n2. View Tickets\n3. Search by PNR\n4. Search by Train Number\n5. Cancel Ticket\n6. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.bookTicket(); break;
            case 2: manager.viewTickets(); break;
            case 3: manager.searchByPNR(); break;
            case 4: manager.searchByTrainNumber(); break;
            case 5: manager.cancelTicket(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
