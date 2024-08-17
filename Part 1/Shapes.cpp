#include <iostream>
#include <cmath>  

using namespace std;

class Shape {
public:
  double getVolume() const { return 0.0; }  
};

class Sphere : public Shape {
private:
  double radius; 

public:

  Sphere(double radius) : radius(radius) {}


  double getVolume() { return (4.0 / 3.0) * M_PI * pow(radius, 3); }
};

class Pyramid : public Shape {
private:
  double baseLength;  
  double height;  

public:

  Pyramid(double baseLength, double height) {
    this->baseLength = baseLength;
    this->height = height;
  }


  double getBaseArea() const {
    return baseLength * baseLength;
  }

  double getVolume() { return (1.0 / 3.0) * getBaseArea() * height; }
};

class Cube : public Shape {
private:
  double sideLength;  

public:

  Cube(double sideLength) : sideLength(sideLength) {}


  double getVolume() { return sideLength * sideLength * sideLength; }
};

int main() {
  double radius, baseLength, height, sideLength;

  cout << "Calculating Sphere, Pyramid and Cube Volume " << endl;

  cout << "Enter sphere Radius: " << endl;
  cin >> radius;
  Sphere sphere(radius);
  cout << "Sphere Volume: " << sphere.getVolume() << endl;

  cout << "Enter Pyramid baselength and height: ";
  cin >> baseLength >> height;
  Pyramid pyramid(baseLength, height);
  cout << "pyramid volume is: " << pyramid.getVolume() << endl;

  cout << "Enter Cube sidelength: " << endl;
  cin >> sideLength;
  Cube cube(sideLength);
  cout << "Cube volume is: " << cube.getVolume() << endl;

  return 0;
}
