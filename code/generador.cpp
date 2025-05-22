#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <random>
#include <algorithm>

enum class Pattern {RANDOM, ASCENDING, DESCENDING, PARTIALLY_SORTED};

void generate(const std::string& filename, size_t num_integers, Pattern pattern) {
    std::vector<int32_t> data(num_integers);
    std::mt19937 rng(42);
    //std::uniform_int_distribution<int32_t> dist(0, 1000);
    std::uniform_int_distribution<int32_t> dist(INT32_MIN, INT32_MAX);

    for(size_t i = 0; i < num_integers; ++i){
        data[i] = dist(rng);
    }

    switch(pattern){
        case Pattern::ASCENDING:
            std::sort(data.begin(), data.end());
            break;
        case Pattern::DESCENDING:
            std::sort(data.begin(), data.end(), std::greater<>());
            break;
        case Pattern::PARTIALLY_SORTED:{
            size_t sorted_size = num_integers * 90 / 100;
            std::sort(data.begin(), data.begin() + sorted_size);
            break;
        }
        case Pattern::RANDOM:
            break;
    }

    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    out.write(reinterpret_cast<const char*>(data.data()), num_integers * sizeof(int32_t));
    std::cout << "File generated: " << filename << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <size_in_MB>" << std::endl;
        return 1;
    }
    const size_t MB = atoi(argv[1]);
    size_t num_integers = MB * 1024 * 1024 / sizeof(int32_t);

    generate("aleatorio_" + std::to_string(MB) + "MB.bin", num_integers, Pattern::RANDOM);
    generate("ascendente_" + std::to_string(MB) + "MB.bin", num_integers, Pattern::ASCENDING);
    generate("descendente_" + std::to_string(MB) + "MB.bin", num_integers, Pattern::DESCENDING);
    generate("parcialmente_ordenado_" + std::to_string(MB) + "MB.bin", num_integers, Pattern::PARTIALLY_SORTED);

    return 0;
}