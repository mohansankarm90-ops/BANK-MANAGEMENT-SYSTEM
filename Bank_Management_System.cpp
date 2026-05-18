#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Account {
public:
    int accNo;
    string name;
    float balance;

    void create() {
        cout << "Account No: "; cin >> accNo;
        cout << "Name: "; cin >> name;
        cout << "Initial Deposit: "; cin >> balance;
    }

    void display() {
        cout << "\nAcc No: " << accNo << "\nName: " << name << "\nBalance: " << balance << endl;
    }
};

// Save single account to file (append)
void saveAccount(Account a) {
    ofstream f("bank.dat", ios::binary | ios::app);
    f.write((char*)&a, sizeof(a));
    f.close();
}

// Find and display account by accNo
bool findAccount(int no) {
    Account a;
    ifstream f("bank.dat", ios::binary);
    while (f.read((char*)&a, sizeof(a))) {
        if (a.accNo == no) {
            a.display();
            f.close();
            return true;
        }
    }
    f.close();
    return false;
}

// Deposit or withdraw (type: 'd' or 'w')
void transaction(int no, float amount, char type) {
    Account a;
    fstream f("bank.dat", ios::binary | ios::in | ios::out);
    while (f.read((char*)&a, sizeof(a))) {
        if (a.accNo == no) {
            if (type == 'w' && a.balance < amount) {
                cout << "Insufficient balance!\n";
                f.close();
                return;
            }
            if (type == 'd') a.balance += amount;
            else              a.balance -= amount;
            // Move back and overwrite
            f.seekp(-(int)sizeof(a), ios::cur);
            f.write((char*)&a, sizeof(a));
            cout << "Done. New balance: " << a.balance << endl;
            f.close();
            return;
        }
    }
    cout << "Account not found.\n";
    f.close();
}

int main() {
    int choice, no;
    float amt;
    Account a;

    while (true) {
        cout << "\n1.Create  2.Deposit  3.Withdraw  4.Balance  5.Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                a.create();
                saveAccount(a);
                cout << "Account created.\n";
                break;
            case 2:
                cout << "Acc No: "; cin >> no;
                cout << "Amount: "; cin >> amt;
                transaction(no, amt, 'd');
                break;
            case 3:
                cout << "Acc No: "; cin >> no;
                cout << "Amount: "; cin >> amt;
                transaction(no, amt, 'w');
                break;
            case 4:
                cout << "Acc No: "; cin >> no;
                if (!findAccount(no)) cout << "Not found.\n";
                break;
            case 5:
                return 0;
        }
    }
}
