//
// Created by dmitrij on 3/26/22.
//

#include <chrono>
#include <iostream>
#include "m3i_by_t_o.h"
#include <vector>

typedef std::chrono::steady_clock Clock;

std::vector<double> test_time(int dim1 = 10, int dim2 = 10, int dim3 = 10, int iter = 10) {
    std::vector<double> times(iter, 0);
    for (int i=0; i < iter; ++i) {
        auto start = Clock::now();
        M3i give_me_a_name(dim1, dim2, dim3);
        auto end = Clock::now();
        auto duration = end - start;
        times[i] = duration.count() * 0.001;
    }
    return times;
}

int main() {

    {
        // 10x10x10 - 10 times
        int dim1 = 10, dim2 = 10, dim3 = 10;
        int iter = 20;
        std::vector<double> times;
        auto start = Clock::now();
        times = test_time(dim1, dim2, dim3, iter);
        auto end = Clock::now();
        auto duration = end - start;
        double mean_time = duration.count() * 0.001 / iter;
        double median = 0, dispersion = 0;
        for (int i=0; i < iter; ++i) {
            median += times[i];
            dispersion += times[i] * times[i];
        }
        median /= iter;
        dispersion /= iter;
        dispersion = dispersion - median * median;
        std::cout << "Size: " << dim1 << "x" << dim2 << "x" << dim3 << std::endl;
        std::cout << "Iterations: " << iter << std::endl;
        std::cout << "Mean time (ms): " << mean_time << std::endl;
        std::cout << "Median time (ms): " << median << std::endl;
        std::cout << "Dispersion (ms): " << dispersion << std::endl;
        std::cout << std::endl;
    }

    {
        // 100x100x100 - 100 times
        int dim1 = 200, dim2 = 200, dim3 = 200;
        int iter = 20;
        std::vector<double> times;
        auto start = Clock::now();
        times = test_time(dim1, dim2, dim3, iter);
        auto end = Clock::now();
        auto duration = end - start;
        double mean_time = duration.count() * 0.001 / iter;
        double median = 0, dispersion = 0;
        for (int i=0; i < iter; ++i) {
            median += times[i];
            dispersion += times[i] * times[i];
        }
        median /= iter;
        dispersion /= iter;
        dispersion = dispersion - median * median;
        std::cout << "Size: " << dim1 << "x" << dim2 << "x" << dim3 << std::endl;
        std::cout << "Iterations: " << iter << std::endl;
        std::cout << "Mean time (ms): " << mean_time << std::endl;
        std::cout << "Median time (ms): " << median << std::endl;
        std::cout << "Dispersion (ms): " << dispersion << std::endl;
        std::cout << std::endl;
    }

    {
        // 1000x1000x1000 - 1000 times
        int dim1 = 900, dim2 = 900, dim3 = 900;
        int iter = 20;
        std::vector<double> times;
        auto start = Clock::now();
        times = test_time(dim1, dim2, dim3, iter);
        auto end = Clock::now();
        auto duration = end - start;
        double mean_time = duration.count() * 0.001 / iter;
        double median = 0, dispersion = 0;
        for (int i=0; i < iter; ++i) {
            median += times[i];
            dispersion += times[i] * times[i];
        }
        median /= iter;
        dispersion /= iter;
        dispersion = dispersion - median * median;
        std::cout << "Size: " << dim1 << "x" << dim2 << "x" << dim3 << std::endl;
        std::cout << "Iterations: " << iter << std::endl;
        std::cout << "Mean time (ms): " << mean_time << std::endl;
        std::cout << "Median time (ms): " << median << std::endl;
        std::cout << "Dispersion (ms): " << dispersion << std::endl;
        std::cout << std::endl;
    }
}

/*
Size: 10x10x10
Iterations: 10
Mean time (ms): 7.322
Median time (ms): 4.8854
Dispersion (ms): 4.93627

Size: 100x100x100
Iterations: 100
Mean time (ms): 4628.07
Median time (ms): 3909.46
Dispersion (ms): 2.76356e+06

Size: 1000x1000x1000
Iterations: 1000
 ???
 (Started to worry about my notebook)
 */


/*
Dron
Size: 10x10x10
Iterations: 20
Mean time (ms): 3.3123
Median time (ms): 3.0074
Dispersion (ms): 1.7736

Size: 200x200x200
Iterations: 20
Mean time (ms): 24465.8
Median time (ms): 24340.3
Dispersion (ms): 1.5496e+07

Size: 900x900x900
Iterations: 20
Mean time (ms): 3.11746e+06
Median time (ms): 2.94252e+06
Dispersion (ms): 3.60293e+11
 */

/*
Padas
Size: 10x10x10
Iterations: 20
Mean time (ms): 2.809
Median time (ms): 2.43915
Dispersion (ms): 1.39161

Size: 200x200x200
Iterations: 20
Mean time (ms): 18811.5
Median time (ms): 18695.8
Dispersion (ms): 1.04017e+07

Size: 900x900x900
Iterations: 20
Mean time (ms): 2.27761e+06
Median time (ms): 2.13855e+06
Dispersion (ms): 2.20334e+11
 */

/*
Orusov
Size: 10x10x10
Iterations: 20
Mean time (ms): 2.1347
Median time (ms): 1.8211
Dispersion (ms): 0.550256

Size: 200x200x200
Iterations: 20
Mean time (ms): 14866.4
Median time (ms): 14744.7
Dispersion (ms): 1.55989e+07

Size: 900x900x900
Iterations: 20
Mean time (ms): 2.59879e+06
Median time (ms): 2.4075e+06
Dispersion (ms): 3.68089e+11
 */

/*
 Pavliuchenkov
Size: 10x10x10
Iterations: 20
Mean time (ms): 1.1745
Median time (ms): 0.7534
Dispersion (ms): 8.26166

Size: 200x200x200
Iterations: 20
Mean time (ms): 5.72385
Median time (ms): 2.24055
Dispersion (ms): 1.11224

Size: 900x900x900
Iterations: 20
Mean time (ms): 9.65845
Median time (ms): 2.28585
Dispersion (ms): 0.115659
 */