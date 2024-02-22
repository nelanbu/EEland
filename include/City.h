#ifndef CITY_H
#define CITY_H
#include <string>

using namespace std;
enum visited {UNVISITED, VISITED};
class Route;
class City //this is class for cities including the name, index in city array , its mark(whether it is visited or not) and a Route type pointer pointing the routes from the current city
{
private:
    int city_ind;
    Route *adj_head;
    string city_name;
    int mark;
public:
    City()
    {


    }
    City(int indx, string name) //constructor
    {
        city_name=name;
        city_ind=indx;
        adj_head=NULL;
    }
    void set_head(Route *head) //sets the route type pointer to input head pointer
    {
        adj_head=head;
    }
    Route* get_head() //returns Route type pointer
    {
        return adj_head;
    }
    int get_index() //returns index of the city in the city array
    {
        return city_ind;
    }
    string get_name() //returns name of the current city
    {
        return city_name;
    }

    void set_mark() //sets the mark as visited to indicate the current city is visited
    {
        mark=VISITED;
    }
    int get_mark() //returns what mark is
    {
        return mark;
    }
    void reset_mark() //resets mark as unvisited
    {
        mark=UNVISITED;
    }


};
#endif // CITY_H
