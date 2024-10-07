#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <chrono>

#include "Map.h"

void GetStats(int testsCount, int pointsCount)
{
     std::cout << std::format("testsCount : {}, pointsCount : {}", testsCount, pointsCount) << std::endl;
     std::shared_ptr<Map> pointsMap;
     pointsMap = std::make_shared<Map>(pointsCount);
     std::vector<float> runningTimes;

     std::chrono::time_point<std::chrono::steady_clock> start;
     std::chrono::time_point<std::chrono::steady_clock> end;
     std::chrono::duration<float, std::milli> duration;
     
     for (int i = 0; i < testsCount; ++i)
     {
          pointsMap->Generate();
          start = std::chrono::high_resolution_clock::now();
          pointsMap->GetClosestPointsPair();
          
          end = std::chrono::high_resolution_clock::now();
          duration = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(end - start);
          runningTimes.push_back(duration.count());
     }

     float avg = std::accumulate(runningTimes.begin(), runningTimes.end(), 0.0f) / static_cast<float>(runningTimes.size());

     float variance = 0.0f;

     for (auto runningTime : runningTimes)
     {
          variance += std::pow(runningTime - avg, 2.0f);
     }

     variance /= (runningTimes.size() - 1);
     
     std::cout << std::format("avg : {}ms", avg) << std::endl;
     std::cout << std::format("variance : {}ms^2", variance) << std::endl;
     std::cout << std::endl;
     
}

int main()
{
     GetStats(50, 100);
     GetStats(50, 1000);
     GetStats(50, 10000);
}
