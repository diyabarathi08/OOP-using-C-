
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Base custom exception class
class BankException : public exception
{
protected:
    string message;

public:
    BankException(string msg)
    {
        message = msg;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

// Derived exception class
class InsufficientFundsException : public BankException
{
public:
    InsufficientFundsException()
        : BankException("Error: Insufficient balance for withdrawal.")
    {
    }
};

// Another derived exception class
class InvalidAmountException : public BankException
{
public:
    InvalidAmountException()
        : BankException("Error: Amount must be greater than zero.")
    {
    }
};

class BankAccount
{
private:
    string name;
    double balance;
    int transactions;

public:
    BankAccount(string n, double b)
    {
        name = n;
        balance = b;
        transactions = 0;
    }

    void deposit(double amount)
    {
        if (amount <= 0)
            throw InvalidAmountException();

        balance += amount;
        transactions++;
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
            throw InvalidAmountException();

        if (amount > balance)
            throw InsufficientFundsException();

        balance -= amount;
        transactions++;
    }

    void display()
    {
        cout << "Account Holder: " << name << endl;
        cout << "Balance: Rs. " << balance << endl;
        cout << "Successful Transactions: "
             << transactions << endl;
    }
};

int main()
{
    string name;
    double balance, amount;
    int n, choice;

    cout << "Enter Account Holder Name: ";
    getline(cin, name);

    cout << "Enter Initial Balance: Rs. ";
    cin >> balance;

    if (balance < 0)
    {
        cout << "Initial balance cannot be negative." << endl;
        return 0;
    }

    BankAccount account(name, balance);

    cout << "\nInitial Account Details:" << endl;
    account.display();

    cout << "\nEnter number of transactions: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "\n1. Deposit";
        cout << "\n2. Withdraw";
        cout << "\nEnter your choice: ";
        cin >> choice;

        cout << "Enter amount: Rs. ";
        cin >> amount;

        try
        {
            if (choice == 1)
            {
                account.deposit(amount);
                cout << "Amount deposited successfully." << endl;
            }
            else if (choice == 2)
            {
                account.withdraw(amount);
                cout << "Amount withdrawn successfully." << endl;
            }
            else
            {
                cout << "Invalid choice." << endl;
            }
        }
        catch (const InsufficientFundsException &e)
        {
            cout << e.what() << endl;
        }
        catch (const InvalidAmountException &e)
        {
            cout << e.what() << endl;
        }
        catch (const BankException &e)
        {
            cout << "Bank Exception: " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cout << "General Exception: " << e.what() << endl;
        }
    }

    cout << "\nFinal Account Details:" << endl;
    account.display();

    return 0;
}
