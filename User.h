#ifndef USER_H
#define USER_H

#include <iostream>
#include <unordered_map>
#include <string>

class User {
private:
    std::unordered_map<std::string, std::string> users;
    std::string loggedInUser;

public:
    User();
    void signup();
    void login();
    void logout();
    bool isLoggedInFunc();
    std::string getLoggedInUser();
};

#endif
