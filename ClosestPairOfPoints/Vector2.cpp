#include <ostream>
#include "Vector2.h"

float Vector2::Distance(Vector2 src, Vector2 dest)
{
    return std::sqrt(static_cast<float>(std::pow(dest.x - src.x, 2.0f) + std::pow(dest.y - src.y, 2.0f)));
}

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Vector2& lhs, const Vector2& rhs)
{
    return !operator==(lhs, rhs);
}

std::ostream& operator<<(std::ostream& os, const Vector2& v)
{
    os << std::format("[{},{}]", v.x, v.y);
    return os;
}

std::ostream& operator<<(std::ostream& os, Vector2* v)
{
    os << std::format("[{},{}]", v->x, v->y);
    return os;
}
