#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cmath> // For abs() function

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

    Date() : day(1), month(1), year(1) {}
    
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    bool IsValidDate(int d, int m, int y) const {
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > Days(m, y)) return false;
        if (y < 1 || y > 9999) return false;
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

    // Get values for date difference calculations
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

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
        DisplayDate();
        return *this;
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
        DisplayDate();
        return *this;
    }

    void MinusDays(int n) {
        cout << "Subtracting " << n << " days..." << endl;
        for (int i = 0; i < n; i++) {
            PrevDayPrefix();
        }
    }

    void PlusDays(int n) {
        cout << "Adding " << n << " days..." << endl;
        for (int i = 0; i < n; i++) {
            NextDayPrefix();
        }
    }

    // Calculate approximate date difference in days
    static int DateDiff(const Date& date1, const Date& date2) {
        // Convert both dates to approximate days since year 0
        int days1 = date1.getYear() * 365 + date1.getDay();
        for(int m = 1; m < date1.getMonth(); m++) {
            days1 += date1.Days(m, date1.getYear());
        }
        
        int days2 = date2.getYear() * 365 + date2.getDay();
        for(int m = 1; m < date2.getMonth(); m++) {
            days2 += date2.Days(m, date2.getYear());
        }
        
        // Add leap years adjustment
        days1 += date1.getYear() / 4 - date1.getYear() / 100 + date1.getYear() / 400;
        days2 += date2.getYear() / 4 - date2.getYear() / 100 + date2.getYear() / 400;
        
        return abs(days2 - days1);
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
        // Check for Esc key press to exit
        if (_kbhit()) {
            int key = _getch();
            if (key == 27) { // ESC key
                cout << "Exiting the program..." << endl;
                break;
            }
        }

        // Choose between math operations and day movement
        char choice;
        while (true) {
            cout << "  (m) Math operations (add/subtract days)" << endl;
            cout << "  (d) Day movement (next/previous day)" << endl;
            cout << "  (c) Compare with another date" << endl;
            cout << "  (v) View current date" << endl;
            cin >> choice;
            if (choice == 'm' || choice == 'd' || choice == 'c' || choice == 'v' ) {
                break;
            }
            cout << "Invalid choice! Please enter 'm', 'd', 'c', or 'v'." << endl;
        }

        if (choice == 'm') {
            // Math operations (add/subtract days)
            char operation;
            while (true) {
                cout << "Add or subtract days? (+/-): ";
                cin >> operation;
                if (operation == '+' || operation == '-') {
                    break;
                }
                cout << "Invalid choice! Please enter '+' or '-'." << endl;
            }

            int days;
            cout << "Enter the number of days: ";
            cin >> days;

            if (operation == '+') {
                date1.PlusDays(days);
            } else {
                date1.MinusDays(days);
            }
        } 
        else if (choice == 'd') {
            // Move one day forward/backward
            char direction;
            while (true) {
                cout << "Go to next or previous day? (+/-): ";
                cin >> direction;
                if (direction == '+' || direction == '-') {
                    break;
                }
                cout << "Invalid choice! Please enter '+' or '-'." << endl;
            }

            if (direction == '+') {
                date1.NextDayPrefix();
            } else {
                date1.PrevDayPrefix();
            }
        }
        else if (choice == 'c') {
            // Compare with another date
            Date date2;
            int d2, m2, y2;
            
            cout << "Enter second date to compare with first date:" << endl;
            while (true) {
                cout << "Enter the day: ";
                cin >> d2;
                cout << "Enter the month: ";
                cin >> m2;
                cout << "Enter the year: ";
                cin >> y2;

                if (date2.IsValidDate(d2, m2, y2)) {
                    break;
                }
                cout << "Invalid date! Please try again." << endl;
            }

            date2.ParameterizedDate(d2, m2, y2);

            int diff = Date::DateDiff(date1, date2);
            cout << "Approximate difference between dates: " << diff << " days" << endl;
        }
        else if (choice == 'v') {
            // View current date
            date1.DisplayDate();
        }
    }

    return 0;
}