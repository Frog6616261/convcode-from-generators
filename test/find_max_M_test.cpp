#include <cassert>
#include <iostream>
#include <vector>
#include <cstdint>

using uint = unsigned int;

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


uint  findMaxM(const std::vector<std::vector<uint>>& G_pol8){
    uint _k = G_pol8.size();
    uint maxM = 0;

    for (size_t row = 0; row < _k; ++row){
        size_t col_numb = G_pol8[row].size();

        for (size_t col = 0; col < col_numb; ++col){
            uint cur_deg = static_cast<uint>(convertPol8ToVect(G_pol8[row][col]).size());
            std::cout << row << " " << col << "  " << G_pol8[row][col] << " " << cur_deg <<"\n";


            if (cur_deg != 0 && cur_deg > maxM) maxM = cur_deg; 
        }
    }

    return maxM;
}

int main(){

    std::vector<std::vector<uint>> G1 = {{123, 34, 1},{24, 0, 1},{15, 35, 0}};
    std::vector<std::vector<uint>> G2 = {{1, 1, 1},{1, 1, 1, 1, 1}};
    std::vector<std::vector<uint>> G3 = {{0, 0, 0},{0, 0, 0, 0, 0, 0}};
    std::vector<std::vector<uint>> G4 = {{123, 34, 1},{24, 0, 1},{15, 35, 0}};
    std::vector<std::vector<uint>> G5 = {{1}, {1}, {1}, {1}, {1}};
    std::vector<std::vector<uint>> G6 = {{}, {}, {}, {}, {}};
    std::vector<std::vector<uint>> G7 = {{}, {}, {}, {}, {0, 0, 0, 1}};
    std::vector<std::vector<uint>> G8 = {};
    std::vector<std::vector<uint>> G9 = {{1}};
    std::vector<std::vector<uint>> G10 = {{1}, {2}, {3}, {0}, {0}, {7}};
    std::vector<std::vector<uint>> G11 = {{56, 56, 56, 56}, {56, 56, 56, 56}, {56, 56, 56, 56}, {56, 56, 56, 56}, {56, 56, 56, 56}};
    std::vector<std::vector<uint>> G12 = {{0}, {56, 56, 56, 56, 1, 2, 3, 654, 4, 4, 4}, {17}, {56, 56, 0, 203, 5, 6, 124}, {56, 2, 56, 1}};


    assert(findMaxM(G1) == 7);
    std::cout << "--------------------\n";
    assert(findMaxM(G2) == 1);
    std::cout << "--------------------\n";
    assert(findMaxM(G3) == 0);
    std::cout << "--------------------\n";
    assert(findMaxM(G4) == 7);
    std::cout << "--------------------\n";
    assert(findMaxM(G5) == 1);
    std::cout << "--------------------\n";
    assert(findMaxM(G6) == 0);
    std::cout << "--------------------\n";
    assert(findMaxM(G7) == 1);
    std::cout << "--------------------\n";
    assert(findMaxM(G8) == 0);
    std::cout << "--------------------\n";
    assert(findMaxM(G9) == 1);
    std::cout << "--------------------\n";
    assert(findMaxM(G10) == 3);
    std::cout << "--------------------\n";
    assert(findMaxM(G11) == 6);
    std::cout << "--------------------\n";
    assert(findMaxM(G12) == 9);

    



}
