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

void doConvolToVect(uint pol8){
    std::vector<bool> v_a = convertPol8ToVect(pol8);
    std::cout << size_t(pol8) << ":  ";
    for(size_t i = 0; i < v_a.size(); ++i)
        std::cout << v_a[i];
    std::cout << "  vec_size:" << v_a.size();
    std::cout << "\n";
}


int main(){

    doConvolToVect(0);
    doConvolToVect(1);
    doConvolToVect(2);
    doConvolToVect(3);
    doConvolToVect(4);
    doConvolToVect(5);
    doConvolToVect(6);
    doConvolToVect(7);
    doConvolToVect(71);
    doConvolToVect(47);
    doConvolToVect(14);
    doConvolToVect(26);
    doConvolToVect(563);
    doConvolToVect(123);
    doConvolToVect(56);
    doConvolToVect(654);


}
