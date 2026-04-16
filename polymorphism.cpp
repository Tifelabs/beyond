#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual double area() const { return 0.0; }
    virtual std::string getName() const { return "Shape"; }
};

class Circle : public Shape {
private:
    double radius;
public:
    explicit Circle(double r) : radius(r) {}
    void draw() const override {
        std::cout << "Drawing Circle (radius = " << radius << ")\n";
    }
    double area() const override {
        return 3.14159 * radius * radius;
    }
    std::string getName() const override {
        return "Circle";
    }
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    void draw() const override {
        std::cout << "Drawing Rectangle (" << width << " x " << height << ")\n";
    }
    double area() const override {
        return width * height;
    }
    std::string getName() const override {
        return "Rectangle";
    }
};

class Triangle : public Shape {
private:
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}
    void draw() const override {
        std::cout << "Drawing Triangle (base=" << base << ", height=" << height << ")\n";
    }
    double area() const override {
        return 0.5 * base * height;
    }
    std::string getName() const override {
        return "Triangle";
    }
};

void renderShape(const Shape& shape) {
    std::cout << "=== " << shape.getName() << " ===\n";
    shape.draw();
    std::cout << "Area: " << shape.area() << "\n\n";
}

void renderAllShapes(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        renderShape(*shape);
    }
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Triangle>(10.0, 8.0));
    shapes.push_back(std::make_unique<Circle>(3.5));

    renderAllShapes(shapes);

    std::unique_ptr<Shape> s1 = std::make_unique<Circle>(7.2);
    std::unique_ptr<Shape> s2 = std::make_unique<Rectangle>(5.0, 10.0);

    renderShape(*s1);
    renderShape(*s2);

    return 0;
}