#include "User.h"
#include "Admin.h"
#include "Student.h"

bool authenticate(string uname, string pass, string& role) {
    if (uname == "admin" && pass == "admin123") {
        role = "admin";
        return true;
    }
    else if (uname == "student" && pass == "student123") {
        role = "student";
        return true;
    }
    return false;
}

int main() {
    string uname, pass, role;
    cout << "\n==== Quiz Management System ====\n";
    cout << "\nLogin\n";
    cout << "User: "; cin >> uname;
    cout << "Password: "; cin >> pass;

    if (authenticate(uname, pass, role)) {
        if (role == "admin") {
            Admin admin(uname, pass);
            admin.showMenu();
        }
        else if (role == "student") {
            Student student(uname, pass);
            student.showMenu();
        }
    }
    else {
        cout << "Invalid credentials!\n";
    }

    return 0;
}
