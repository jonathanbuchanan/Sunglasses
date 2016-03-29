// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLOGGER_H
#define SUNLOGGER_H

#include <string>
#include <vector>
#include <map>

#include "../Core/SunNode.h"
#include "../Core/SunService.h"

const std::string BASH_COLOR_PREFIX             = "\033[";
const std::string BASH_COLOR_SEPARATOR          =     ";";
const std::string BASH_COLOR_SUFFIX             =     "m";

const std::string BASH_COLOR_RESET              =     "0";
const std::string BASH_COLOR_BRIGHT             =     "1";
const std::string BASH_COLOR_DIM                =     "2";
const std::string BASH_COLOR_UNDERSCORE         =     "4";
const std::string BASH_COLOR_BLINK              =     "5";
const std::string BASH_COLOR_REVERSE            =     "7";
const std::string BASH_COLOR_HIDDEN             =     "8";

const std::string BASH_COLOR_FOREGROUND_BLACK   =    "30";
const std::string BASH_COLOR_FOREGROUND_RED     =    "31";
const std::string BASH_COLOR_FOREGROUND_GREEN   =    "32";
const std::string BASH_COLOR_FOREGROUND_YELLOW  =    "33";
const std::string BASH_COLOR_FOREGROUND_BLUE    =    "34";
const std::string BASH_COLOR_FOREGROUND_MAGENTA =    "35";
const std::string BASH_COLOR_FOREGROUND_CYAN    =    "36";
const std::string BASH_COLOR_FOREGROUND_WHITE   =    "37";

const std::string BASH_COLOR_BACKGROUND_BLACK   =    "40";
const std::string BASH_COLOR_BACKGROUND_RED     =    "41";
const std::string BASH_COLOR_BACKGROUND_GREEN   =    "42";
const std::string BASH_COLOR_BACKGROUND_YELLOW  =    "43";
const std::string BASH_COLOR_BACKGROUND_BLUE    =    "44";
const std::string BASH_COLOR_BACKGROUND_MAGENTA =    "45";
const std::string BASH_COLOR_BACKGROUND_CYAN    =    "46";
const std::string BASH_COLOR_BACKGROUND_WHITE   =    "47";

enum BashColor {
    BashColorReset,
    BashColorBright,
    BashColorDim,
    BashColorUnderscore,
    BashColorBlink,
    BashColorReverse,
    BashColorHidden,

    BashColorForegroundBlack,
    BashColorForegroundRed,
    BashColorForegroundGreen,
    BashColorForegroundYellow,
    BashColorForegroundBlue,
    BashColorForegroundMagenta,
    BashColorForegroundCyan,
    BashColorForegroundWhite,

    BashColorBackgroundBlack,
    BashColorBackgroundRed,
    BashColorBackgroundGreen,
    BashColorBackgroundYellow,
    BashColorBackgroundBlue,
    BashColorBackgroundMagenta,
    BashColorBackgroundCyan,
    BashColorBackgroundWhite
};

extern std::map<BashColor, std::string> ColorMap;

extern std::string getBashColorSetter(std::vector<BashColor> colors);
extern std::string getBashColorSetter(BashColor color);

class SunLogger : public SunService {
public:
    SunLogger();
    ~SunLogger();

    void update();

    void reset();
    void bright();
    void dim();
    void underscore();
    void blink();
    void reverse();
    void hidden();

    void logBlack(std::string message);
    void logRed(std::string message);
    void logGreen(std::string message);
    void logYellow(std::string message);
    void logBlue(std::string message);
    void logMagenta(std::string message);
    void logCyan(std::string message);
    void logWhite(std::string message);

    void logError(std::string message);
    void logSuccess(std::string message);

    void log(std::string message);
};

#endif
