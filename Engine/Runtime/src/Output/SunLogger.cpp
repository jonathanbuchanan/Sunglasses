// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunLogger.h"
#include <iostream>

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

string getBashColorSetter(std::vector<BashColor> colors) {
    string colorString = BASH_COLOR_PREFIX;
    
    for (int i = 0; i < colors.size(); i++) {
        if (i > 0)
            colorString += BASH_COLOR_SEPARATOR;
        colorString += ColorMap[colors[i]];
    }
    
    colorString += BASH_COLOR_SUFFIX;
    
    return colorString;
}

string getBashColorSetter(BashColor color) {
    string colorString = BASH_COLOR_PREFIX;
    
    colorString += ColorMap[color];
    
    colorString += BASH_COLOR_SUFFIX;
    
    return colorString;
}

SunLogger::SunLogger() {
    defaultColors = {BashColorForegroundBlue, BashColorBright};
}

void SunLogger::reset() {
    std::cout << getBashColorSetter(BashColorReset);
}

void SunLogger::bright() {
    std::cout << getBashColorSetter(BashColorBright);
}

void SunLogger::dim() {
    std::cout << getBashColorSetter(BashColorDim);
}

void SunLogger::underscore() {
    std::cout << getBashColorSetter(BashColorUnderscore);
}

void SunLogger::blink() {
    std::cout << getBashColorSetter(BashColorBlink);
}

void SunLogger::reverse() {
    std::cout << getBashColorSetter(BashColorReverse);
}

void SunLogger::hidden() {
    std::cout << getBashColorSetter(BashColorHidden);
}

void SunLogger::logBlack(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundBlack);
    std::cout << message;
}

void SunLogger::logRed(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundRed);
    std::cout << message;
    reset();
}

void SunLogger::logGreen(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundGreen);
    std::cout << message;
    reset();
}

void SunLogger::logYellow(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundYellow);
    std::cout << message;
    reset();
}

void SunLogger::logBlue(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundBlue);
    std::cout << message;
    reset();
}

void SunLogger::logMagenta(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundMagenta);
    std::cout << message;
    reset();
}

void SunLogger::logCyan(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundCyan);
    std::cout << message;
    reset();
}

void SunLogger::logWhite(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundWhite);
    std::cout << message;
    reset();
}

void SunLogger::logError(std::string message) {
    std::cout << getBashColorSetter(std::vector<BashColor>{BashColorForegroundRed, BashColorBright});
    std::cout << "ERROR: ";
    std::cout << message;
    reset();
    std::cout << std::endl;
}

void SunLogger::logSuccess(std::string message) {
    std::cout << getBashColorSetter(std::vector<BashColor>{BashColorForegroundGreen, BashColorBright});
    std::cout << "SUCCESS: ";
    std::cout << message;
    reset();
    std::cout << std::endl;
}

void SunLogger::log(std::string message) {
    std::cout << getBashColorSetter(defaultColors);
    std::cout << message;
    reset();
    std::cout << std::endl;
}