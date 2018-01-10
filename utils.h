#include <iostream>
#include <type_traits>
#include <utility>

namespace utils{


template <typename T,typename = void>
struct has_data
{
    static const bool val = 0;
};

template <typename T>
struct has_data<T,std::void_t<decltype(std::declval<T>().data())>>
{
    static const bool val = 1;
};

template <typename T>
bool has_data_func(T a)
{
    static_cast<void>(a);
    return has_data<T>::val;
}

template <typename T>
auto return_data_ptr(T&& a)
{
    static_cast<void>(a);
    if(has_data<T>::val)
    {
        return a.data();
    }
}
} // utils
