#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v{10, 3, 5, 6, 40};

    for (std::vector<int>::iterator it{v.begin()}; it != v.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}