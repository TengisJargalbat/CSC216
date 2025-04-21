#include <iostream>
#include <random>
#include <vector>
#include <iomanip>

int main() {
    std::vector<int> n_list = { 100, 500, 1000, 5000, 10000 };
    std::vector<double> p_list = { 0.25, 0.50, 0.75 };
    int m = 10;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "n,trial,p,heads\n";
    std::cout << std::fixed << std::setprecision(2);

    for (int n : n_list) {
        for (double p : p_list) {
            std::binomial_distribution<int> dist(n, p);

            for (int trial = 1; trial <= m; ++trial) {
                int heads = dist(gen);
                std::cout
                    << n << ','
                    << trial << ','
                    << p << ','
                    << heads << '\n';
            }
        }
    }

    return 0;
}
