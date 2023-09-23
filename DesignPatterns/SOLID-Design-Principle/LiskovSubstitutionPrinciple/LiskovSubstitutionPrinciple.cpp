//
// Created by Amit Kumar on 23/09/23.
//
//
//  Created by Amit Kumar on 23/09/23
//

#include "iostream"
#include "vector"

using namespace std;

namespace BreakTheHierarchy {
    class Bird {
    public:
        virtual void makeSound() {

        }
    };

    class FlyingBird : public Bird {
    public:
        virtual void fly() {
            cout << "bird is flying" << endl;
        }
    };

    class NonFlyingBird : public Bird {
    public:
        virtual void walk() {
            cout << "bird is walking" << endl;
        }
    };

    class Eagle : public FlyingBird {
    public:
        void makeSound() override {
            cout << "eagle sound" << endl;
        }

        void fly() override {
            FlyingBird::fly();
        }
    };

    class Penguin : public NonFlyingBird {
    public:
        void makeSound() override {
            cout << "penguin sound" << endl;
        }

        void walk() override {
            cout << "penguin is walking" << endl;
        }
    };
};

class Customer {
public:
    int discount{};

    virtual void setDiscount() {
        this -> discount = 20;
    }
};

class LoyalCustomer: public Customer {
public:

    void setDiscount() override {
        this->discount = 20;
        setExtraDiscount();
    }
    void setExtraDiscount(){
        this -> discount += 20;
    }
};
int main() {
    vector<Customer*> customers {new Customer(), new Customer(), new LoyalCustomer()};

    for (auto & customer: customers) {
        customer -> setDiscount();
        // checking whether it's loyal customer or not ?
        cout << "discount applied: " << customer->discount << endl;
    }
    return 0;
}