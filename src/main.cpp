#include <iostream>
#include <type_traits>
#include <list>
#include <vector>
#include <tuple>
#include <string>
#include <type_traits.h>


template<typename T>
static std::enable_if_t<std::is_integral_v<T>,void> printIP(T t){

    static const size_t constexpr SizeInOctets = sizeof(T);
    for (size_t i = SizeInOctets; i--;)
    {
        std::cout << (t >> (i << 3) & 0xFF);
        if (i > 0)
            std::cout << ".";
    }
    std::cout << std::endl;
}

template<typename T>
std::enable_if_t<is_string_v<T>, void> printIP(T t){
    std::cout<< t <<std::endl;
}

template<typename T>
std::enable_if_t<is_container_v<T>,void> printIP(T t)
{   
    for(auto it = t.begin(); it != t.end(); ++it)
    {
        std::cout<<*it;
        if (it != std::prev(t.end()))
            std::cout<<".";
    }
    std::cout<<std::endl;
}

/*template<typename... Args>
void printIP(std::tuple<Args...> T)
{
    bool i = 0;
    std::apply([&i](auto&&... args) {(((i == 0 ? std::cout << args : std::cout << "." << args), i = 1), ...);}, T);    
    std::cout<<std::endl;
}
*/
template <typename ...Args>
std::enable_if_t<is_all_of_v<Args...>, void>
printIP(std::tuple<Args...> T)
{
    bool i = 0;
    std::apply([&i](auto&&... args) {(((i == 0 ? std::cout << args : std::cout << "." << args), i = 1), ...);}, T);    
    std::cout<<std::endl;
}

int main()
{
    printIP(static_cast<char>(-1));
    printIP(static_cast<short>(0));
    printIP(static_cast<int>(2130706433));
    printIP(static_cast<long>(8875824491850138409));
    printIP(std::string{"185.110.56.0"});
    printIP(std::vector<int>{185,110,56,0});
    printIP(std::list<int>{185,110,56,0});
    printIP(std::tuple<int,int,int,int>{185,110,56,0});
    

    return 0;
}

