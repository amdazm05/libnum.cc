#ifndef  _LIBNUM
#define  _LIBNUM
#include <vector>
#include <concepts>
#include <type_traits>

namespace mathcc
{
    template <typename T>
    concept _IntegralChk = requires(T type)
    {
        {static_cast<decltype(type)>(type)}->std::integral;
    };
    

    template <class T>
    requires _IntegralChk<T>
    class libnum
    {
        public:
            libnum();
            libnum(std::vector<T> &A,std::vector<T> &B,std::pair<int,int> &Adim, std::pair<int,int> &Bdim);
            libnum(std::initializer_list<T> &&A,std::initializer_list<T> &&B,std::pair<int,int> &&Adim, std::pair<int,int> &&Bdim);
            ~libnum();
        private:
            std::vector<T> _x;
            std::vector<T> _A;
            std::vector<T> _B;

            std::pair<int,int> Adim;
            std::pair<int,int> Bdim;
    };

    template<class T>
    requires _IntegralChk<T>
    libnum<T>::libnum()
    {
        // Default constructor
    }

    template<class T>
    requires _IntegralChk<T>
    libnum<T>::libnum(std::vector<T> &A,std::vector<T> &B,std::pair<int,int> &Adim, std::pair<int,int> &Bdim)
    {
        //Reserve something for the solution
        _x.reserve(Adim.first * Adim.second);
        _A =std::move(A);
        _B =std::move(B);
        this->Adim= std::move(Adim);
        this->Bdim= std::move(Bdim);
    }

    template<class T>
    requires _IntegralChk<T>
    libnum<T>::libnum(std::initializer_list<T> && A,std::initializer_list<T> && B, std::pair<int,int> && Adim, std::pair<int,int> && Bdim)
    {
        // following a Row into column convention 
        // the missing terms have the same size as the vector X that is to be computed
        _x.reserve(Bdim.first * Bdim.second);
        _A = std::move(A);
        _B = std::move(B);

        this->Adim= std::move(Adim);
        this->Bdim= std::move(Bdim);
    }


    template<class T>
    requires _IntegralChk<T>
    libnum<T>::~libnum()
    {
        
    }

    
};
    
#endif //_LIBNUM