//
// Created by Amit Kumar on 09/09/23.
//
#include "string"
#include "vector"
#include "iostream"

enum class Color {
    red, green, blue
};

enum class Size {
    small, medium, large
};

class Product {
public:
    std::string name;
    Color color;
    Size size;
};

class ProductFilter {
public:
    static std::vector<Product *> by_color(const std::vector<Product *> &items, Color color) {
        std::vector<Product *> result;
        for (auto &itr: items) {
            if (itr->color == color) {
                result.emplace_back(itr);
            }
        }
        return result;
    }

    // to implement size we have copy/paste the code we already tested.
    static std::vector<Product *> by_size(const std::vector<Product *> &items, Size size) {
        std::vector<Product *> result;
        for (auto &itr: items) {
            if (itr->size == size) {
                result.emplace_back(itr);
            }
        }
        return result;
    }

    // now if we need to filter the product by both color and size then again need to copy/paste the code
    static std::vector<Product *> by_size_and_color(const std::vector<Product *> &items, Size size, Color color) {
        std::vector<Product *> result;
        for (auto &itr: items) {
            if (itr->size == size and itr->color == color) {
                result.emplace_back(itr);
            }
        }
        return result;
    }
};

/*
 *  Open Closed Principal states that system should be open for extension and closed for modification, but in the above approach we were modifying the existing
 *  code.
 *
 *  Let's implement a better filter with enterprise pattern related to data.
 */

template<typename T>
class AndSpecification;

template<typename T>
struct Specification {
public:
    virtual bool is_satisfied(T *item) = 0;

    AndSpecification<T> operator&&(Specification<T> &&other) {
        return AndSpecification<T>(*this, other);
    }
};

template<typename T>
class Filter {
public:
    virtual std::vector<Product *> filter(std::vector<T *> items, Specification<T> &specification) = 0;
};


class BetterFilter : Filter<Product> {
public:
    std::vector<Product *> filter(std::vector<Product *> items, Specification<Product> &specification) override {
        std::vector<Product *> result;
        for (auto &itr: items) {
            if (specification.is_satisfied(itr)) {
                result.emplace_back(itr);
            }
        }
        return result;
    }
};

struct ColorSpecification : Specification<Product> {
    Color color;
public:
    explicit ColorSpecification(Color color) : color(color) {}

    bool is_satisfied(Product *item) override {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product> {
    Size size;
public:
    explicit SizeSpecification(Size size) : size(size) {}

    bool is_satisfied(Product *item) override {
        return item->size == size;
    }
};

// this will generate a specification for separating item with color as well as size
template<typename T>
struct AndSpecification : Specification<T> {
public:
    Specification<T> &first;
    Specification<T> &second;

    AndSpecification(Specification<T> &first, Specification<T> &second) : first(first), second(second) {}

private:
    bool is_satisfied(T *item) override {
        return first.is_satisfied(item) and second.is_satisfied(item);
    }
};

int main() {
    Product apple{"apple", Color::green, Size::small};
    Product tree{"tree", Color::green, Size::large};
    Product house{"house", Color::blue, Size::large};

    std::vector<Product *> items{&apple, &tree, &house};

    for (auto &itr: ProductFilter::by_color(items, Color::green)) {
        std::cout << itr->name << " is green" << std::endl;
    }

    // re-writing again in with better filters

    BetterFilter bf;
    ColorSpecification green(Color::green);

    for (auto &itr: bf.filter(items, green)) {
        std::cout << itr->name << " is green [BetterFilter]" << std::endl;
    }

    SizeSpecification size(Size::large);
    AndSpecification<Product> green_and_large(green, size);

    auto spec = ColorSpecification(Color::green) && SizeSpecification(Size::large);

    for (auto &itr: bf.filter(items, green_and_large)) {
        std::cout << itr->name << " is green and large [BetterFilter (AndSpecification)]" << std::endl;
    }

    for (auto &itr: bf.filter(items, spec)) {
        std::cout << itr->name << " is green and large [BetterFilter with custom Operator]" << std::endl;
    }

    return 0;
}