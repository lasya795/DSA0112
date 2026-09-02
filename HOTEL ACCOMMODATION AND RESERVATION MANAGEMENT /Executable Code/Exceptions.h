#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Base exception for the whole hotel system. Everything else derives from
// this so callers can choose to catch broadly (HotelException) or narrowly
// (e.g. RoomUnavailableException) depending on what they need to do.
class HotelException : public std::runtime_error {
public:
    explicit HotelException(const std::string& message)
        : std::runtime_error(message) {}
};

class InvalidInputException : public HotelException {
public:
    explicit InvalidInputException(const std::string& message)
        : HotelException(message) {}
};

class InvalidGuestException : public HotelException {
public:
    explicit InvalidGuestException(const std::string& message)
        : HotelException(message) {}
};

class InvalidRoomException : public HotelException {
public:
    explicit InvalidRoomException(const std::string& message)
        : HotelException(message) {}
};

class RoomUnavailableException : public HotelException {
public:
    explicit RoomUnavailableException(const std::string& message)
        : HotelException(message) {}
};

class InvalidDateException : public HotelException {
public:
    explicit InvalidDateException(const std::string& message)
        : HotelException(message) {}
};

class InvalidReservationException : public HotelException {
public:
    explicit InvalidReservationException(const std::string& message)
        : HotelException(message) {}
};

#endif // EXCEPTIONS_H
