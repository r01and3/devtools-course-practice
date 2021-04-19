// Copyright 2021 Pronkin Dmitry

#include <gtest/gtest.h>

#include "include/wave_algorithm.h"

TEST(WaveAlgorithm, ExceptionEmptyMap) {
    ASSERT_ANY_THROW(WaveAlgorithm::Map(std::vector<int>(), 1, 1));
}

TEST(WaveAlgorithm, ExceptionIncorrectParm) {
    ASSERT_ANY_THROW(WaveAlgorithm::Map(std::vector<int>(4), 0, -1));
}

TEST(WaveAlgorithm, ExceptionNotMatch) {
    ASSERT_ANY_THROW(WaveAlgorithm::Map(std::vector<int>(4), 2, 1));
}

TEST(WaveAlgorithm, MapCreateTest) {
    ASSERT_NO_THROW(WaveAlgorithm::Map(std::vector<int>(4), 2, 2));
}

TEST(WaveAlgorithm, MapCopyTest) {
    ASSERT_NO_THROW(WaveAlgorithm::Map(WaveAlgorithm::Map(std::vector<int>(4), 2, 2)));
}

TEST(WaveAlgorithm, IndexingOperatorException) {
    WaveAlgorithm::Map map(std::vector<int>(4), 2, 2);
    ASSERT_ANY_THROW(map[WaveAlgorithm::point(-1, -1)]);
}

TEST(WaveAlgorithm, IndexingOperatorGetTest) {
    WaveAlgorithm::Map map(std::vector<int>(4), 2, 2);
     WaveAlgorithm::point p = WaveAlgorithm::point(0, 0);
    ASSERT_EQ(0, map[p]);
}

TEST(WaveAlgorithm, IndexingOperatorSetTest) {
    WaveAlgorithm::Map map(std::vector<int>(4), 2, 2);
    WaveAlgorithm::point p = WaveAlgorithm::point(0, 0);
    map[p] = WALL;
    ASSERT_EQ(WALL, map[p]);
}

TEST(WaveAlgorithm, DISABLED_OutOfRangeException) {
    std::vector<int> map = {
        FREE, WALL,
        WALL, FREE
    };
    WaveAlgorithm::point start(0, 0);
    WaveAlgorithm::point finish(-1, 1);
    WaveAlgorithm::Map m(map, 2, 2);
    std::vector<WaveAlgorithm::point> path;
    ASSERT_ANY_THROW(WaveAlgorithm::Algorithm::findPath(m, path, start, finish));
}

TEST(WaveAlgorithm, DISABLED_NotFreePointException) {
    std::vector<int> map = {
        FREE, WALL,
        WALL, FREE
    };
    WaveAlgorithm::point start(1, 0);
    WaveAlgorithm::point finish(1, 1);
    WaveAlgorithm::Map m(map, 2, 2);
    std::vector<WaveAlgorithm::point> path;
    ASSERT_ANY_THROW(WaveAlgorithm::Algorithm::findPath(m, path, start, finish));
}

TEST(WaveAlgorithm, AlgorithmTest) {
    std::vector<int> map = {
        0, FREE, FREE, FREE,
        WALL, FREE, WALL, WALL,
        WALL, FREE, FREE, WALL,
        FREE, WALL, FREE, FREE
    };
    WaveAlgorithm::Map m(map, 4, 4);
    WaveAlgorithm::point start(0, 0);
    WaveAlgorithm::point finish(1, 2);
    std::vector<WaveAlgorithm::point> path;
    std::vector<WaveAlgorithm::point> testPath = {
        WaveAlgorithm::point(0, 0),
        WaveAlgorithm::point(1, 1),
        WaveAlgorithm::point(1, 2)
    };
    WaveAlgorithm::Algorithm::findPath(m, path, start, finish);
    ASSERT_EQ(testPath, path);
}