#include "../include/conv_code.hpp"


//Ctor
ConvCode::ConvCode(const std::vector<std::vector<uint>>& G_pol8, Algorithm decode_algorithm):
          _n((G_pol8.at(0)).size())
        , _k(G_pol8.size())
        , _G_pol8(G_pol8)
        , _deco_algo(decode_algorithm) {}

ConvCode::ConvCode(const ConvCode& other)
        : ConvCode::ConvCode(other._G_pol8, other._deco_algo) {}

ConvCode& ConvCode::operator=(ConvCode other){
    ConvCode::swap(other);

    return *this;
}

void ConvCode::swap(ConvCode& other){
    std::swap(_n, other._n);
    std::swap(_k, other._k);
    std::swap(_G_pol8, other._G_pol8);
    std::swap(_deco_algo, other._deco_algo);
}

//Dtor



//private methods
void ConvCode::createTrellis(){

}

void ConvCode::doBLAST(){

}

void ConvCode::doFAST(){

}

void ConvCode::doHARD(){

}

//pub methods
std::vector<bool> ConvCode::encode(const std::vector<bool>& in_bits){

}

std::vector<bool> ConvCode::decode(const std::vector<bool>& in_bits){

}

std::vector<bool> ConvCode::decode(const std::vector<double>& in_symb){

}

void ConvCode::print_trellis(){

}

void ConvCode::print_all_trellis(){

}

//enum classes
enum class ConvCode::Algorithm : int {
    HARD = 0,
    SOFT = 1,
    QUANTIZE = 2
};




