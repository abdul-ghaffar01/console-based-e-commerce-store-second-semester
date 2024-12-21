#ifndef PRODUCT
#define PRODUCT

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Product
{
private:
    string productID;   // Unique identifier for the product
    string productName; // Name of the product
    double price;       // Price of the product
    int quantity;       // Quantity available in stock
    string description; // Description of the product

public:
    // Default constructor
    Product() : productID(""), productName(""), price(0.0), quantity(0), description("") {}

    // Parameterized constructor
    Product(string productID, string productName, double price, int quantity, string description)
        : productID(productID), productName(productName), price(price), quantity(quantity), description(description) {}

    // Getter and Setter methods
    string getProductID() const { return productID; }
    void setProductID(const string &id) { productID = id; }

    string getProductName() const { return productName; }
    void setProductName(const string &name) { productName = name; }

    double getPrice() const { return price; }
    void setPrice(double p) { price = p; }

    int getQuantity() const { return quantity; }
    void setQuantity(int qty) { quantity = qty; }

    string getDescription() const { return description; }
    void setDescription(const string &desc) { description = desc; }

    // Method to display product details
    void displayProductDetails() const
    {
        cout << "Product ID: " << productID << endl;
        cout << "Product Name: " << productName << endl;
        cout << "Price: $" << price << endl;
        cout << "Quantity Available: " << quantity << endl;
        cout << "Description: " << description << endl;
    }

    // Method to check if product is in stock
    bool isInStock() const
    {
        return quantity > 0;
    }

    // Method to update stock (after purchase)
    void updateStock(int purchasedQuantity)
    {
        if (quantity >= purchasedQuantity)
        {
            quantity -= purchasedQuantity;
            cout << "Stock updated. Remaining stock: " << quantity << endl;
        }
        else
        {
            cout << "Not enough stock available!" << endl;
        }
    }

    // Method to restock the product
    void restock(int additionalQuantity)
    {
        quantity += additionalQuantity;
        cout << "Product restocked. New stock: " << quantity << endl;
    }

    void display()
    {
        int width = max(productName.length(), description.length()) + 17;
        string line;
        for (int i = 0; i < width - 2; i++)
        {
            line += '_';
        }

        // creating object of single color text and initializing with line
        SingleColorText s(line, Text::cyan(), 1, 10);

        // printing horizontal line
        cout << Text::cyan() << Text::bold() << '/';
        s.print();
        cout << Text::bold() << Text::cyan() <<"\\" << endl;

        // printing empty line
        cout << '\\';
        emptyLine(width);
        cout << '/' << endl;

        // Printing product id
        cout << "/ " << Text::white();
        s.setText(productID);
        s.setDelay(100);
        s.print();
        printSpaces(width - productID.length() - 3);
        cout << Text::cyan() << Text::bold() << "\\" << endl;

        // printing horizontal line
        cout << Text::cyan() << Text::bold() << '\\';
        s.setText(line);
        s.setDelay(10);
        s.print();
        cout << Text::bold() << Text::cyan() <<"/" << endl;


        // printing empty line
        cout << '/';
        emptyLine(width);
        cout << '\\' << endl;

        // Printing name
        cout << "\\ " << Text::white() << "Name";
        printSpaces(7);
        cout << ": " << Text::normal();
        s.setBold(0);
        s.setText(productName);
        s.setDelay(50);
        s.print();
        printSpaces(width - 17 - productName.length());
        cout << Text::cyan() << Text::bold() << " /" << endl;

        // Printing Price
        cout << "/ " << Text::white() << "Price";
        printSpaces(6);
        cout << ": " << Text::normal() << Text::cyan() << fixed << setprecision(0) << price;
        printSpaces(width - 17 - numberOfDigits(price));
        cout << Text::cyan() << Text::bold() << " \\" << endl;

        // printing quantity
        cout << "\\ " << Text::white() << "Quantity";
        printSpaces(3);
        cout << ": " << Text::normal() << Text::cyan() << quantity;
        printSpaces(width - 17 - numberOfDigits(quantity));
        cout << Text::cyan() << Text::bold() << " /" << endl;

        // Printing
        cout << Text::cyan() << "/ " << "\033[37m" << "Description: " << Text::normal();
        s.setText(description);
        s.print(); 
        cout << Text::cyan() << Text::bold() << " \\" << endl;
        
        // printing horizontal line
        cout << Text::cyan() << Text::bold() << '\\';
        s.setText(line);
        s.setDelay(1);
        s.setBold(1);
        s.print();
        cout << Text::bold() << Text::cyan() <<"/" << endl << endl << Text::white() << Text::normal();
        
    }

private:
    void emptyLine(int width)
    {
        cout << Text::bold();
        for (int i = 0; i < width - 2; i++)
        {
            cout << ' ';
        }
    }

    void printSpaces(int times)
    {
        for (int i = 0; i < times; i++)
        {
            cout << ' ';
        }
    }

    int numberOfDigits(int n)
    {
        int cnt = 0;
        while (n > 0)
        {
            cnt++;
            n /= 10;
        }
        return cnt;
    }

public:
    // Destructor
    ~Product() {}
};

#endif