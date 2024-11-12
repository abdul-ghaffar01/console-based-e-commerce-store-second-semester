#ifndef ADMIN
#define ADMIN

#include<iostream>
#include <string>
#include "./user.cpp"
#include "./list.cpp"
using namespace std;

using namespace std;

class Admin : public User {
private:
    List<string> managedUsers;   // List of managed user names
    List<string> productCatalog; // List of product IDs or names

public:
    Admin(string username, string password, string email, string phoneNumber = "", string address = "", string dateOfRegistration = "");

    // Admin functionalities
    void addProduct(const string& productID);
    void removeProduct(const string& productID);
    void displayCatalog() const;

    void addUser(const string& username);
    void removeUser(const string& username);
    void displayManagedUsers() const;

    // Initiate the admin panel
    void begin();

    ~Admin();
};




// Constructor
Admin::Admin(string username, string password, string email, string phoneNumber, string address, string dateOfRegistration)
    : User(username, password, email, "admin", phoneNumber, address, dateOfRegistration),
      managedUsers(50), productCatalog(100) {}

// Add a product to the catalog
void Admin::addProduct(const string& productID) {
    if (!productCatalog.push_back(productID)) {
        cout << "Failed to add product: Catalog is full." << endl;
    } else {
        cout << "Product " << productID << " added to catalog." << endl;
    }
}

// Remove a product from the catalog
void Admin::removeProduct(const string& productID) {
    for (int i = 0; i < productCatalog.length(); i++) {
        if (productCatalog[i] == productID) {
            productCatalog.pop_start();
            cout << "Product " << productID << " removed from catalog." << endl;
            return;
        }
    }
    cout << "Product " << productID << " not found in catalog." << endl;
}

// Display the product catalog
void Admin::displayCatalog() const {
    cout << "Product Catalog:" << endl;
    for (int i = 0; i < productCatalog.length(); i++) {
        cout << "- " << productCatalog.get(i) << endl;
    }
}

// Add a user to the managed list
void Admin::addUser(const string& username) {
    if (!managedUsers.push_back(username)) {
        cout << "Failed to add user: Managed users list is full." << endl;
    } else {
        cout << "User " << username << " added to managed users." << endl;
    }
}

// Remove a user from the managed list
void Admin::removeUser(const string& username) {
    for (int i = 0; i < managedUsers.length(); i++) {
        if (managedUsers[i] == username) {
            managedUsers.pop_start();
            cout << "User " << username << " removed from managed users." << endl;
            return;
        }
    }
    cout << "User " << username << " not found in managed users." << endl;
}

// Display managed users
void Admin::displayManagedUsers() const {
    cout << "Managed Users:" << endl;
    for (int i = 0; i < managedUsers.length(); i++) {
        cout << "- " << managedUsers.get(i) << endl;
    }
}

// Initiate the admin panel
void Admin::begin() {
    int choice;
    do {
        cout << "\n--- Admin Panel ---\n";
        cout << "1. Display Catalog\n";
        cout << "2. Add Product\n";
        cout << "3. Remove Product\n";
        cout << "4. Display Managed Users\n";
        cout << "5. Add User\n";
        cout << "6. Remove User\n";
        cout << "0. Exit Admin Panel\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayCatalog();
            break;
        case 2: {
            cout << "Enter product ID to add: ";
            string productID;
            cin >> productID;
            addProduct(productID);
            break;
        }
        case 3: {
            cout << "Enter product ID to remove: ";
            string productID;
            cin >> productID;
            removeProduct(productID);
            break;
        }
        case 4:
            displayManagedUsers();
            break;
        case 5: {
            cout << "Enter username to add to managed users: ";
            string username;
            cin >> username;
            addUser(username);
            break;
        }
        case 6: {
            cout << "Enter username to remove from managed users: ";
            string username;
            cin >> username;
            removeUser(username);
            break;
        }
        case 0:
            cout << "Exiting Admin Panel..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

// Destructor
Admin::~Admin() {}

#endif