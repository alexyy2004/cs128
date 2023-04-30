#include "functions.hpp"
#include <iostream>
#include <cctype>
// Your function definitions should go in this source file.
std::string HawaiianWord(std::string str) {
    std::string lower;
    std::string result;
    for (unsigned int i = 0; i < str.size(); ++i) {lower += (char)tolower(str.at(i));}
    for (unsigned int i = 0; i < lower.size(); ++i) {char current = lower.at(i);
        char next = ' ';
        if (i < lower.size() - 1) {next = lower.at(i + 1);}
        char previous = ' ';
        if (i > 0) {previous = lower.at(i - 1);}
        if (current == 'w') {
            if (previous == 'i' || previous == 'e') {result += "v";
            } else {result += "w";} 
        } else if (current == 'a') {
            if (next == 'i' || next == 'e') {result += "eye-";i++;
            } else if (next == 'o' || next == 'u') {result += "ow-";i++;
            } else {result += "ah-";}
        } else if (current == 'e') {if (next == 'i') {result += "ay-";i++;
            } else if (next == 'u') {result += "eh-oo-";i++;
            } else {result += "eh-";}
        } else if (current == 'i') {
            if (next == 'u') {result += "ew-";i++;
            } else {result += "ee-"; }
        } else if (current == 'o') {
            if (next == 'i') {result += "oy-";i++;
            } else if (next == 'u') {result += "ow-";i++;
            } else {result += "oh-";}
        } else if (current == 'u') {
            if (next == 'i') {result += "ooey-";i++;
            } else {result += "oo-";}
        } else if (current == 'p' || current == 'h' || current == 'k' || current == 'l' || current == 'm' || current == 'n' || current == ' ' || current == '\''){result += current;
        } else {return str + " contains a character not a part of the Hawaiian language.";}
        if (result.at(result.size() - 1) == '-' && (next == ' ' || next == '\'')) {result = result.substr(0, result.size() - 1);}
    }
    if (result.at(result.size() - 1) == '-') {result = result.substr(0, result.size() - 1);}
    return result;
}