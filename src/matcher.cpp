#include "matcher.h"
#include <algorithm>

bool Matcher::match(std::string_view text, std::string_view pattern) {
    return std::search(text.begin(), text.end(), pattern.begin(), pattern.end()) != text.end();
}