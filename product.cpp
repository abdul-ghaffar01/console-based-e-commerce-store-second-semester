#ifndef PRODUCT
#define PRODUCT

#include <iostream>
#include <string>
#include "list.cpp"  // Include your List class definition here

using namespace std;

class ProductItem {
private:
    static int idCounter;  // Static counter to generate unique IDs
    int productID;
    string name;
    string description;
    double price;
    int quantity;
    List<string> tags;
    List<string> reviews;
    List<int> relatedProducts;  // Stores IDs of related products

public:
    // Constructor
    ProductItem(const string &name, const string &description, double price, int quantity, int tagSize = 5, int reviewSize = 10, int relatedSize = 5)
        : name(name), description(description), price(price), quantity(quantity),
          tags(tagSize), reviews(reviewSize), relatedProducts(relatedSize) {
        productID = ++idCounter;  // Assign a unique ID to each product
    }

    // Add a tag
    bool addTag(const string &tag) {
        return tags.push_back(tag);
    }

    // Add a review
    bool addReview(const string &review) {
        return reviews.push_back(review);
    }

    // Add a related product by ID
    bool addRelatedProduct(int relatedProductID) {
        return relatedProducts.push_back(relatedProductID);
    }

    // Display product details
    void display() const {
        cout << "Product ID: " << productID << endl;
        cout << "Name: " << name << endl;
        cout << "Description: " << description << endl;
        cout << "Price: $" << price << endl;
        cout << "Quantity: " << quantity << endl;

        // Display tags
        cout << "Tags: ";
        tags.print();

        // Display reviews
        cout << "Reviews: ";
        reviews.print();

        // Display related products
        cout << "Related Products: ";
        relatedProducts.print();
        cout << endl;
    }

    // Getters
    int getID() const { return productID; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    // Setters
    void setName(const string &newName) { name = newName; }
    void setPrice(double newPrice) { price = newPrice; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }

    // Destructor
    ~ProductItem() {}
};

// Initialize static variable
int ProductItem::idCounter = 0;


#endif