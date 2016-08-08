// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNCLOPTIONPARSING_H
#define SUNCLOPTIONPARSING_H

#include <string>
#include <functional>
#include <vector>

#include <tclap/CmdLine.h>

namespace sunglasses {

/// An abstract struct that represents a command line option
/**
 * This abstract struct represents an option/argument on the command line. Subclasses
 * must implement the add and
 */
struct SunCLOption {
    /// Adds the option to a command line object.
    /**
     * This member function adds the option to the command line object. This
     * has to be implemented for each subclass because it is a pure virtual
     * function. This is called automatically by the parseOptions function.
     * @param commandLine A reference to the command line object
     */
    virtual void add(TCLAP::CmdLine &commandLine) = 0;

    /// Processes the value of the option after parsing.
    /**
     * This member function processes the option after parsing is done. This is
     * pure virtual, so it must be implemented in each subclass. This is called
     * automatically on every option after parsing in the parseOptions function.
     */
    virtual void process() = 0;
};



/// A subclass of SunCLOption that represents a switch option
/**
 * This subclass of SunCLOption represents a switch option. It adds itself
 * using the TCLAP::SwitchArg, and has a reference to a boolean where it
 * will store its value.
 */
struct SunCLSwitchOption : public SunCLOption {
public:
    /// Constructs the switch option.
    /**
     * @param shortOption The short name for the switch
     * @param longOption The long name for the switch
     * @param description The description for the switch (used in help)
     * @param defaultValue The default value of the switch (normally false)
     * @param _value A pointer to the boolean that should be assigned with the value of the option
     */
    SunCLSwitchOption(std::string shortOption, std::string longOption, std::string description, bool defaultValue, bool *_value);

    /// Adds the switch option to the command line object.
    /**
     * @param commandLine A reference to the command line object
     */
    virtual void add(TCLAP::CmdLine &commandLine);

    /// Assigns the value of the option to the boolean.
    virtual void process();
private:
    /// The TCLAP argument attached to the command line
    TCLAP::SwitchArg arg;

    /// The reference to the boolean that it should be stored in
    bool *value;
};



/// A subclass of SunCLOption that represents a value option
/**
 * This subclass of SunCLOption represents a value option. It adds itself
 * using the TCLAP::ValueArg, and has a reference to an object of its type
 * where it will store its value.
 */
template<typename T>
struct SunCLValueOption : public SunCLOption {
public:
    /// Constructs the value option.
    /**
     * @param shortOption The short name for the option
     * @param longOption The long name for the option
     * @param description The description for the option (used in help)
     * @param typeDescription The description for the type of the option (used in help)
     * @param defaultValue The default value of the option
     * @param required Whether the option is required
     * @param _value A pointer to the object that should b assigned with the value of the option
     */
    SunCLValueOption(std::string shortOption, std::string longOption, std::string description, std::string typeDescription, T defaultValue, bool required, T *_value) : arg(shortOption, longOption, description, required, defaultValue, typeDescription), value(_value) { }

    /// Adds the value option to the command line object.
    /**
     * @param commandLine A reference to the command line object
     */
    virtual void add(TCLAP::CmdLine &commandLine) {
        commandLine.add(arg);
    }

    /// Assigns the value of the option to the associated object.
    virtual void process() {
        (*value) = arg.getValue();
    }
private:
    /// The TCLAP argument attached to the command line
    TCLAP::ValueArg<T> arg;

    /// The reference to the object that it should be stored in
    T *value;
};



/// Parses command line options.
/**
 * This function takes in argc and argv from main and parses the given options
 * using the TCLAP library.
 * @param options The vector of options to be parsed
 * @param help The help message
 * @param version The version string
 * @param argc The argument count (given in main)
 * @param argv The argument vector (given in main)
 */
extern void parseOptions(const std::vector<SunCLOption *> &options, std::string help, std::string version, int argc, char **argv);

} // namespace

#endif
