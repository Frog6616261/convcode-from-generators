#include <vector>
#include <cstring>

#include "trellis.hpp"


class ConvCode {
public:
    //enum classes
    //Enum classes
    enum class Algorithm : int;

private:
    uint _n = 0;
    uint _k = 0;

    std::vector<std::vector<uint>> _G_pol8;

    //Constructors
    ConvCode() = delete;
    void swap(ConvCode&);

    //Destructors
    ~ConvCode() = default;


    //algo funcs
    void createTrellis();
    void doBLAST();
    void doFAST();
    void doHARD();
    void doSOFT();
    void doQUANTIZE();

public:
    Algorithm _deco_algo = Algorithm(0);

    //Constructors
    explicit ConvCode(const std::vector<std::vector<uint>>& G_pol8, Algorithm decoded_algorithm);
    explicit ConvCode(const ConvCode&);
    ConvCode& operator=(ConvCode);
    

    //methods
    std::vector<bool> encode(const std::vector<bool>& in_bits);
    std::vector<bool> decode(const std::vector<bool>& in_bits);
    std::vector<bool> decode(const std::vector<double>& in_symb);
    void print_trellis();
    void print_all_trellis();    
};


