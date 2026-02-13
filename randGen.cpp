#include <iostream>
#include <set>
#include <random>
#include <fstream>
#include <string>

int main() 
{
    // Sizes to generate
    int N_values[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
    int num_N_values = sizeof(N_values) / sizeof(N_values[0]);

    // Random number generator setup (reuse across files)
    std::random_device rd;
    std::mt19937 gen(rd());
    const int range = 100000000; // 100 million
    std::uniform_int_distribution<int> dis(1, range);

    for (int i = 0; i < num_N_values; ++i) 
    {
        int N = N_values[i];

        // Generate unique random numbers (auto-sorted by set)
        std::set<int> numbers;
        while ((int)numbers.size() < N) 
        {
            numbers.insert(dis(gen));
        }

        // Create filename like: 10_numbers.csv, 100_numbers.csv, ...
        std::string fname = std::to_string(N) + "_numbers.csv";
        std::ofstream writeFile(fname);
        if (!writeFile.is_open()) 
        {
            std::cerr << "Unable to open file for writing: " << fname << std::endl;
            return 1;
        }

        // Write numbers in ascending order
        for (int num : numbers) 
        {
            writeFile << num << "\n";
        }

        writeFile.close();
        std::cout << "Wrote " << N << " numbers to " << fname << std::endl;
    }

    return 0;
}
