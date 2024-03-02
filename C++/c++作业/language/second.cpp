#include <iostream>

class Shape
{
public:
    virtual void calculateArea(int a){
        std::cout<<" "<<std::endl;
    }
};

class Circle : public Shape
{
public:
    void calculateArea(int a)
    {
        std::cout << "圆的面积:" << 3.14 * a * a << std::endl;
    }
};

class Rectangle : public Shape
{
public:
    void calculateArea(int a)
    {
        std::cout << "矩形的面积:" << a * a << std::endl;
    }
};

int main()
{
    Circle circle;
    circle.calculateArea(10);
    Rectangle rectangle;
    rectangle.calculateArea(10);
    return 0;
}
