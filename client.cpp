#ifndef CLIENT
#define CLIENT

#include <iostream>
#include "user.cpp"
#include "cart.cpp"
#include "product.cpp"
#include "user.cpp"
using namespace std;

class Client
{
private:
    Cart cart;
    User *user;

public:
    // Default constructor
    Client() {}
    Client(User *user)
    {
        this->user = user;
        cart.setUsername(user->getUsername());
    }

    // Method to display the client panel
    void begin()
    {
        SingleColorText s("", Text::blue());
        int choice;
        do
        {
            cout << "\nWelcome, " << Text::green() << user->getUsername() << Text::white() << "! Choose an option:" << endl;
            cout << "1. View Products" << endl;
            cout << "2. Go to Cart" << endl;
            cout << "3. View Order History" << endl;
            cout << "4. Update Profile" << endl;
            cout << "0. Exit" << endl;
            s.setText("Enter your choice: ");
            s.print();
            cin >> choice;

            switch (choice)
            {
            case 1:
                viewProducts();
                break;
            case 2:
                goToCart();
                break;
            case 3:
                user->displayOrderHistory();
                break;
            case 4:
                updateProfile();
                break;
            case 0:
                s.setText("Exiting the client panel. Goodbye, " + user->getUsername() + "!");
                s.setColor(Text::green());
                s.print();
                break;
            default:
                s.setText("Invalid choice. Please try again.");
                s.setColor(Text::red());
                s.print();
                break;
            }
        } while (choice != 0);
    }

private:
    // Method to view available products
    void viewProducts()
    {
        ProductManager pm("files/product.txt");
        pm.displayCatalog();
        cout << endl;

        List<Product> products = pm.getAllProducts();
        string productID;
        int quantity;
        cout << "Enter the Product ID to add to cart (or type 'exit' to return): ";
        cin >> productID;
        if (productID == "exit")
            return;

        cout << "Enter the quantity: ";
        cin >> quantity;

        for (int i = 0; i < products.length(); i++)
        {
            if (products[i].getProductID() == productID)
            {
                cart.addProduct(products[i]);
                return;
            }
        }

        cout << "Product ID not found. Returning to menu." << endl;
    }

    // Method to manage the cart
    void goToCart()
    {
        SingleColorText s("", Text::blue());
        int choice;
        do
        {
            cout << "\nCart Menu:" << endl;
            cout << "1. View Cart" << endl;
            cout << "2. Remove Item from Cart" << endl;
            cout << "3. Checkout" << endl;
            cout << "4. Return to Main Menu" << endl;
            s.setText("Enter your choice: ");
            s.print();
            cin >> choice;

            switch (choice)
            {
            case 1:
                cart.displayCart();
                break;
            case 2:
            {
                string productID;
                s.setText("Enter the Product ID to remove: ");
                s.setColor(Text::blue());
                s.print();
                cin >> productID;
                cart.removeProduct(productID);
                break;
            }
            case 3:
                checkout();
                break;
            case 4:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                s.setColor(Text::red());
                s.setText("Invalid choice, Please try again.");
                cout << endl;
                s.print();
                cout << endl;
                break;
            }
        } while (choice != 4);
    }

    // Method to checkout
    void checkout()
    {
        double totalCost = cart.getTotalPrice();
        cout << "\nTotal Cost: $" << totalCost << endl;
        string confirmation;
        SingleColorText s("Do you want to confirm the purchase? (yes/no): ", Text::blue());
        s.print();
        cin >> confirmation;

        if (confirmation == "yes")
        {
            s.setText("Enter the amount: ");
            s.setColor(Text::blue());
            s.print();
        }
        else
        {
            s.setText("Checkout canceled.");
            s.setColor(Text::red());
            s.print();
        }
    }

    // Method to update client profile
    void updateProfile()
    {
        cout << "\nUpdate Profile:" << endl;
        cout << "1. Update Phone Number" << endl;
        cout << "2. Update Address" << endl;
        cout << "3. Return to Main Menu" << endl;
        string username, address;

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter new phone number: ";
            cin >> username;
            user->setUsername(username);
            cout << "Phone number updated!" << endl;
            break;
        case 2:
            cout << "Enter new address: ";
            cin.ignore();
            getline(cin, address);
            user->setAddress(address);
            cout << "Address updated!" << endl;
            break;
        case 3:
            cout << "Returning to main menu." << endl;
            break;
        default:
            cout << "Invalid choice. Returning to menu." << endl;
            break;
        }
    }
};

#endif

// class Client{
//     public:
//     void begin(){
//         cout << "Client begin" << endl;
//     }
// };