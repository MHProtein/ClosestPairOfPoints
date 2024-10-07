#pragma once
#include <format>
#include <ostream>

class Vector2
{
public:
    int x;
    int y;
    
    Vector2() : x(0), y(0)
    {
    }
    
    Vector2(int x, int y) : x(x), y(y)
    {
    }

    static float Distance(Vector2 src, Vector2 dest);
    
};

inline bool operator==(const Vector2& lhs, const Vector2& rhs);

inline bool operator!=(const Vector2& lhs, const Vector2& rhs);

std::ostream& operator<<(std::ostream& os, const Vector2& v);

std::ostream& operator<<(std::ostream& os, Vector2* v);


namespace std
{
    template<>
    struct less<Vector2>
    {
        bool operator()(const Vector2& lhs, const Vector2& rhs) const
        {
            return (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y);
        }
    };
}
