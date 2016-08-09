// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SERVICE_H
#define SERVICE_H

#include <string>

namespace sunglasses {

enum ButtonState {
    ButtonStateNone = -1,
    ButtonStateUp = 0,
    ButtonStateDown = 1
};

enum ButtonEvent {
    ButtonEventUpSingle = 0,
    ButtonEventDownSingle = 1,

    ButtonEventUpContinuous = 2,
    ButtonEventDownContinuous = 3
};

/// An abstract class that is used to provide services to all Base objects
/**
 * Service is an abstract class that is meant to be subclassed and used to provide
 * services to Base objects. Base has a static map of Services, which can
 * be used to identify and use services. Game also updates each service every game
 * cycle.
 */
class Service {
public:
    /// The default constructor
    /**
     * This constructor, which is the default constructor with no arguments, does not
     * initialize the name member (string).
     */
    Service();

    /// The virtual destructor
    /**
     * This is the virtual destructor, and should be implemented by all services
     * because they are handled as a list of pointers to Service.
     */
    virtual ~Service();

    /// The constructor for the name member (string)
    /**
     * This constructor takes the single parameter (string) and initializes the name
     * member with it.
     */
    Service(std::string _name);

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
