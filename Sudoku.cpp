//
// Created by Bennet on 29. Jan. 2018.
//
#ifndef LEARNINGCPP_SUDOKU_CPP
#define LEARNINGCPP_SUDOKU_CPP

#include "Sudoku.hpp"
#include <exception>
#include <sstream>

template<size_t Size>
bool Sudoku<Size>::seeded = false;

template<size_t Size>
std::mt19937 Sudoku<Size>::rng; // NOLINT

template<size_t Size>
std::uniform_int_distribution<int> Sudoku<Size>::dist(1, Size); // NOLINT

template<size_t Size>
inline const bool Sudoku<Size>::checkRange(const size_t x) const {
    return ((x >= 0 && x < grid.size()));
};

template<size_t Size>
inline const bool Sudoku<Size>::checkRange(size_t x, size_t y) const {
    return checkRange(x) && checkRange(y);
};


template<size_t Size>
void Sudoku<Size>::generateRandom() {
    int x, y, v;
    if (!seeded) {
        rng.seed(std::random_device()());
        seeded = true;
    }

    int count = 0;
    while (count <= Size * Size / 3) {
        x = dist(rng)-1;
        y = dist(rng)-1;
        v = dist(rng);
        if (valueAt(x, y) <= 0) {
            grid[x][y] = v;
            if (isCorrect()) {
                count++;
            }else{
                grid[x][y] = 0;
            }
        }
    }
    //TODO

};

template<size_t Size>
const bool Sudoku<Size>::isSolved() const {
    for (size_t i = 0; i < Size; i++) {
        for (size_t j = 0; j < Size; j++) {
            if (grid[i][j] <= 0) {
                return false;
            }
        }
    }
    return isCorrect();
};

template<size_t Size>
const size_t Sudoku<Size>::valueAt(const size_t x, const size_t y) const {
    if (!checkRange(x, y)) {
        throw new std::runtime_error{"IndexOutOfBounds"};
	}
    return grid[x][y];
};


template<size_t Size>
const bool Sudoku<Size>::tryInsert(const size_t value, const size_t x, const size_t y) {
    if (!(value > 0 && value <= Size))

        if (!checkRange(x, y)) {
            return false;
        }

    if (valueAt(x, y) > 0) {
        return false;
    }

    grid[x][y] = value;
    return true;

};

template<size_t Size>
Sudoku<Size>::Sudoku(size_t w, size_t h):inside_height(h), inside_width(w) {
    std::cout << "Creating Sudoku" << std::endl;

    if (h * w != Size) {
        std::stringstream error_msg;
        error_msg << "Inner grid of unexpected size " << h * w << " expected " << Size << "!\n";
        throw new std::runtime_error(error_msg.str());
    }

    for (size_t x = 0; x < Size; x++) {
        for (size_t y = 0; y < Size; y++) {
            grid[x][y] = 0;
        }
    }
};

template<size_t Size>
Sudoku<Size>::Sudoku(Grid_t p_grid, const size_t w, const size_t h) : grid(p_grid), inside_width(w),
                                                                      inside_height(h) {

};

template<size_t Size>
Sudoku<Size>::Sudoku(const Sudoku<Size> &sudoku)
        :grid(), inside_width(sudoku.inside_width), inside_height(sudoku.inside_height) {
    std::cout << "Copy\n";
    for (size_t x = 0; x < Size; x++) {
        for (size_t y = 0; y < Size; y++) {
            grid[x][y] = sudoku.grid[x][y];
        }
    }
};


template<size_t Size>
const bool Sudoku<Size>::isCorrect() const {
    //size_t flag;
    //TODO
    return true;
};

template<size_t Size>
const bool Sudoku<Size>::erase(size_t x, size_t y) {
    if (!checkRange(x, y)) {
        return false;
    }
    grid[x][y] = -1;
    return true;
};

template<size_t Size>
const size_t Sudoku<Size>::size() const {
    return Size;
};

template<size_t Size>
const size_t Sudoku<Size>::height() const {
    return inside_height;
};

template<size_t Size>
const size_t Sudoku<Size>::width() const {
    return inside_width;
};


#endif //LEARNINGCPP_SUDOKU_CPP

