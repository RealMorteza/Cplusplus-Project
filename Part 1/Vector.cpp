#include <iostream>
#include <stdexcept>

class Vector {
private:
    int* data;
    size_t size;
    size_t count;


public:
    Vector();
    ~Vector();
    
    void resize(size_t new_size);
    
    int& operator[](size_t index);
    size_t get_count() const;
    void push_back(int value);
};

// Constructor
Vector::Vector() : data(nullptr), size(0), count(0) {}

// Destructor
Vector::~Vector() {
    delete[] data;
}

// Overloaded operator[]
int& Vector::operator[](size_t index) {
    if (index >= count) {
        std::cout << "index out of range";
    }
    return data[index];
}

// get_count() function
size_t Vector::get_count() const {
    return count;
}

// resize() function
void Vector::resize(size_t new_size) {
    if (new_size > size) {
        int* new_data = new int[new_size];
        for (size_t i = 0; i < count; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        size = new_size;
    }
    count = new_size;
}

// push_back() function
void Vector::push_back(int value) {
    if (count == size) {
        size_t new_size = size++;
        resize(new_size);
    }
    data[count++] = value;
}

int main() {
    Vector vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::cout << "Vector count: " << vec.get_count() << std::endl;

    for (size_t i = 0; i < vec.get_count(); ++i) {
        std::cout << "vec[" << i << "] = " << vec[i] << std::endl;
    }

    vec.resize(5);
    std::cout << "Vector count after resize: " << vec.get_count() << std::endl;

    for (size_t i = 0; i < vec.get_count(); ++i) {
        std::cout << "vec[" << i << "] = " << vec[i] << std::endl;
    }

    return 0;
}
