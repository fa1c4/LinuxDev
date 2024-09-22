#include <string>
#include <tuple>
#include <iostream>


template<typename... Targs>
void param_pack_demo(Targs... Fargs) {
    const int length = sizeof...(Targs);
    std::cout << "total args: " << length << std::endl;
    int res[length] = {Fargs...};

    float mAvg = 0.0;
    for (int i = 0; i < length; ++i) {
        mAvg += res[i];
        // std::cout << res[i] << ", ";
    }
    std::cout << std::endl;
    mAvg = mAvg / length;
    std::cout << "Average is: " << mAvg << std::endl;
}


int main(int argc, char* argv[]) {
    std::cout << "param_pack_demo(1, 2, 3, 4)" << " ";
    param_pack_demo(1, 2, 3, 4);

    std::cout << "param_pack_demo(1, 2, 3, 4, 5, 6, 7, 8, 9)" << " ";
    param_pack_demo(1, 2, 3, 4, 5, 6, 7, 8, 9);

    return 0;
}
