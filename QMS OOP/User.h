#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class User {
protected:
    string username;
    string password;

public:
    User() {}
    User(string uname, string pass) : username(uname), password(pass) {}

    void setUsername(string uname) 
    { 
        username = uname; 
    }
    void setPassword(string pass) 
    { 
        password = pass; 
    }
    string getUsername() 
    {
        return username; 
    }
    string getPassword() 
    { 
        return password; 
    }

    virtual void showMenu() = 0; // Pure virtual function (Abstraction)
};

#endif