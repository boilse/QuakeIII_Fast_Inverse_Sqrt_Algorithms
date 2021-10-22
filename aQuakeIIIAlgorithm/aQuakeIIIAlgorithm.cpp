#include <iostream>
#include <iomanip>
#include <cmath>

float Q_rsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long*)&y; //Devils bit hack
    i = 0x5f3759df - (i >> 1); //wtf
    y = *(float*)&i;
    y = y * (threehalfs - (x2 * y * y));//1st iteration
//    y = y * (threehalfs - (x2 * y * y));//2nd iteration(can be removed)


    return y;
}

double invsqrtQuake(double number)
{
    double y = number;
    double x2 = y * 0.5;
    std::int64_t i = *(std::int64_t*)&y;
    // The magic number is for doubles is from https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
    i = 0x5fe6eb50c7b537a9 - (i >> 1);
    y = *(double*)&i;
    y = y * (1.5 - (x2 * y * y));   // 1st iteration
   // y  = y * ( 1.5 - ( x2 * y * y ) );   // 2nd iteration, this can be removed
    return y;
}

template <typename T, char iterations = 2> inline T inv_sqrt(T x) {
    static_assert(std::is_floating_point<T>::value, "T must be floating point");
    static_assert(iterations == 1 or iterations == 2, "itarations must equal 1 or 2");
    typedef typename std::conditional<sizeof(T) == 8, std::int64_t, std::int32_t>::type Tint;
    T y = x;
    T x2 = y * 0.5;
    Tint i = *(Tint*)&y;
    i = (sizeof(T) == 8 ? 0x5fe6eb50c7b537a9 : 0x5f3759df) - (i >> 1);
    y = *(T*)&i;
    y = y * (1.5 - (x2 * y * y)); //can be a warning
    if (iterations == 2)
        y = y * (1.5 - (x2 * y * y)); //also warning 
    return y;
}


int main()
{

    
    std::cout
        << std::setprecision(128)
        << Q_rsqrt(300.0F) <<'\n'
       // << 1.0/invsqrtQuake(300.0) << '\n' //double
       // << 1.0/inv_sqrt<double>(300.0) << '\n' //double
        <<  inv_sqrt<float>(300.0F) << '\n'
        << 1.F/sqrt(300.0F);
}
