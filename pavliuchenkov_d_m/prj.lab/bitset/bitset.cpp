//
// Created by dmitrij on 3/30/22.
//

#include "bitset.h"

int BitSet::Size() const {
    return size_;
}

void BitSet::Fill(const bool val) {
    int rest = size_ % BIT_SIZE;
    uint16_t value = val ? UINT16_MAX : 0;
    if (rest > 0) {
        array_[array_.size() - 1] = value >> (BIT_SIZE - rest);
    }
    for (int i = 0; i < size_ / BIT_SIZE; ++i) {
        array_[i] = value;
    }
}

BitSet::BitHolder BitSet::operator[](const int index) {
    if (index >= size_ || index < 0) {
        throw std::out_of_range("Index is out of range");
    }
    return BitHolder(*this, index);
}

bool BitSet::operator[](const int index) const {
    if (index >= size_ || index < 0) {
        throw std::out_of_range("Index is out of range");
    }
    uint16_t mask = 1;
    int arr_ind = index / BIT_SIZE;
    int res = array_[arr_ind] >> (index % BIT_SIZE);
    return res & mask;
}
