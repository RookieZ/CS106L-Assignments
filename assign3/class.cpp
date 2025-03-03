#include "class.h"

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int x, int y) {
    setX(x);
    setY(y);
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

void Point::setX(int x) {
    this->x = x;
}

void Point::setY(int y) {
    this->y = y;
}

std::string Point::toString() const {
    return "Point{x: " + std::to_string(getX()) + ", y: " +  std::to_string(getY()) + "}";
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << p.toString();
}