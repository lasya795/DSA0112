#ifndef DATEUTILS_H
#define DATEUTILS_H

#include "Exceptions.h"
#include <ctime>
#include <string>

// Small header-only helper for parsing "DD-MM-YYYY" dates, validating
// them, and computing real calendar information (nights between two
// dates, and whether a date falls on a weekend) using <ctime>. Kept
// separate from Hotel so the date-handling logic isn't tangled up with
// business/menu logic.
namespace DateUtils {

struct SimpleDate {
    int day, month, year;
};

inline SimpleDate parseDate(const std::string& text) {
    // Expected format: DD-MM-YYYY
    if (text.size() != 10 || text[2] != '-' || text[5] != '-') {
        throw InvalidDateException("Date must be in DD-MM-YYYY format, e.g. 24-12-2026.");
    }
    for (int pos : {0, 1, 3, 4, 6, 7, 8, 9}) {
        if (!isdigit(static_cast<unsigned char>(text[pos]))) {
            throw InvalidDateException("Date must be in DD-MM-YYYY format, e.g. 24-12-2026.");
        }
    }

    SimpleDate d;
    d.day = std::stoi(text.substr(0, 2));
    d.month = std::stoi(text.substr(3, 2));
    d.year = std::stoi(text.substr(6, 4));

    if (d.month < 1 || d.month > 12) {
        throw InvalidDateException("Month must be between 01 and 12.");
    }
    static const int daysInMonth[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (d.day < 1 || d.day > daysInMonth[d.month - 1]) {
        throw InvalidDateException("Day is out of range for the given month.");
    }
    if (d.year < 2024 || d.year > 2100) {
        throw InvalidDateException("Year must be between 2024 and 2100.");
    }
    return d;
}

inline std::time_t toTimeT(const SimpleDate& d) {
    std::tm tm{};
    tm.tm_mday = d.day;
    tm.tm_mon = d.month - 1;
    tm.tm_year = d.year - 1900;
    tm.tm_hour = 12; // avoid DST edge issues
    return std::mktime(&tm);
}

// Returns number of nights between check-in and check-out. Throws if
// check-out is not strictly after check-in.
inline int nightsBetween(const std::string& checkIn, const std::string& checkOut) {
    SimpleDate inDate = parseDate(checkIn);
    SimpleDate outDate = parseDate(checkOut);
    std::time_t t1 = toTimeT(inDate);
    std::time_t t2 = toTimeT(outDate);
    double seconds = std::difftime(t2, t1);
    int nights = static_cast<int>(seconds / (60 * 60 * 24) + 0.5);
    if (nights <= 0) {
        throw InvalidDateException("Check-out date must be after the check-in date.");
    }
    return nights;
}

// A stay is treated as a "weekend stay" if check-in falls on Fri/Sat/Sun.
inline bool isWeekendCheckIn(const std::string& checkIn) {
    SimpleDate d = parseDate(checkIn);
    std::tm tm{};
    tm.tm_mday = d.day;
    tm.tm_mon = d.month - 1;
    tm.tm_year = d.year - 1900;
    tm.tm_hour = 12;
    std::mktime(&tm); // normalizes and fills tm_wday
    return tm.tm_wday == 0 || tm.tm_wday == 5 || tm.tm_wday == 6; // Sun, Fri, Sat
}

// Simple peak-season rule: December, January, June and July.
inline bool isSeasonalPeak(const std::string& checkIn) {
    SimpleDate d = parseDate(checkIn);
    return d.month == 12 || d.month == 1 || d.month == 6 || d.month == 7;
}

} // namespace DateUtils

#endif // DATEUTILS_H
