#ifndef  _LIBNUM
#define  _LIBNUM

#include <vector>
#include <math.h>
#include <iostream>
#include <concepts>
#include <string>
#include <stdexcept>
#include <type_traits>
#include <algorithm>

#if defined __MMX__ && defined __SSE__
    #include <immintrin.h>
#else
    #warning "System does not have any vector instructions (SSE and MMX instructions x86)"
#endif

#ifdef _XM_ARM_NEON_INTRINSICS_
    // Add neon includes
    #include <arm_neon.h>
#else
    #warning "System does not have any vector instructions (ARM Neon)"
#endif

template <typename T>
concept _IntegralChk = requires(T type)
{
    {static_cast<decltype(type)>(type)}->std::integral;
};

template <typename T>
concept _FloatingPointChk = requires(T type)
{
    {static_cast<decltype(type)>(type)}->std::floating_point;
};

namespace conversion_utils
{
    template<typename T>
    requires _IntegralChk<T>
    inline float _convert_integeral_to_float(T && a)
    {
        return std::move(a); 
    }

    template<typename T>
    requires _IntegralChk<T>
    inline double _convert_integeral_to_double(T && a)
    {
        return std::move(a); 
    }

}
namespace mathcc
{
    enum Solvers :  uint8_t 
    {
        LU_DECOMPOSITION,
        GAUSIAN_ELIMINATION,
        CHOLESKY_METHOD,
        GAUS_JORDAN,
        MATRIX_INVERSION
    };
    
    template <class T>
    requires _IntegralChk<T> || _FloatingPointChk<T>
    class libnum
    {
        public:
            libnum();
            libnum(std::vector<T> &A,std::vector<T> &B,std::pair<int,int> &&Adim, std::pair<int,int> &&Bdim);
            libnum(std::initializer_list<T> &&A,std::initializer_list<T> &&B,std::pair<int,int> &&Adim, std::pair<int,int> &&Bdim);
            std::vector<T> solve();
            std::vector<T> solve_vectorised();
            std::vector<T> solve(std::uint8_t solver);

            ~libnum();
        private:
            std::vector<T> _x;
            std::vector<T> _A;
            std::vector<T> _B;

            std::vector<float> _xC4;
            std::vector<float> _AC4;
            std::vector<float> _BC4;

            std::vector<double> _xC8;
            std::vector<double> _AC8;
            std::vector<double> _BC8;

            std::pair<int,int> Adim;
            std::pair<int,int> Bdim;
    };

    template<class T>
    requires _IntegralChk<T> || _FloatingPointChk<T>
    libnum<T>::libnum()
    {
        // Default constructor
    }

    template<class T>
    requires _IntegralChk<T> || _FloatingPointChk<T>
    libnum<T>::libnum(std::vector<T> &A,std::vector<T> &B,std::pair<int,int> &&Adim, std::pair<int,int> &&Bdim)
    {
        // Check for square matrix 
        if(Adim.first != Adim.second)
        {
            throw std::invalid_argument("\"A\" should be a square matrix for a solution to exist");
        }

        else
        {
            if constexpr (std::is_integral<T>::value && sizeof(T)<=4)
            {
                _xC4.resize(Bdim.first * Bdim.second);
                _AC4.reserve(Adim.first * Adim.second);
                _BC4.reserve(Bdim.first * Bdim.second);
                std::transform(std::make_move_iterator(A.begin()),std::make_move_iterator(A.end()),std::back_inserter(_AC4), &conversion_utils::_convert_integeral_to_float<T>);
                std::transform(std::make_move_iterator(B.begin()),std::make_move_iterator(B.end()),std::back_inserter(_BC4), &conversion_utils::_convert_integeral_to_float<T>);
                _A =std::move(A);
                _B =std::move(B);
            }
            else if (std::is_integral<T>::value && sizeof(T)>4)
            {
                _xC8.resize(Bdim.first * Bdim.second);
                _AC8.reserve(Adim.first * Adim.second);
                _BC8.reserve(Bdim.first * Bdim.second);
                std::transform(std::make_move_iterator(A.begin()),std::make_move_iterator(A.end()),std::back_inserter(_AC8), &conversion_utils::_convert_integeral_to_double<T>);
                std::transform(std::make_move_iterator(B.begin()),std::make_move_iterator(B.end()),std::back_inserter(_BC8), &conversion_utils::_convert_integeral_to_double<T>);
                _A =std::move(A);
                _B =std::move(B);
            }
            else if (std::is_floating_point<T>::value)
            {
                //Reserve something for the solution
                _x.resize(Bdim.first * Bdim.second);
                _A =std::move(A);
                _B =std::move(B);
                this->Adim= std::move(Adim);
                this->Bdim= std::move(Bdim);
            }

            else
            {
                // Pretty much never the case here
                // put placing for the case of completeness
            }
        }
        
            
    }

    template<class T>
    requires _IntegralChk<T> || _FloatingPointChk<T>
    libnum<T>::libnum(std::initializer_list<T> && A,std::initializer_list<T> && B, std::pair<int,int> && Adim, std::pair<int,int> && Bdim)
    {
        // Check for square matrix 
        if(Adim.first != Adim.second)
        {
            throw std::invalid_argument("\"A\" should be a square matrix for a solution to exist");
        }
        // following a Row into column convention 
        // the missing terms have the same size as the vector X that is to be computed
        _x.resize(Bdim.first * Bdim.second);
        _A = std::move(A);
        _B = std::move(B);

        this->Adim= std::move(Adim);
        this->Bdim= std::move(Bdim);
    }

    template<class T>
    requires _IntegralChk<T> || _FloatingPointChk<T>
    std::vector<T> libnum<T>::solve()
    {
        if (Adim.second != Bdim.first)
        {
            throw std::invalid_argument("Invalid dimensions: A has " + std::to_string(Adim.second) + " columns, B has " + std::to_string(Bdim.first) + " rows");
        }
        // Solve the linear equation using Gaussian elimination
        for (int i = 0; i < Adim.second; i++)
        {
            // Find the row with the largest absolute value in column i
            int maxRow = i;
            double maxValue = std::abs(_A[i * Adim.second + i]);
            for (int j = i + 1; j < Adim.first; j++)
            {
                double value = std::abs(_A[j * Adim.second + i]);
                if (value > maxValue)
                {
                    maxRow = j;
                    maxValue = value;
                }
            }

            // Swap the current row with the row with the largest absolute value
            if (maxRow != i)
            {
                for (int j = 0; j < Adim.second; j++)
                {
                    std::swap(_A[i * Adim.second + j], _A[maxRow * Adim.second + j]);
                }
                std::swap(_B[i], _B[maxRow]);
            }

            // Eliminate the elements below the current row in column i
            for (int j = i + 1; j < Adim.first; j++)
            {
                double factor = _A[j * Adim.second + i] / _A[i * Adim.second + i];
                for (int k = i + 1; k < Adim.second; k++)
                {
                    _A[j * Adim.second + k] -= factor * _A[i * Adim.second + k];
                }
                _B[j] -= factor * _B[i];
            }
        }

        // Back-substitute to solve for the elements of _x
        for (int i = Adim.second - 1; i >= 0; i--)
        {
            double sum = 0;
            for (int j = i + 1; j < Adim.second; j++)
            {
                sum += _A[i * Adim.second + j] * _x[j];
            }
            _x[i] = (_B[i] - sum) / _A[i * Adim.second + i];
        }
        return _x;
    }

    template<class T>
    requires _IntegralChk<T> || _FloatingPointChk<T>
    std::vector<T> libnum<T>::solve_vectorised()
    {
        // Solve using x86 intrinsics
        #if defined __MMX__ && defined __SSE__
        if(Adim.first > 4)
        {
            //32 bytes 
            __m256 A_vals_avx_;

            for(int i = 0 ; i < Adim.second; i+=8)
            {
                
            }
        }

        else
        {
            // 16 bytes 
            __m128 A_vals_avx_;
            __m128 A_vals_avx_tmp;
            __m128 A_vals_prev_row;

            for(int i = 0 ; i <(Adim.first * Adim.second); i+=4)
            {
                A_vals_avx_ = _mm_load_ps((float_t*)(&_A[i]));
                A_vals_avx_tmp = A_vals_avx_;
                for (int j = i+1; j < Adim.first*Adim.second ; j+=1)
                {
                    double scalar_mul = -(_A[((i+j)*Adim.second)])/(_A[(i)*(Adim.second)]);
                    __m128 scalar_v = _mm_set1_ps(scalar_mul);
                    A_vals_avx_tmp =_mm_mul_ps(A_vals_avx_, scalar_v);
                    A_vals_prev_row = _mm_load_ps((float_t*)&_A[((i+j)*Adim.second)]);
                    A_vals_prev_row = _mm_add_ps(A_vals_avx_tmp,A_vals_prev_row);
                    _mm_storeu_si32(&_A[((i+j)*Adim.second)], (__m128i)A_vals_prev_row);
                }
            }
        }
            
        #endif 
        return _x;
    }

    template<class T>
    requires _IntegralChk<T> || _FloatingPointChk<T>
    libnum<T>::~libnum()
    {
        
    }

    
};
    
#endif //_LIBNUM