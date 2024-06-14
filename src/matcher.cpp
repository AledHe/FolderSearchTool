#include "matcher.h"

bool Matcher::match(const std::string& text, const std::string& pattern) {
    return text.find(pattern) != std::string::npos;
}