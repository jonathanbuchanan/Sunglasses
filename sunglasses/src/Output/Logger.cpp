// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Output/Logger.h>
#include <iostream>

namespace sunglasses {

std::map<BashColor, std::string> ColorMap = {
    {BashColorReset,             BASH_COLOR_RESET},
    {BashColorBright,            BASH_COLOR_BRIGHT},
    {BashColorDim,               BASH_COLOR_DIM},
    {BashColorUnderscore,        BASH_COLOR_UNDERSCORE},
    {BashColorBlink,             BASH_COLOR_BLINK},
    {BashColorReverse,           BASH_COLOR_REVERSE},
    {BashColorHidden,            BASH_COLOR_HIDDEN},

    {BashColorForegroundBlack,   BASH_COLOR_FOREGROUND_BLACK},
    {BashColorForegroundRed,     BASH_COLOR_FOREGROUND_RED},
    {BashColorForegroundGreen,   BASH_COLOR_FOREGROUND_GREEN},
    {BashColorForegroundYellow,  BASH_COLOR_FOREGROUND_YELLOW},
    {BashColorForegroundBlue,    BASH_COLOR_FOREGROUND_BLUE},
    {BashColorForegroundMagenta, BASH_COLOR_FOREGROUND_MAGENTA},
    {BashColorForegroundCyan,    BASH_COLOR_FOREGROUND_CYAN},
    {BashColorForegroundWhite,   BASH_COLOR_FOREGROUND_WHITE},

    {BashColorBackgroundBlack,   BASH_COLOR_BACKGROUND_BLACK},
    {BashColorBackgroundRed,     BASH_COLOR_BACKGROUND_RED},
    {BashColorBackgroundGreen,   BASH_COLOR_BACKGROUND_GREEN},
    {BashColorBackgroundYellow,  BASH_COLOR_BACKGROUND_YELLOW},
    {BashColorBackgroundBlue,    BASH_COLOR_BACKGROUND_BLUE},
    {BashColorBackgroundMagenta, BASH_COLOR_BACKGROUND_MAGENTA},
    {BashColorBackgroundCyan,    BASH_COLOR_BACKGROUND_CYAN},
    {BashColorBackgroundWhite,   BASH_COLOR_BACKGROUND_WHITE}
};

std::string getBashColorSetter(std::vector<BashColor> colors) {
    std::string colorString = BASH_COLOR_PREFIX;

    for (size_t i = 0; i < colors.size(); i++) {
        if (i > 0)
            colorString += BASH_COLOR_SEPARATOR;
        colorString += ColorMap[colors[i]];
    }

    colorString += BASH_COLOR_SUFFIX;

    return colorString;
}

std::string getBashColorSetter(BashColor color) {
    std::string colorString = BASH_COLOR_PREFIX;

    colorString += ColorMap[color];

    colorString += BASH_COLOR_SUFFIX;

    return colorString;
}

Logger::Logger() {

}

Logger::~Logger() {

}

void Logger::update() {

}

void Logger::reset() {
    std::cout << getBashColorSetter(BashColorReset);
}

void Logger::bright() {
    std::cout << getBashColorSetter(BashColorBright);
}

void Logger::dim() {
    std::cout << getBashColorSetter(BashColorDim);
}

void Logger::underscore() {
    std::cout << getBashColorSetter(BashColorUnderscore);
}

void Logger::blink() {
    std::cout << getBashColorSetter(BashColorBlink);
}

void Logger::reverse() {
    std::cout << getBashColorSetter(BashColorReverse);
}

void Logger::hidden() {
    std::cout << getBashColorSetter(BashColorHidden);
}

void Logger::logBlack(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundBlack);
    std::cout << message;
}

void Logger::logRed(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundRed);
    std::cout << message;
    reset();
}

void Logger::logGreen(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundGreen);
    std::cout << message;
    reset();
}

void Logger::logYellow(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundYellow);
    std::cout << message;
    reset();
}

void Logger::logBlue(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundBlue);
    std::cout << message;
    reset();
}

void Logger::logMagenta(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundMagenta);
    std::cout << message;
    reset();
}

void Logger::logCyan(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundCyan);
    std::cout << message;
    reset();
}

void Logger::logWhite(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundWhite);
    std::cout << message;
    reset();
}

void Logger::logError(std::string message) {
    std::cout << getBashColorSetter(std::vector<BashColor>{BashColorForegroundRed, BashColorBright});
    std::cout << "ERROR: ";
    std::cout << message;
    reset();
    std::cout << std::endl;
}

void Logger::logSuccess(std::string message) {
    std::cout << getBashColorSetter(std::vector<BashColor>{BashColorForegroundGreen, BashColorBright});
    std::cout << "SUCCESS: ";
    std::cout << message;
    reset();
    std::cout << std::endl;
}

void Logger::log(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundBlue);
    std::cout << getBashColorSetter(BashColorBright);
    std::cout << message;
    reset();
    std::cout << std::endl;
}

} // namespace
