#include <iostream>
#include <string>
#include <map>

#include "MyAllocator.h"
#include "DynamicPoolStrategy.h"
#include "FixedPoolStrategy.h"
#include "LinkedList.h"

namespace Homework {

    int factorial(int number) {
        if (number == 0) {
            return 1;
        }
        int result = 1;
        for (int i = 1; i <= number; ++i) {
            result *= i;
        }
        return result;
    }

    template<class Map> 
    void printMap(Map map) {
        for (int i = 0; i < map.size(); ++i) {
            std::cout << i << ' ' << map[i] << std::endl;
        }
    }
}

int main() {
    const std::size_t numberOfElements = 10;

    std::cout << "A map with a default allocator.\n" << std::endl;
    {
        std::map<int, int> map;
        for (int i = 0; i < numberOfElements; ++i) {
            map[i] = Homework::factorial(i);
        }
        Homework::printMap(map);
    }
    std::cout << "\nA map with a custom allocator (with a fixed number of elements).\n" << std::endl;
    {
        using Allocator = Homework::MyAllocator<std::pair<const int, int>, numberOfElements, Homework::FixedPoolStrategy>;

        std::map<int, int, std::less<int>, Allocator> map;
        
        for (int i = 0; i < numberOfElements; ++i) {
            map[i] = Homework::factorial(i);
        }

        Homework::printMap(map);
    }
    std::cout << "\nA map with a custom allocator (with a variable number of elements).\n" << std::endl;
    {
        const std::size_t initPoolSize = 4; //the pool size is less than numberOfElements
        using Allocator = Homework::MyAllocator<std::pair<const int, int>, initPoolSize, Homework::DynamicPoolStrategy>;
        
        std::map<int, int, std::less<int>, Allocator> map;
        
        for (int i = 0; i < numberOfElements; ++i) {
            map[i] = Homework::factorial(i);
        }

        Homework::printMap(map);
    }
    std::cout << "\nA custom linked list with a custom allocator (with a fixed number of elements).\n" << std::endl;
    {
        using Allocator = Homework::MyAllocator<int, numberOfElements, Homework::FixedPoolStrategy>;
        Homework::LinkedList<int, Allocator> list;
        for (int i = 0; i < numberOfElements; ++i) {
            list.add(Homework::factorial(i));
        }

        //print all values
        for (auto value : list) {
            std::cout << value << std::endl;
        }
    }

    std::cout << "\nA custom linked list with a custom allocator (with a variable number of elements).\n" << std::endl;
    {
        const std::size_t initPoolSize = 4; //the pool size is less than numberOfElements
        using Allocator = Homework::MyAllocator<int, initPoolSize, Homework::DynamicPoolStrategy>;
        Homework::LinkedList<int, Allocator> list;
        for (int i = 0; i < numberOfElements; ++i) {
            list.add(Homework::factorial(i));
        }

        //print all values
        for (auto value : list) {
            std::cout << value << std::endl;
        }
    }
    return 0;
}