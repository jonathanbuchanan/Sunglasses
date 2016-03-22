// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunCLOptionParsing.h"

SunCLOption::SunCLOption() {

}

SunCLOption::SunCLOption(std::string _shortName, std::string _longName, std::string _description, std::function<void()> _function) : shortName(_shortName), longName(_longName), description(_description), function(_function) {
    SunCLOption();
}




int parseOptions(int argc, char **argv, std::vector<SunCLOption> options) {
    return 0;
}
