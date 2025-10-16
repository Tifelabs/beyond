#include <iostream>
#include <utility> 

template <typename T>
class UniquePtr {
private:
T* ptr;

public:
// Constructor
explicit UniquePtr(T* p = nullptr) : ptr(p) {}

// Destructor 
~UniquePtr() {
    delete ptr;
}

/* Delete copy constructor and copy assignment */
UniquePtr(const UniquePtr&) = delete;
UniquePtr& operator=(const UniquePtr&) = delete;

// Move constructor
UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;
}

// Move assignment operator
UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
        delete ptr; // Clean up existing resource
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    return *this;
}

// Dereference operators
T& operator*() const {
    return *ptr;
}

T* operator->() const {
    return ptr;
}

// Get raw pointer
T* get() const {
    return ptr;
}

// Release ownership and return raw pointer
T* release() {
    T* temp = ptr;
    ptr = nullptr;
    return temp;
}

// Reset with a new pointer
void reset(T* p = nullptr) {
    delete ptr;
    ptr = p;
}

// Check if pointer is not null
explicit operator bool() const {
    return ptr != nullptr;
}

};

// Helper function to create UniquePtr (like std::make_unique)
template <typename T, typename Args>
UniquePtr<T> makeUnique(Args&& args) {
return UniquePtr<T>(new T(std::forward<Args>(args)));
}

// Example usage
class MyClass {
public:
int value;

MyClass(int v) : value(v) {
    std::cout << "MyClass constructed with value: " << value << "\n";
}

~MyClass() {
    std::cout << "MyClass with value " << value << " destroyed\n";
}

void display() {
    std::cout << "Value: " << value << "\n";
}

};

int main() {
std::cout << "=== Creating UniquePtr ===\n";
UniquePtr<MyClass> ptr1 = makeUnique<MyClass>(42);
ptr1->display();


std::cout << "\n=== Move semantics ===\n";
UniquePtr<MyClass> ptr2 = std::move(ptr1);

if (!ptr1) {
    std::cout << "ptr1 is now empty\n";
}

if (ptr2) {
    std::cout << "ptr2 owns the object\n";
    ptr2->display();
}

std::cout << "\n=== Reset ===\n";
ptr2.reset(new MyClass(100));

std::cout << "\n=== Exiting (automatic cleanup) ===\n";
return 0;
}