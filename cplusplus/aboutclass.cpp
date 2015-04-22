#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class X {
    int i;
    int j;
public:
    X() {//
    }
    X(int _) : j(_), i(j) {}
    void display() {
        cout<<i<<" "<<j<<endl;
        //if(i) throw out_of_range(">>>>0");
    }
};
X s(3);

class GT_cls {
    string::size_type bound;
public:
    GT_cls(size_t val = 0) : bound(val) {}
    bool operator() (const string &s) {
        return s.size() >= bound;
    }
}; 

template<typename InputIterator, class Predicate>
size_t count_ifs(InputIterator begin, InputIterator end, Predicate pred) {
    size_t res = 0;
    for(InputIterator it = begin; it != end; ++it) {
        if(pred(*it)) ++res;
    }
    return res;
}

vector<string> vs(5);
X some;

void plu(int a, double b) {
    cout<<"call int + double"<<endl;
    //return a + int(b);
}

void plu(double a, int b) {
    cout<<"call double + int"<<endl;
    //return int(a) + b;
}

class base {
private:
    int s;
public:
    void basemem();
protected:
    int i;
};

void base::basemem() {
    //
}

struct pub_derived : public base {
    int use_base() {
        return i;
    }
    int use_s() {
        //return s;
    }
};

struct pri_derived : private base {
    int use_base() {
        return i;
    }
};

struct Base {
    void foo(int);
protected:
    int bar;
    double foo_bar;
};

struct derived : public Base {
    void foo(string);
    //bool bar(Base *pb);
    void foobar();
protected:
    string bar;
};

int main() {
    //derived d; d.foo(1024);
    //error
    //plu(2, 2);
    //plu(2.0, 2.0);
    base b;
    pub_derived dp;
    pri_derived dr;
    b.basemem();
    dp.basemem();
    dr.use_base();
    
    plu(2, 2.0);
    plu(2.0, 2);
    X x(2);
    some = X();
    some.display();
    x.display();
    s.display();
    string s;
    int i = 0;
    while(cin>>s && i < 5) {
        if(GT_cls(6)(s)) {
            cout<<s<<" has more than 6 characters."<<endl;
        }
        vs[i] = s;
        i++;
    }
    cout<<count_ifs(vs.begin(), vs.end(), GT_cls(6));
    
    return 0;
}

