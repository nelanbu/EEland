#ifndef ROUTE_H
#define ROUTE_H
#include "City.h"
#include <string>

class Route //class for Routes between cities including the cost, the next route pointer from the current city, and the destination from current city as forming current route
{
private:
    int m_cost;
    City *m_dest;
    Route *m_next;
public:
    bool new_added;
    Route(int cost, City *dest) //constructor
    {
        m_cost=cost;
        m_dest=dest;
        m_next=nullptr;
        new_added= true;
    }
    void set_next(Route *next) //sets the next pointer of route type pointer (since we used adjacency matrix, the routes from a city created as linked list)
    {
        m_next=next;
    }
    City* get_dest() //returns the current destination
    {
        return m_dest;
    }
    Route *get_next() //returns the current next route
    {
        return m_next;
    }
    int get_cost() // returns the cost of current route from current city to "dest" -destination
    {
        return m_cost;
    }
    void set_cost(int newcost) //sets the current cost as input new cost
    {
        m_cost=newcost;
    }

};

#endif // ROUTE_H
