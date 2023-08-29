#include <iostream>
#include "DoubleLinkedList.h"

int main()
{
    DoubleLinkedList Integers;

    for (int i = 0; i <= 10; ++i)
        Integers.PushFront(i);

    /*for (auto i = Integers.Begin(); i != Integers.End(); i++)
        std::cout << *i << std::endl;*/

    Integers.PushAt(343, 1);

    for (auto i = Integers.Begin(); i != Integers.End(); i++)
        std::cout << *i << std::endl;

    std::cout << '\n';
    Integers.PullFront();

    for (auto i = Integers.Begin(); i != Integers.End(); i++)
        std::cout << *i << std::endl;
}
