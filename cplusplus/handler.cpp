//c++ primer, about class
/*
 * Contact: zzcedar@126.com
 *    Time: 2015/4/22 14:04:17
 *    File: handler.cpp
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <stdexcept>
#include <set>

using namespace std;
class Item_base;

class Item_base {
private:
    string isbn;
public:
    string book() const {
        return isbn;
    }
    
    virtual Item_base* clone() const {
        return new Item_base(*this);
    }
};
class Sales_item {
public:
    Sales_item() : p(0), use(new std::size_t(1)) {}
    Sales_item(const Item_base& item) :  p(item.clone()), use(new std::size_t(1)) {
        
    }
    Sales_item(const Sales_item &i) : p(i.p), use(i.use) {
        ++*use;
    }
    ~Sales_item() {
        decr_use();
    }
    Sales_item& operator= (const Sales_item&);
    const Item_base *operator->() const {
        if(p) return p;
        else throw std::logic_error("ubound Sales_item*");
    }
    const Item_base &operator*() const {
        if(p) return *p;
        else throw std::logic_error("ubound Sales_item*");
    }
private:
    Item_base *p;
    std::size_t *use;
    void decr_use() {
        if((--*use) == 0) {
            delete p;
            delete use;
        }
    }
};
Sales_item& Sales_item::operator= (const Sales_item& rhs) {
    ++*rhs.use;
    decr_use();
    p = rhs.p;
    use = rhs.use;
    return *this;
}


class Bulk_Item : public Item_base {
public:
    virtual Bulk_Item* clone() const {
        return new Bulk_Item(*this);
    }
};

inline bool compare(const Sales_item &lhs, const Sales_item &rhs) {
    return lhs->book() < rhs->book();
}

class basket {
    typedef bool (*Comp)(const Sales_item&, const Sales_item&);
public:
    typedef multiset<Sales_item, Comp> set_type;
    typedef set_type::size_type size_type;
    typedef set_type::const_iterator const_iter;
    basket() : items(compare) {}
    void add_item(const Sales_item &item) {
        items.insert(item); 
    }
    size_type size(const Sales_item& i) const {
        return items.count(i);
    }
    double total() const;
private:
    multiset<Sales_item, Comp> items;
};

int main() {
    //
    return 0;
}

