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
            libnum()=default;
        private:
            std::vector<T> _A;
            std::vector<T> _B;
            std::vector<T> _x;
    };
};
    
#endif //_LIBNUM