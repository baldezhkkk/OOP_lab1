#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cmath> // For abs() function
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

class Date {
private:
    int day, month, year;

    static int existingCount;
    static int totalCreated;

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

    int DayOfYear() const {
        int doy = day;
        for (int i = 1; i < month; i++) {
            doy += Days(i, year);
        }
        return doy;
    }

public:
    // Default constructor
    Date() : day(1), month(1), year(1) {
        existingCount++;
        totalCreated++;
    }
    
    // Constructor with parameters
    Date(int d, int m, int y) : day(d), month(m), year(y) {
        existingCount++;
        totalCreated++;
    }

    ~Date() {
        existingCount--;
    }

    bool IsValidDate(int d, int m, int y) const {
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > Days(m, y)) return false;
        if (y < 1 || y > 9999) return false;
        return true;
    }

    string DayOfWeek() const {
        int y = year, m = month;
        if (m < 3) {
            m += 12;
            y -= 1;
        }
        int K = y % 100;
        int J = y / 100;
        int h = (day + 13*(m + 1)/5 + K + K/4 + J/4 + 5*J) % 7;
        static const string days[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
        return days[h];
    }

    int WeekNumber() const {
        return (DayOfYear() - 1) / 7 + 1;
    }

    string ToString() const {
        ostringstream oss;
        oss << setfill('0') << setw(2) << day << "."
            << setw(2) << month << "."
            << setw(4) << year;
        return oss.str();
    }

    static Date FromString(const string& str) {
        int d, m, y;
        char dot1, dot2;
        istringstream iss(str);
        if (iss >> d >> dot1 >> m >> dot2 >> y && dot1 == '.' && dot2 == '.') {
            return Date(d, m, y);
        } else {
            throw invalid_argument("Invalid date string format");
        }
    }

    static int GetExistingCount() {
        return existingCount;
    }

    static int GetTotalCreated() {
        return totalCreated;
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

    // New method to display day of week
    void DisplayDayOfWeek() const {
        cout << "Day of week: " << DayOfWeek() << endl;
    }
    
    // New method to display week number
    void DisplayWeekNumber() const {
        cout << "Week number: " << WeekNumber() << " (of the year)" << endl;
    }
    
    // New method to display string representation
    void DisplayAsString() const {
        cout << "String representation: " << ToString() << endl;
    }
    
    // New static method to display object counts
    static void DisplayObjectCounts() {
        cout << "Object counts:" << endl;
        cout << "  Currently existing: " << GetExistingCount() << endl;
        cout << "  Total created: " << GetTotalCreated() << endl;
    }

    // Get values for date difference calculations
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    // Set individual fields with validation
    bool setDay(int d) {
        if (d < 1 || d > Days(month, year)) {
            cout << "Invalid day value! Day must be between 1 and " << Days(month, year) << " for month " << month << endl;
            return false;
        }
        day = d;
        return true;
    }

    bool setMonth(int m) {
        if (m < 1 || m > 12) {
            cout << "Invalid month value! Month must be between 1 and 12." << endl;
            return false;
        }
        
        // Check if the current day is valid for the new month
        if (day > Days(m, year)) {
            cout << "Invalid month change! Current day (" << day << ") exceeds maximum days (" 
                 << Days(m, year) << ") for month " << m << endl;
            return false;
        }
        
        month = m;
        return true;
    }

    bool setYear(int y) {
          // Validate year range
        if (y <= 0 || y > 9999) {
            cout << "Invalid year value! Year must be between 1 and 9999." << endl;
            return false;
        }
        // Check if February 29 in a leap year would become invalid
        if (month == 2 && day == 29 && !LeapYear(y)) {
            cout << "Invalid year change! February 29 does not exist in non-leap year " << y << endl;
            return false;
        }
        
        year = y;
        return true;
    }

    // Method to modify a specific field
    bool modifyField(char field, int value) {
        bool success = false;
        
        switch(field) {
            case 'd':
                success = setDay(value);
                break;
            case 'm':
                success = setMonth(value);
                break;
            case 'y':
                success = setYear(value);
                break;
            default:
                cout << "Invalid field! Please use 'd' for day, 'm' for month, or 'y' for year." << endl;
                return false;
        }
        
        if (success) {
            cout << "Field updated successfully!" << endl;
            DisplayDate();
        } else {
            cout << "Field update failed. Date remains unchanged." << endl;
        }
        
        return success;
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

int Date::existingCount = 0;
int Date::totalCreated = 0;

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

    // Create and destroy some additional Date objects to demonstrate counters
    {
        Date tempDate1(1, 1, 1);
        Date tempDate2(25, 5, 2025);
        cout << "\nCreated two temporary dates. Current object counts:" << endl;
        Date::DisplayObjectCounts();
    } // tempDate1 and tempDate2 are destroyed here

    cout << "\nAfter temporary dates are destroyed:" << endl;
    Date::DisplayObjectCounts();

    // Demonstrate string conversion
    cout << "\nDemonstrating string conversion:" << endl;
    date1.DisplayAsString();
    
    // Demonstrate string parsing
    string dateStr = "15.09.2022";
    cout << "\nCreating a date from string: " << dateStr << endl;
    try {
        Date parsedDate = Date::FromString(dateStr);
        parsedDate.DisplayDate();
        parsedDate.DisplayDayOfWeek();
        parsedDate.DisplayWeekNumber();
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }

    while (true) {
        // Check for Esc key press to exit
        if (_kbhit()) {
            int key = _getch();
            if (key == 27) { // ESC key
                cout << "Exiting the program..." << endl;
                break;
            }
        }

        // Choose between math operations, day movement, or field modification
        char choice;
        while (true) {
            cout << "\nChoose operation:" << endl;
            cout << "  (m) Math operations (add/subtract days)" << endl;
            cout << "  (d) Day movement (next/previous day)" << endl;
            cout << "  (c) Compare with another date" << endl;
            cout << "  (f) Modify individual field" << endl;
            cout << "  (v) View current date" << endl;
            cout << "  (w) View day of week" << endl;
            cout << "  (n) View week number" << endl;
            cout << "  (s) View string representation" << endl;
            cout << "  (o) View object counts" << endl;
            cout << "Enter choice (m/d/c/f/v/w/n/s/o): ";
            cin >> choice;
            if (choice == 'm' || choice == 'd' || choice == 'c' || choice == 'f' ||
                choice == 'v' || choice == 'w' || choice == 'n' || choice == 's' || choice == 'o') {
                break;
            }
            cout << "Invalid choice! Please try again." << endl;
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
            } else if (operation == '-') {
                date1.MinusDays(days);
            }
        } else if (choice == 'd') {
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
        } else if (choice == 'c') {
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
        } else if (choice == 'f') {
            // Modify individual field
            char field;
            while (true) {
                cout << "Which field to modify? (d)ay, (m)onth, or (y)ear: ";
                cin >> field;
                if (field == 'd' || field == 'm' || field == 'y') {
                    int value;
                    cout << "Enter the new value: ";
                    cin >> value;
                    date1.modifyField(field, value);
                    break;  // Break after handling the modification
                }
                cout << "Invalid field! Please enter 'd', 'm', or 'y'." << endl;
            }
            
        } else if (choice == 'v') {
            // Just display the current date
            date1.DisplayDate();
        } else if (choice == 'w') {
            // Display day of week
            date1.DisplayDayOfWeek();
        } else if (choice == 'n') {
            // Display week number
            date1.DisplayWeekNumber();
        } else if (choice == 's') {
            // Display string representation
            date1.DisplayAsString();
        } else if (choice == 'o') {
            // Display object counts
            Date::DisplayObjectCounts();
        }
    }

    return 0;
}