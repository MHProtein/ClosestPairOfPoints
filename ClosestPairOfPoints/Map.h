#pragma once
#ifndef MAP_H
#define MAP_H

#include <vector>
#include <ostream>
#include "Vector2.h"

struct PointPair
{
    std::pair<Vector2*, Vector2*>* points;
    float distance;

    PointPair();
};

inline bool operator<(const PointPair& lhs, const PointPair& rhs);
std::ostream& operator<<(std::ostream& os, const PointPair& pair);

class Map
{
public:
    static inline auto compareXPointer = [](Vector2* lhs, Vector2* rhs){return (lhs->x < rhs->x) || (lhs->x == rhs->x && lhs->y < rhs->y); };
    static inline auto compareYPointer = [](Vector2* lhs, Vector2* rhs){return (lhs->y < rhs->y) || (lhs->y == rhs->y && lhs->x < rhs->x); };
    
    Map(int pointsCount);

    PointPair GetClosestPointsPair();   
    
    void Print();
    void Generate();
    
private:

    PointPair ClosestPointsRecursion(int low, int high);
    

    inline void SortX(std::vector<Vector2*>& list);
    inline void SortY(std::vector<Vector2*>& list);

    inline bool FirstMax(const PointPair& a, const PointPair& b, const PointPair& c);
    
    std::vector<Vector2*> _map;
    const int _pointsCount;
};
#endif