#include <tuple>
#include <iostream>
#include <array>
#include <utility>
#include "utils.h"
#include <vector>

using std::cout;
using std::endl;
using std::vector;

//check for template args
template <typename T>
struct WhichType;

template <typename T>
void func_whichtype_caller()
{
    WhichType<T> a; //should always fail
}

template <typename T>
class span
{
    public: //public for now to avoid setters and getters
    template<typename U,std::enable_if_t<utils::has_data<U>::val>* = nullptr>
    span(U&& u)
    {
        _data = static_cast<T*>(utils::return_data_ptr(u)); //return data_ptr returns void * that can be cast to T*
        
    }
    template<typename U>
    span(U * data)
    {
        _data = data;
    }
    
    //members:
    T* _data;
    std::size_t size;
};


//takes in a pointer and creates appropriate span object
template <typename T>
auto make_span_object(T data)
{
    //WhichType<typename std::remove_pointer<T>::type> a;
    span<typename std::remove_pointer<T>::type> a(data);
    //span<int> a(data);
    return a;
}

//takes in a container and forwards the data pointer
template <typename T>
auto get_span(T&& container)
{
    return make_span_object(utils::return_data_ptr(container));
}

int main()
{
    vector<int> vec{1,2,3};
    cout << utils::has_data_func(vec) << endl;
    cout << vec.data();
    cout << endl;
    cout << utils::return_data_ptr(vec) <<endl;
    
    cout << "____ SPAN  ____" << endl;
    
    auto x = span<int>(vec);
    
    cout << "the _data pointer for the object should be the .data() of the object passsed in ! \n\n";
    
    cout << x._data << endl;
    
    auto g = get_span(vec);
   
    //auto g = make_span_object(vec.data());
    
    cout << x._data << endl;
    
    cout << &g << " " << &x << endl;
    
    
}
