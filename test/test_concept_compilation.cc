#include <iostream>
#include <libnum.tpp>

int main()
{
    mathcc::libnum<int> a;
    mathcc::libnum<short> b;
    mathcc::libnum<long long> c;
    mathcc::libnum<char> d;

    mathcc::libnum<int> f({1,2,3,4,5,6},{1,2,3,4,5,6},{2,3},{2,3});

    std::vector<short> A = {1,2,3,4,5,6};
    std::vector<short> B = {1,2,3,4,5,6};
    
    std::pair<int,int> dimA;
    std::pair<int,int> dimB;

    mathcc::libnum<short> e(A,B,dimA,dimB);
    mathcc::libnum<int> g({1,2,3,4,5,6},{1,2,3,4,5,6},{1,2},{1,2});

    return 0;
}
