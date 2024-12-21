#ifndef USER
#define USER

#include <iostream>
#include <string>
#include "list.cpp"
#include "text.cpp"

using namespace std;

class User
{
protected:
    string username;
    string password;
    string email;
    string role; // "client" or "admin"
    string phoneNumber;
    string address;
    string dateOfRegistration;
    bool isActive;
    List<string> orderHistory; // Stores order IDs

public:
    // Default constructor
    User()
        : username(""), password(""), email(""), role("client"),
          phoneNumber(""), address(""), dateOfRegistration(""), isActive(true) {}

    // Constructor
    User(string username, string password, string email, string role,
         string phoneNumber = "", string address = "", string dateOfRegistration = "", bool isActive = true);

    // Copy constructor
    User(const User &other)
        : username(other.username),
          password(other.password),
          email(other.email),
          role(other.role),
          phoneNumber(other.phoneNumber),
          address(other.address),
          dateOfRegistration(other.dateOfRegistration),
          isActive(other.isActive),
          orderHistory(other.orderHistory) // Copy the order history
    {
    }

    // Getters and Setters
    string getUsername() const;
    void setUsername(const string &newUsername);

    string getRole() const;

    string getPassword() const;
    void setPassword(const string &newPassword);

    string getEmail() const;
    void setEmail(const string &newEmail);

    string getPhoneNumber() const;
    void setPhoneNumber(const string &newPhoneNumber);

    string getAddress() const;
    void setAddress(const string &newAddress);

    string getDateOfRegistration() const;
    void setDateOfRegistration(const string &date);

    bool getIsActive() const;
    void setIsActive(bool status);

    bool isAdmin() const;
    bool isClient() const;

    // Order History Management
    void addOrderToHistory(const string &orderID);
    void displayOrderHistory() const;

    // Display user information
    virtual void displayInfo() const;

    static User *findUserByUsername(const string &username, const List<User> &users)
    {
        for (int i = 0; i<users.length(); i++)
        {
            if (users[i].getUsername() == username)
            {
                return new User(users[i]); // Return a copy of the user
            }
        }
        return nullptr;
    }

    // Destructor
    virtual ~User();
};

// -------- All the definitions of methods ---------

// Constructor
User::User(string username, string password, string email, string role,
           string phoneNumber, string address, string dateOfRegistration, bool isActive)
    : username(username), password(password), email(email), role(role),
      phoneNumber(phoneNumber), address(address), dateOfRegistration(dateOfRegistration), isActive(isActive) {}

// Getters and Setters
string User::getUsername() const { return username; }
void User::setUsername(const string &newUsername) { username = newUsername; }

string User::getPassword() const { return password; }
void User::setPassword(const string &newPassword) { password = newPassword; }

string User::getRole() const { return role; }

string User::getEmail() const { return email; }
void User::setEmail(const string &newEmail) { email = newEmail; }

string User::getPhoneNumber() const { return phoneNumber; }
void User::setPhoneNumber(const string &newPhoneNumber) { phoneNumber = newPhoneNumber; }

string User::getAddress() const { return address; }
void User::setAddress(const string &newAddress) { address = newAddress; }

string User::getDateOfRegistration() const { return dateOfRegistration; }
void User::setDateOfRegistration(const string &date) { dateOfRegistration = date; }

bool User::getIsActive() const { return isActive; }
void User::setIsActive(bool status) { isActive = status; }

bool User::isAdmin() const { return role == "admin"; }
bool User::isClient() const { return role == "client"; }

// Order History Management
void User::addOrderToHistory(const string &orderID)
{
    orderHistory.push_back(orderID);
}

void User::displayOrderHistory() const
{
    cout << "Order History for " << username << ":" << endl;
    for (int i = 0; i < orderHistory.length(); i++)
    {
        cout << "- " << orderHistory[i] << endl;
    }
}

void User::displayInfo() const
{
    // Display username in green color
    SingleColorText t(username, Text::green(), 100);
    cout << "Username: ";
    t.print();

    // Display email
    t.setText(email);
    cout << "Email: ";
    t.print();

    // Display role
    t.setText(role);
    cout << "Role: ";
    t.print();

    // Display phone number
    t.setText(phoneNumber);
    cout << "Phone Number: ";
    t.print();

    // Display address
    t.setText(address);
    cout << "Address: ";
    t.print();

    // Display date of registration
    t.setText(dateOfRegistration);
    cout << "Date of Registration: ";
    t.print();

    // Display active status with dynamic color based on status
    t.setText(isActive ? "yes" : "no");
    cout << "Active Status: ";
    t.setColor(isActive ? Text::green() : Text::red());
    t.print();
}

// Destructor
User::~User() {}

#endif