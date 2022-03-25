#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int radius, const char *label)
    : Figure(id, x, y), radius(radius)
{
    this->label = new char[strlen(label) + 1];
    strcpy(this->label, label);
}
Circle::~Circle()
{
    delete[] label;
}

void Circle::print() const
{
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius, label);
}
bool Circle::is_inside(int _x, int _y) const
{
    int dx = x - _x;
    int dy = y - _y;
    return (dx * dx + dy * dy) <= (radius * radius);
}
void Circle::zoom(int factor)
{
    radius *= factor;
}