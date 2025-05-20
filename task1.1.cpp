#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Date {

private:
    int day, month, year;

public:
    // Default constructor
    Date() {
        day = 1;
        month = 1;
        year = 1;
        cout << "Default date (constructor)" << endl;
        cout << "      " << setfill('0') << setw(2) << day << "."
             << setfill('0') << setw(2) << month << "."
             << setfill('0') << setw(4) << year << endl;
    }

    // Parameterized constructor
    Date(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
        cout << "Initializing a value (constructor)" << endl;
        cout << "      " << setfill('0') << setw(2) << day << "."
             << setfill('0') << setw(2) << month << "."
             << setfill('0') << setw(4) << year << endl;
    }

    // Copy constructor
    Date(const Date& otherDate) {
        day = otherDate.day;
        month = otherDate.month;
        year = otherDate.year;
        cout << "Copying (constructor)" << endl;
        cout << "      " << setfill('0') << setw(2) << day << "."
             << setfill('0') << setw(2) << month << "."
             << setfill('0') << setw(4) << year << endl;
    }
};

int main() {
    Date date1; // Default constructor
    Date date2(15, 5, 2023); // Parameterized constructor
    Date date3 = date2; // Copy constructor

    return 0;
}