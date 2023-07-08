//
// Created by Amit Kumar on 08/07/23.
//

/*
 *  Single Responsibility Principal states that A class should a single reason to change.
 *  OR a class should a primary responsibility and should not take other responsibilities.
 *
 *  In single term we can say that If a class consists of two functionality and these are dependent
 *  in such a way change in functionality A could break the functionality B, that we are breaking
 *  SRP and we should separate out the classes;
 */

#include <utility>
#include "fstream"

#include "string"

using namespace std;


/*
 * This Journal class only have capability to add entries to the Journal
 */
class Journal {
    string title;
    vector<string> entries;
public:
    explicit Journal(string title) : title(std::move(title)) {}

    void add_entry(const string &entry) {
        static int counter = 1;
        entries.emplace_back(to_string(counter++) + ": " + entry);
    }

    const vector<string> &getEntries() const {
        return entries;
    }
};

/*
 * Now if we want to save the entries into a file that is another functionality;
 * Simply we can add a method into Journal class itself and that would do the job but in future
 * if this functionality needs an update and end-up changing the constructor maybe add a few more parameters
 * then this would be a issue for Journal class because if we want to save it in different manner then Journal
 * class should not be worried about it. This task needs to be delegated.
 *
 * So what we are going to do is called Separation Of Concerns :-)
 */

class PersistenceManager {
public:
    static void save(const Journal &j, const string &filename) {
        ofstream output(filename);
        for (auto &itr: j.getEntries()) {
            output << itr << '\n';
        }
        output.flush();
    }
};

int main() {
    Journal journal("TestJournal");
    journal.add_entry("this is my first entry");
    journal.add_entry("this is my second entry");

    PersistenceManager::save(journal, "SRP_Journal_temp");
    return 0;
}