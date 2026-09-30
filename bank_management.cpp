#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Account {
    int accNo;
    string name;
    float balance;
};

void createAccount() {
    ofstream file("bank.txt", ios::app);
    Account a;
    cout << "Enter Account No: "; cin >> a.accNo;
    cout << "Enter Name: "; cin.ignore(); getline(cin, a.name);
    cout << "Enter Initial Balance: "; cin >> a.balance;
    file << a.accNo << "," << a.name << "," << a.balance << "\n";
    file.close();
    cout << "Account created!\n";
}

void displayAccounts() {
    ifstream file("bank.txt");
    string line;
    cout << "\n--- All Accounts ---\n";
    while(getline(file, line)) cout << line << "\n";
    file.close();
}

void deposit() {
    int accNo; float amount;
    cout << "Enter Account No: "; cin >> accNo;
    cout << "Enter Deposit Amount: "; cin >> amount;
    ifstream file("bank.txt");
    ofstream temp("temp.txt");
    string line; bool found = false;
    while(getline(file, line)) {
        int id = stoi(line.substr(0, line.find(',')));
        if(id == accNo) {
            string rest = line.substr(line.find(',') + 1);
            string name = rest.substr(0, rest.find(','));
            float bal = stof(rest.substr(rest.find(',') + 1));
            bal += amount;
            temp << id << "," << name << "," << bal << "\n";
            found = true;
            cout << "Deposited! New Balance: " << bal << "\n";
        } else temp << line << "\n";
    }
    file.close(); temp.close();
    remove("bank.txt"); rename("temp.txt", "bank.txt");
    if(!found) cout << "Account not found.\n";
}

void withdraw() {
    int accNo; float amount;
    cout << "Enter Account No: "; cin >> accNo;
    cout << "Enter Withdrawal Amount: "; cin >> amount;
    ifstream file("bank.txt");
    ofstream temp("temp.txt");
    string line; bool found = false;
    while(getline(file, line)) {
        int id = stoi(line.substr(0, line.find(',')));
        if(id == accNo) {
            string rest = line.substr(line.find(',') + 1);
            string name = rest.substr(0, rest.find(','));
            float bal = stof(rest.substr(rest.find(',') + 1));
            if(bal >= amount) { bal -= amount; cout << "Withdrawn! New Balance: " << bal << "\n"; }
            else cout << "Insufficient balance!\n";
            temp << id << "," << name << "," << bal << "\n";
            found = true;
        } else temp << line << "\n";
    }
    file.close(); temp.close();
    remove("bank.txt"); rename("temp.txt", "bank.txt");
    if(!found) cout << "Account not found.\n";
}

void checkBalance() {
    int accNo;
    cout << "Enter Account No: "; cin >> accNo;
    ifstream file("bank.txt");
    string line;
    while(getline(file, line)) {
        int id = stoi(line.substr(0, line.find(',')));
        if(id == accNo) {
            string rest = line.substr(line.find(',') + 1);
            float bal = stof(rest.substr(rest.find(',') + 1));
            cout << "Balance: " << bal << "\n";
            file.close(); return;
        }
    }
    cout << "Account not found.\n";
    file.close();
}

int main() {
    int choice;
    do {
        cout << "\n=== Bank Management System ===\n";
        cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. Check Balance\n5. Display All\n6. Exit\n";
        cout << "Choice: "; cin >> choice;
        switch(choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: displayAccounts(); break;
            case 6: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while(choice != 6);
    return 0;
}
