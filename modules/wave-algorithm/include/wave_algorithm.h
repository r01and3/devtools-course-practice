// Copyright 2021 Pronkin Dmitry

#ifndef MODULES_WAVE_ALGORITHM_INCLUDE_WAVE_ALGORITHM_H_
#define MODULES_WAVE_ALGORITHM_INCLUDE_WAVE_ALGORITHM_H_

#define WALL -2
#define FREE -1

#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <stdexcept>

namespace WaveLib{
using point = std::pair<int, int>;
class WaveAlgorithm {
 private:
    int mapHeight;
    int mapWidth;
    std::vector<int> map;
 public:
    WaveAlgorithm(int _mapHeight, int _mapWidth);
    WaveAlgorithm(int _mapHeight, int _mapWidth, const std::vector<int>& _map);

    bool findPath(
        const point& start,
        const point& finish,
        std::vector<point>* path);

 private:
    bool waveProp(const point& start, const point& finish);
    void buildPath(
        const point& start,
        const point& finish,
        std::vector<point>* path);
    bool checkPoint(const point& currPoint);
};
};  // namespace WaveLib

#endif  // MODULES_WAVE_ALGORITHM_INCLUDE_WAVE_ALGORITHM_H_
