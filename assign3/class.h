#pragma once
#include <string>
#include <iostream>

class Point {
    public:
        Point();
        Point(int x, int y);
        int getX() const;
        int getY() const;
        void setX(int x);
        void setY(int y);

        friend std::ostream& operator<<(std::ostream& os, const Point& p);
        
    private:
        int x;
        int y;
        std::string toString() const;
};

std::ostream& operator<<(std::ostream& os, const Point& p);