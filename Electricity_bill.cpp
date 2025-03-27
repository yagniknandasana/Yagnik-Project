#include <bits/stdc++.h>
using namespace std;

// Structure to store consumer details and billing informations
struct Consumer {
    int consumerID;
    string name;
    string address;
    string mobileNo;
};

struct Bill {
    int consumerID;
    int month;
    int year;
    int unitsConsumed;
    double amt;
};

 double costPerUnit = 8.0;

//consumer and bill records are stored in vectors
vector<Consumer> consumerDetails;
vector<Bill> billDetails;

//Validations for mobile no., month, year, address
bool valid_num(const string& mobileNo) {
    if (mobileNo.length() != 10) {
        return false;
    }

    for (char c : mobileNo) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool vaildYear(int year) {
    return year >= 2000 && year <= 2024;
}

bool vaildMonth(int month) {
    return month >= 1 && month <= 12;
}

bool validAddress(const string& address) {
    return !address.empty() && address.length() >= 7;
}

// This function checks whether the consumer already exists
bool checkConsumer(int consumerID) {
    for (const auto& consumer : consumerDetails) {
        if (consumer.consumerID == consumerID) {
            return true;
        }
    }
    return false;
}

// This function checks whether the bill of input consumer exists
bool checkBill(int consumerID, int month, int year) {
    for (const auto& bill : billDetails) {
        if (bill.consumerID == consumerID && bill.month == month && bill.year == year) {
            return true;
        }
    }
    return false;
}

// this function to adding a new consumer in the consumer vector
void addConsumer(int consumerID, string name, string address, string mobileNo) {
    if (!valid_num(mobileNo)) {
        cout << "Invalid mobile no." << endl;
        return;
    }
    if (!validAddress(address)) {
        cout << "Invalid address." << endl;
        return;
    }

    // check weather the consumer ID already existed or not
    if (checkConsumer(consumerID)) {
        cout << "Consumer already exists." << endl;
        return;
    }

    consumerDetails.push_back({consumerID, name, address, mobileNo});
    cout << "Consumer successfully added." << endl;
}

// Gives the list of all consumers which are entered
void displayConsumer() {
    if (consumerDetails.empty()) {
        cout << "No consumer records found." << endl;
        return;
    }

    cout << "\nList of Consumers:\n";
    for (const auto& consumer : consumerDetails) {
        cout << "Consumer ID: " << consumer.consumerID << endl;
        cout << "Name: " << consumer.name << endl;
        cout << "Address: " << consumer.address << endl;
        cout << "Mobile Number: " << consumer.mobileNo << endl;
        cout << "----------------------------" << endl;
    }
}

// this function checks the validation before adding the new bill
void addBill(int consumerID, int month, int year, int unitsConsumed) {
    if (!vaildMonth(month)) {
        cout << "Invalid month." << endl;
        return;
    }
    if (!vaildYear(year)) {
        cout << "Invalid year." << endl;
        return;
    }
    if (!checkConsumer(consumerID)) {
        cout << "Consumer not found." << endl;
        return;
    }
    if (checkBill(consumerID, month, year)) {
        cout << "Consumer already exists." << endl;
        return;
    }

    double amt = unitsConsumed * costPerUnit;
    billDetails.push_back({consumerID, month, year, unitsConsumed, amt});
    cout << "Bill added successfully ." << endl;
}

// this function is used to display a bill of a specific consumer
void generateBill(int consumerID, int month, int year) {
    if (!vaildYear(year)) {
        cout << "Invalid year." << endl;
        return;
    }

    // To find the record of user input consumer ID
    Consumer* consumerPtr = nullptr;
    for (auto& consumer : consumerDetails) {
        if (consumer.consumerID == consumerID) {
            consumerPtr = &consumer;
            break;
        }
    }

    if (!consumerPtr) {
        cout << "Consumer not found." << endl;
        return;
    }

    // To find the bill of user input consumer ID
    Bill* currentBill = nullptr;
    for (auto& bill : billDetails) {
        if (bill.consumerID == consumerID && bill.month == month && bill.year == year) {
            currentBill = &bill;
            break;
        }
    }

    if (!currentBill) {
        cout << "No bill found for the given month and year." << endl;
        return;
    }

    // To display the consumer bill
    cout << fixed << setprecision(2);
    cout << "\nBill for " << month << "/" << year << " for consumer " << consumerID << ":\n";
    cout << "Consumer Name: " << consumerPtr->name << endl;
    cout << "Address: " << consumerPtr->address << endl;
    cout << "Mobile Number: " << consumerPtr->mobileNo << endl;
    cout << "Units Consumed: " << currentBill->unitsConsumed << endl;
    cout << "amount Due: " << currentBill->amt << endl;

    // Collect past bills for reference
    vector<Bill> pastBill;
    for (const auto& bill : billDetails) {
        if (bill.consumerID == consumerID && (bill.year < year || (bill.year == year && bill.month < month))) {
            pastBill.push_back(bill);
        }
    }

    // This gives the past three months bill details of the consumer by sorting
    sort(pastBill.begin(), pastBill.end(), [](const Bill& a, const Bill& b) {
        return (a.year != b.year) ? (a.year > b.year) : (a.month > b.month);
    });

    cout << "\nPrevious 3 months Bills:\n";
    for (int i = 0; i < min(pastBill.size(), size_t(3)); ++i) {
        cout << "  Month: " << pastBill[i].month << "/" << pastBill[i].year << " - amount: " << pastBill[i].amt << endl;
    }
}

// Main function for user interactions
int main() {
    int choice;
    while (true) {
        cout << "Menu:"<<endl;
        cout << "1. To Add Consumer"<<endl;
        cout << "2. To Display all Consumers"<<endl;
        cout << "3. To Add Bill"<<endl;
        cout << "4. To Generate Bill of particular consumer"<<endl;
        cout << "5. Exit"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int consumerID;
                string name, address, mobileNo;
                cout << "Enter consumer ID: ";
                cin >> consumerID;
                cin.ignore();
                cout << "Enter consumer's name: ";
                getline(cin, name);
                cout << "Enter consumer's address: ";
                getline(cin, address);
                cout << "Enter consumer's mobile number: ";
                getline(cin, mobileNo);

                addConsumer(consumerID, name, address, mobileNo);
                break;
            }
            case 2:
                displayConsumer();
                break;
            case 3: {
                int consumerID, month, year, unitsConsumed;
                cout << "Enter consumer ID: ";
                cin >> consumerID;
                cout << "Enter month: ";
                cin >> month;
                cout << "Enter year: ";
                cin >> year;
                cout << "Enter total units consumed: ";
                cin >> unitsConsumed;

                addBill(consumerID, month, year, unitsConsumed);
                break;
            }
            case 4: {
                int consumerID, month, year;
                cout << "Enter consumer ID: ";
                cin >> consumerID;
                cout << "Enter month: ";
                cin >> month;
                cout << "Enter year: ";
                cin >> year;

                generateBill(consumerID, month, year);
                break;
            }
            case 5:
                cout << "Exiting the program....." << endl;
                return 0;
            default:
                cout <<"Choose correct option."<< endl;
        }
    }
}
