// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>

// enum t_size{
//     S;
//     M;
//     L;
// }

int _comp(std::string s1, std::string s2)
{
    int a[2],b[2];
    int i = 0;
    while  (s1[i] == 'X')   
        i++;
    a[0] = i;
    i = 0;
    while  (s2[i] == 'X')   
        i++;
    b[0] = i;
    if (s1[a[0]] == 'S')
        a[1] = 1;
    else if (s1[a[0]] == 'M')
        a[1] = 2;
    else if (s1[a[0]] == 'L')
        a[1] = 3;
    if (s2[b[0]] == 'S')
        b[1] = 1;
    else if (s2[b[0]] == 'M')
        b[1] = 2;
    else if (s2[b[0]] == 'L')
        b[1] = 3;
    if (a[1] > b[1])
        return 1;
    else if (a[1] < b[1])
        return -1;
    else if (a[1] == b [1])
    {
        if (a[0] > b[0])
            return 1;
        else if (a[0] < b[0])
            return -1;
    }
    return 0;
}   

int main() {
 
    int i,n;
    std::string s; 
    std::cin >> n;
    n *= 2;
    std::string arr[n];
    for  (i= 0; i < n ; i++){
        std::cin >> s;
        arr[i] = s;
    }
    for (i = 0; i< n ; i++)
    {
        int b = _comp(arr[i], arr[i + 1]);
        if ( b > 0)
            std::cout << ">" << std::endl;
        else if (b < 0)
            std::cout << "<" << std::endl;
        else if (!b)
            std::cout << "=" << std::endl;
        i++;
    }

    return 0;
}