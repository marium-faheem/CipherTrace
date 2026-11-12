// RuleBook.h
#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Rule.h"

class RuleBook {
private:
    std::vector<Rule> rules;
    int lastComparisons;   // how many comparisons the last search used

public:
    RuleBook() : lastComparisons(0) {}

    // Reads "keyword,CATEGORY,weight" lines, then sorts them
    bool loadFromFile(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open())
            return false;

        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r')
                line.pop_back();                       // Windows line ending
            if (line.empty() || line[0] == '#')
                continue;                              // skip blanks and comments

            size_t c1 = line.find(',');
            size_t c2 = line.find(',', c1 + 1);
            if (c1 == std::string::npos || c2 == std::string::npos)
                continue;                              // malformed line

            try {
                Rule r;
                r.keyword  = line.substr(0, c1);
                r.category = categoryFromString(line.substr(c1 + 1, c2 - c1 - 1));
                r.weight   = std::stoi(line.substr(c2 + 1));
                rules.push_back(r);
            } catch (...) {
                continue;                              // bad weight number
            }
        }
        sortRules();
        return true;
    }

    // Insertion sort: orders rules alphabetically by keyword. O(n^2), done once at load.
    void sortRules() {
        for (int i = 1; i < (int)rules.size(); i++) {
            Rule current = rules[i];          // save it, shifting will overwrite rules[i]
            int j = i - 1;
            // shift every bigger keyword one slot to the right
            while (j >= 0 && rules[j].keyword > current.keyword) {
                rules[j + 1] = rules[j];
                j--;
            }
            rules[j + 1] = current;           // drop current into the gap
        }
    }

    // Binary search on the sorted rules. Returns the index, or -1 if not found.
    // O(log n): each round throws away half of the remaining rules.
    int binarySearch(const std::string& keyword) {
        lastComparisons = 0;
        int low = 0;
        int high = (int)rules.size() - 1;

        while (low <= high) {
            lastComparisons++;
            int mid = (low + high) / 2;

            if (rules[mid].keyword == keyword)
                return mid;                   // found it
            else if (rules[mid].keyword < keyword)
                low = mid + 1;                // target is in the right half
            else
                high = mid - 1;               // target is in the left half
        }
        return -1;                            // not found
    }

    // The slow way, for comparison. O(n).
    int linearSearch(const std::string& keyword) {
        lastComparisons = 0;
        for (int i = 0; i < (int)rules.size(); i++) {
            lastComparisons++;
            if (rules[i].keyword == keyword)
                return i;
        }
        return -1;
    }

    const Rule& getRule(int index) const { return rules[index]; }
    int size() const { return (int)rules.size(); }
    int getLastComparisons() const { return lastComparisons; }

    void printAll() const {
        for (int i = 0; i < (int)rules.size(); i++)
            std::cout << i << ": " << rules[i].keyword << " ["
                      << categoryName(rules[i].category) << ", "
                      << rules[i].weight << "]\n";
    }
};
