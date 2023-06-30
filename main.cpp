#include <iostream>
#include <memory>

class Toy {
public:
    Toy(const std::string& name) {
        name_ = name;
    }
    std::string getName() {
        return name_;
    }
    ~Toy() {
        std::cout << "Toy " << name_ << " was dropped." << std::endl;
    }

private:
    std::string name_;
};

class Dog {
public:
    void getToy(std::shared_ptr<Toy> toy) {
        if (toy == nullptr) {
            std::cout << "Invalid toy." << std::endl;
            return;
        }

        if (toy.get() == toy_.get()) {
            std::cout << "I already have this toy." << std::endl;
        } else if (toy_.use_count() > 1) {
            std::cout << "Another dog is playing with this toy." << std::endl;
        } else {
            toy_ = toy;
            std::cout << "I picked up the toy: " << toy_->getName() << std::endl;
        }
    }


    void dropToy() {
        if (toy_ == nullptr) {
            std::cout << "Nothing to drop." << std::endl;
            return;
        }

        std::cout << "I dropped the toy: " << toy_->getName() << std::endl;
        toy_.reset();
    }

private:
    std::shared_ptr<Toy> toy_;
};

int main() {
    // Create some toys
    std::shared_ptr<Toy> toy1 = std::make_shared<Toy>("Ball");
    std::shared_ptr<Toy> toy2 = std::make_shared<Toy>("Bone");

    // Create dogs
    Dog dog1;
    Dog dog2;

    // Dog 1 tries to get the same toy multiple times
    dog1.getToy(toy1);
    dog1.getToy(toy1);
    dog1.getToy(toy1);

    // Dog 2 tries to get the same toy
    dog2.getToy(toy1);

    // Dog 1 drops the toy
    dog1.dropToy();

    // Dog 2 gets the toy after it was dropped
    dog2.getToy(toy1);

    return 0;
}
