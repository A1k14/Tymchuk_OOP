#include <iostream>
#include <string>
#include <limits>

class Point {
private:
    int x, y;
public:
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point& other) : x(other.x), y(other.y) {}
    Point(Point&& other)  : x(other.x), y(other.y) { other.x = 0; other.y = 0; }
    virtual ~Point() {}

    Point& operator=(const Point& other) {
        if (this != &other) { x = other.x; y = other.y; }
        return *this;
    }

    Point& operator=(Point&& other)  {
        if (this != &other) { x = other.x; y = other.y; other.x = 0; other.y = 0; }
        return *this;
    }

    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int val) { x = val; }
    void setY(int val) { y = val; }
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << "(" << p.getX() << ", " << p.getY() << ")";
}

std::istream& operator>>(std::istream& is, Point& p) {
    int x, y;
    std::cout << "Enter X: ";
    while (!(is >> x)) {
        is.clear();
        std::cout << "Invalid X. Try again: ";
    }
    std::cout << "Enter Y: ";
    while (!(is >> y)) {
        is.clear();
        std::cout << "Invalid Y. Try again: ";
    }
    p.setX(x); p.setY(y);
    return is;
}

class ColorPoint : public Point {
private:
    std::string color;
public:
    ColorPoint() : Point(), color("black") {}
    ColorPoint(int x, int y, std::string c) : Point(x, y), color(std::move(c)) {}
    ColorPoint(const ColorPoint& other) : Point(other), color(other.color) {}
    ColorPoint(ColorPoint&& other) noexcept : Point(std::move(other)), color(std::move(other.color)) {}
    ~ColorPoint() override {}

    ColorPoint& operator=(const ColorPoint& other) {
        if (this != &other) {
            Point::operator=(other);
            color = other.color;
        }
        return *this;
    }

    ColorPoint& operator=(ColorPoint&& other) noexcept {
        if (this != &other) {
            Point::operator=(std::move(other));
            color = std::move(other.color);
        }
        return *this;
    }

    std::string getColor() const { return color; }
    void setColor(const std::string& c) { color = c; }
    void setColor(std::string&& c) { color = std::move(c); }
};

std::ostream& operator<<(std::ostream& os, const ColorPoint& cp) {
    os << static_cast<const Point&>(cp) << ", Color: " << cp.getColor();
    return os;
}

std::istream& operator>>(std::istream& is, ColorPoint& cp) {
    is >> static_cast<Point&>(cp);
    std::cout << "Enter Color: ";
    std::string c;
    is >> std::ws;
    std::getline(is, c);
    cp.setColor(std::move(c));
    return is;
}

int main() {
    ColorPoint cp1(5, 7, "blue"), cp2;
    cp2 = cp1;
    std::cout << "Copy assignment: " << cp2 << std::endl;

    ColorPoint cp3 = std::move(cp1);
    std::cout << "Move construction: " << cp3 << std::endl;

    std::cout << "Enter a new ColorPoint:\n";
    ColorPoint cpInput;
    std::cin >> cpInput;
    std::cout << "You entered: " << cpInput << std::endl;

    return 0;
}
