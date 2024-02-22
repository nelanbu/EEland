#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

static const int MAX_CITY_NUM=100;
string city[MAX_CITY_NUM];


class Graph //graph class including an array which has city names and an integer of city number
{
private:
    int numCities, numRoutes; // number of edges and vertices

    City *cities;
    int city_count;


public:
    Graph(); // Constructor
    //~Graph(); //destructor can be implemented if it is needed to delete City type array created in constructor
    void AddGCity(int ind, string name);
    void ListAllCities() const;
    int GetCityNum() const;
    void RemoveGCity(string name);
    City * SearchGCity(string name) const;
    void AddGRoute(string from, string to);
    void RemoveGRoute(string flight_no);
    Route* SearchGRoute(string from, string to);
    Route* SearchGRoute(string flight_no);
    void ListGRoute() const;
    City* get_cities() const;
    void resetMark();
    bool path_exists;



};


Graph::Graph() //constructor opens memory for the city
{
    city_count=0;
    cities= new City [MAX_CITY_NUM];


}
void Graph::AddGCity(int ind, string name) //this method adds new city to city array and counts the number of cities
{
    cities[city_count]= *new City(ind, name);

    city_count++;
}
void Graph::ListAllCities() const //this method prints the routes and its cost, and if it is new added route it indicates.
{
    for(int i=0;i<city_count;i++)
    {
        Route *temp= cities[i].get_head();

        while(temp!=NULL)
        {
            if (temp->new_added)
            {
                cout<<"(NEW) ";
                temp->new_added=false;
            }
            cout<<"From: "<<cities[i].get_name()<<" ("<<cities[i].get_index()<<") to: "
                <<temp->get_dest()->get_name()<<" ("<<temp->get_dest()->get_index()<<") Route fare: "<<temp->get_cost()<< "$"<<endl;
            temp=temp->get_next();

        }
    }
}
int Graph::GetCityNum() const //returns number of cities
{
    return city_count;
}
void Graph::AddGRoute(string from, string to) //this method adds new route between given input city names and assign a random cost
{
    City* from_city=SearchGCity(from); //searchGCity is a method finds the input string name of the city in the city array
    City* to_city=SearchGCity(to);

    if(from_city==NULL || to_city==NULL)
    {
        cerr<<"Route cannot be added."<<endl;
        return ;
    }
    int random_cost= (rand() %(50-10)+10)*10; //cost is chosen randomly in [100,500) and multiples of 10
    Route *tmp_route= new Route(random_cost,to_city); // a new route type pointer created to add new route and rest is operations like adding a doubly linked list
    if(from_city->get_head() ==NULL)
    {
        from_city->set_head(tmp_route) ;
    }
    else
    {
        Route *temp = tmp_route;
        temp->set_next(from_city->get_head());
        from_city->set_head(temp);

    }
}

City* Graph::SearchGCity(string name) const // searches the input city in the city array
{
    for(int i=0;i<city_count;i++)
    {
        if(cities[i].get_name()==name)
        {
            return &cities[i];
        }
    }
    cerr<<"city cannot be found"<<endl;
    return NULL;
}
City * Graph::get_cities() const //returns City type pointer pointing to the city array
{
    return cities;
}
Route* Graph::SearchGRoute(string from, string to) //this method checks whether a route exists or not between input cities
{
    City* from_city=SearchGCity(from);
    City* to_city=SearchGCity(to);
    Route* temp=from_city->get_head();
    while(temp!=NULL)
    {
        if(temp->get_dest()==to_city) // it checks the destination pointer in the route type temporary pointer
            return temp;
        temp=temp->get_next();
    }
    return NULL;
}

Route* Graph::SearchGRoute(string flight_no) // it searches route as previous method but this time input is the flight number rather than two cities
{
    int from= stoi(flight_no.substr(2,2)); //stoi is used here to convert given string number to integer
    int to= stoi(flight_no.substr(4,2));
    return SearchGRoute(cities[from].get_name(), cities[to].get_name());

}
void Graph:: RemoveGRoute(string flight_no) //this method removes the input flight and it prints the removed flight
{
    int from= stoi(flight_no.substr(2,2));
    int to= stoi(flight_no.substr(4,2));

    City* from_city=SearchGCity(cities[from].get_name());
    City* to_city=SearchGCity(cities[to].get_name());


    Route *curr_route= from_city->get_head();
    Route *prev_route=NULL;
    while(curr_route!=NULL)
    {
        if(curr_route->get_dest()==to_city)
        {
            if(prev_route==NULL) //we delete the first route type node from the adjacency list
            {
                from_city->set_head(curr_route->get_next());

            }
            else // if removal is happening at the middle (not removing the first)
            {
                prev_route->set_next(curr_route->get_next());
            }
            cout<<"Discarded route: from "<<from_city->get_name()<<" to "<<to_city->get_name()<<endl;
            delete curr_route;
            return;
        }
        prev_route=curr_route;
        curr_route=curr_route->get_next();
    }

}
void Graph::resetMark() //resets the mark of all cities in the city array as unvisited
{
    for(int i=0;i<city_count;i++)
    {
        cities[i].reset_mark();
    }
}



#endif // GRAPH_H
