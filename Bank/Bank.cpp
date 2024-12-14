#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

class BankAccount 
{
private:
    int accountNumber;
    string pinHash;
    float balance;

    static string hashPin(const string& pin) 
    {
        hash<string> hashFunc;
        return to_string(hashFunc(pin));
    }

    static bool validatePin(const string& pin)
    {
        if (pin.length() != 4) return false;
        return all_of(pin.begin(), pin.end(), ::isdigit);
    }

public:
    BankAccount() = default;
    BankAccount(const string& pin) 
    {
        if (!validatePin(pin)) 
        {
            throw invalid_argument("Invalid pin-code. Must be a 4-digit number!");
        }
        accountNumber = generateAccountNumber();
        pinHash = hashPin(pin);
        balance = 0.0f;
    }

    int getAccountNumber() const 
    {
        return accountNumber;
    }

    float getBalance() const 
    {
        return balance;
    }

    void deposit(float amount) 
    {
        if (amount <= 0) 
        {
            throw invalid_argument("Deposit amount must be positive!");
        }
        balance += amount;
    }

    static int generateAccountNumber() 
    {
        static int lastAccountNumber = 100000;
        return lastAccountNumber++;
    }

    static bool isValidPin(const string& pin) 
    {
        return validatePin(pin);
    }
};

class Bank 
{
private:
    vector<BankAccount> accounts;

public:
    void addAccount(const string& pin) 
    {
        try 
        {
            BankAccount newAccount(pin);
            accounts.push_back(newAccount);
            cout << "Account created successfully. Account Number: " << newAccount.getAccountNumber() << endl;
        }
        catch (const exception& e) 
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    void displayAccounts() const 
    {
        if (accounts.empty()) 
        {
            cout << "No accounts available! Try to create one." << endl;
            return;
        }
        cout << "Accounts: " << endl;
        for (const auto& account : accounts) 
        {
            cout << "- Account Number: " << account.getAccountNumber() << endl;
        }
    }

    void displayBalance(int accountNumber) const 
    {
        for (const auto& account : accounts) 
        {
            if (account.getAccountNumber() == accountNumber) 
            {
                cout << "Account Number: " << accountNumber << ", Balance: " << fixed << setprecision(2) << account.getBalance() << endl;
                return;
            }
        }
        cout << "Account not found, sorry." << endl;
    }

    void topUpBalance(int accountNumber, float amount) 
    {
        for (auto& account : accounts) 
        {  
            if (account.getAccountNumber() == accountNumber) 
            {
                try 
                {
                    account.deposit(amount);
                    cout << "Deposit successful. New Balance: " << fixed << setprecision(2) << account.getBalance() << endl;
                }
                catch (const exception& e) 
                {
                    cout << "Error: " << e.what() << endl;
                }
                return;
            }
        }
        cout << "Account not found." << endl;
    }
};

int main() 
{
    Bank bank;
    int choice;

    do 
    {
        cout << "\nBank Application\n";
        cout << "1. Add Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Display Account Balance\n";
        cout << "4. Top Up Balance\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1: 
            {
                string pin;
                cout << "Enter a 4-digit PIN: ";
                cin >> pin;
                bank.addAccount(pin);
                break;
            }
            case 2:
                bank.displayAccounts();
                break;
            case 3: 
            {
                int accountNumber;
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                bank.displayBalance(accountNumber);
                break;
            }
            case 4: 
            {
                int accountNumber;
                float depositAmount;
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Deposit Amount: ";
                cin >> depositAmount;
                bank.topUpBalance(accountNumber, depositAmount);
                break;
            }
            case 5:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again!" << endl;
        }
    } while (choice != 5);
}