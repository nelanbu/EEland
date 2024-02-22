//Yagmur Eren 2304574 time spent: 39 hours
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "City.h"
#include "Route.h"
#include "Graph.h"
#include "BinSearchTree.h"
#include "Queue.h"
#include <queue>


using namespace std;






//all cities are defined as string and their index is also defined as int
static const string Probia="Probia";
static const int probia_ind=0; // index of probia is used as 0 and we see it in flight number as EE00XY
static const string Machineland="Machineland";
static const string LasDatas="Las Datas";
static const int lasdatas_ind=2;
static const string SanAntenna="San Antenna";
static const string WestCircuitta="West Circuitta";
static const string EastCircuitta="East Circuitta";
static const string Logicheim="Logicheim";
static const string Analograd="Analograd";
static const string IslandofSemicon="Island of Semicon";
static const string Biomedberg="Biomedberg";
static const string Magneta="Magneta";
static const string Waverium="Waverium";
static const string Telecommunicastan="Telecommunicastan";
static const string Prokontrolkka="Prokontrolkka";
static const string Signale="Signale";
static const string NorthKirchoff="North Kirchoff";
static const string SouthKirchoff="South Kirchoff";
static const string GulfofArchi="Gulf of Archi";
static const string NewOerstad="New Oerstad";
static const string NeuralsDeep="Neural's Deep";

static const int OT=40;
static const int N=5;








class ArchiveNode //this class is the main structure of FlightArchive in the below to archive monthly flights
{
public:
    BinSearchTree *data;
    int month;
    ArchiveNode *next;
    ArchiveNode *prev;

    ArchiveNode(BinSearchTree *bst)
    {
        data=bst;
        next=NULL;
        prev=NULL;
        month=1;
    }
    ArchiveNode *get_next()
    {
        return next;
    }
    ArchiveNode *get_prev()
    {
        return prev;
    }
};

class FlightArchive //By using this class, monthly flights will be archived
{
public:
    ArchiveNode *head;
    ArchiveNode *tail;
    FlightArchive()
    {
        head=NULL;
        tail=NULL;
    }

    void AddMonthData(BinSearchTree *bst) //this method adds new binary search tree which is the flights belong to any month
    {
        ArchiveNode *NewArchive;
        NewArchive= new ArchiveNode(bst);
        if(head==NULL)
        {
            head= NewArchive;
            tail= NewArchive;
        }
        else
        {
            tail->next=NewArchive;
            NewArchive->prev=tail;
            NewArchive->month=tail->month+1;
            tail=NewArchive;

        }
    }
    void print_archive() const //prints the archived flights just for tests
    {

        ArchiveNode *temp;
        temp=head;
        while(temp!=NULL)
        {
            cout<<"Month"<<temp->month<<endl;
            temp->data->PrintTree(temp->data);
            temp=temp->next;
        }
    }

    BinSearchTree * GetLastMonthFlights() //returns last archived (month) flights binary search tree
    {
        if(tail==NULL)
            return NULL;
        return tail->data;
    }
    BinSearchTree * Get2MonthsBeforeFlights() //returns two tree (two months) before which is archived flights binary search tree
    {
        if(tail==NULL || tail->prev==NULL)
        {
            return NULL;
        }
        return tail->prev->data;
    }
};





int ReadCityNames() //it reads the city names from the given text file
{
    string line;
    int i=0;
    ifstream myfile ("citylist.txt");
    if (myfile.is_open())
    {

    while ( getline (myfile,line) )
    {
    city[i]=line;
//    cout <<i+1<<" "<< city[i] << "\n";
    i++;
    }
    myfile.close();
    }
    else cout << "Unable to open file";
    return i;
}

void InitRouteMap(Graph &c) //this method forms the given route map using the AddGCity method to add the cities to the graph
{
    int city_cnt=ReadCityNames();
    for(int i=0; i<city_cnt ;i++)
    {
        c.AddGCity(i,city[i]);
    }
    c.AddGRoute(Probia,Logicheim);
    c.AddGRoute(Logicheim,Probia);
    c.AddGRoute(GulfofArchi,Logicheim);
    c.AddGRoute(Probia,GulfofArchi);
    c.AddGRoute(Probia,LasDatas);
    c.AddGRoute(Signale,Probia);

}

string CreateFlightNum(int source_idx, int destination_idx) //this method creates the flight number between input cities as in the requested format
{
    string source = to_string(source_idx);
        if(source_idx<10)
        {
            source= "0"+source;
        }

        string destination= to_string(destination_idx);
        if(destination_idx<10)
        {
            destination= "0"+destination;
        }
        return "EE"+source+destination;
}


void InitFlightPlan(BinSearchTree *&flight, Graph &city) //this method creates the binary search tree using the input graph and tree
{
    for(int i=0;i<city.GetCityNum();i++)
    {

        Route *temp= city.get_cities()[i].get_head();


        while(temp!=NULL)
        {

            string flight_no= CreateFlightNum(city.get_cities()[i].get_index(),temp->get_dest()->get_index());
            if(flight==NULL)
            {
                flight= new BinSearchTree(flight_no);
            }
            else
            {
                flight->AddTFlight(flight_no,flight);
            }


            temp=temp->get_next();

        }

    }

}
void AddMonthlyNewFlights(int source, int destination, BinSearchTree *bst) //a new flight is added using the input cities as source and destination
{
    string flight_no= CreateFlightNum(source, destination);
    bst->AddTFlight(flight_no,bst);
}
// I have merged AddMonthlyNewFlights and AddMonthlyNewRoutes in this method
void AddMonthlyNewRoutes(int N, Graph &c, BinSearchTree* bst) //new routes are added
{
    int cnt=0;
    while(cnt<N)
    {
        City source = c.get_cities()[rand()%(c.GetCityNum())] ;
        City destination = c.get_cities()[rand()%(c.GetCityNum())];
        if (source.get_name()!=destination.get_name() && c.SearchGRoute(source.get_name(), destination.get_name())==NULL )
        {
            c.AddGRoute(source.get_name(), destination.get_name());

            AddMonthlyNewFlights(source.get_index(),destination.get_index(),bst);
            cnt++;
        }
    }
}
BinSearchTree* CancelUnpopularFlights(string flight_no, BinSearchTree *bst) //cancels flights with low occupancy rate in consecutive 2 months
{
    return bst->RemoveTFlight(flight_no,bst);

}
void traverseTree(BinSearchTree *prevmonth, BinSearchTree *twomonthsbefore, Graph *routes, BinSearchTree *&bst)
{
    if(prevmonth==NULL)
    {
        return;
    }
    if(prevmonth->GetOccupancyState()<OT)
    {

        BinSearchTree *twomonthsbeforeFlight=twomonthsbefore->SearchTFlight(prevmonth->key,twomonthsbefore);
        if(twomonthsbeforeFlight==NULL || twomonthsbefore->GetOccupancyState()>=OT) //this flight does not exist 2 months before or it exists but occupancy state is not under OT.
        {
            // half the price in routes graph
            Route *route_halfpriced= routes->SearchGRoute(prevmonth->key);
            cout<<"Changing Route Fare 50% Discount "<<prevmonth->key<<" : ";
            cout<<"Old Route Fare: "<<route_halfpriced->get_cost()<<" ";
            route_halfpriced->set_cost(route_halfpriced->get_cost()/2);
            cout<<"New Route Fare: "<<route_halfpriced->get_cost()<<endl;

        }
        else //this flight exists two months before and occupancy state is under OT
        {

            //discard route

            routes->RemoveGRoute(prevmonth->key);
            bst=CancelUnpopularFlights(prevmonth->key, bst);
        }

    }
    traverseTree(prevmonth->Left(),twomonthsbefore,routes,bst);
    traverseTree(prevmonth->Right(),twomonthsbefore,routes,bst);
}


//I have merged DiscardUnpopularRoutesAndUpdatePrices and CancelUnpopularFlights methods
void DiscardUnpopularRoutesAndUpdatePrices(FlightArchive *arc, Graph *routes, BinSearchTree *&bst) //here above method is used inside
{ //to check each route's occupancy states and update their costs
    BinSearchTree *preceedingMonth;
    BinSearchTree *twoMonthsBefore;
    preceedingMonth=arc->GetLastMonthFlights();
    twoMonthsBefore= arc->Get2MonthsBeforeFlights();

    if(preceedingMonth==NULL)
        return;
    traverseTree(preceedingMonth,twoMonthsBefore,routes,bst);

}
void AddReturnFlight(int source, int destination, BinSearchTree *bst) //adds return flight between input cities
{
    string flight_no= CreateFlightNum(source, destination);
    bst->AddTFlight(flight_no,bst);
}

void CheckNAddReturnRoutes(Graph *city_graph, BinSearchTree*& bst) //it checks whether there is a route or not between two city,
{ //then it adds if no return exists
    for(int i=0;i<city_graph->GetCityNum();i++)
    {
        Route *temp= city_graph->get_cities()[i].get_head();
        City *new_to=&city_graph->get_cities()[i];

        while(temp!=NULL)
        {
            City *new_from=temp->get_dest();
            if(city_graph->SearchGRoute(new_from->get_name(),new_to->get_name())==NULL)
               {
                   city_graph->AddGRoute(new_from->get_name(),new_to->get_name());
                    AddReturnFlight(new_from->get_index(), new_to->get_index(),bst);
                   cout<<"Return flight has been added from: "<<new_from->get_name()<<" to "<<new_to->get_name()<<endl;
               }
            temp=temp->get_next();
        }
    }
}

void DFS(int from, int to, Graph *city_graph, int *path, int path_ind, list<list<int>> &direct, list<list<int>> &one_stop,list<list<int>> &two_stop)//depth first search on graph to find paths between two cities
{ //deep first seacrh
    //mark the current node as visited
    city_graph->get_cities()[from].set_mark();
    //stored in path
    path[path_ind]=from;
    path_ind++;
    if(from==to)
    {
        city_graph->path_exists=true;
        list<int> *temp= new list<int>;
        for(int i=0; i<path_ind;i++)
        {
            temp->push_back(path[i]);

        }
        if(path_ind==3) //one stop path
        {
            one_stop.push_back(*temp);
        }
        else if(path_ind==4)//two stop path
        {
            two_stop.push_back(*temp);
        }
        else if(path_ind==2)//no stop-direct path
        {
            direct.push_back(*temp);
        }


        //cout<<path[path_ind-1]<<endl;
    }
    else //if curret city is not equal to arraival city
        //recur for all the adjacent cities
    {
        Route *curr_route=city_graph->get_cities()[from].get_head();
        while(curr_route!=NULL)
        {
            City *curr_to_city= curr_route->get_dest();
            if(curr_to_city->get_mark()==UNVISITED)
            {
                DFS(curr_to_city->get_index(),to, city_graph, path, path_ind,direct,one_stop,two_stop);
            }
            curr_route=curr_route->get_next();
        }
    }
    //remove current city from path and mark it as unvisited
    path_ind--;
    city_graph->get_cities()[from].reset_mark();



}

void PrintPath(list<list<int>> path, Graph *city_graph, BinSearchTree *bst) //this prints paths and costs from a city as no stop, one stop and two stops
{
    list<list<int>> :: iterator it;

        for (it= path.begin(); it != path.end(); ++it)
         {
            int sum=0;
            string sum_str="";
            list<int>::iterator pth_itr;
            list<int>& pth_pointer = *it;
            City* prev_city=NULL;

             for (pth_itr = pth_pointer.begin(); pth_itr != pth_pointer.end(); pth_itr++)
             {
                 City *city=&city_graph->get_cities()[*pth_itr];
                 if(prev_city!=NULL)
                 {

                     string flight_no= CreateFlightNum(prev_city->get_index(),city->get_index());
                     cout<<" ---> "<<flight_no<<" ---> ";
                     int cost=city_graph->SearchGRoute(flight_no)->get_cost();
                     sum+=cost;
                     if(sum_str!="")
                     {
                         sum_str+=" + ";
                     }
                    sum_str+=to_string(cost);
                 }

                 cout << " " << city->get_name() << " ";
                 prev_city=city;
             }
             cout<<" for "<<sum<<"$ "<<"("<<sum_str<<")"<<endl;
         }

}



void DisplayRouteOptions(Graph *city_graph, BinSearchTree* bst, int from, int to)
{
    //mark all the cities unvisited
    city_graph->resetMark();
    int *path= new int [city_graph->GetCityNum()]; //create an array to store paths
    int path_ind=0;
    list<list<int>> direct;
    list<list<int>> one_stop;
    list<list<int>> two_stop;
    city_graph->path_exists= false;
    DFS(from,to, city_graph,path,path_ind,direct,one_stop,two_stop);

    cout<<"One-way Trip Options for "<<city_graph->get_cities()[from].get_name()<<" ---> "<<city_graph->get_cities()[to].get_name()<<" :"<<endl;


    if(city_graph->path_exists)
    {
        if(direct.size()>0)
        {
            cout<<"Direct Option: "<<endl;
            PrintPath(direct, city_graph, bst);
        }
        if(one_stop.size()>0)
        {
            cout<<"1-Stop Option: "<<endl;
            PrintPath(one_stop, city_graph, bst);
        }
        if(two_stop.size()>0)
        {
            cout<<"2-Stop Option: "<<endl;
            PrintPath(two_stop, city_graph, bst);
        }
    }
    else
    {
        cout<<"No Trip Options"<<endl;
    }
}



int main()
{
    FlightArchive archive;
    Graph city_graph;
    BinSearchTree *flight_bst=NULL;

    //first month
    cout<<"MONTH: 1"<<endl;
    cout<<endl;

    InitRouteMap(city_graph);
    InitFlightPlan(flight_bst,city_graph);//prints flight number
    cout<<"ROUTES:"<<endl;
    city_graph.ListAllCities();
    archive.AddMonthData(flight_bst->clone(flight_bst));
    cout<<endl;
    cout<<"FLIGTHS: "<<endl;
    flight_bst->PrintTree(archive.tail->data);


for(int i=2;i<7;i++)
{
    cout<<endl;
    cout<<"MONTH: "<<i<<endl;
    cout<<endl;

    AddMonthlyNewRoutes(N,city_graph,flight_bst);
    cout<<"FARE CHANGES AND DISCARDED ROUTES/FLIGHTS"<<endl;
    DiscardUnpopularRoutesAndUpdatePrices(&archive,&city_graph,flight_bst);
    cout<<endl;



    if(i%6==0)
    {
        //run this code for every 6 months
        CheckNAddReturnRoutes(&city_graph, flight_bst); //return fligths are also checked in this method

    }
    cout<<endl;
    cout<<"ROUTES:"<<endl;
    city_graph.ListAllCities();
    archive.AddMonthData(flight_bst->clone(flight_bst));
    cout<<endl;
    cout<<"FLIGTHS: "<<endl;
    flight_bst->PrintTree(archive.tail->data);

}
    //flight_bst->printLevelOrder(flight_bst);
    DisplayRouteOptions(&city_graph,flight_bst,probia_ind ,lasdatas_ind);//at the beginning only probia and las datas indexes are declared
//since the displayRouteOptions takes integers as the index of cities, by giving index numbers of two cities to see the route options between them as follows
    DisplayRouteOptions(&city_graph,flight_bst,5,13);
    DisplayRouteOptions(&city_graph,flight_bst,6,15);
    DisplayRouteOptions(&city_graph,flight_bst,10,2);
    DisplayRouteOptions(&city_graph,flight_bst,8,13);
    //archive.print_archive(); //prints all months flights up to last month


    //city_graph.ListAllCities();

    //flight_bst->PrintTree(flight_bst);

    return 0;
}
