// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNCLOPTIONPARSING_H
#define SUNCLOPTIONPARSING_H

#include <string>
#include <functional>
#include <vector>

/// A struct representing a command line option
/**
 * This struct represents a command line option. It contains a short name ('-x'),
 * a long name ('-\-name'), a description (for '-h/-\-help'), and a function called
 * when the option is present.
 */
struct SunCLOption {
    /// The default constructor
    SunCLOption();

    /**
     * @param _shortName The short name of the new option.
     * @param _longName The long name of the new option.
     * @param _description The description of the new option.
     * @param _function The function of the new option.
     */
    SunCLOption(std::string _shortName, std::string _longName, std::string _description, std::function<void()> _function);

    /// The short name of the option ('-x')
    /**
     * This member is the short name of the option. It can be invoked as '-x', where
     * 'x' is the short name. Short names must be prefixed with '-'.
     * Short names of different options can be combined, such
     * as '-xy' if you have two options with short names 'x' and 'y'.
     * @warning When combining short names, any option with a parameter must be at the end
     * of the string of short names ('-yx' is not valid if 'y' has a parameter).
     */
    std::string shortName;

    /// The long name of the option ('-\-name')
    /**
     * This member is the long name of the option. It can be invoked is '--name', where
     * 'name' is the long name. Unlike short names, long names are prefixed with '-\-'.
     * You cannot combine long names. To specify an argument, append an equals sign and the
     * desired argument ('-\-somebool=yes') or separate it by a space ('-\-somebool yes').
     */
    std::string longName;

    /// The description of the option
    /**
     * This member is the description of the option. This is only displayed when '-h'
     * or '--help' is invoked.
     */
    std::string description;

    /// The function of the option
    /**
     * This member is the function that is invoked when the option is used.
     */
    std::function<void()> function;
};

/// A namespace for internal use for parsing command line options
namespace _SunPrivateCLOptionParsing {
    /// Determines whether a string is a long option
    /**
     * This function tells whether a string forms a long option. It must be of the form
     * '-\-x' to be true.
     * @param option The string to be tested
     * @return A boolean indicating whether the string was a long option
     */
    extern bool isLongOption(char *option);

    /// Determines whether a string is a short option
    /**
     * This function tells whether a string forms a short option. It must be of the
     * form '-x' to be true.
     * @param option The string to be tested
     * @return A boolean indicating whether the string was a short option
     */
    extern bool isShortOption(char *option);
};

/// Generates a help option
/**
 * This function generates a help option for use in parsing arguments.
 * @param options The vector of options (defined in SunGame)
 * @return An option that generates the help message
 */
extern SunCLOption generateHelpOption(const std::vector<SunCLOption> &options);

/// Parses command line options.
/**
 * @param argc The argument count (given in main())
 * @param argv The argument array (given in main())
 * @param options The vector of options (defined in SunGame)
 * @retval 0    Parsing executed successfully
 * @retval -1   Parsing did not execute successfully
 */
extern int parseOptions(int argc, char **argv, const std::vector<SunCLOption> &options);

#endif
