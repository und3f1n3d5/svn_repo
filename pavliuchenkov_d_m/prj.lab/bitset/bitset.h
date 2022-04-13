//
// Created by dmitrij on 3/30/22.
//
#pragma once
#ifndef SE_STUDY_PAVLIUCHENKOV_BITSET_H
#define SE_STUDY_PAVLIUCHENKOV_BITSET_H
#include <vector>
#include <cstdint>
#include <iosfwd>
#include <stdexcept>

class BitSet {
private:
    class BitHelper;

public:
    BitSet() = default;
    BitSet(const BitSet& other) = default;
    BitSet(BitSet&& other) = default;
    ~BitSet() = default;
    BitSet& operator=(const BitSet& other) = default;
    BitSet& operator=(BitSet&& other) = default;
    explicit BitSet(int size, bool val = false);
    [[nodiscard]] int Size() const;
    void Resize(int size);
    void Fill(bool val); // not done
    bool operator[](int ind) const;
    BitHelper operator[](int ind);
    BitSet& operator|=(const BitSet& right);
    BitSet& operator&=(const BitSet& right);
    BitSet& operator^=(const BitSet& other);
    BitSet operator~() const;

private:
    class BitHelper {
    public:
        BitHelper(BitSet& bs, int index);
        BitHelper(const BitHelper& other) = default;
        BitHelper(BitHelper&& other) = default;
        ~BitHelper() = default;
        BitHelper& operator=(const BitHelper& other) = default;
        BitHelper& operator=(BitHelper&& other) = default;
        BitHelper& operator=(bool val);
        explicit operator bool() const;
    private:
        BitHelper();
        BitSet& bs_;
        int idx_;
    };
    std::vector<uint16_t> array_;
    int sz_ = 0;
    static const int BSZ = 16;
};

BitSet operator^ (const BitSet& left, const BitSet& right);
BitSet operator& (const BitSet& left, const BitSet& right);
BitSet operator| (const BitSet& left, const BitSet& right);

std::ostream& operator<<(std::ostream& ostrm, const BitSet& bitset);
std::istream& operator>>(std::istream& istrm, BitSet& bs);


#endif //SE_STUDY_PAVLIUCHENKOV_BITSET_H
