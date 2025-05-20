#include <iostream>
#include <iomanip>
#include <conio.h>

using namespace std;

class Date {

private:
    int day, month, year;

    bool LeapYear(int y) const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    int Days(int m, int y) const {
        if (m == 2) {
            return LeapYear(y) ? 29 : 28;
        }
        if (m == 4 || m == 6 || m == 9 || m == 11) {
            return 30;
        }
        return 31;
    }

    public:

    bool IsValidDate(int d, int m, int y) const {
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > Days(m, y)) return false;
        return true;
    }

    void ParameterizedDate(int d, int m, int y) {
        if (!IsValidDate(d, m, y)) {
            cout << "Invalid date! Please enter a valid date." << endl;
            return;
        }

        day = d;
        month = m;
        year = y;

        DisplayDate();
    }

    // Display the current date
    void DisplayDate() const {
        cout << "Date is..." << endl;
        cout << "      " << setfill('0') << setw(2) << day << "."
             << setfill('0') << setw(2) << month << "."
             << setfill('0') << setw(4) << year << endl;
    }

    Date& NextDayPrefix() {
        day++;
        if (day > Days(month, year)) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        return *this;
    }

    Date NextDayPostfix() {
        Date temp = *this;  // Create a copy with original values
        day++;              // Modify this object
        if (day > Days(month, year)) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        return temp;        // Return the unmodified copy
    }

    Date& PrevDayPrefix() {
        day--;
        if (day < 1) {
            month--;
            if (month < 1) {
                month = 12;
                year--;
            }
            day = Days(month, year);
        }
        return *this;
    }

    Date PrevDayPostfix() {
        Date temp = *this;  // Create a copy with original values
        day--;              // Modify this object
        if (day < 1) {
            month--;
            if (month < 1) {
                month = 12;
                year--;
            }
            day = Days(month, year);
        }
        return temp;        // Return the unmodified copy
    }
 

};

int main() {
    Date date1;
    int d, m, y;


    while (true) {
        cout << "Enter the day: ";
        cin >> d;
        cout << "Enter the month: ";
        cin >> m;
        cout << "Enter the year: ";
        cin >> y;

        if (date1.IsValidDate(d, m, y)) {
            break;
        }
        cout << "Invalid date! Please try again." << endl;
    }

    date1.ParameterizedDate(d, m, y);

    while (true) {
        if (_getch() == 27) // ESC key
            return 0;

        
        char c;
        while (true) {
            cout << "Go to next or previous day? (+/-): ";
            cin >> c;
            if (c == '+' || c == '-') {
                break;
            }
            cout << "Invalid choice! Please enter '+' or '-'." << endl;
        }


        int n;
        while (true) {
            cout << "Prefix or Postfix? (1/2): ";
            cin >> n;
            if (n == 1 || n == 2) {
                break;
            }
            cout << "Invalid choice! Please enter 1 or 2." << endl;
        }

        Date result;

        if (c == '+') {
            if (n == 1) {
                result = date1.NextDayPrefix();  // Modify date1 and get reference to it
                cout << "After prefix increment: ";
            } else {
                result = date1.NextDayPostfix();  // Get copy of original date1, then modify date1
                cout << "Original date (from postfix): ";
                result.DisplayDate();
                cout << "After postfix increment: ";
            }
        } else {
            if (n == 1) {
                result = date1.PrevDayPrefix();  // Modify date1 and get reference to it
                cout << "After prefix decrement: ";
            } else {
                result = date1.PrevDayPostfix();  // Get copy of original date1, then modify date1
                cout << "Original date (from postfix): ";
                result.DisplayDate();
                cout << "After postfix decrement: ";
            }
        }
        
        date1.DisplayDate();  // Display the current state of date1
    }

}