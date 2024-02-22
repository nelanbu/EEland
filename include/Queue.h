#ifndef QUEUE_H
#define QUEUE_H


#include <iostream>

using namespace std;
const int MaxQuSize=50;

template<class T> //this class is manually implemented queue class and it includes methods to manipulate queues as we are already familiar
class Queue
{
private:
    int f,r,c;
    T queuelist[MaxQuSize];
public:
    Queue();
    void Qinsert(const T &item);
    T Qdelete();
    void ClearQ();
    T Qfront() const;
    //queue test methods
    int Qlength() const;
    int QFull() const;
    int QEmpty() const;
    void Print() const;
};

template<class T>
Queue<T>::Queue()
{
    f=0;
    r=0;
    c=0;
}
//test methods
template<class T>
int Queue<T>::Qlength() const
{
    return c;
}
template<class T>
int Queue<T>::QFull() const{
    return (c==MaxQuSize);
}
template<class T>
int Queue<T>::QEmpty() const
{
    return (c==0);
}


template<class T>
void Queue<T>::Qinsert(const T &item)
{
    if(QFull())
    {
        cerr<<"Queue is full"<<endl;
        exit(1);
    }
    queuelist[r]=item;
    r=(r+1)%MaxQuSize;
    c=c+1;
}
template<class T>
T Queue<T>::Qdelete()
{
    T temp;
    if (QEmpty())
    {
        cerr<<"Queue is Empty"<<endl;
        exit(1);
    }
    temp=queuelist[f];
    f=(f+1)%MaxQuSize;
    c=c-1;
    return temp;
}
template<class T>
T Queue<T>::Qfront() const
{
    return queuelist[f];
}
template<class T>
void Queue<T>::ClearQ()
{
    f=0;
    r=0;
    c=0;
}

template <class T>
void Queue<T>::Print() const
 {   int i=0;
     while(i!=MaxQuSize)
     {
      cout<<queuelist[i]<<endl;
      i++;
     }
 }


#endif // QUEUE_H
