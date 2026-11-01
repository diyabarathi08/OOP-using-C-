
#include <iostream>
using namespace std;

class Shape
{
public:
    virtual float area() = 0;
    virtual void display() = 0;
};

class Circle : public Shape
{
private:
    float radius;

public:
    Circle(float r)
    {
        radius = r;
    }

    float area()
    {
        return 3.14 * radius * radius;
    }

    void display()
    {
        cout << "Radius of Circle: " << radius << endl;
    }
};

class Rectangle : public Shape
{
private:
    float length, breadth;

public:
    Rectangle(float l, float b)
    {
        length = l;
        breadth = b;
    }

    float area()
    {
        return length * breadth;
    }

    void display()
    {
        cout << "Length of Rectangle: " << length << endl;
        cout << "Breadth of Rectangle: " << breadth << endl;
    }
};

class Triangle : public Shape
{
private:
    float base, height;

public:
    Triangle(float b, float h)
    {
        base = b;
        height = h;
    }

    float area()
    {
        return 0.5 * base * height;
    }

    void display()
    {
        cout << "Base of Triangle: " << base << endl;
        cout << "Height of Triangle: " << height << endl;
    }
};

int main()
{
    float radius, length, breadth, base, height;
    cout << "Enter radius of Circle: ";
    cin >> radius;

    cout << "Enter length of Rectangle: ";
    cin >> length;
    cout << "Enter breadth of Rectangle: ";
    cin >> breadth;

    cout << "Enter base of Triangle: ";
    cin >> base;
    cout << "Enter height of Triangle: ";
    cin >> height;

    Circle c(radius);
    Rectangle r(length, breadth);
    Triangle t(base, height);

    Shape *ptr;

    ptr = &c;
    ptr->display();
    cout << "Area of Circle: " << ptr->area() << endl;

    cout << endl;

    ptr = &r;
    ptr->display();
    cout << "Area of Rectangle: " << ptr->area() << endl;

    cout << endl;

    ptr = &t;
    ptr->display();
    cout << "Area of Triangle: " << ptr->area() << endl;

    return 0;
}