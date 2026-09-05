#include "MaxSubarray.hpp"
#include <vector>

int main() {

    if (!MaxSubarray::verifyCorrectness(100)) {
        return 1;
    }

    std::vector<int> tamanos = {1000, 2000, 4000, 8000 , 16000
    };
    MaxSubarray::runBenchmarksAndExportCSV("tiempos.csv", tamanos);

    MaxSubarray::testLargeKadane(100000000);

    return 0;
}
