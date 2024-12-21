#ifndef AUTH
#define AUTH

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "list.cpp"
#include "user.cpp"
#include "file handler.cpp"

using namespace std;

class Authentication
{
private:
    List<User> users;   // Stores registered users
    User *loggedInUser; // Pointer to the currently logged-in user
    string filename;    // File to store user data

public:
    // Constructor with filename for persistence
    Authentication(const string &filename = "files/users.txt", int maxUsers = 100);

    // Register and login functionalities
    bool registerUser(const string &username, const string &password, const string &email, const string &role,
                      const string &phoneNumber = "", const string &address = "", const string &dateOfRegistration = "");
    bool login(const string &username, const string &password, const string &role);
    void logout();

    // User management
    bool isLoggedIn() const;
    User *getCurrentUser() const;
    void displayAllUsers() const;
    List<User> getAllUsers();

private:
    // File handling methods
    void loadUsersFromFile();
    void appendUserToFile(const User &user);

    // Helper function to find user by username
    User *findUserByUsername(const string &username);
};

// Constructor loads users from file
Authentication::Authentication(const string &filename, int maxUsers) : filename(filename), users(maxUsers), loggedInUser(nullptr)
{
    loadUsersFromFile();
}

// Register a new user and append to file
bool Authentication::registerUser(const string &username, const string &password, const string &email, const string &role,
                                  const string &phoneNumber, const string &address, const string &dateOfRegistration)
{
    if (findUserByUsername(username) != nullptr)
    {
        cout << "Username already exists. Registration failed." << endl;
        return false;
    }
    User newUser(username, password, email, role, phoneNumber, address, dateOfRegistration);
    if (users.push_back(newUser))
    {
        appendUserToFile(newUser); // Save new user to file
        cout << "User registered successfully." << endl;
        return true;
    }
    cout << "Registration failed. User list may be full." << endl;
    return false;
}

// Login function
bool Authentication::login(const string &username, const string &password, const string &role)
{
    User *user = findUserByUsername(username);
    // cout << "username" << user->getUsername() << endl
    //      << "password" << user->getPassword() << endl
    //      << "role" << user->getRole() << endl;
    if (user && user->getPassword() == password && (user->getRole() == "admin" || user->getRole() == role))
    { // Check password
        this->loggedInUser = user;
        cout << "Login successful." << endl;
        return true;
    }
    return false;
}

// Logout function
void Authentication::logout()
{
    if (loggedInUser)
    {
        loggedInUser = nullptr;
        cout << "Logged out successfully." << endl;
    }
    else
    {
        cout << "No user is currently logged in." << endl;
    }
}

// Check if user is logged in
bool Authentication::isLoggedIn() const
{
    return loggedInUser != nullptr;
}

// Get the current logged-in user
User *Authentication::getCurrentUser() const
{
    return loggedInUser;
}

// Display all users (admin only)
void Authentication::displayAllUsers() const
{
    if (loggedInUser && loggedInUser->isAdmin())
    {
        for (int i = 0; i < users.length(); ++i)
        {
            users[i].displayInfo();
            cout << "----------------------" << endl;
        }
    }
    else
    {
        cout << "Access denied. Only admins can view all users." << endl;
    }
}

// Helper function to find user by username
User *Authentication::findUserByUsername(const string &username)
{
    for (int i = 0; i < users.length(); ++i)
    {
        if (users[i].getUsername() == username)
        {
            return &users[i];
        }
    }
    return nullptr;
}

// Load all the users
void Authentication::loadUsersFromFile()
{
    FileHandler fileHandler(filename);               // Initialize FileHandler with filename
    List<string> lines = fileHandler.readAllLines(); // Read all lines from the file

    if (lines.length() == 0)
    {
        cout << "Could not read from the file: " << filename << ". Starting with an empty user list." << endl;
        return;
    }

    // Parse each line into User object and add to the list
    for (int i = 0; i < lines.length(); ++i)
    {
        stringstream ss(lines[i]);
        string username, password, email, role, phoneNumber, address, dateOfRegistration;
        bool isActive;

        ss >> username >> password >> email >> role >> phoneNumber >> address >> dateOfRegistration >> isActive;

        User user(username, password, email, role, phoneNumber, address, dateOfRegistration, isActive);
        users.push_back(user); // Add user to the List<User> `users`
    }
}

void Authentication::appendUserToFile(const User &user)
{
    FileHandler fileHandler(filename); // Initialize FileHandler with filename

    // Prepare user data as a single string line
    string userData = user.getUsername() + " " + user.getPassword() + " " + user.getEmail() + " " +
                      user.getRole() + " " + user.getPhoneNumber() + " " + user.getAddress() + " " +
                      user.getDateOfRegistration() + " " + (user.getIsActive() ? "1" : "0");

    // Append the user data line to the file
    fileHandler.appendLine(userData);
}

List<User> Authentication::getAllUsers()
{
    return this->users;
}

#endif