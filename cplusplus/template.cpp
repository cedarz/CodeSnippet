/*
 * Contact: zzcedar@126.com
 *    Time: 2015/4/22 17:05:39
 *    File: template.cpp
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

template <typename T, int t>
T func() {
    //
}
template <typename T>
bool compare(const T &a, const T &b) {
    return a <= b;
}
void func(int (*) (const string&, const string&));
void func(int (*) (const int&, const int&));
// 主模板
template<int N>
struct Fib
{
    enum { Result = Fib<N-1>::Result + Fib<N-2>::Result };
};

// 完全特化版
template <>
struct Fib<1>
{
    enum { Result = 1 };
};


// 完全特化版
template <>
struct Fib<0>
{
    enum { Result = 0 };
};

int main() {
    //
    int i = Fib<30>::Result;
    std::cout << i << std::endl;
    cout<<compare(2, 3)<<endl;
    cout<<compare<int>(1,2)<<endl;
    return 0;
}

