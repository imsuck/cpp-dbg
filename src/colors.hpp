#pragma once

#include <ostream>
#include <string>

namespace dbg {

    // ANSI color codes for output formatting
    enum class Color {
        Reset = 0,
        Black = 30,
        Red = 31,
        Green = 32,
        Yellow = 33,
        Blue = 34,
        Magenta = 35,
        Cyan = 36,
        White = 37,
        BrightBlack = 90,
        BrightRed = 91,
        BrightGreen = 92,
        BrightYellow = 93,
        BrightBlue = 94,
        BrightMagenta = 95,
        BrightCyan = 96,
        BrightWhite = 97
    };

    // Convert color to ANSI escape sequence string
    inline std::string to_string(Color color) {
        if (color == Color::Reset) {
            return "\033[0m";
        }
        return "\033[" + std::to_string(static_cast<int>(color)) + "m";
    }

    // Stream operator for colors
    inline std::ostream &operator<<(std::ostream &os, Color color) {
        return os << to_string(color);
    }

} // namespace dbg
