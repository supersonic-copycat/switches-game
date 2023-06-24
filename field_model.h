#ifndef FIELD_MODEL_H
#define FIELD_MODEL_H

#include <vector>
#include <cassert>
#include <algorithm>

struct GameField {
public:
    GameField(size_t width, size_t height) : width(width), height(height), field(std::vector<int>(width*height)) {}
    size_t set(size_t r, size_t c, size_t val) {
        assert((val == 1) || (val ==0) );
        field.at(r*this->width + c) = val;
        return 0;
    }

    size_t get(size_t r, size_t c) {
        return field.at(r*this->width + c);
    }

    size_t switch_cell(size_t r, size_t c) {
        return field.at(r*width + c) ^ 1;
    }

    void switch_cells(size_t r, size_t c) {
        for (size_t i = std::clamp<size_t>(r - 1, 0, height); i < std::clamp<size_t>(r+1, 0, width); ++i) {
            for (size_t j = std::clamp<size_t>(r - 1, 0, height); j < std::clamp<size_t>(r+1, 0, width); ++j) {

            }
        }
    }

private:
    size_t width, height;
    std::vector<int> field;
};

#endif // FIELD_MODEL_H
