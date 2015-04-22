#include <iostream>
#include <cstdio>

using namespace std;

template <typename T> 
class ArrayList{
    private:
        const static int SIZE = 128;
        int length;
        int capacity;
        T   *data;
    public:
        //ArrayList() {
            //cout<<"default constructor..."<<endl;
        //}
        ArrayList(int len = 0) {
            length = 0;
            capacity = SIZE;
            cout<<"constructor with default parameter..."<<endl; 
            data = new T[SIZE];
        }
};


int main() {
    ArrayList<int> aList;
    return 0;
}
