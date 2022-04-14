#ifndef __M3I_LAB_H__
#define __M3I_LAB_H__

#include<iostream>
#include<initializer_list>
#include <mutex>
#include <atomic>

class M3i {
public:
    M3i();
    M3i(const int x, const int y, const int z);
    M3i(const std::initializer_list<std::initializer_list<std::initializer_list<int>>>& list);

    M3i(const M3i&); //конструктор копирования
    M3i& operator=(const M3i&); //присваивание копированием
    M3i(M3i&&); //конструктор перемещения
    M3i& operator=(M3i&&); //присваивание перемещением

    ~M3i();

    M3i Clone() const;

    M3i& Resize(const int x, const int y, const int z);

    int At(const int x, const int y, const int z) const;
    int& At(const int x, const int y, const int z);

    int Size(const int dim) const;
    void Fill(const int value);

private:
    struct Data {
        Data() = default;
        Data(int* values, int* shape_other, int ref_counter) : values(values), ref_counter(ref_counter) {
            shape[0] = shape_other[0];
            shape[1] = shape_other[1];
            shape[2] = shape_other[2];
        }
        int* values = nullptr;
        int shape[3] = {0, 0, 0};
        std::atomic<int> ref_counter;
        std::mutex mutex;
    };

    Data* data;

    void deleteCurrent();
};

std::istream& operator>>(std::istream& istrm, M3i& m);
std::ostream& operator<<(std::ostream& ostrm, const M3i& m);

#endif //__M3I_LAB_H__