#include <algorithm>
#include <iostream>
#include <ostream>
#include <set>
#include <random>

#include "QuickSort.h"
#include "Map.h"

#include <string>

PointPair::PointPair(): distance(0)
{
    points = new std::pair<Vector2*, Vector2*>;
}

bool operator<(const PointPair& lhs, const PointPair& rhs)
{
    return lhs.distance < rhs.distance;
}

std::ostream& operator<<(std::ostream& os, const PointPair& pair)
{
    std::cout << "Points : " << pair.points->first << ", " << pair.points->second << std::endl;
    std::cout << "Distance : " << pair.distance;
    return os;
}

Map::Map(int pointsCount): _pointsCount(pointsCount)
{
}

PointPair Map::GetClosestPointsPair()
{
    SortX(_map);
    return ClosestPointsRecursion(0, _map.size() - 1);
}

void Map::Print()
{
    int i = 0;
    for (auto vec : _map)
    {
        std::cout << vec;
        i++;
        if(i % 10 == 0)
            std::cout << "\n";
    }
}

PointPair Map::ClosestPointsRecursion(int low, int high)
{
    PointPair result;
    int sz = high - low + 1;
    
    if(sz == 1)
    {
        result.distance = 0.0f;
        return result;
    }
    if(sz == 2)
    {
        result.points->first = _map[low];
        result.points->second = _map[high];
        result.distance = Vector2::Distance(*_map[low], *_map[high]);
        return result;
    }
    if(sz == 3)
    {
        PointPair pair1;
        PointPair pair2;
        PointPair pair3;

        pair1.points->first = _map[low];
        pair1.points->second = _map[high];
        
        pair2.points->first = _map[low];
        pair2.points->second = _map[low + 1];
        
        pair3.points->first = _map[low + 1];
        pair3.points->second = _map[high];

        if(FirstMax(pair1, pair2, pair3)) return pair1;
        if(FirstMax(pair2, pair1, pair3)) return pair2;
        if(FirstMax(pair3, pair1, pair2)) return pair3;
    }
    
    int middle = (low + high) / 2;

    result = std::min(ClosestPointsRecursion(low, middle), ClosestPointsRecursion(middle, high));

    std::vector<Vector2*> verticalStrip;

    for (int i = low; i != high + 1; ++i)
    {
        if(_map[i]->x < result.distance)
            verticalStrip.emplace_back(_map[i]);
    }
    SortY(verticalStrip);

    float temp;
    for(int i = 0; i != verticalStrip.size(); ++i)
    {
        for(int j = i + 1; j != verticalStrip.size() && verticalStrip[j] - verticalStrip[i] < result.distance; ++j)
        {
            temp = Vector2::Distance(*verticalStrip[j], *verticalStrip[i]);
            if(temp < result.distance)
            {
                result.points->first = verticalStrip[i];
                result.points->second = verticalStrip[j];
                result.distance = temp;
            }
        }
    }
    
    return result;
}

void Map::Generate()
{
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<int> distribution(0, _pointsCount);

    std::set<Vector2*, decltype(compareXPointer)> vecs;
    for (int i = 0; i != _pointsCount; ++i)
    {
        vecs.emplace(new Vector2(distribution(gen), distribution(gen)));
    }
    
    while (vecs.size() != _pointsCount)
    {
        int leftCount = _pointsCount - vecs.size();

        for (int i = 0; i != leftCount; ++i)
        {
            vecs.emplace(new Vector2(distribution(gen), distribution(gen)));
        }
    }
    _map.assign(vecs.begin(), vecs.end());
}

inline void Map::SortX(std::vector<Vector2*>& list)
{
    QuickSort<Vector2*>::Sort(list, compareXPointer);
}

void Map::SortY(std::vector<Vector2*>& list)
{
    QuickSort<Vector2*>::Sort(list, compareYPointer);
}

inline bool Map::FirstMax(const PointPair& a, const PointPair& b, const PointPair& c)
{
    return (a.distance > b.distance) && (a.distance > c.distance);
}
