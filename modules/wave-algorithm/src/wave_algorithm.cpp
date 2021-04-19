// Copyright 2021 Pronkin Dmitry

#include "include/wave_algorithm.h"

WaveAlgorithm::Map::Map(const std::vector<int>& map, unsigned int mapRows, unsigned int mapCols) {
    if (map.empty()) {
        throw std::invalid_argument("Map is empty");
    }
    if (mapRows <=0 || mapCols <=0) {
        throw std::invalid_argument("Incorrect map parameters");
    }
    if (map.size() != static_cast<size_t>(mapRows * mapCols)) {
        throw std::invalid_argument("Map size doesn't match the parameters");
    }
    this->map = std::vector<int>(map);
    this->mapCols = mapCols;
    this->mapRows = mapRows;
}

WaveAlgorithm::Map::Map(const Map& copy) : map(copy.map), mapRows(copy.mapRows), mapCols(copy.mapCols) {}

int& WaveAlgorithm::Map::operator[] (const WaveAlgorithm::point& p) {
    if (p.first < 0 || p.first > this->mapCols - 1 ||
        p.second < 0 || p.second > this->mapRows - 1) {
            throw std::out_of_range("Out of range");
        }
    return this->map[p.second * this->mapCols + p.first];
}

int WaveAlgorithm::Map::operator[] (const WaveAlgorithm::point& p) const {
    if (p.first < 0 || p.first > this->mapCols - 1 ||
        p.second < 0 || p.second > this->mapRows - 1) {
            throw std::out_of_range("Out of range");
        }
    return this->map[p.second * this->mapCols + p.first];
}

bool WaveAlgorithm::Map::operator==(const Map& map) const {
    return map.map == this->map;
}

unsigned int WaveAlgorithm::Map::getRows() const {
    return mapRows;
}

unsigned int WaveAlgorithm::Map::getCols() const {
    return mapCols;
}

int WaveAlgorithm::Algorithm::findPath(const Map& map, std::vector<point>& path, const point& start, const point& finish) {
    if (start.first < 0 || start.first > map.getCols() - 1 ||
        start.second < 0 || start.second > map.getRows() - 1 ||
        finish.first < 0 || finish.first > map.getCols() - 1 ||
        finish.second < 0 || finish.second > map.getRows() - 1) {
        throw std::invalid_argument("Coord out of range");
    }
    if (map[start] == WALL || map[finish] == WALL) {
        throw std::invalid_argument("Coord not free");
    }
    Map tmp(map);
    tmp[start] = 0;
    if (!waveProp(tmp, start, finish)) {
        return -1;
    }
    buildPath(tmp, path, start, finish);
    std::reverse(path.begin(), path.end());
    return 1;
}

bool WaveAlgorithm::Algorithm::waveProp(Map& map, const point& start, const point& finish) {
    std::queue<point> pointQueue({start});
    bool pathWasFound = false;
    while(!pointQueue.empty()) {
        if (pointQueue.front() == finish) {
            pathWasFound = true;
            break;
        }
        for (int j = -1; j <= 1; j++) {
            for (int i = -1; i <= 1; i++) {
                point tmpPoint(pointQueue.front().first + i, pointQueue.front().second + j);
                if (tmpPoint != pointQueue.front() && checkPoint(map, tmpPoint) && map[tmpPoint] == FREE) {
                    pointQueue.push(tmpPoint);
                    map[tmpPoint] = map[pointQueue.front()] + 1;
                }
            }
        }
        pointQueue.pop();
    }
    return pathWasFound;
}

void WaveAlgorithm::Algorithm::buildPath(const Map& map, std::vector<point>& path, const point& start, const point& finish) {
    point pathPoint(finish);
    path.push_back(pathPoint);
    while (pathPoint != start) {
        for (int j = -1; j <= 1; j++) {
            for (int i = -1; i <= 1; i++) {
                point tmpPoint(pathPoint.first + i, pathPoint.second + j);
                if (tmpPoint != pathPoint && checkPoint(map, tmpPoint) && map[tmpPoint] + 1 == map[pathPoint]) {
                    pathPoint = tmpPoint;
                    path.push_back(pathPoint);
                    break;
                }
            }
        }
    }
}

bool WaveAlgorithm::Algorithm::checkPoint(const Map& map, const point& p) {
    if (p.first < 0 || p.first > map.getCols() - 1 ||
        p.second < 0 || p.second > map.getRows() - 1 ||
        map[p] == WALL) {
        return false;
    }
    return true;
}