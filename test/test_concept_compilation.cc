#include <iostream>
#include <vector>
#include <algorithm>
#include <libnum.tpp>

int main()
{
    mathcc::libnum<int> a;
    mathcc::libnum<short> b;
    mathcc::libnum<long long> c;
    mathcc::libnum<char> d;

    mathcc::libnum<int> f({1,2,3,4,5,6},{1,2,3,4,5,6},{2,3},{2,3});
    mathcc::libnum<double> dflt;
    mathcc::libnum<double> dflti({1.1,1.2,1.5,1.7},{1.4,1.5},{2,2},{2,1});

    mathcc::libnum<float> fflt;
    mathcc::libnum<float> fflti({1.1,1.2,1.5,1.7},{1.4,1.5},{2,2},{2,1});

    std::vector<short> A = {1,2,3,4,5,6};
    std::vector<short> B = {1,2,3,4,5,6};


    mathcc::libnum<short> e(A,B,{1,3},{1,3});
    mathcc::libnum<int> g({1,2,3,4,5,6},{1,2,3,4,5,6},{1,2},{1,2});
    mathcc::libnum<int> h({1,2,6,4},{5,13},{2,2},{2,1});
    std::vector<int> sol = h.solve();
    std::for_each(sol.begin(),sol.end(),[](int i){std::cout<<i<<" "<<std::endl;});
    return 0;
}
