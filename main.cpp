#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <map>
#include <cstdlib>

using namespace std;

// Encryption utility function
string encryptPIN(const string &pin) {
    string encrypted;
    for (char c : pin) {
        encrypted += (c + 5); // Simple Caesar cipher for demonstration
    }
    return encrypted;
}

string decryptPIN(const string &encrypted) {
    string decrypted;
    for (char c : encrypted) {
        decrypted += (c - 5);
    }
    return decrypted;
}

// Account class
class Account{
private:
    string accountNumber;
    string name;
    double balance;
    string encryptedPIN;

public:
    // Default constructor
    Account() {}

    // Constructor
    Account(const string &accNumber, const string &accName, double initialBalance, const string &pin) 
        : accountNumber(accNumber), name(accName), balance(initialBalance), encryptedPIN(encryptPIN(pin)) {}

    // Getters
    string getAccountNumber() const { return accountNumber; }
    string getName() const { return name; }
    double getBalance() const { return balance; }

    // PIN Validation
    bool validatePIN(const string &pin) const { return decryptPIN(encryptedPIN) == pin; }

    // Deposit
    void deposit(double amount) { 
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful! New balance: " << balance << "\n";
        } else {
            cerr << "Invalid deposit amount.\n";
        }
    }

    // Withdraw
    void withdraw(double amount) { 
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful! New balance: " << balance << "\n";
        } else {
            cerr << "Invalid or insufficient funds for withdrawal.\n";
        }
    }
};

// ATMController class
class ATMController {
private:
    map<string, Account> accounts;

public:
    // Add a new account
    void addAccount(const string &accNumber, const string &name, double initialBalance, const string &pin) {
        if (accounts.find(accNumber) == accounts.end()) {
            accounts[accNumber] = Account(accNumber, name, initialBalance, pin);
            cout << "Account created successfully!\n";
        } else {
            cerr << "Account with this number already exists.\n";
        }
    }

    // Find an account by account number
    Account *findAccount(const string &accNumber) {
        if (accounts.find(accNumber) != accounts.end()) {
            return &accounts[accNumber];
        } else {
            cerr << "Account not found.\n";
            return nullptr;
        }
    }

    // Process transactions
    void processTransaction() {
        string accNumber, pin;
        cout << "Enter account number: ";
        cin >> accNumber;
        Account *account = findAccount(accNumber);
        if (!account) return;
        cout << "Enter PIN: ";
        cin >> pin;
        if (!account->validatePIN(pin)) {
            cerr << "Invalid PIN. Access denied.\n";
            return;
        }
        int choice;
        do {
            cout << "\n1. Balance Inquiry\n2. Deposit\n3. Withdraw\n4. Exit\nEnter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Current balance: " << account->getBalance() << "\n";
                    break;
                case 2: {
                    double depositAmount;
                    cout << "Enter amount to deposit: ";
                    cin >> depositAmount;
                    account->deposit(depositAmount);
                    break;
                }
                case 3: {
                    double withdrawAmount;
                    cout << "Enter amount to withdraw: ";
                    cin >> withdrawAmount;
                    account->withdraw(withdrawAmount);
                    break;
                }
                case 4:
                    cout << "Exiting...\n";
                    break;
                default:
                    cerr << "Invalid choice. Try again.\n";
            }
        } while (choice != 4);
    }
};


int main() {
    ATMController atm;
    int choice;
    do {
        cout << "\n*** ATM Controller Menu ***\n";
        cout << "1. Create Account\n2. Access Account\n3. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string accNumber, name, pin;
                double initialBalance;
                cout << "Enter account number: ";
                cin >> accNumber;
                cout << "Enter account holder's name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter initial balance: ";
                cin >> initialBalance;
                cout << "Set a 4-digit PIN: ";
                cin >> pin;
                atm.addAccount(accNumber, name, initialBalance, pin);
                break;
            }
            case 2:
                atm.processTransaction();
                break;
            case 3:
                cout << "Thank you for using the ATM Controller. Goodbye!\n";
                break;
            default:
                cerr << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}