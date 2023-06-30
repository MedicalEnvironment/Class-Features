#include <iostream>
#include <string>


class Toy {
public:
    Toy(const std::string& name) : name_(name) {}
    std::string getName() const { return name_; }
    ~Toy() { std::cout << "Toy " << name_ << " was destroyed." << std::endl; }
private:
    std::string name_;
};

class shared_ptr_toy {
public:
    shared_ptr_toy() : ptr_(nullptr), ref_count_(nullptr) {}

    explicit shared_ptr_toy(Toy* toy) {
        ptr_ = toy;
        ref_count_ = new size_t(1);
    }

    shared_ptr_toy(const shared_ptr_toy& other) {
        ptr_ = other.ptr_;
        ref_count_ = other.ref_count_;
        (*ref_count_)++;
    }

    shared_ptr_toy& operator=(const shared_ptr_toy& other) {
        if (this != &other) {
            if (ptr_ && --(*ref_count_) == 0) {
                delete ptr_;
                delete ref_count_;
            }
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            (*ref_count_)++;
        }
        return *this;
    }

    ~shared_ptr_toy() {
        if (ptr_ && --(*ref_count_) == 0) {
            delete ptr_;
            delete ref_count_;
        }
    }

    Toy* operator->() const { return ptr_; }
    Toy& operator*() const { return *ptr_; }

private:
    Toy* ptr_;
    size_t* ref_count_;
};

template<typename... Args>
shared_ptr_toy make_shared_toy(Args&&... args) {
    return shared_ptr_toy(new Toy(std::forward<Args>(args)...));
}

int main() {
    shared_ptr_toy toy1 = make_shared_toy("Teddy Bear");
    shared_ptr_toy toy2 = make_shared_toy("Robot");

    shared_ptr_toy toy3 = toy1;
    shared_ptr_toy toy4;
    toy4 = toy2;

    std::cout << toy1->getName() << std::endl;
    std::cout << toy2->getName() << std::endl;
    std::cout << toy3->getName() << std::endl;
    std::cout << toy4->getName() << std::endl;


    return 0;
}
