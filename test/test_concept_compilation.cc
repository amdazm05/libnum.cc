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

    mathcc::libnum<int> f({1,2,3,4,5,6},{1,2,3,4,5,6},{2,2},{2,3});
    mathcc::libnum<double> dflt;
    mathcc::libnum<double> dflti({1.1,1.2,1.5,1.7},{1.4,1.5},{2,2},{2,1});

    mathcc::libnum<float> fflt;
    mathcc::libnum<float> fflti({1.1,1.2,1.5,1.7},{1.4,1.5},{2,2},{2,1});

    std::vector<short> A = {1,2,3,4,5,6};
    std::vector<short> B = {1,2,3,4,5,6};

    std::cout<<"INTEGERAL POINT RESULTS"<<std::endl;
    mathcc::libnum<short> e(A,B,{3,3},{1,3});
    mathcc::libnum<int> g({1,2,3,4,5,6},{1,2,3,4,5,6},{2,2},{1,2});
    mathcc::libnum<int> h({1,2,6,4},{5,13},{2,2},{2,1});
    std::vector<int> sol = h.solve();
    std::for_each(sol.begin(),sol.end(),[](int i){std::cout<<i<<" "<<std::endl;});
    
    std::vector<uint64_t> A1 = {1,2,3,4,5,6};
    std::vector<uint64_t> B2 = {1,2,3,4,5,6};
    mathcc::libnum<uint64_t> e1(A1,B2,{3,3},{1,3});

    std::cout<<"FLOATING POINT RESULTS"<<std::endl;
    mathcc::libnum<float> hf({1,2,6,4},{5,13},{2,2},{2,1});
    std::vector<float> solf = hf.solve();
    std::for_each(solf.begin(),solf.end(),[](float i){std::cout<<i<<" "<<std::endl;});

    mathcc::libnum<int> h1({1,2,6,4,5,4,5,3,4,2,1,7,8,9,0,12},{5,13,12,11},{4,4},{4,1});
    h1.solve_vectorised();
    return 0;
}
