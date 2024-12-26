#ifndef CART
#define CART

#include <iostream>
#include <fstream>
#include <string>
#include "product.cpp"
#include "list.cpp"
#include "file handler.cpp"

using namespace std;

class Cart
{
private:
    List<Product> items; // List of products in the cart
    string userID;       // User-specific file ID for persistence
    void saveCart() const;
    void loadCart();

public:
    Cart() {}
    // Constructor that initializes cart for a user and loads existing items
    Cart(const string &userID) : userID(userID)
    {
        loadCart();
    }

    // Add a product to the cart
    void addProduct(const Product &product);

    // Remove a product from the cart by product ID
    void removeProduct(const string &productID);

    // Display items in the cart
    void displayCart() const;

    // Calculate the total price of items in the cart
    double getTotalPrice() const;

    // Clear the cart
    void clearCart();

    void setUsername(const string &username);
};

// Helper method to load cart items from the user's file
void Cart::loadCart()
{
    // Initialize FileHandler with the user's cart file path
    FileHandler fileHandler("files/cart/" + userID + ".txt");

    // Read all lines from the user's cart file
    List<string> lines = fileHandler.readAllLines();

    // If no lines were read, start with an empty cart
    if (lines.length() == 0)
    {
        cout << "Could not open file for user: " << userID << ". Starting with an empty cart." << endl;
        return;
    }

    // Parse each line to extract product details and add to items list
    for (int i = 0; i < lines.length(); ++i)
    {
        istringstream lineStream(lines[i]);
        string id, name, description;
        double price;
        int quantity;

        // Read product details from the line
        lineStream >> id >> name >> price >> quantity;
        getline(lineStream, description); // Read the remaining description

        // Create Product object and add it to the cart items
        Product product(id, name, price, quantity, description);
        items.push_back(product);
    }
}

// Helper method to save cart items to the user's file
void Cart::saveCart() const
{
    // Create a FileHandler instance for the user's cart file
    FileHandler fileHandler("files/cart/" + userID + ".txt");

    // Prepare a List<string> to hold the formatted lines for each product
    List<string> lines;

    // Format each product's details and add to lines
    for (int i = 0; i < items.length(); ++i)
    {
        Product p = items.get(i);
        string line = p.getProductID() + " " +
                      p.getProductName() + " " +
                      to_string(p.getPrice()) + " " +
                      to_string(p.getQuantity()) + " " +
                      p.getDescription();
        lines.push_back(line);
    }

    // Write all lines to the file using FileHandler
    fileHandler.writeAllLines(lines);
}

// Add a product to the cart
void Cart::addProduct(const Product &product)
{
    items.push_back(product);
    cout << product.getProductName() << " added to cart." << endl;
    saveCart(); // Save after each change
}

// Remove a product from the cart by product ID
void Cart::removeProduct(const string &productID)
{
    for (int i = 0; i < items.length(); ++i)
    {
        if (items.get(i).getProductID() == productID)
        {
            cout << items.get(i).getProductName() << " removed from cart." << endl;
            items.removeAt(i);
            saveCart(); // Save after each change
            return;
        }
    }
    cout << "Product with ID " << productID << " not found in cart." << endl;
}

// Display items in the cart
void Cart::displayCart() const
{
    if (items.length() == 0)
    {
        cout << "Your cart is empty." << endl;
        return;
    }

    cout << "Items in your cart:" << endl;
    for (int i = 0; i < items.length(); ++i)
    {
        items.get(i).display();
    }
}

// Calculate the total price of items in the cart
double Cart::getTotalPrice() const
{
    double total = 0;
    for (int i = 0; i < items.length(); ++i)
    {
        total += items.get(i).getPrice()*items.get(i).getQuantity();
    }
    return total;
}

// Clear the cart
void Cart::clearCart()
{
    items.clear();
    // cout << "Your cart has been cleared." << endl;
    saveCart(); // Save the empty state
}

void Cart::setUsername(const string &username)
{
    this->userID = username;
}

#endif
