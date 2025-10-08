#include <cassert>
#include <iostream>
#include <vector>
#include <cstdint>

using uint = unsigned int;

template<typename T>
void print_vec(const std::vector<std::vector<T>>& vec){
    uint k = vec.size();
    std::cout << "-----------------vec-----------------\n";
    for (size_t row = 0; row < k; ++row){
        size_t col_numb = vec[row].size();

        for (size_t col = 0; col < col_numb; ++col) std::cout << vec[row][col] << " ";

        std::cout << "\n";
    }

    std::cout << "-----------------vec-----------------\n";
}

std::vector<bool> convertPol8ToVect(uint pol8){
    std::vector<bool> result;
    if (pol8 == uint(0)) return result;

    while(pol8 != 0){
        uint cur = pol8 % 10;
        pol8 = pol8 /10;

        for(uint i = 0; i < uint(3); ++i){
            result.push_back(cur % 2);
            cur = cur >> 1;
        }
    }

    //delete 0 in end
    for(size_t i = 0; i < size_t(3); ++i){
        if (!(result[result.size() - 1])) result.pop_back();
    }

    return result;
}

uint findNumbOfConditions(const std::vector<std::vector<uint>>& G_pol8){
    uint cells_numb = 0;
    uint _k = G_pol8.size();

    for (size_t row = 0; row < _k; ++row){
        size_t col_numb = G_pol8[row].size();
        uint cur_max_cel_numb = 0;

        for (size_t col = 0; col < col_numb; ++col){
            uint cur_cel_numb = static_cast<uint>(convertPol8ToVect(G_pol8[row][col]).size());

            if (cur_cel_numb != 0 && cur_cel_numb > cur_max_cel_numb) cur_max_cel_numb = cur_cel_numb; 
        }

        cells_numb += cur_max_cel_numb;
    }

    return cells_numb;
}


int main(){
std::vector<std::vector<uint>> G1 = {{1, 2, 3}, {4, 5, 6}, {7, 10, 11}};
std::vector<std::vector<uint>> G2 = {{1, 2, 3}, {4, 5, 6}, {7, 10, 11, 12, 14, 15}};
std::vector<std::vector<uint>> G3 = {{0}, {0}, {0}, {0}};
std::vector<std::vector<uint>> G4 = {{0}, {0}, {0}, {5}};
std::vector<std::vector<uint>> G5 = {{}};
std::vector<std::vector<uint>> G6 = {};
std::vector<std::vector<uint>> G7 = {{23, 45, 123}, {11, 26, 27}, {657, 356, 777}};
std::vector<std::vector<uint>> G8 = {{}, {}, {}, {}, {}, {}, {1, 4, 45}};
std::vector<std::vector<uint>> G9 = {{0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    
assert(findNumbOfConditions(G1) == 9);
assert(findNumbOfConditions(G2) == 9);
assert(findNumbOfConditions(G3) == 0);
assert(findNumbOfConditions(G4) == 3);
assert(findNumbOfConditions(G5) == 0);
assert(findNumbOfConditions(G6) == 0);
assert(findNumbOfConditions(G7) == 21);
assert(findNumbOfConditions(G8) == 6);
assert(findNumbOfConditions(G9) == 0);



}