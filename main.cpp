
#include <iostream>
#include "text.cpp"
#include "list.cpp"
#include "authentication.cpp"
#include "admin/admin.cpp"

using namespace std;





int main() {
    // Single-color text
    // SingleColorText singleColorText("Hello, World!", Text::red(), 100);
    // singleColorText.print();  // Display with animation in red

    // Multi-color text
    List<string> colors(10);
    colors.push_back(Text::red());
    colors.push_back(Text::green());
    colors.push_back(Text::blue());
    
    // MultiColorText multiColorText("Hello, Multi-Color World!", colors, 150);
    // multiColorText.print();  // Display with animation in multi-color
    
    string logoText = ".____                  __    .____           \n"
                      "|    |    ____   _____/  |_  |    |    ____  \n"
                      "|    |   /  _ \\ /  _ \\   __\\ |    |   /  _ \\ \n"
                      "|    |__(  <_> |  <_> )  |   |    |__(  <_> )\n"
                      "|_______ \\____/ \\____/|__|   |_______ \\____/ \n"
                      "        \\/                           \\/      ";
    
    MultiColorText logo = MultiColorText(logoText, colors, 20);
    logo.print();
    
    BlinkingText b(logoText, 100, 1);
    b.print();
    return 0;
}





// int main() {
//     Authentication auth;
//     auth.login("ags", "ags");
//     Admin admin;
//     admin.begin();

//     return 0;
// }

