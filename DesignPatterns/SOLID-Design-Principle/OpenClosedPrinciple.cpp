//
//  main.cpp
//  OpenClosedPrinciple
//
//  Created by Amit Kumar on 19/09/23.
//


#include "vector"
#include "iostream"

using namespace std;

enum class Colour {
    White, Space_Grey, Black
};

enum BatterySize {
    Large, Medium, Small
};

class Product {
private:
    string name;
    Colour colour;
    BatterySize batterySize;

public:
    Product(const string &name, const Colour &colour, const BatterySize &batterySize) : name(name), colour(colour),
                                                                                        batterySize(batterySize) {}

    const string &getName() const {
        return name;
    }

    const Colour &getColour() const {
        return colour;
    }

    const BatterySize &getBatterySize() const {
        return batterySize;
    }
};

namespace BadCode {
    class Filter {
    public:

        static vector<Product *> by_color(const vector<Product *> &bag, const Colour &colour) {
            vector < Product * > result;

            for (auto &item: bag) {
                if (item->getColour() == colour) {
                    result.push_back(item);
                }
            }

            return result;
        }

        static vector<Product *> by_size(const vector<Product *> &bag, const BatterySize &size) {
            vector < Product * > result;

            for (auto &item: bag) {
                if (item->getBatterySize() == size) {
                    result.push_back(item);
                }
            }

            return result;
        }

        static vector<Product *> by_size_and_colour(const vector<Product *> &bag, const BatterySize &size,
                                                    const Colour &colour) {
            vector < Product * > result;

            for (auto &item: bag) {
                if (item->getBatterySize() == size and item->getColour() == colour) {
                    result.push_back(item);
                }
            }

            return result;
        }
    };
};

template<typename T>
class Specification {
public:
    virtual bool is_satisfied(T *item) const = 0;
};

class ColourSpecification : public Specification<Product> {
    Colour color;
public:
    ColourSpecification(const Colour &colour) : color(colour) {}

    bool is_satisfied(Product *item) const override {
        return item->getColour() == color;
    }
};

class SizeSpecification : public Specification<Product> {
    BatterySize bsize;
public:
    SizeSpecification(const BatterySize &bsize) : bsize(bsize) {}

    bool is_satisfied(Product *item) const override {
        return item->getBatterySize() == bsize;
    }
};

class AndSpecification : public Specification<Product> {
    ColourSpecification color;
    SizeSpecification bsize;
public:
    AndSpecification(const ColourSpecification &color, const SizeSpecification &bsize) :
            color(color), bsize(bsize) {}

    bool is_satisfied(Product *item) const override {
        return color.is_satisfied(item) and bsize.is_satisfied(item);
    }
};

template<typename T>
class Filter {
public:
    virtual vector<T *> filter(const vector<T *> &bags, const Specification<T> &spec) const = 0;
};

class ProductFilter : public Filter<Product> {
public:
    vector<Product *> filter(const vector<Product *> &bag, const Specification<Product> &spec) const override {
        vector < Product * > result;
        for (auto &item: bag) {
            if (spec.is_satisfied(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};

int main() {

    Product phone{"Phone", Colour::White, BatterySize::Medium};
    Product watch{"Watch", Colour::Black, BatterySize::Small};
    Product headphone{"HeadPhone", Colour::Black, BatterySize::Medium};
    Product laptop{"Laptop", Colour::Space_Grey, BatterySize::Large};

    vector < Product * > bag{&phone, &watch, &headphone, &laptop};


    ProductFilter pf;

    ColourSpecification white_color(Colour::White);

    for (auto &item: pf.filter(bag, white_color)) {
        cout << item->getName() << "is white in colour" << endl;
    }

    cout << endl << endl;

    SizeSpecification medium_battery(BatterySize::Medium);

    for (auto &item: pf.filter(bag, medium_battery)) {
        cout << item->getName() << " has medium battery size" << endl;
    }

    cout << endl << endl;

    AndSpecification size_and_colour(white_color, medium_battery);

    for (auto &item: pf.filter(bag, size_and_colour)) {
        cout << item->getName() << " has Medium battery size and white in colour" << endl;
    }

    return 0;
}
