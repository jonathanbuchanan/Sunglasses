// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Input/SunCLOptionParsing.h>

namespace sunglasses {

SunCLSwitchOption::SunCLSwitchOption(std::string shortOption, std::string longOption, std::string description, bool defaultValue, bool *_value) : arg(shortOption, longOption, description, defaultValue), value(_value) { }

void SunCLSwitchOption::add(TCLAP::CmdLine &commandLine) {
    commandLine.add(arg);
}

void SunCLSwitchOption::process() {
    (*value) = arg.getValue();
}



void parseOptions(const std::vector<SunCLOption *> &options, std::string help, std::string version, int argc, char **argv) {
    try {
        TCLAP::CmdLine commandLine(help, ' ', version);

        //TCLAP::ValueArg<std::string> nameArg("n","name","Name to print",true,"homer","string");
        for (size_t i = 0; i < options.size(); ++i)
            options[i]->add(commandLine);

        //commandline.add(nameArg);

        commandLine.parse(argc, argv);

        for (size_t i = 0; i < options.size(); ++i)
            options[i]->process();
    } catch (TCLAP::ArgException &e) { }
}

} // namespace
