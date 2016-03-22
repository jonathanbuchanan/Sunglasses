// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunCLOptionParsing.h"

#include <iostream>
#include <algorithm>
#include <string.h>

SunCLOption::SunCLOption() {

}

SunCLOption::SunCLOption(std::string _shortName, std::string _longName, std::string _description, std::function<void(int, char **, int)> _function) : shortName(_shortName), longName(_longName), description(_description), function(_function) {
    SunCLOption();
}



namespace _SunPrivateCLOptionParsing {
    extern bool isLongOption(char *option) {
        if (strlen(option) > 2) {
            if (strncmp(option, "--", 2) == 0)
                return true;
        }
        return false;
    }

    extern bool isShortOption(char *option) {
        if (strlen(option) > 1) {
            if (option[0] == '-' && option[1] != '-')
                return true;
        }
        return false;
    }
};

SunCLOption generateHelpOption(const std::vector<SunCLOption> &options) {
    std::function<void(int, char **, int)> function = [&options](int argc, char **argv, int i) -> void {
        std::cout << "HELP!" << std::endl;
    };

    return SunCLOption("h", "help", "Shows the help message.", function);
}

char * getArgument(int argc, char **argv, int index) {
    
}

int parseOptions(int argc, char **argv, const std::vector<SunCLOption> &options) {
    for (int i = 1; i < argc; ++i) { // Iterate through the arguments (starting at 1 because argv[0] == command)
        char *arg = argv[i]; // Get the argument/option
        if (_SunPrivateCLOptionParsing::isShortOption(arg)) {
            for (size_t j = 1; j < strlen(arg); ++j) { // Split the short option
                char *ch = (char *)malloc(2 * sizeof(char));
                ch[0] = arg[j];
                ch[1] = '\0';
                auto findshortname = [ch](const SunCLOption &option) -> bool {
                    return (strcmp(ch, option.shortName.c_str()) == 0);
                };
                auto iterator = std::find_if(options.begin(), options.end(), findshortname);
                if (iterator != options.end())
                    iterator->function(argc, argv, i);
            }
        } else if (_SunPrivateCLOptionParsing::isLongOption(arg)) {
            auto findlongname = [arg](const SunCLOption &option) -> bool {
                return (strcmp(arg, ("--" + option.longName).c_str()) == 0);
            };
            auto iterator = std::find_if(options.begin(), options.end(), findlongname);
            if (iterator != options.end())
                iterator->function(argc, argv, i);
        }
    }
    return 0;
}
