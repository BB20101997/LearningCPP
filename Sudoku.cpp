//
// Created by Bennet on 29. Jan. 2018.
//
#ifndef LEARNING_CPP_SUDOKU_CPP
#define LEARNING_CPP_SUDOKU_CPP

#include "Sudoku.hpp"
#include <sstream>

template<size_t Size>
bool Sudoku<Size>::seeded = false;

template<size_t Size>
std::mt19937 Sudoku<Size>::rng; // NOLINT

template<size_t Size>
std::uniform_int_distribution<size_t> Sudoku<Size>::dist{1, Size}; // NOLINT

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
    size_t x, y, v;
    if (!Sudoku<Size>::seeded) {
        rng.seed(std::random_device()());
        Sudoku<Size>::seeded = true;
    }

    int count = 0;
    while (count <= Size * Size / 3) {
        x = dist(rng) - 1;
        y = dist(rng) - 1;
        v = dist(rng);
        if (tryInsert(v, x, y)) {
            count++;
        }
    }
    //TODO check for solveability
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
        throw std::runtime_error{"IndexOutOfBounds"};
    }
    return grid[x][y];
};


template<size_t Size>
const bool Sudoku<Size>::tryInsert(const size_t value, const size_t x, const size_t y) {
    if (!(value > 0 && value <= Size)) {
        return false; //value out of range
    }

    if (!checkRange(x, y)) {
        return false; //coordinates out of range
    }

    if (valueAt(x, y) > 0) {
        return false; //field already set
    }

    grid[x][y] = value;
    if (!isCorrect()) {
        grid[x][y] = 0; //reset since it is not a valid move
        return false;
    }
    return true;
};

template<size_t Size>
Sudoku<Size>::Sudoku(size_t width, size_t height):inside_height(height), inside_width(width) {
    std::cout << "Creating Sudoku" << std::endl;

    if (height * width != Size) {
        std::stringstream error_msg;
        error_msg << "Inner grid of unexpected size " << height * width << " expected " << Size << "!\n";
        throw std::runtime_error(error_msg.str());
    }

    for (size_t x = 0; x < Size; x++) {
        for (size_t y = 0; y < Size; y++) {
            grid[x][y] = 0;
        }
    }
};

template<size_t Size>
Sudoku<Size>::Sudoku(Grid_t p_grid, const size_t width, const size_t height) : grid(p_grid), inside_width(width),
                                                                      inside_height(height) {

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
    std::array<bool, Size> flagRow, flagColumn, flagGrid;
    size_t inner_x, inner_y;
    for (size_t x = 0; x < Size; x++) {
        flagRow.fill(false);
        flagColumn.fill(false);
        flagGrid.fill(false);
        for (size_t y = 0; y < Size; y++) {
            if (grid[y][x] != 0) {
                if (flagColumn[grid[y][x]]) {
                    return false;
                }
                flagColumn[grid[y][x]] = true;
            }
            if (grid[x][y] != 0) {
                if (flagRow[grid[x][y]]) {
                    return false;
                }
                flagRow[grid[x][y]] = true;
            }
            inner_x = x % height() * width() + y % width();
            inner_y = x / height() * height() + y / width();
            if (grid[inner_x][inner_y] != 0) {
                if (flagGrid[grid[inner_x][inner_y]]) {
                    return false;
                }
                flagGrid[grid[inner_x][inner_y]] = true;
            }
        }
    }
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


#endif //LEARNING_CPP_SUDOKU_CPP

