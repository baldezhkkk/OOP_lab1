# OOP_lab1
#Date Class Implementation
This project implements a versatile Date class in C++ with various features for date manipulation, validation, and comparison. The implementation evolves through several tasks, each adding new capabilities.
Overview
The Date class provides a comprehensive set of functionalities for working with dates, including:

# Date validation
Date manipulation (next/previous day, adding/subtracting days)
Date comparison
Day of week calculation
Week number calculation
String conversions
Object tracking

# Code Structure
The project consists of multiple implementation files, each building on the previous one:

task1.1.cpp - Basic Date class with constructors
task1.2.cpp - Date validation and day manipulation
task1.3.cpp - Date arithmetic operations
task1.4.cpp - Field modification capabilities
task1.5.cpp - Extended features (day of week, week number, string conversion, object tracking)

# Key Interactions

Enter a valid date
Choose operations:

(m) Math operations (add/subtract days)
(d) Day movement (next/previous day)
(c) Compare with another date
(f) Modify individual field
(v) View current date
(w) View day of week
(n) View week number
(s) View string representation
(o) View object counts

Press ESC key to exit

# Notes
Date validation is performed thoroughly to ensure consistency.
The class handles leap years correctly for February 29.
When modifying individual fields, the class ensures the resulting date remains valid.
The DateDiff method provides an approximate difference in days between two dates.
