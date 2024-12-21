#include <iostream>
#include "text.cpp"
#include "list.cpp"
#include "cart.cpp"
#include "authentication.cpp"
#include "admin.cpp"
#include "client.cpp"
#include "product_manager.cpp"

using namespace std;

// Takking username and password
List<string> takeUsernamePassword()
{
    List<string> credentials;
    string username, password;
    // Taking user name
    SingleColorText s("Enter username: ", Text::blue());
    s.print();
    cin >> username;

    // Taking password
    s.setText("Enter password: ");
    s.print();
    cin >> password;

    credentials.push_back(username);
    credentials.push_back(password);
    return credentials;
}

int main()
{
    // ----- Logo printing for the first time -----
    // Logo colors
    List<string> colors(10);
    colors.push_back(Text::red());
    colors.push_back(Text::green());
    colors.push_back(Text::blue());
    // Logo Text
    string logoText = ".____                  __    .____           \n"
                      "|    |    ____   _____/  |_  |    |    ____  \n"
                      "|    |   /  _ \\ /  _ \\   __\\ |    |   /  _ \\ \n"
                      "|    |__(  <_> |  <_> )  |   |    |__(  <_> )\n"
                      "|_______ \\____/ \\____/|__|   |_______ \\____/ \n"
                      "        \\/                           \\/      ";

    MultiColorText logo = MultiColorText(logoText, colors, 20);
    // logo.print();
    cout << endl
         << endl;

    // Authencation handling if user goes to any protected screen
    Authentication auth;
    int choice;
    do
    {
        // Printing menu
        cout << endl
             << "1. Client panel"
             << endl
             << "2. Admin panel"
             << endl
             << "3. Create an account"
             << endl
             << "4. See all products"
             << endl
             << "0. Exit" << endl;

        // creating object of animated text for input
        SingleColorText s("Enter your choice: ", Text::blue(), false, 50);
        s.print();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Checking if already loggedin so don't take credentials
            if (auth.isLoggedIn())
            {
                // const User *user = User::findUserByUsername(auth.getCurrentUser()->getUsername());
                Client client(auth.getCurrentUser());
                client.begin();
            }
            else
            {
                while (true)
                {
                    List<string> credentials = takeUsernamePassword();
                    // loggingIn
                    bool result = auth.login(credentials[0], credentials[1], "client");
                    if (result)
                    {
                        Client client(auth.getCurrentUser());
                        client.begin();
                        break;
                    }
                    else
                    {
                        s.setText("Error: Wrong credentials");
                        s.setColor(Text::red());
                        s.print();
                        cout << endl;
                    }
                }
            }
            break;
        }
        case 2:
        {
            Admin admin;
            if (auth.isLoggedIn() && auth.getCurrentUser()->getRole() == "admin")
            {
                admin.begin();
            }
            else
            {
                List<string> credentials = takeUsernamePassword();
                bool result = auth.login(credentials[0], credentials[1], "admin");
                if (result && auth.getCurrentUser()->getRole() == "admin")
                {
                    admin.begin();
                }
                else
                {
                    s.setText("Error: Wrong credentials");
                    s.setColor(Text::red());
                    s.print();
                }
            }
            break;
        }
        case 3:
        {
            string username, password, email, phoneNumber, address, role = "client";
            List<string> usernameAndPass = takeUsernamePassword();
            username = usernameAndPass[0];
            password = usernameAndPass[1];
            s.setColor(Text::blue());
            s.setText("Enter email: ");
            s.print();
            cin >> email;
            s.setText("Enter phone numbmer: ");
            s.print();
            cin >> phoneNumber;
            s.setText("Enter address: ");
            s.print();
            cin >> address;

            bool result = auth.registerUser(username, password, email, role, phoneNumber, address);
            if (result)
                auth.login(username, password, "client");

            // redirecting to the client panel instantly
            Client client(User::findUserByUsername(auth.getCurrentUser()->getUsername(), auth.getAllUsers()));
            client.begin();
            break;
        }
        case 4:
        {
            ProductManager pm("files/product.txt");
            pm.displayCatalog();
            break;
        }
        case 0:
            s.setText("Bye! have a good day.");
            s.setColor(Text::green());
            exit(0);

        default:
        {
            s.setColor(Text::red());
            s.setText("Invalid choice, Please try again.");
            cout << endl;
            s.print();
            cout << endl;
        }
            cin.ignore();
        }
    } while (choice != 0);

    cout << endl
         << endl;
    return 0;
}
