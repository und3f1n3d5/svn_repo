#include "m3i_by_t_o.h"
#include <cstring>
#include <stdexcept>

M3i::M3i() {
    data = new Data();
}

M3i::M3i(const int x, const int y, const int z) {
    if (x <= 0 || y <= 0 || z <= 0) {
        throw std::out_of_range("X, y, z have to be > 0");
    }
    int shape[3] = {x, y, z};
    data = new Data(new int[x * y * z], shape, 1);
    for (int i = 0; i < x * y * z; ++i) {
        data -> values[i] = 0;
    }
}

M3i::M3i(const std::initializer_list<std::initializer_list<std::initializer_list<int>>>& list) {
    int shape[3] = {(int)list.size(), (int)list.begin()->size(), (int)list.begin()->begin()->size()};
    data = new Data(new int[shape[0] * shape[1] * shape[2]], shape, 1);
    int position = 0;
    for (auto i : list) {
        for (auto j : i) {
            for (auto value : j) {
                data->values[position] = value;
                ++position;
            }
        }
    }
}


M3i::M3i(const M3i& other) {
    data = other.data;
    data->ref_counter++;
}

M3i& M3i::operator=(const M3i& other) {
    deleteCurrent();
    data = other.data;
    data->ref_counter++;
    return *this;
}

M3i::M3i(M3i&& other) {
    data = other.data;
    other.data = nullptr;
}

M3i& M3i::operator=(M3i&& other) {
    deleteCurrent();
    data = other.data;
    other.data = nullptr;
    return *this;
}

M3i::~M3i() {
    deleteCurrent();
}

M3i M3i::Clone() const {
    std::lock_guard<std::mutex> lock(data->mutex);
    M3i copy(data->shape[0], data->shape[1], data->shape[2]);
    for (int x = 0; x < data->shape[0]; ++x) {
        for (int y = 0; y < data->shape[1]; ++y) {
            for (int z = 0; z < data->shape[2]; ++z) {
                copy.At(x, y, z) = At(x, y, z);
            }
        }
    }
    return copy;
}

M3i& M3i::Resize(const int x, const int y, const int z) {
    std::lock_guard<std::mutex> lock(data->mutex);
    if (x <= 0 || y <= 0 || z <= 0) {
        throw std::out_of_range("X, y, z have to be > 0");
    }
    int* old_values = data -> values;
    int old_shape[3] = {data -> shape[0], data -> shape[1], data -> shape[2]};
    data->shape[0] = x;
    data->shape[1] = y;
    data->shape[2] = z;
    data -> values = new int[x * y * z];
    memset(data -> values, 0, x * y * z * sizeof(int));
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                if (i >= old_shape[0] || j >= old_shape[1] || k >= old_shape[2]) {
                    At(i, j, k) = 0;
                } else {
                    At(i, j, k) = old_values[i * old_shape[1] * old_shape[2] + j * old_shape[2] + k];
                }
            }
        }
    }
    if (!old_values) {
        delete[] old_values;
    }
    return *this;
}

int M3i::At(const int x, const int y, const int z) const {
    if (x >= Size(0) || x < 0 || y >= Size(1) || y < 0 || z >= Size(2) || z < 0) {
        throw std::out_of_range("Invalid coordinates in At");
    }
    return data -> values[x * (data -> shape[1] * data -> shape[2]) + y * data -> shape[2] + z];
}

int& M3i::At(const int x, const int y, const int z) {
    if (x >= Size(0) || x < 0 || y >= Size(1) || y < 0 || z >= Size(2) || z < 0) {
        throw std::out_of_range("Invalid coordinates in At");
    }
    return data -> values[x * (data -> shape[1] * data -> shape[2]) + y * data -> shape[2] + z];
}

int M3i::Size(const int dim) const {
    if (dim > 2 || dim < 0) {
        throw std::out_of_range("Dim in Size is in {0, 1, 2}");
    }
    return data -> shape[dim];
}

void M3i::Fill(const int value) {
    std::lock_guard<std::mutex> lock(data->mutex);
    for (int x = 0; x < Size(0); ++x) {
        for (int y = 0; y < Size(1); ++y) {
            for (int z = 0; z < Size(2); ++z) {
                At(x, y, z) = value;
            }
        }
    }
}

void M3i::deleteCurrent() {
    if (data != nullptr) {
        --data -> ref_counter;
        if (data -> ref_counter == 0) {
            if (data -> values != nullptr) {
                delete[] data -> values;
            }
            delete data;
        }
    }
}

std::istream& operator>>(std::istream& istrm, M3i& m) {
    int x = 0;
    int y = 0;
    int z = 0;
    istrm >> x >> y >> z;
    m.Resize(x, y, z);
    for (int i = 0; i < m.Size(0); ++i) {
        for (int j = 0; j < m.Size(1); ++j) {
            for (int k = 0; k < m.Size(2); ++k) {
                istrm >> m.At(i, j, k);
            }
        }
    }
    return istrm;
}

std::ostream& operator<<(std::ostream& ostrm, const M3i& m) {
    ostrm << m.Size(0) << " " << m.Size(1) << " " << m.Size(2) << "\n";
    for (int i = 0; i < m.Size(0); ++i) {
        for (int j = 0; j < m.Size(1); ++j) {
            for (int k = 0; k < m.Size(2); ++k) {
                ostrm << m.At(i, j, k) << " ";
            }
            ostrm << "\n";
        }
        ostrm << "\n";
    }
    return ostrm;
}