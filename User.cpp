#include "User.h"
using namespace std;

User::User() {}

void User::signup() {
    string username, password;
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter new password: ";
    cin >> password;

    if (users.count(username)) {
        cout << "Username already exists.\n";
        return;
    }
    users[username] = password;
    cout << "Signup successful.\n";
}

void User::login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (users.count(username) && users[username] == password) {
        loggedInUser = username;
        cout << "Login successful.\n";
    } else {
        cout << "Invalid credentials.\n";
    }
}

void User::logout() {
    loggedInUser = "";
    cout << "Logged out.\n";
}

bool User::isLoggedInFunc() {
    return !loggedInUser.empty();
}

string User::getLoggedInUser() {
    return loggedInUser;
}
