#include <vector>


using uint = unsigned int;

 
class Trellis {

    uint    _n = 0;
    uint    _k = 0;
    uint    _in_cond = 0; // 1 << _k
    uint    _m_max = 0; // max count of cells
    uint    _numb_cond = 0; // 31 > m_max * k  
    uint*   _arr_m = nullptr; // number of cells in a given stream
    uint**  _arr_end = nullptr;
    uint**  _arr_out = nullptr;

    // Ctor
    Trellis() = delete;
    void swap(Trellis& other);
    // Dtor
    ~Trellis() noexcept(true);

    template<typename T>
    bool checkIsMatrixValidity(const std::vector<std::vector<T>>& G_pol8);

    uint findMaxM(const std::vector<std::vector<uint>>& G_pol8);
    uint findNumbOfConditions(const std::vector<std::vector<uint>>& G_pol8);
    void fillTrellis(const std::vector<std::vector<uint>>& G_pol8);
    std::vector<bool> convertPol8ToVect(uint pol8);

public: 
    // Ctor
    explicit Trellis(const std::vector<std::vector<uint>>& G_pol8);
    explicit Trellis(const Trellis& other);
    Trellis& operator=(Trellis other);

    //methods
    void changeCondition(uint& currentCond, uint& curOutput);


};
