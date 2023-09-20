//
// Created by Amit Kumar on 17/09/23.
//

#include "string"

#include "fstream"

using namespace std;


class Movie {
private:

    string name;
    string releaseMonth;
    int releaseYear;

public:
    Movie(const string &name, const string &releaseMonth, int releaseYear) : name(name), releaseMonth(releaseMonth),
                                                                             releaseYear(releaseYear) {}


    const string &getName() const {
        return name;
    }

    const string &getReleaseMonth() const {
        return releaseMonth;
    }

    int getReleaseYear() const {
        return releaseYear;
    }
};

class StorageManager {
public:
    static void saveInfo(const Movie &movie, const string &filename) {
        fstream ofs(filename);

        ofs << movie.getName() << endl;

        ofs << movie.getReleaseMonth() << endl;

        ofs << movie.getReleaseYear() << endl;

        ofs.close();
    }

};

int main() {

    Movie movie{"firstMovie", "Jan", 2000};

    StorageManager::saveInfo(movie, "newFileName");
    return 0;
}