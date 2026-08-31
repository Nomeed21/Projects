#include <iostream>
#include <vector>
using namespace std;

class Journal {
public:
    void addEntry(const string& entry) {
        entries.push_back(entry);
    }

    void displayEntries() const {
        cout << "Journal Entries:" << endl;
        for (const auto& entry : entries) {
            cout << "- " << entry << endl;
        }
    }

private:
    vector<string> entries;
};

int main() {
    Journal journal;
    journal.addEntry("Today I learned about C++ classes.");
    journal.addEntry("It was a productive day.");
    journal.displayEntries();
    return 0;
}