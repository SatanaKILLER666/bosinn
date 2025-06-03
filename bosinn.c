functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>

template <typename T>
int findIdx(const std::vector<T>& arr, const T& element);

template <typename T>
int count(const std::vector<T>& arr, const T& element);

template <typename T>
std::string specialize(const T& element);

template <>
std::string specialize<bool>(const bool& element);

#endif

functions.cpp


#include "functions.h"
#include <iostream>
#include <sstream>

template <typename T>
int findIdx(const std::vector<T>& arr, const T& element) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == element)
            return static_cast<int>(i);
    }
    return -1;
}

template <typename T>
int count(const std::vector<T>& arr, const T& element) {
    int cnt = 0;
    for (const auto& el : arr) {
        if (el == element)
            ++cnt;
    }
    return cnt;
}

template <typename T>
std::string specialize(const T& element) {
    std::ostringstream oss;
    oss << element;
    return oss.str();
}

template <>
std::string specialize<bool>(const bool& element) {
    return element ? "true" : "false";
}

template int findIdx<int>(const std::vector<int>&, const int&);
template int findIdx<std::string>(const std::vector<std::string>&, const std::string&);
template int findIdx<bool>(const std::vector<bool>&, const bool&);

template int count<int>(const std::vector<int>&, const int&);
template int count<std::string>(const std::vector<std::string>&, const std::string&);
template int count<bool>(const std::vector<bool>&, const bool&);

template std::string specialize<int>(const int&);
template std::string specialize<std::string>(const std::string&);
template std::string specialize<bool>(const bool&);

int main() {
    std::vector<int> vInt{1, 2, 3, 2, 4, 2};
    std::vector<std::string> vStr{"apple", "banana", "apple", "cherry"};
    std::vector<bool> vBool{true, false, true, true};

    std::cout << "findIdx examples:" << std::endl;
    std::cout << "Index of 2 in vInt: " << findIdx(vInt, 2) << std::endl;
    std::cout << "Index of 'apple' in vStr: " << findIdx(vStr, std::string("apple")) << std::endl;
    std::cout << "Index of false in vBool: " << findIdx(vBool, false) << std::endl;

    std::cout << "\ncount examples:" << std::endl;
    std::cout << "Count of 2 in vInt: " << count(vInt, 2) << std::endl;
    std::cout << "Count of 'apple' in vStr: " << count(vStr, std::string("apple")) << std::endl;
    std::cout << "Count of true in vBool: " << count(vBool, true) << std::endl;

    std::cout << "\nspecialize examples:" << std::endl;
    std::cout << "specialize(123): " << specialize(123) << std::endl;
    std::cout << "specialize(\"hello\"): " << specialize(std::string("hello")) << std::endl;
    std::cout << "specialize(true): " << specialize(true) << std::endl;
    std::cout << "specialize(false): " << specialize(false) << std::endl;

    return 0;
}