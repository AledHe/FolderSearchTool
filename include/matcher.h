#ifndef MATCHER_H
#define MATCHER_H

#include <string>
#include <vector>

class Matcher {
public:
    // Checks if the pattern is a substring of text
    static bool match(const std::string& text, const std::string& pattern);
};

#endif // MATCHER_H