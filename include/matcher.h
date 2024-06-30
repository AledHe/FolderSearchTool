#ifndef MATCHER_H
#define MATCHER_H

#include <string>
#include <string_view>

class Matcher {
public:
    // Checks if the pattern is a substring of text
    static bool match(std::string_view text, std::string_view pattern);
};

#endif // MATCHER_H