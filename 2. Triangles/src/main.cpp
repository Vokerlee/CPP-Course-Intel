#include "../include/line.hpp"

int main()
{
    std::cout << "Test\n";

    geom::Line kek({1, 1}, (geom::Point){1, 4});

    std::cout << kek;
    return 0;
}