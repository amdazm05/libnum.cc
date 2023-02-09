#include <iostream>
#include <libnum.tpp>

int main()
{
    mathcc::libnum<int> a;
    mathcc::libnum<short> b;
    mathcc::libnum<long long> c;
    mathcc::libnum<char> d;

    mathcc::libnum<int> f({1,2,3,4,5,6},{1,2,3,4,5,6},{2,3},{2,3});
    return 0;
}