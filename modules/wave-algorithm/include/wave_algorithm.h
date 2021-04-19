// Copyright 2021 Pronkin Dmitry

#ifndef MODULES_WAVE_ALGORITHM_INCLUDE_WAVE_ALGORITHM_H
#define MODULES_WAVE_ALGORITHM_INCLUDE_WAVE_ALGORITHM_H

#define WALL -2
#define FREE -1

#include <vector>
#include <queue>
#include <stack>
#include <stdexcept>

namespace WaveAlgorithm {
    using point = std::pair<int, int>;
    struct Map {
    private:
        unsigned int mapRows;
        unsigned int mapCols;
        std::vector<int> map;
    public:
        Map(const std::vector<int>& map, unsigned int mapRows, unsigned int mapCols);
        Map(const Map& copy);

        int& operator[] (const point& p);
        int operator[] (const point& p) const;
        bool operator== (const Map& map) const;

        unsigned int getRows() const;
        unsigned int getCols() const;
    };
    class Algorithm {
    public:
        static int findPath(const Map& map, std::vector<point>& path, const point& start, const point& finish);
    private:
        static bool waveProp(Map& map, const point& start, const point& finish);
        static void buildPath(const Map& map, std::vector<point>& path, const point& start, const point& finish);
        static bool checkPoint(const Map& map, const point& p);
    };
}

#endif // MODULES_WAVE_ALGORITHM_INCLUDE_WAVE_ALGORITHM_H