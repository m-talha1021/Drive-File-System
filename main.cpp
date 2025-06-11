#include "User.h"
#include "FileSystem.h"
#include <limits>

int main() {
    User auth;
    FileSystem fs;
    int choice;
    std::string name, content;

    std::cout << R"(
       ____                   _             
      / ___| ___   ___   ___ | | ___     
     | |  _ / _ \ / _ \ / _ || |/ _ \   
     | |_| | (_) | (_) | (_)|| |  __/   
      \____|\___/ \___/ \__ ||_|\___|   
                        |___/        
        Google Drive File System
    )" << std::endl;
    system("color 0B");

    while (!auth.isLoggedInFunc()) {
        std::cout << "\n 1. Signup\n 2. Login\n 0. Exit\nEnter choice: ";
        while (!(std::cin >> choice)) {
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << " Invalid input! Please enter 0, 1, or 2: ";
        }

        switch (choice) {
            case 1: auth.signup(); break;
            case 2: auth.login(); break;
            case 0: std::cout << "Exiting...\n"; return 0;
            default: std::cout << "Invalid choice!\n";
        }
    }

    do {
        std::cout << "\n3. Logout\n4. Create Folder\n5. Create File\n6. Delete Item\n7. Change Directory\n8. List Directory\n";
        std::cout << "9. Restore Deleted File\n10. Show Recent Files\n11. Write File\n12. Read File\n0. Exit\nEnter choice: ";
        while (!(std::cin >> choice)) {
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << " Invalid input! Try again: ";
        }

        switch (choice) {
            case 3: auth.logout(); break;
            case 4: std::cout << "Folder name: "; std::cin >> name; fs.create(name, true); break;
            case 5: std::cout << "File name: "; std::cin >> name; fs.create(name, false); break;
            case 6: std::cout << "Delete item: "; std::cin >> name; fs.deleteItem(name); break;
            case 7: std::cout << "Change dir (.. for root): "; std::cin >> name; fs.changeDirectory(name); break;
            case 8: fs.listDirectory(); break;
            case 9: fs.restoreDeleted(); break;
            case 10: fs.showRecent(); break;
            case 11: std::cout << "File name: "; std::cin >> name; std::cout << "Content: "; std::cin.ignore(); std::getline(std::cin, content); fs.writeFile(name, content); break;
            case 12: std::cout << "File name: "; std::cin >> name; fs.readFile(name); break;
            case 0: std::cout << "Exiting program...\n"; break;
            default: std::cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    system("pause");
    return 0;
}
