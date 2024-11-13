#ifndef PRODUCT
#define PRODUCT

#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    string productID;    // Unique identifier for the product
    string productName;  // Name of the product
    double price;        // Price of the product
    int quantity;        // Quantity available in stock
    string description;  // Description of the product

public:
    // Default constructor
    Product() : productID(""), productName(""), price(0.0), quantity(0), description("") {}

    // Parameterized constructor
    Product(string productID, string productName, double price, int quantity, string description)
        : productID(productID), productName(productName), price(price), quantity(quantity), description(description) {}

    // Getter and Setter methods
    string getProductID() const { return productID; }
    void setProductID(const string& id) { productID = id; }

    string getProductName() const { return productName; }
    void setProductName(const string& name) { productName = name; }

    double getPrice() const { return price; }
    void setPrice(double p) { price = p; }

    int getQuantity() const { return quantity; }
    void setQuantity(int qty) { quantity = qty; }

    string getDescription() const { return description; }
    void setDescription(const string& desc) { description = desc; }

    // Method to display product details
    void displayProductDetails() const {
        cout << "Product ID: " << productID << endl;
        cout << "Product Name: " << productName << endl;
        cout << "Price: $" << price << endl;
        cout << "Quantity Available: " << quantity << endl;
        cout << "Description: " << description << endl;
    }

    // Method to check if product is in stock
    bool isInStock() const {
        return quantity > 0;
    }

    // Method to update stock (after purchase)
    void updateStock(int purchasedQuantity) {
        if (quantity >= purchasedQuantity) {
            quantity -= purchasedQuantity;
            cout << "Stock updated. Remaining stock: " << quantity << endl;
        } else {
            cout << "Not enough stock available!" << endl;
        }
    }

    // Method to restock the product
    void restock(int additionalQuantity) {
        quantity += additionalQuantity;
        cout << "Product restocked. New stock: " << quantity << endl;
    }

    // Destructor
    ~Product() {}
};

#endif
