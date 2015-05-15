#include <iostream>
#include <vector>

using namespace std;

template<class T> class Queue;
template<typename T> 
class QueueItem {
    QueueItem(const T &t) : item(t), next(0) {}
    T item;
    QueueItem *next;
    friend class Queue<T>;
};

template<class T> 
class Queue{
private:
    QueueItem<T> *head;
    QueueItem<T> *tail;
    size_t cnt;
    void destroy();
    void copy_elems(const Queue&);
    
public:
    Queue() : head(0), tail(0), cnt(0) {}
    Queue(const Queue &q) : head(0), tail(0), cnt(0) { copy_elems(q); }
    Queue& operator= (const Queue&);
    ~Queue() { destroy(); }
    
    T& front() { return head->item; }
    const T& front() const { return head->item; }
    void push(const T &);
    void pop();
    bool empty() { return head == 0; }
    void print();
    size_t size() { return cnt; }
};
    
template<class T> void Queue<T>::destroy() {
    while(!empty()) pop();
}
template<class T> Queue<T>& Queue<T>::operator=(const Queue<T> &rhs) {
    //                 |||lacking of <T> of the return type 
    //                      generates the a compile-time error 
    head = rhs.head;
    tail = rhs.tail;
    cnt = rhs.cnt;
    copy_elems(rhs);
    return *this;
}
template<class T> void Queue<T>::push(const T& t) {
    QueueItem<T> *tmp = new QueueItem<T>(t);
    if(empty()) {
        head = tail = tmp;
    } else {
        tail->next = tmp;
        tail = tmp;
    }
    cnt++;
}
template<class T> void Queue<T>::pop() {
    QueueItem<T> *p = head;
    if(!empty()) {
        head = p->next;
        delete p;
        if(head == NULL) tail = head;
        cnt--;
    } else {
        //
    }
}
template<class T> void Queue<T>::copy_elems(const Queue &orig) {
    for(QueueItem<T> *pt = orig.head; pt; pt = pt->next) {
        push(pt->item);
    }
}
template<class Type> void Queue<Type>::print() {
    QueueItem<Type> *p;
    cout<<"< ";
    for(p = head; p; p = p->next) {
        cout<<p->item<<" ";
    }
    cout<<">"<<endl;
}
bool comp(const int &a, const int &b) {
    return a < b;
}

int main() {
    //
    vector<const int &> v;   
    cout<<comp(2, 3)<<endl;
    Queue<int> q;
    q.push(1);q.push(2);q.push(5);q.push(8);
    cout<<q.size()<<endl;
    q.print();    
}
    

