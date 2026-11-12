// Rule.h
#pragma once
#include <string>

// The kinds of red flag CipherTrace understands
enum class Category { URGENCY, MONEY, CREDENTIAL, IMPERSONATION, LINK, PATTERN };

// Category -> text (for printing)
inline std::string categoryName(Category c) {
    switch (c) {
        case Category::URGENCY:       return "URGENCY";
        case Category::MONEY:         return "MONEY";
        case Category::CREDENTIAL:    return "CREDENTIAL";
        case Category::IMPERSONATION: return "IMPERSONATION";
        case Category::LINK:          return "LINK";
        default:                      return "PATTERN";
    }
}

// Text -> category (for reading rules.txt)
inline Category categoryFromString(const std::string& s) {
    if (s == "URGENCY")       return Category::URGENCY;
    if (s == "MONEY")         return Category::MONEY;
    if (s == "CREDENTIAL")    return Category::CREDENTIAL;
    if (s == "IMPERSONATION") return Category::IMPERSONATION;
    if (s == "LINK")          return Category::LINK;
    return Category::PATTERN;
}

// One entry in the scam dictionary
struct Rule {
    std::string keyword;
    Category category;
    int weight;
};

// One clue found in a message (used from Phase 4 onward)
struct Evidence {
    std::string found;
    Category category;
    int weight;
    std::string reason;
};