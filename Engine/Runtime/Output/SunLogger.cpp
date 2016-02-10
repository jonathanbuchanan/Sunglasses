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

void SunLogger::logError(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundRed);
    std::cout << message;
    std::cout << getBashColorSetter(BashColorReset);
    std::cout << std::endl;
}

void SunLogger::logSuccess(std::string message) {
    std::cout << getBashColorSetter(BashColorForegroundGreen);
    std::cout << message;
    std::cout << getBashColorSetter(BashColorReset);
    std::cout << std::endl;
}