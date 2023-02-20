// For vectorisations


// Is an arm platform and supports XM neon instructions

#ifndef  _LIBNUM
#define  _LIBNUM
#include <vector>
#include <math.h>
#include <iostream>
#include <concepts>
#include <string>
#include <stdexcept>
#include <type_traits>


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
        //Reserve something for the solution
        _x.resize(Bdim.first * Bdim.second);
        _A =std::move(A);
        _B =std::move(B);
        this->Adim= std::move(Adim);
        this->Bdim= std::move(Bdim);
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