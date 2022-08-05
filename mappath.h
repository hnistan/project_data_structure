#ifndef MAPPATH_H
#define MAPPATH_H
#include <vector>
#include <iostream>
#include <limits.h>
#include <stdio.h>
using namespace std;
enum req
{
    SHORTESTPATH,
    BESTPATH
};

class mappath
{
private:
    vector<vector<double>> traficgraph;   // a vector for store trafic amount
    vector<vector<double>> distancegraph; // a vector for store distance amount
    vector<int> node;                     // a vector for store path node
    double algorithm(int request);        // algorithm for find best path or shortest path in graph
    int minimumdis(vector<double> &, vector<bool> &);

public:
    mappath(vector<vector<double>>, vector<vector<double>>); // constructor
    ~mappath();
    void get_path(int req); // show cost or distance of path
    void path();            // show node path and trafic average
};

#endif