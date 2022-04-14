//
// Created by dmitrij on 3/30/22.
//

#include "bitset.h"

BitSet operator| (const BitSet& left, const BitSet& right) {
    return BitSet(left) |= right;
}

int BitSet::Size() const {
    return sz_;
}

BitSet operator& (const BitSet& left, const BitSet& right) {
    return BitSet(left) &= right;
}

BitSet operator^ (const BitSet& left, const BitSet& right) {
    return BitSet(left) ^= right;
}

void BitSet::Resize(const int size) {
    if (size <= 0)
        throw std::invalid_argument("Size must be positive");
    std::vector<uint16_t> new_arr = std::vector<uint16_t>(size / BSZ, 0);
    if (size >= sz_) {
        for (int i = 0; i < array_.size(); ++i)
            new_arr[i] = array_[i];
    } else {
        for (int i = 0; i < new_arr.size(); ++i)
            new_arr[i] = array_[i];
        if (size % BSZ > 0)
            new_arr.push_back(array_[new_arr.size()] >> (BSZ - size % BSZ));
    }
    array_ = new_arr;
    sz_ = size;
}

void BitSet::Fill(const bool val) {
    int remainder = sz_ % BSZ;
    uint16_t value = val ? UINT16_MAX : 0;
    if (remainder > 0) {
        array_[array_.size() - 1] = value >> (BSZ - remainder);
    }
    for (int i = 0; i < sz_ / BSZ; ++i) {
        array_[i] = value;
    }
}

BitSet::BitHelper BitSet::operator[](const int ind) {
    if (ind >= sz_ || ind < 0) {
        throw std::out_of_range("Index is out of range");
    }
    return BitHelper(*this, ind);
}

bool BitSet::operator[](const int ind) const {
    uint16_t mask = 1;
    int arr_ind = ind / BSZ;
    if (ind >= sz_ || ind < 0) {
        throw std::out_of_range("Index is out of range");
    }
    int res = array_[arr_ind] >> (ind % BSZ);
    return res & mask;
}

BitSet BitSet::operator~() const {
    BitSet new_bitset = *this;
    for (int i = 0; i < sz_ / BSZ; ++i) {
        new_bitset.array_[i] = ~array_[i];
    }
    int remainder = sz_ % BSZ;
    if (remainder > 0)
        new_bitset.array_[array_.size() - 1] = (UINT16_MAX >> (BSZ - remainder)) &
                                               (~array_[array_.size() - 1]);
    return new_bitset;
}

BitSet& BitSet::operator^=(const BitSet& right) {
    if (this->sz_ != right.sz_)
        throw std::invalid_argument("Dimensions of bitsets must be equal");
    for (int i = 0; i < array_.size(); ++i)
        array_[i] ^= right.array_[i];
    return *this;
}

BitSet& BitSet::operator|=(const BitSet& right) {
    if (sz_ != right.sz_)
        throw std::invalid_argument("Dimensions of bitsets must be equal");
    for (int i = 0; i < array_.size(); ++i)
        array_[i] |= right.array_[i];
    return *this;
}

BitSet& BitSet::operator&=(const BitSet& right) {
    if (sz_ != right.sz_) {
        throw std::invalid_argument("Dimensions of bitsets must be equal");
    }
    for (int i = 0; i < array_.size(); ++i) {
        array_[i] &= right.array_[i];
    }
    return *this;
}

BitSet::BitSet(const int size, const bool value) {
    if (size <= 0) {
        throw std::invalid_argument("Size must be positive");
    }
    sz_ = size;
    uint16_t val = value ? UINT16_MAX : 0;
    array_ = std::vector<uint16_t>(size / BSZ, val);
    if (size % BSZ > 0) {
        array_.push_back(val >> (BSZ - size % BSZ));
    }
}

////////////////////////////////////// BitHelper ////////////////////////////


BitSet::BitHelper::BitHelper(BitSet& bs, int index): bs_(bs), idx_(index) {}

BitSet::BitHelper::operator bool() const {
    return (bs_.array_[idx_ / BitSet::BSZ] >> ((idx_ / BitSet::BSZ) % BitSet::BSZ)) & 1;
}

BitSet::BitHelper& BitSet::BitHelper::operator=(const bool val) {
    uint16_t mask = (1 << (idx_ % BitSet::BSZ)) ^UINT16_MAX;
    if (!val)
        bs_.array_[idx_ / BitSet::BSZ] &= mask;
    else
        bs_.array_[idx_ / BitSet::BSZ] |= (~mask);
    return *this;
}

/////////////////////////////////// in & out /////////////////////////////////////////

std::istream& operator>>(std::istream& istrm, BitSet& bs) {
    return istrm;
}

std::ostream& operator<<(std::ostream& ostrm, const BitSet& bitset) {
    return ostrm;
}
