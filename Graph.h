#ifndef __GRAPH_H_
#define __GRAPH_H_

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/***
 If we store each actor as a vertex into an unordered map (hash table)
 we can use that to store each item and a list of movies they are linked to.

 Each movie can be its own vertex (unordered map) as well and have a list of
 actors that are linked to it.
***/


class Graph
{

    public:
        Graph ( string s );
        ~Graph();
        bool setMovie ( string s );
        bool addActor ( string s );
        void printActors();
    private:
        struct vertex
        {
            string id = "";
            bool known = false;
            vertex* next = nullptr;
        };
        unordered_map<string, vertex*> actors;
        unordered_map<string, vertex*> movies;
        string center = "Bacon, Kevin", movie = "";
};

#endif
