#include "Rectangle.hpp"

/* проверяем положение точки (x3,y3) относительно прямой через (x1,y1) (x2,y2)
   <0 слева
    0 на прямой
   >0 справа
*/
static int relative_position(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return (x3 - x1) * (y2 - y1) - (y3 - y1) * (x2 - x1);
}

Rectangle::Rectangle(int id, int x, int y, int width, int height)
    : Figure(id, x, y), width(width), height(height) {}

void Rectangle::print() const
{
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}
bool Rectangle::is_inside(int _x, int _y) const
{
    return (relative_position(x - width / 2, y - height / 2, x - width / 2, y + height / 2, _x, _y) >= 0) &&
           (relative_position(x - width / 2, y + height / 2, x + width / 2, y + height / 2, _x, _y) >= 0) &&
           (relative_position(x + width / 2, y + height / 2, x + width / 2, y - height / 2, _x, _y) >= 0) &&
           (relative_position(x + width / 2, y - height / 2, x - width / 2, y - height / 2, _x, _y) >= 0);
}
void Rectangle::zoom(int factor)
{
    width *= factor;
    height *= factor;
}