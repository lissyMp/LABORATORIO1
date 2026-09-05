#ifndef MAX_SUBARRAY_HPP
#define MAX_SUBARRAY_HPP

#include <vector>
#include <string>

namespace MaxSubarray {

    long long cubic(const std::vector<int>& arr);
    long long quadratic(const std::vector<int>& arr);
    long long kadane(const std::vector<int>& arr);

    bool verifyCorrectness(int num_tests = 100);
    void runBenchmarksAndExportCSV(const std::string& filename, const std::vector<int>& sizes);
    void testLargeKadane(long long n_size);

}

#endif
