#ifndef ADMIN
#define ADMIN

#include <iostream>
#include <string>
#include "user.cpp"
#include "product_manager.cpp"
using namespace std;

class Admin : public User
{
private:
    ProductManager productManager;

    // Admin functionalities
    void displayCatalog() const;
    void addProduct();
    void removeProduct();
    void updateProduct();

public:
    Admin(string username, string password, string email, string phoneNumber = "", string address = "", string dateOfRegistration = "");
    Admin();
    // Initiate the admin panel
    void begin();

    ~Admin();
};

Admin::Admin() : productManager("files/product.txt")
{
}

Admin::Admin(string username, string password, string email, string phoneNumber, string address, string dateOfRegistration)
    : User(username, password, email, "admin", phoneNumber, address, dateOfRegistration),
      productManager("files/product.txt")
{
}

void Admin::displayCatalog() const
{
    productManager.displayCatalog();
}

void Admin::addProduct()
{
    string productID, productName, description;
    double price;
    int quantity;

    // Setting heading
    SingleColorText s("\nAdd a new product", Text::yellow());
    s.setBold(1);
    s.print();
    cout << endl;

    // Taking the product id
    s.setText("Enter product ID: ");
    s.setBold(0);
    s.setColor(Text::blue());
    s.print();
    cin >> productID;

    s.setText("Enter product name: ");
    s.print();
    cin.ignore(); // To handle newline left in the input buffer
    getline(cin, productName);

    s.setText("Enter product price: ");
    s.print();
    cin >> price;
    s.setText("Enter quantity: ");
    s.print();
    cin >> quantity;
    s.setText("Enter description: ");
    s.print();
    cin.ignore();
    getline(cin, description);

    Product newProduct(productID, productName, price, quantity, description);
    productManager.addProduct(newProduct);
}

void Admin::removeProduct()
{
    SingleColorText s("Enter product ID to remove: ", Text::blue());
    s.print();
    string productID;
    cin >> productID;
    if (productManager.removeProduct(productID))
    {
        s.setText("Product removed successfully.\n");
        s.setColor(Text::green());
        s.print();
    }
    else
    {
        s.setText("Product not found.\n");
        s.setColor(Text::red());
        s.print();
    }
}

void Admin::updateProduct()
{
    string productID, productName, description;
    double price;
    int quantity;

    // Setting heading
    SingleColorText s("\nAdd a new product", Text::yellow());
    s.setBold(1);
    s.print();
    cout << endl;

    // Taking the product id
    s.setText("Enter product ID: ");
    s.setBold(0);
    s.setColor(Text::blue());
    s.print();
    cin >> productID;

    s.setText("Enter product name: ");
    s.print();
    cin.ignore(); // To handle newline left in the input buffer
    getline(cin, productName);

    s.setText("Enter product price: ");
    s.print();
    cin >> price;
    s.setText("Enter  quantity: ");
    s.print();
    cin >> quantity;
    s.setText("Enter description: ");
    s.print();
    cin.ignore();
    getline(cin, description);

    Product updatedProduct(productID, productName, price, quantity, description);
    if (productManager.updateProduct(productID, updatedProduct))
    {

        s.setText("Product updated successfully.\n");
        s.setColor(Text::green());
        s.print();
    }
    else
    {
        s.setText("Product not found.\n");
        s.setColor(Text::red());
        s.print();
    }
}

void Admin::begin()
{
    int choice;
    do
    {

        List<string> colors(3);
        colors.push_back(Text::red());
        colors.push_back(Text::green());
        colors.push_back(Text::blue());

        MultiColorText m("Admin Panel", colors);
        cout << "\n---------- ";
        m.print();
        cout << " ----------\n";
        cout << "1. Display Catalog\n";
        cout << "2. Add Product\n";
        cout << "3. Remove Product\n";
        cout << "4. Update Product\n";
        cout << "0. Exit Admin Panel\n";

        SingleColorText s("", Text::blue());
        s.setText("Enter your choice: ");
        s.setDelay(30);
        s.print();
        cin >> choice;

        switch (choice)
        {
        case 1:
            displayCatalog();
            break;
        case 2:
            addProduct();
            break;
        case 3:
            removeProduct();
            break;
        case 4:
            updateProduct();
            break;
        case 0:
            cout << "Exiting Admin Panel...\n";
            break;
        default:
            s.setColor(Text::red());
            s.setText("Invalid choice. Please try again.");
            cout << endl;
            s.print();
            cout << endl;
        }
    } while (choice != 0);
}

Admin::~Admin() {}

#endif
