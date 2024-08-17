#include <iostream>
#include <stdexcept>
#include <ctime> // for clock()

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
    void insert(size_t index, int value);
    void remove(size_t index);
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
        throw std::out_of_range("Index out of range");
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
        size_t new_size = size == 0 ? 1 : size * 2;
        resize(new_size);
    }
    data[count++] = value;
}

// insert() function
void Vector::insert(size_t index, int value) {
    if (index > count) {
        throw std::out_of_range("Index out of range");
    }
    if (count == size) {
        resize(size == 0 ? 1 : size * 2);
    }
    for (size_t i = count; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    ++count;
}

// remove() function
void Vector::remove(size_t index) {
    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = index; i < count - 1; ++i) {
        data[i] = data[i + 1];
    }
    --count;
}

int main() {
    Vector vec;

    // Create a vector with some elements
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    // Insert at index 5
    vec.insert(5, 99);
    
    // Remove at index 7
    vec.remove(7);

    // Display the vector contents
    std::cout << "Vector contents after insert and remove operations:\n";
    for (size_t i = 0; i < vec.get_count(); ++i) {
        std::cout << "vec[" << i << "] = " << vec[i] << std::endl;
    }

    // Measure performance of insert and remove operations
    const int num_operations = 1000;
    Vector large_vec;

    // Allocate large memory for testing
    for (int i = 0; i < 100; ++i) {
        large_vec.push_back(i);
    }

    std::clock_t start, end;

    // Measuring insert operations
    start = std::clock();
    for (int i = 0; i < num_operations; ++i) {
        large_vec.insert(50, i);
    }
    end = std::clock();
    std::cout << "Time for " << num_operations << " insert operations: "
              << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

    // Measuring remove operations
    start = std::clock();
    for (int i = 0; i < num_operations; ++i) {
        large_vec.remove(50);
    }
    end = std::clock();
    std::cout << "Time for " << num_operations << " remove operations: "
              << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

    return 0;
}
