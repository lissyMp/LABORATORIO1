#include "MaxSubarray.hpp"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <climits>

namespace MaxSubarray {

    long long cubic(const std::vector<int>& arr) {
        int n = arr.size();
        long long mejor = LLONG_MIN;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                long long suma = 0;
                for (int k = i; k <= j; ++k) {
                    suma += arr[k];
                }
                if (suma > mejor) mejor = suma;
            }
        }
        return mejor;
    }

    long long quadratic(const std::vector<int>& arr) {
        int n = arr.size();
        long long mejor = LLONG_MIN;
        for (int i = 0; i < n; ++i) {
            long long suma = 0;
            for (int j = i; j < n; ++j) {
                suma += arr[j];
                if (suma > mejor) mejor = suma;
            }
        }
        return mejor;
    }

    long long kadane(const std::vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return 0;
        long long aqui = arr[0];
        long long global = arr[0];
        for (int i = 1; i < n; ++i) {
            aqui = std::max((long long)arr[i], aqui + arr[i]);
            global = std::max(global, aqui);
        }
        return global;
    }

    static std::vector<int> generateRandomArray(int size) {
        static std::mt19937 rng(42);
        std::uniform_int_distribution<int> dist(-100, 100);
        std::vector<int> arr(size);
        for (int i = 0; i < size; ++i) {
            arr[i] = dist(rng);
        }
        return arr;
    }

    template <typename Func>
    static double measureTimeSeconds(Func func, const std::vector<int>& arr) {
        auto start = std::chrono::high_resolution_clock::now();

        volatile long long result = func(arr);
        (void)result;

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start; // Resultado directo en segundos
        return elapsed.count();
    }

    bool verifyCorrectness(int num_tests) {
        std::cout << "VERIFICACION (" << num_tests << " pruebas) \n";
        for (int t = 0; t < num_tests; ++t) {
            int size = 10 + (t % 40);
            auto arr = generateRandomArray(size);

            long long r1 = cubic(arr);
            long long r2 = quadratic(arr);
            long long r3 = kadane(arr);

            if (r1 != r2 || r2 != r3) {
                std::cout << "Discrepancia en test " << t << "\n";
                return false;
            }
        }
        std::cout << "Las 3 soluciones coinciden en todas las pruebas.\n\n";
        return true;
    }

    void runBenchmarksAndExportCSV(const std::string& filename, const std::vector<int>& sizes) {
        std::ofstream csvFile(filename);
        if (!csvFile.is_open()) {
            std::cerr << "Error al crear el archivo " << filename << "\n";
            return;
        }

        // Encabezado CSV adaptado a segundos (s)
        csvFile << "n,cubic_s,cubic_ratio,quad_s,quad_ratio,kadane_s,kadane_ratio\n";

        std::cout << "MEDICIONES Y EXPORTACION A CSV \n";
        std::cout << std::left << std::setw(8) << "n"
                  << std::setw(15) << "Cúbica (s)" << std::setw(10) << "Razón"
                  << std::setw(15) << "Cuadrát. (s)" << std::setw(10) << "Razón"
                  << std::setw(15) << "Kadane (s)" << std::setw(10) << "Razón" << "\n";
        std::cout << std::string(83, '-') << "\n";

        double prev_c = 0.0, prev_q = 0.0, prev_k = 0.0;

        for (int n : sizes) {
            auto arr = generateRandomArray(n);


            double t_c = measureTimeSeconds(cubic, arr);
            double t_q = measureTimeSeconds(quadratic, arr);
            double t_k = measureTimeSeconds(kadane, arr);


            double r_c = (prev_c > 0) ? (t_c / prev_c) : 0.0;
            double r_q = (prev_q > 0) ? (t_q / prev_q) : 0.0;
            double r_k = (prev_k > 0) ? (t_k / prev_k) : 0.0;

            std::cout << std::left << std::setw(8) << n
                      << std::setw(15) << std::fixed << std::setprecision(6) << t_c
                      << std::setw(10) << (r_c > 0 ? std::to_string(r_c).substr(0, 4) : "-")
                      << std::setw(15) << t_q
                      << std::setw(10) << (r_q > 0 ? std::to_string(r_q).substr(0, 4) : "-")
                      << std::setw(15) << t_k
                      << std::setw(10) << (r_k > 0 ? std::to_string(r_k).substr(0, 4) : "-") << "\n";

            csvFile << n << "," << t_c << "," << r_c << ","
                    << t_q << "," << r_q << ","
                    << t_k << "," << r_k << "\n";

            prev_c = t_c;
            prev_q = t_q;
            prev_k = t_k;
        }

        csvFile.close();
        std::cout << "\nResultados guardados exitosamente en: " << filename << "\n\n";
    }

    void testLargeKadane(long long n_size) {
        std::cout << "PRUEBA CON N = " << n_size << " (Kadane) \n";
        auto arr = generateRandomArray(n_size);
        double t_s = measureTimeSeconds(kadane, arr);
        std::cout << "Tiempo real de Kadane: " << std::fixed << std::setprecision(6) << t_s << " segundos.\n\n";
    }

}
