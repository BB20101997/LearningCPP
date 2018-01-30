//
// Created by Bennet on 29. Jan. 2018.
//

#ifndef LEARNINGCPP_SUDOKU_HPP
#define LEARNINGCPP_SUDOKU_HPP

#include <array>
#include <iostream>
#include <random>

template<size_t Size>
class Sudoku {
    private:
        static std::mt19937 rng;
        static bool seeded;
        static std::uniform_int_distribution<int> dist;
        using Grid_t = std::array<std::array<size_t, Size>, Size>;

        const bool checkRange(size_t x) const;

        Grid_t grid;
        size_t inside_height, inside_width;
    public:
        void generateRandom();

        Sudoku(size_t width, size_t height);

        Sudoku(Grid_t p_grid, size_t width, size_t height);

        Sudoku(const Sudoku<Size> &);

        const bool isSolved() const;

        const bool isCorrect() const;

        const bool erase(size_t x, size_t y);

        const bool tryInsert(size_t value, size_t x, size_t y);

        const size_t valueAt(size_t x, size_t y) const;

        const bool checkRange(size_t x, size_t y) const;

        const size_t width() const;

        const size_t height() const;

        const size_t size() const;
};


#include "../Sudoku.cpp"

#endif //LEARNINGCPP_SUDOKU_HPP
