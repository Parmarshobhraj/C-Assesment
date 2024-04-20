#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
using namespace std;

// Class representing a Bank Account
class BankAccount {
private:
    string holderName;
    string address;
    string branchName;
    string accountNumber;
    double balance;

public:
    // Constructor to initialize account details
    BankAccount(string name, string addr, string branch, string accNum, double bal) {
        holderName = name;
        address = addr;
        branchName = branch;
        accountNumber = accNum;
        balance = bal;
    }

    // Function to deposit cash
    void deposit(double amount) {
        balance += amount;
    }

    // Function to withdraw cash
    bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        } else {
            return false;
        }
    }

    // Function to display account details and balance
    void displayAccount() {
        cout << "The name of Account Holder are : " << holderName << endl;
        cout << "Account holder's Address is: " << address << endl;
        cout << "The Branch location is : " << branchName << endl;
        cout << "Account Number : " << accountNumber << endl;
        cout << "Current Balance: Rs. " << fixed << setprecision(2) << balance << endl;
    }
};

// Class representing ATM functionality
class ATM {
private:
    const string ATM_PIN = "12345";
    BankAccount& account;
    bool authenticated;

public:
    // Constructor to initialize ATM with a bank account
    ATM(BankAccount& acc) : account(acc), authenticated(false) {}

    // Function to display welcome screen
    void welcomeScreen() {
        time_t now = time(0);
        cout << "=============== Welcome to  ATM ================" << endl;
        cout << "\t ------------------ " <<endl;
        cout << "Date and Time: " << ctime(&now);
        cout << "\t ------------------ " << endl;
        cout << "================================================" << endl;
        cout << "Press 1 and then Press Enter to access your account via PIN number." << endl;
        cout << "OR" << endl;
        cout << "Press 0 and press Enter to get help!" << endl;
    }

    // Function to authenticate ATM PIN
    void authenticatePIN() {
        cout << "Enter your acc PIN Access Number! [only one attempt is allowed ]: ";
        string pin;
        cin >> pin;
        if (pin == ATM_PIN) {
            authenticated = true;
            cout << "PIN authentication successful." << endl;
        } else {
            authenticated = false;
            cout << "You had made your attempt which failed!! No more attempts allowed !! Sorry!!" << endl;
        }
    }

    // Function to display help screen
    void helpScreen() {
        cout << "You must have the corrct PIN Number to access this acount See your" << endl;
        cout << "bank representative for assistance during bank opening hours" << endl;
        cout << "Thanks for, Your choice today!!" << endl;
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        cin.get();
    }

    // Function to run the ATM application
    void run() {
        welcomeScreen();
        char choice;
        cin >> choice;
        if (choice == '1') {
            authenticatePIN();
            if (authenticated) {
                displayMenu();
            }
        } else if (choice == '0') {
            helpScreen();
        } else {
            cout << "Invalid choice. Exiting..." << endl;
        }
    }

    // Function to display menu
    void displayMenu() {
        char choice;
        do {
            cout << "\n============== ATM main Menu Screen ===============" << endl;
            cout << "Enter [1] to Deposit Cash" << endl;
            cout << "Enter [2] to Withdraw Cash" << endl;
            cout << "Enter [3] to Balance Inquiry" << endl;
            cout << "Enter [0] Exit ATM" << endl;
            cout << "Please Enter a Selection and Press return key : ";
            cin >> choice;
            switch (choice) {
                case '1':
                    depositCash();
                    break;
                case '2':
                    withdrawCash();
                    break;
                case '3':
                    checkBalance();
                    break;
                case '0':
                    cout << "Thank you for using our ATM. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        } while (choice != '0');
    }

    // Function to deposit cash
    void depositCash() {
        double amount;
        cout << "Enter amount to deposit: Rs. ";
        cin >> amount;
        account.deposit(amount);
        cout << "Deposit successful." << endl;
        account.displayAccount();
    }

    // Function to withdraw cash
    void withdrawCash() {
        double amount;
        cout << "Enter amount to withdraw: Rs. ";
        cin >> amount;
        if (account.withdraw(amount)) {
            cout << "Withdrawal successful." << endl;
            account.displayAccount();
        } else {
            cout << "Insufficient available balance in your account \n Sorry !!!." << endl;
        }
    }

    // Function to check balance
    void checkBalance() {
        account.displayAccount();
    }
};

int main() {
    // Create a Bank Account object
    BankAccount account("Shobhraj", "123 Main Street", "Gujarat", "1234567890", 60000.00);

    // Create an ATM object with the bank account
    ATM atm(account);

    // Run the ATM application
    atm.run();

    return 0;
}
