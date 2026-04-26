#include "../include/trellis.hpp"
#include <cstddef>
#include <algorithm>
#include <iterator>
#include <memory>
#include <exception>
#include <stdexcept>

template <typename T>
const T& check_or_throw(bool condition, const T& value, const char* message) {
    if (!condition) {
        throw std::invalid_argument(message);
    }

    return value;
}


// private
void Trellis::swap(Trellis& other){
    std::swap(_n, other._n);
    std::swap(_k, other._k);
    std::swap(_in_cond, other._in_cond);
    std::swap(_m_max, other._m_max);
    std::swap(_numb_cond, other._numb_cond);
    std::swap(_arr_m, other._arr_m);
    std::swap(_arr_end, other._arr_end);
    std::swap(_arr_out, other._arr_out);
};

// Dtor
Trellis::~Trellis() noexcept(true){
    for(size_t i = 0; i < _numb_cond; ++i){
        delete[] _arr_out[i];
        delete[] _arr_end[i];
    }

    delete[] _arr_end;
    delete[] _arr_out;
    delete[] _arr_m;
};

template<typename T>
bool Trellis::checkIsMatrixValidity(const std::vector<std::vector<T>>& G_pol8){
    //check equal vectors size
    if (!(std::all_of(G_pol8.begin(), G_pol8.end()
            ,[&G_pol8](const std::vector<T>& pol_8_vec){
                return pol_8_vec.size() == G_pol8[0].size();
            })))
        return false;


    //check zeros row and colum
    for(size_t row = 0; row < _k; ++row){
        if (std::all_of((G_pol8[row]).begin(), G_pol8[row].end(), [](const T& pol8){
                return pol8 == 0;
            }))
            return false;
    
        size_t col_special = row;
        bool is_all_zeros = true;
        for (size_t row_special = 0; row_special < _n; ++row_special)
            if (G_pol8[row_special][col_special] != T(0)){
                is_all_zeros = false;
                break;
            }
            
        if (is_all_zeros)
            return false;
    }

    return true;
}

uint  Trellis::findMaxM(const std::vector<std::vector<uint>>& G_pol8){
    uint max = 0;
    uint cur;

    for (size_t row = 0; row < _k; ++row){
        if (G_pol8[row].empty()) continue;

        cur = *std::max_element(G_pol8[row].begin(), G_pol8[row].end());
        
        if (cur > max) max = cur; 
    }
 
    return (max == 1 || max == 0) ? 0 : (convertPol8ToVect(max).size() - 1);
}

uint Trellis::findNumbOfConditions(const std::vector<std::vector<uint>>& G_pol8){
    /**
     * @brief Counts the total number of states of the turbo encoder, **excluding the input bits**, which are counted separately.
     * @param G_pol8 pol matrix
     * @return count of conditions
     */    
    uint cells_numb = 0;

    std::vector<uint>::const_iterator iter_max;

    for (size_t row = 0; row < _k; ++row){
        if (G_pol8[row].empty()) continue;

        iter_max = std::max_element(G_pol8[row].begin(), G_pol8[row].end());
        if (*iter_max != 0 && *iter_max > 1) cells_numb += (convertPol8ToVect(*iter_max).size() - 1);        
    }

    if (cells_numb == 0) return 0;
     
    return (1 << cells_numb);
}

void Trellis::findAllFlowSizes(const std::vector<std::vector<uint>>& G_pol8){
    std::vector<uint>::const_iterator iter_max;
    uint flow_sz;

    for (size_t k_num = 0; k_num < _k; ++k_num){
        if (G_pol8[k_num].empty()) continue;

        iter_max = std::max_element(G_pol8[k_num].begin(), G_pol8[k_num].end()); 
        flow_sz = (convertPol8ToVect(*(iter_max))).size();
        _arr_m[k_num] = (flow_sz == 0  || flow_sz == 1) ? 0 : flow_sz - 1;
    }
}

void Trellis::fillTrellis(const std::vector<std::vector<uint>>& G_pol8){

    // obtain an power matrix D_i
    std::unique_ptr<std::unique_ptr<uint[]>[]> matrix_D = std::make_unique<std::unique_ptr<uint[]>[]>(_m_max);
    size_t num_powers; 

    for (size_t row = 0; row < _k; ++row){
        for (size_t col = 0; col < _n; ++col){
            std::vector<bool> G_bits_vec = convertPol8ToVect(G_pol8[row][col]);
            num_powers = G_bits_vec.size();

            for (uint pow = 0; pow < num_powers; ++pow){
                matrix_D[pow][row] += (G_bits_vec[pow] << pow);
            }
        }
    }

    // create array with ones for current cell cond
    std::unique_ptr<uint[]> ones_symbls_m = std::make_unique<uint[]>(_k);
    uint cur_ones_before = 0;
    uint last_pos_ones = 0;

    for (size_t num_m = 0; num_m < _k; ++num_m){
        ones_symbls_m[num_m] = ((1 << (_arr_m[num_m] + 1 + last_pos_ones)) - 1 ) ^ cur_ones_before; // 1111 000 -> 0111 000
        cur_ones_before += ones_symbls_m[num_m]; // 1000 0000 + 0111 0000
        last_pos_ones += ones_symbls_m[num_m]; // 1 + 3
    }

    // parameter iteration for array filling 1 -> 1000 000 00000 00 ..., 2 -> 0100 000 00000 00 ..., 16 -> 0000 100 00000 00 ...
    for (size_t cur_cond = 0; cur_cond < _numb_cond; ++cur_cond){
        for (size_t cur_in_cond = 0; cur_in_cond < _in_cond; ++cur_in_cond){
            // set current state
            
        
            // find output
            _arr_out[cur_cond][cur_in_cond] = 1; //need algoirithm kerningana

            // find next state
            _arr_end[cur_cond][cur_in_cond] = 1; // use <<
        }
    }
}

std::vector<bool> Trellis::convertPol8ToVect(uint pol8){
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

//public: 
// Ctor
Trellis::Trellis(const std::vector<std::vector<uint>>& G_pol8) try
        : _n        (check_or_throw(G_pol8.at(0).size() >= 0,
                        G_pol8.at(0).size(), "n <= 0"))
        , _k        (check_or_throw(G_pol8.size() >= 0,
                        G_pol8.size(), "k <= 0")) 
        , _in_cond  (check_or_throw(!(checkIsMatrixValidity(G_pol8)),
                        1 << _k, "Invalid matrix: has zero colums or rows, not equal vectors size"))
        , _m_max    (findMaxM(G_pol8))
        , _numb_cond(findNumbOfConditions(G_pol8))
        , _arr_m    (new uint[_k])//new uint[_numb_cond]{0}
        , _arr_end  (new uint*[_numb_cond]{new uint[_in_cond]}) // _k <= 31 new uint*[_numb_cond]{new uint[uint(1<<_k)]{0}}
        , _arr_out  (new uint*[_numb_cond]{new uint[_in_cond]}) {
      
    findAllFlowSizes(G_pol8);
    fillTrellis(G_pol8);

} catch (...) {

}


Trellis::Trellis(const Trellis& other)
        : _n        (other._n)
        , _k        (other._k)
        , _in_cond  (other._in_cond)
        , _m_max    (other._m_max)
        , _numb_cond(other._numb_cond)
        , _arr_m    (new uint[_k])//new uint[_numb_cond]{0}
        , _arr_end  (new uint*[_numb_cond]{new uint[_in_cond]}) // _k <= 31 new uint*[_numb_cond]{new uint[uint(1<<_k)]{0}}
        , _arr_out  (new uint*[_numb_cond]{new uint[_in_cond]}) {
    
    std::copy_n(other._arr_m, _k, _arr_m);

    for (size_t i = 0; i < _numb_cond; ++i){
            std::copy_n(other._arr_end[i], _in_cond, _arr_end[i]);
            std::copy_n(other._arr_out[i], _in_cond, _arr_out[i]);
    }        
}

//error don't copy smart ptr
Trellis& Trellis::operator=(Trellis other){
    swap(other);
    return *this;
}