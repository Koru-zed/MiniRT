#include <string>
#include <iostream>

int main()
{
    std::string str = "hamid";
    std::string& R = str;

    std::cout <<"str -> " <<str << "address -> "<< &str  << std::endl;
    std::cout<< "R -> "  << R << "address -> "<< &R <<std::endl; 
    str += " howa lmadani";

    std::cout <<"str -> " <<str << "address -> "<< &str  << std::endl;
    std::cout<< "R -> "  << R << "address -> "<< &R <<std::endl; 
    // free(str);

}