// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNSERVICE_H
#define SUNSERVICE_H

#include <string>

namespace sunglasses {

enum SunButtonState {
    SunButtonStateNone = -1,
    SunButtonStateUp = 0,
    SunButtonStateDown = 1
};

enum SunButtonEvent {
    SunButtonEventUpSingle = 0,
    SunButtonEventDownSingle = 1,

    SunButtonEventUpContinuous = 2,
    SunButtonEventDownContinuous = 3
};

/// An abstract class that is used to provide services to all SunBase objects
/**
 * SunService is an abstract class that is meant to be subclassed and used to provide
 * services to SunBase objects. SunBase has a static map of SunServices, which can
 * be used to identify and use services. SunGame also updates each service every game
 * cycle.
 */
class SunService {
public:
    /// The default constructor
    /**
     * This constructor, which is the default constructor with no arguments, does not
     * initialize the name member (string).
     */
    SunService();

    /// The virtual destructor
    /**
     * This is the virtual destructor, and should be implemented by all services
     * because they are handled as a list of pointers to SunService.
     */
    virtual ~SunService();

    /// The constructor for the name member (string)
    /**
     * This constructor takes the single parameter (string) and initializes the name
     * member with it.
     */
    SunService(std::string _name);

    /// A pure virtual function that should update the service
    /**
     * This member function, which is a pure virtual function, should be implemented
     * in each subclass and should update the service in its implementation.
     */
    virtual void update() = 0;

    /// Gets the name member (string).
    std::string getName() { return name; }
    /// Sets the name member (string).
    void setName(std::string _name) { name = _name; }
private:
    /// A string that is used to identify the service.
    std::string name;
};

} // namespace

#endif
