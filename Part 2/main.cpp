#include <iostream>
#include <vector>
#include <cmath>

// Abstract Shape class
class Shape {
public:
    double density;

    Shape(double density) : density(density) {}

    virtual double volume() const = 0;
    virtual double surface() const = 0;

    double mass() const {
        return density * volume();
    }
};

// Sphere class
class Sphere : public Shape {
public:
    double radius;

    Sphere(double radius, double density) : Shape(density), radius(radius) {}

    double volume() const override {
        return (4.0 / 3.0) * M_PI * pow(radius, 3);
    }

    double surface() const override {
        return 4.0 * M_PI * pow(radius, 2);
    }
};

// Pyramid class
class Pyramid : public Shape {
public:
    double baseLength, height;

    Pyramid(double baseLength, double height, double density)
        : Shape(density), baseLength(baseLength), height(height) {}

    double getBaseArea() const {
        return pow(baseLength, 2);
    }

    double volume() const override {
        return (1.0 / 3.0) * getBaseArea() * height;
    }

    double surface() const override {
        // Surface area calculation is simplified; depends on the slant height and base.
        double slantHeight = sqrt(pow(baseLength / 2, 2) + pow(height, 2));
        return baseLength * baseLength + 2 * baseLength * slantHeight;
    }
};

// Cube class
class Cube : public Shape {
public:
    double sideLength;

    Cube(double sideLength, double density) : Shape(density), sideLength(sideLength) {}

    double volume() const override {
        return pow(sideLength, 3);
    }

    double surface() const override {
        return 6 * pow(sideLength, 2);
    }
};

// Cylinder class
class Cylinder : public Shape {
public:
    double radius, height;

    Cylinder(double radius, double height, double density) 
        : Shape(density), radius(radius), height(height) {}

    double volume() const override {
        return M_PI * pow(radius, 2) * height;
    }

    double surface() const override {
        return 2 * M_PI * radius * (radius + height);
    }
};

// Device class
class Device {
public:
    std::vector<Shape*> shapes;
    std::vector<Device*> devices;

    Device() {}

    void addShape(Shape* shape) {
        shapes.push_back(shape);
    }

    void addDevice(Device* device) {
        devices.push_back(device);
    }

    double evalVolume() const {
        double totalVolume = 0.0;
        for (const auto& shape : shapes) {
            totalVolume += shape->volume();
        }
        for (const auto& device : devices) {
            totalVolume += device->evalVolume();
        }
        return totalVolume;
    }

    double evalSurface() const {
        double totalSurface = 0.0;
        for (const auto& shape : shapes) {
            totalSurface += shape->surface();
        }
        for (const auto& device : devices) {
            totalSurface += device->evalSurface();
        }
        return totalSurface;
    }

    double evalMass() const {
        double totalMass = 0.0;
        for (const auto& shape : shapes) {
            totalMass += shape->mass();
        }
        for (const auto& device : devices) {
            totalMass += device->evalMass();
        }
        return totalMass;
    }
};

int main() {
    // Create simple shapes
    Sphere sphere(3.0, 2.5);       // radius = 3.0, density = 2.5
    Cube cube(2.0, 4.0);           // sideLength = 2.0, density = 4.0
    Cylinder cylinder(1.5, 5.0, 3.0); // radius = 1.5, height = 5.0, density = 3.0
    Pyramid pyramid(2.0, 4.0, 5.0); // baseLength = 2.0, height = 4.0, density = 5.0

    // Create the main device and add simple shapes
    Device mainDevice;
    mainDevice.addShape(&sphere);
    mainDevice.addShape(&cube);
    mainDevice.addShape(&cylinder);
    mainDevice.addShape(&pyramid);

    // Create a sub-device with some shapes
    Device subDevice;
    subDevice.addShape(new Cube(1.0, 2.5));   // sideLength = 1.0, density = 2.5
    subDevice.addShape(new Sphere(2.0, 3.0)); // radius = 2.0, density = 3.0

    // Add sub-device to the main device
    mainDevice.addDevice(&subDevice);

    // Another nested device within the sub-device
    Device nestedDevice;
    nestedDevice.addShape(new Cylinder(0.5, 2.0, 7.0)); // radius = 0.5, height = 2.0, density = 7.0
    subDevice.addDevice(&nestedDevice);

    // Calculate and display the results for the main device
    std::cout << "Main device total volume: " << mainDevice.evalVolume() << std::endl;
    std::cout << "Main device total surface area: " << mainDevice.evalSurface() << std::endl;
    std::cout << "Main device total mass: " << mainDevice.evalMass() << std::endl;

    return 0;
}
