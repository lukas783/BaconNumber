#ifndef __GRAPH_H_
#define __GRAPH_H_

#include <iomanip>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

/**
 * The graph is populated now, so we must begin our BFS to decide distance away from our
 * 'center of the universe' start with finding the actor in the actor list, if exists, set his distance
 * to 0, mark it all known, find the movies it is in and look up the actors in that movie, push onto
 * queue and set currDistance to 1, pop them off the queue and mark as known and continue till no more nodes
 * to add on that aren't known
**/

class Graph
{
    public:
        Graph ( string s );   // constructor, initializes the object
        ~Graph();  // destructor, destroys any dynamic memory
        bool setMovie ( string s ); // sets the current movie
        bool addActor ( string s ); // adds the actor to the movie list and to the actor list
        void printCentersMovies(); // prints out the actors <-- idk if this is needed
        void createMST(); // creates a minimum spanning tree for the
        void printStats(); // prints out the histogram as well as the avg distance from 'center'

    private:
        struct vertex
        {
            string id = ""; // the value, either the movie title or the actors name
            bool known = false;
            int degree = 0;
            string parent = "";
            vertex ( string s ) : id ( s ) { }; // constructor for the vertex struct
        };
        unordered_map<string, vertex*> table;
        unordered_map<string, list<string>*> actors;//  vertex* > actors; // hash table of actors containing a list of their movies
        unordered_map<string, list<string>*> movies;// vertex* > movies; // hash table of movies containing the actors in them
        string center = "Bacon, Kevin", movie = ""; // the 'center of universe' and the current movie
        int histogram[9] = { 0 }; // number of actors relative to degrees away from 'center'
};

#endif
