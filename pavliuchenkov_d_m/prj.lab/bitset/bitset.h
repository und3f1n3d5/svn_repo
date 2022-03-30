//
// Created by dmitrij on 3/30/22.
//
#pragma once
#ifndef SE_STUDY_PAVLIUCHENKOV_BITSET_H
#define SE_STUDY_PAVLIUCHENKOV_BITSET_H


class Bitset {
public:
    Bitset();
    Bitset(const Bitset& other);
    Bitset(Bitset&& other);

    ~Bitset();

    Bitset& operator=(const Bitset& other);
    Bitset& operator=(Bitset&& other);

    Bitset(const int size, const bool val = false);

    int Size() const;
    void Resize(const int size);

    bool operator[](const int index) const;

    Bitset& operator|(const Bitset& other);
    Bitset& operator&(const Bitset& other);
    Bitset& operator^(const Bitset& other);
    Bitset& operator~();
private:
    class BoolHolder {
        BoolHolder& operator=(const BoolHolder& other);
    private:
        BoolHolder();
        unsigned char* ptr_;
    };
};

#endif // #define BITSET_HEAD_H_2022_03_03


#endif //SE_STUDY_PAVLIUCHENKOV_BITSET_H
