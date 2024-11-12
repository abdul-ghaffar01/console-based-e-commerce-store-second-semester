
#include <iostream>
#include "text.cpp"
#include "list.cpp"
#include "authentication.cpp"
using namespace std;





// int main() {
//     // Single-color text
//     SingleColorText singleColorText("Hello, World!", Text::red(), 100);
//     singleColorText.print();  // Display with animation in red

//     // Multi-color text
//     List<string> colors(10);
//     colors.push_back(Text::red());
//     colors.push_back(Text::green());
//     colors.push_back(Text::blue());
    
//     MultiColorText multiColorText("Hello, Multi-Color World!", colors, 150);
//     multiColorText.print();  // Display with animation in multi-color
    
//     string logoText = ".____                  __    .____           \n"
//                       "|    |    ____   _____/  |_  |    |    ____  \n"
//                       "|    |   /  _ \\ /  _ \\   __\\ |    |   /  _ \\ \n"
//                       "|    |__(  <_> |  <_> )  |   |    |__(  <_> )\n"
//                       "|_______ \\____/ \\____/|__|   |_______ \\____/ \n"
//                       "        \\/                           \\/      ";
    
//     MultiColorText logo = MultiColorText(logoText, colors, 20);
//     logo.print();

//     return 0;
// }





int main() {
    Authentication auth("users.txt");  // Initialize Authentication with filename for persistence

    int choice;
    string username, password, email, role, phoneNumber, address, dateOfRegistration;
    
    while (true) {
        cout << "\n--- Welcome to the Authentication System ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Logout\n";
        cout << "4. Display User Info (Admin only)\n";
        cout << "5. Exit\n";
        cout << "Please select an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Register a new user
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                cout << "Enter email: ";
                cin >> email;
                cout << "Enter role (admin/client): ";
                cin >> role;
                cout << "Enter phone number (optional): ";
                cin >> phoneNumber;
                cout << "Enter address (optional): ";
                cin >> address;
                cout << "Enter registration date (optional): ";
                cin >> dateOfRegistration;

                auth.registerUser(username, password, email, role, phoneNumber, address, dateOfRegistration);
                break;
            }
            case 2: {
                // Login
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (auth.login(username, password)) {
                    cout << "Logged in successfully as " << username << endl;
                }
                break;
            }
            case 3: {
                // Logout
                auth.logout();
                break;
            }
            case 4: {
                // Display all users (Only admin can access this)
                if (auth.isLoggedIn() && auth.getCurrentUser()->isAdmin()) {
                    auth.displayAllUsers();
                } else {
                    cout << "You need to be an admin to view all users.\n";
                }
                break;
            }
            case 5: {
                // Exit
                cout << "Exiting the system.\n";
                return 0;
            }
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }
}

