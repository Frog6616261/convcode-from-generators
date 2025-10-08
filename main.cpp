#include <cassert>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <cstdint>
//#include "./src/viterbi_conv.cpp"

using arr_1d = std::unique_ptr<uint[]>;


struct S {
    size_t sz = 0;
    std::unique_ptr<std::unique_ptr<uint[]>[]> a = nullptr;

    S() = default;
    S(size_t sz): sz(sz), a(std::make_unique<arr_1d[]>(sz)){

        for (size_t i = 0; i < sz; ++i){
            a[i] = std::make_unique<uint[]>(sz);
        }

        size_t numb = 0;

        for (size_t i = 0; i < sz; ++i){
            for (size_t j = 0; j < sz; ++j){
                a[i][j] = numb;
                numb++;
            }
        }
    }

    void print(){
        for (size_t i = 0; i < sz; ++i){
            for (size_t j = 0; j < sz; ++j){
                std::cout << a[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    S(const S& other): S(other.sz){
        for (size_t i = 0; i < sz; ++i)
            a[i] = std::make_unique<uint[]>(sz);

        for (size_t i = 0; i < sz; ++i)
            for (size_t j = 0; j < sz; ++j)
                a[i][j] = other.a[i][j];
    }

    S& operator=(S other){
        swap(other);

        return *this;
    }

    void swap(S& other){
        std::swap(a, other.a);
        std::swap(sz, other.sz);
    }
};


struct A {
    int* a = nullptr;

    A(){
        a = new int[5]{1};
    }

    A(const A& other): a(other.a){}

};



int main(){

    A l;
    A lc(l);
    std::cout << lc.a[0] << std::endl;

    lc.a[0] = 23;
    std::cout << l.a[0] << std::endl;
    std::cout << lc.a[0] << std::endl;




    

}
