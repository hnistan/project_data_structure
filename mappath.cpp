#include "mappath.h"

// class constructor
mappath::mappath(vector<vector<double>> pathdist, vector<vector<double>> pathtrafic)
{
    this->distancegraph = pathdist;
    this->traficgraph = pathtrafic;
}
//----------------------------
// class distructor
mappath::~mappath()
{
}
// minimumdis method
int mappath::minimumdis(vector<double> &dist, vector<bool> &set)
{
    // Initialize minimum value
    int minimum_value = INT_MAX;
    int min_index = 0;

    for (int v = 0; v < distancegraph.size(); v++)
        if (set[v] == false && dist[v] <= minimum_value)
        {
            minimum_value = dist[v];
            min_index = v;
        }
    return min_index;
}
//------------------------------
// dijkstra's algorithm
double mappath::algorithm(int request)
{
    vector<vector<double>> temp(traficgraph.size() , vector<double>(traficgraph.size(), 0) ); // an temp var
   
    switch (request)
    {
    case SHORTESTPATH:
        // initialize temp 2D vector
        // for find shortestpath
        temp = distancegraph;
        
        break;
    case BESTPATH:
        
        // initialize temp 2D vector
        // for find bestpath
        for (size_t i = 0; i < traficgraph.size(); i++)
        {
            for (size_t j = 0; j < traficgraph.size(); j++)
            {
                temp[i][j] = distancegraph[i][j] * traficgraph[i][j];
            }
        }
        break;
    }

    vector<double> dist; // this vector store shortest path from source vertex
    vector<bool> set; // set[i] will be true if vertex i is included in shortest distance from source to i
    // initialize all distances as INFINITE and set[] as false
    for (int i = 0; i < temp.size(); i++)
    {
        dist.push_back(INT_MAX);
        set.push_back(false);
    }
    // distance of source vertex from itself is always 0
    int src = 0;
    dist[src] = 0;

    // find shortest path for all vertices
    for (int count = 0; count < temp.size() - 1; count++)
    {

        // call find mindis function
        int u = minimumdis(dist, set);

        // mark the picked vertex as processed
        set[u] = true;

        // update distance value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < temp.size(); v++)
        {

            if (!set[v] && temp[u][v] && dist[u] != INT_MAX && dist[u] + temp[u][v] < dist[v])
            {
                dist[v] = dist[u] + temp[u][v];
                node.push_back(u);
            }
        }
    }
    return dist[11]; // int this program 11th node is distination
}
//----------------------------------
// get a rewuest form user and show path
void mappath::get_path(int req)
{
    double cost = 0;
    if (req == SHORTESTPATH)
    {
        cost = algorithm(SHORTESTPATH);
        cout << endl;
        cout << "kotah tarin masir ba fasele " << cost << " az mabda" << endl;
        cout << "--------------------------------" << endl;
        cout << "node path: " << endl;
        path();
    }
    else if (req == BESTPATH)
    {
        cost = algorithm(BESTPATH);
        cout << endl;
        cout << "behtarin masir ba hazine " << cost << " az mabda" << endl;
        cout << "node path: " << endl;
        path();
    }
}
//----------------------------------
// find node path
void mappath::path()
{
    vector<int> temp;
    vector<int> traficavg;
    for (size_t i = 0; i < distancegraph.size(); i++)
    {
        temp.push_back(-1);
        traficavg.push_back(-1);
    }
    int lastnode = 11; // save destination node
    int source = 0;    // save source node
    int j = 0;//use for loop
    while (lastnode != source)
    {
        temp[j] = node[lastnode];
        lastnode = node[lastnode];  
        ++j;
    }
    cout << 11;//show destination 
    //show all node that are in path
    for (size_t i = 0; i < distancegraph.size(); i++)
    {
        if (temp[i] == -1)
        {
            continue;
        }
        traficavg[i] = temp[i];
        cout << "<==" << temp[i];
    }
    cout << endl;
    //calculate average trafic in path
    double avg = 0;
    int i = 0;
    int cheak = 1;
    avg = avg + traficgraph[11][traficavg[0]];

    while (traficavg[i + 1] != -1)
    {
        cheak++;
        avg = avg + traficgraph[traficavg[i]][traficavg[i + 1]];
        i++;
    }
    avg = (avg / cheak);
    cout << "average trafic for this path: " << avg << endl;
}