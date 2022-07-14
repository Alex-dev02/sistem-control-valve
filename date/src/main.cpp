#include "date.hpp"

int main()
{
    Date D;
    Date D2(50,1,2020);
    std::cout<<D.isValid()<<"\n";
    std::cout<<D2.isValid()<<"\n";

return 0;
}