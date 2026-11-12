// main.cpp
#include <iostream>
#include <string>
#include "RuleBook.h"
using namespace std;

int main() {
    RuleBook book;

    if (!book.loadFromFile("rules.txt")) {
        cout << "Could not open rules.txt. Is it in the folder you run .\\main from?" << endl;
        return 1;
    }

    cout << "Loaded " << book.size() << " rules" << endl;
    book.printAll();

    // Is the list really sorted A -> Z?
    bool sorted = true;
    for (int i = 1; i < book.size(); i++)
        if (book.getRule(i - 1).keyword > book.getRule(i).keyword)
            sorted = false;
    cout << "\nSorted correctly? " << sorted << endl;     // expect 1

    // Search tests
    string tests[] = {"urgent", "prize", "otp", "bank", "hello", "zebra"};
    cout << "\n--- Search results ---" << endl;
    for (const string& word : tests) {
        int b = book.binarySearch(word);
        int bComp = book.getLastComparisons();
        int l = book.linearSearch(word);
        int lComp = book.getLastComparisons();

        cout << word << ": binary index " << b << " (" << bComp << " comparisons), "
             << "linear index " << l << " (" << lComp << " comparisons)" << endl;
    }

    return 0;
}