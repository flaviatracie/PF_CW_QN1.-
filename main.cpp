#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class ATM {
private:
    unordered_map<string, string> accounts; // Stores user_id and password
    unordered_map<string, double> balances; // Stores user_id and balance
    string loggedInUser;

public:
    ATM() : loggedInUser("") {}

    void createAccount(const string& userId, const string& password) {
        if (accounts.find(userId) != accounts.end()) {
            cout << "Account already exists!" << endl;
        } else {
            accounts[userId] = password;
            balances[userId] = 0.0;
            cout << "Thank You! Your account has been created!" << endl;
        }
    }

    bool login(const string& userId, const string& password) {
        if (accounts.find(userId) != accounts.end() && accounts[userId] == password) {
            loggedInUser = userId;
            cout << "Access Granted!" << endl;
            return true;
        } else {
            cout << "*** LOGIN FAILED! ***" << endl;
            return false;
        }
    }

    void logout() {
        loggedInUser = "";
    }

    void deposit(double amount) {
        if (amount > 0) {
            balances[loggedInUser] += amount;
            cout << "$" << amount << " deposited." << endl;
        } else {
            cout << "Invalid amount!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && balances[loggedInUser] >= amount) {
            balances[loggedInUser] -= amount;
            cout << "$" << amount << " withdrawn." << endl;
        } else {
            cout << "Insufficient balance or invalid amount." << endl;
        }
    }

    void requestBalance() const {
        cout << "Your balance is $" << balances.at(loggedInUser) << "." << endl;
    }

    void mainMenu() {
        while (true) {
            cout << "d -> Deposit Money" << endl;
            cout << "w -> Withdraw Money" << endl;
            cout << "r -> Request Balance" << endl;
            cout << "q -> Quit" << endl;
            cout << "> ";
            char choice;
            cin >> choice;

            switch (choice) {
                case 'd': {
                    double amount;
                    cout << "Amount of deposit: $";
                    cin >> amount;
                    deposit(amount);
                    break;
                }
                case 'w': {
                    double amount;
                    cout << "Amount of withdrawal: $";
                    cin >> amount;
                    withdraw(amount);
                    break;
                }
                case 'r':
                    requestBalance();
                    break;
                case 'q':
                    logout();
                    return;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }
        }
    }

    void start() {
        cout << "Hi! Welcome to the ATM Machine!" << endl;
        while (true) {
            cout << "Please select an option from the menu below:" << endl;
            cout << "l -> Login" << endl;
            cout << "c -> Create New Account" << endl;
            cout << "q -> Quit" << endl;
            cout << "> ";
            char choice;
            cin >> choice;

            if (choice == 'l') {
                string userId, password;
                cout << "Please enter your user id: ";
                cin >> userId;
                cout << "Please enter your password: ";
                cin >> password;
                if (login(userId, password)) {
                    mainMenu();
                }
            } else if (choice == 'c') {
                string userId, password;
                cout << "Please enter your user name: ";
                cin >> userId;
                cout << "Please enter your password: ";
                cin >> password;
                createAccount(userId, password);
            } else if (choice == 'q') {
                cout << "Thank you for using the ATM. Goodbye!" << endl;
                break;
            } else {
                cout << "Invalid choice! Please try again." << endl;
            }
        }
    }
};

int main() {
    ATM atm;
    atm.start();
    return 0;
}
