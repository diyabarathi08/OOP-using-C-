#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

/**
* @brief Observer interface.
*/
class Observer
{
public:
    virtual void notify(const string& message) = 0;
    virtual ~Observer() {}
};

/**
* @brief Email notification observer.
*/
class EmailNotification : public Observer
{
private:
    string email;

public:
    EmailNotification(string e)
    {
        email = e;
    }

    void notify(const string& message) override
    {
        cout << "Email sent to " << email
             << ": " << message << endl;
    }
};

/**
* @brief SMS notification observer.
*/
class SMSNotification : public Observer
{
private:
    string phoneNumber;

public:
    SMSNotification(string number)
    {
        phoneNumber = number;
    }

    void notify(const string& message) override
    {
        cout << "SMS sent to " << phoneNumber
             << ": " << message << endl;
    }
};

/**
* @brief Factory class for creating notifications.
*/
class NotificationFactory
{
public:
    static shared_ptr<Observer> createNotification(
        const string& type,
        const string& receiver)
    {
        if (type == "EMAIL")
        {
            return make_shared<EmailNotification>(receiver);
        }
        else if (type == "SMS")
        {
            return make_shared<SMSNotification>(receiver);
        }

        return nullptr;
    }
};

/**
* @brief Singleton Event Manager.
*/
class EventManager
{
private:
    vector<shared_ptr<Observer>> observers;

    EventManager()
    {
    }

public:
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    static EventManager& getInstance()
    {
        static EventManager instance;
        return instance;
    }

    void subscribe(shared_ptr<Observer> observer)
    {
        observers.push_back(observer);
    }

    void unsubscribe(shared_ptr<Observer> observer)
    {
        observers.erase(
            remove(observers.begin(), observers.end(), observer),
            observers.end());
    }

    void triggerEvent(const string& message)
    {
        cout << "\nEvent Triggered: "
             << message << endl;

        cout << "Sending Notifications...\n";

        for (auto observer : observers)
        {
            observer->notify(message);
        }
    }
};

int main()
{
    EventManager& manager = EventManager::getInstance();

    vector<shared_ptr<Observer>> users;

    int n, choice;

    cout << "Enter number of observers: ";
    cin >> n;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < n; i++)
    {
        string type, receiver;

        cout << "\nObserver " << i + 1 << endl;

        cout << "Enter notification type (EMAIL/SMS): ";
        cin >> type;

        cout << "Enter email address or phone number: ";
        cin >> receiver;

        shared_ptr<Observer> observer =
            NotificationFactory::createNotification(type, receiver);

        if (observer != nullptr)
        {
            manager.subscribe(observer);
            users.push_back(observer);
            cout << "Observer subscribed successfully." << endl;
        }
        else
        {
            cout << "Invalid notification type." << endl;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string message1, message2;

    cout << "\nEnter first event message: ";
    getline(cin, message1);

    manager.triggerEvent(message1);

    cout << "\nSubscribed Observers:" << endl;

    for (int i = 0; i < users.size(); i++)
    {
        cout << i + 1 << ". Observer " << i + 1 << endl;
    }

    cout << "0. Do not unsubscribe anyone" << endl;

    cout << "\nEnter observer number to unsubscribe: ";
    cin >> choice;

    if (choice >= 1 && choice <= users.size())
    {
        manager.unsubscribe(users[choice - 1]);
        cout << "Observer unsubscribed successfully." << endl;
    }
    else if (choice == 0)
    {
        cout << "No observer unsubscribed." << endl;
    }
    else
    {
        cout << "Invalid observer number. No observer unsubscribed." << endl;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nEnter second event message: ";
    getline(cin, message2);

    manager.triggerEvent(message2);

    return 0;
}
