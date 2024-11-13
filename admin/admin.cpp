#ifndef ADMIN
#define ADMIN

#include <iostream>
#include <string>
#include "../user.cpp"
#include "../list.cpp"
#include "../product.cpp"
#include "../file handler.cpp"
using namespace std;

class Admin : public User {
private:
    List<Product> productCatalog; // List of products managed by the admin
    FileHandler fileHandler; // To manage file operations for products

public:
    Admin(string username, string password, string email, string phoneNumber = "", string address = "", string dateOfRegistration = "");
    Admin();

    // Admin functionalities
    void addProduct(const Product& product);
    void removeProduct(const string& productID);
    void displayCatalog() const;
    void loadProductsFromFile(); // Load products from product.txt
    void saveProductsToFile();   // Save products to product.txt

    // Initiate the admin panel
    void begin();

    ~Admin();
};

// Default constructor
Admin::Admin() : fileHandler("product.txt") {}

// Constructor with parameters
Admin::Admin(string username, string password, string email, string phoneNumber, string address, string dateOfRegistration)
    : User(username, password, email, "admin", phoneNumber, address, dateOfRegistration),
      fileHandler("product.txt") {
    loadProductsFromFile(); // Load products when the admin is created
}

// Load products from file
void Admin::loadProductsFromFile() {
    List<string> lines = fileHandler.readAllLines();
    for (int i = 0; i < lines.length(); ++i) {
        string line = lines.get(i);
        // Assuming the product data is stored as "ID,Name,Price,Quantity,Description"
        size_t pos = 0;
        string productID, productName, description;
        double price;
        int quantity;

        // Parse the line into product attributes
        pos = line.find(",");
        productID = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        productName = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        price = stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(",");
        quantity = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        description = line; // Remaining string is the description

        // Create a Product object and add it to the catalog
        Product product(productID, productName, price, quantity, description);
        productCatalog.push_back(product); // Correctly add product to list
    }
}

// Save all products to the file
void Admin::saveProductsToFile() {
    List<string> lines;
    for (int i = 0; i < productCatalog.length(); ++i) {
        Product& product = productCatalog[i];
        string line = product.getProductID() + "," + product.getProductName() + "," + 
                      to_string(product.getPrice()) + "," + to_string(product.getQuantity()) + "," + 
                      product.getDescription();
        lines.push_back(line);
    }
    fileHandler.writeAllLines(lines);
}

// Add a new product to the catalog
void Admin::addProduct(const Product& product) {
    productCatalog.push_back(product); // Adding product to the list
    saveProductsToFile(); // Save the updated catalog to the file
    cout << "Product " << product.getProductName() << " added to catalog." << endl;
}

// Remove a product from the catalog
void Admin::removeProduct(const string& productID) {
    for (int i = 0; i < productCatalog.length(); ++i) {
        if (productCatalog.get(i).getProductID() == productID) {
            productCatalog.pop_start(); // Remove product from list
            saveProductsToFile(); // Save the updated catalog to the file
            cout << "Product with ID " << productID << " removed from catalog." << endl;
            return;
        }
    }
    cout << "Product with ID " << productID << " not found in catalog." << endl;
}

// Display all products in the catalog
void Admin::displayCatalog() const {
    cout << "Product Catalog:" << endl;
    for (int i = 0; i < productCatalog.length(); ++i) {
        productCatalog.get(i).displayProductDetails(); // Display product details
        cout << endl;
    }
}

// Admin panel for managing products
void Admin::begin() {
    int choice;
    do {
        cout << "\n--- Admin Panel ---\n";
        cout << "1. Display Catalog\n";
        cout << "2. Add Product\n";
        cout << "3. Remove Product\n";
        cout << "0. Exit Admin Panel\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayCatalog();
            break;
        case 2: {
            string productID, productName, description;
            double price;
            int quantity;

            cout << "Enter product ID: ";
            cin >> productID;
            cout << "Enter product name: ";
            cin.ignore();  // To handle newline left in the input buffer
            getline(cin, productName);
            cout << "Enter price: ";
            cin >> price;
            cout << "Enter quantity: ";
            cin >> quantity;
            cout << "Enter description: ";
            cin.ignore();
            getline(cin, description);

            Product newProduct(productID, productName, price, quantity, description);
            addProduct(newProduct);
            break;
        }
        case 3: {
            string productID;
            cout << "Enter product ID to remove: ";
            cin >> productID;
            removeProduct(productID);
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
