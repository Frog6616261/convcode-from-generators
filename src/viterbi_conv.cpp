#include "../include/viterbi_conv.hpp"

#define vcc ViterbiConvCode

//Ctor
vcc::vcc(const std::vector<std::vector<uint>>& G_pol8, Algorithm decode_algorithm):
          _n((G_pol8.at(0)).size())
        , _k(G_pol8.size())
        , _G_pol8(G_pol8)
        , _deco_algo(decode_algorithm) {}

vcc::vcc(const vcc& other)
        : vcc::vcc(other._G_pol8, other._deco_algo) {}

vcc& vcc::operator=(vcc other){
    vcc::swap(other);

    return *this;
}

void vcc::swap(vcc& other){
    std::swap(_n, other._n);
    std::swap(_k, other._k);
    std::swap(_G_pol8, other._G_pol8);
    std::swap(_deco_algo, other._deco_algo);
}

//Dtor



//private methods
void vcc::createTrellis(){

}

void vcc::doBLAST(){

}

void vcc::doFAST(){

}

void vcc::doHARD(){

}

//pub methods
std::vector<bool> vcc::encode(const std::vector<bool>& in_bits){

}

std::vector<bool> vcc::decode(const std::vector<bool>& in_bits){

}

std::vector<bool> vcc::decode(const std::vector<double>& in_symb){

}

void vcc::print_trellis(){

}

void vcc::print_all_trellis(){

}

//enum classes
enum class vcc::Algorithm : int {
    HARD = 0,
    SOFT = 1,
    QUANTIZE = 2
};




