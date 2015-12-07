/** Graph.h **/

//guard against multiple inclusions
#ifndef __GRAPH_H_
#define __GRAPH_H_

//preprocessors
#include <iomanip>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

//class declaration for Graph
class Graph
{
    public:
        Graph ( string s );   // constructor, initializes the object
        ~Graph();  // destructor, destroys any dynamic memory
        bool setMovie ( string s ); // sets the current movie
        bool addActor ( string s ); // adds the actor to the movie list and to the actor list
        void printCentersMovies(); // prints out the list of movies 'center' is in
        void createMST(); // creates a minimum spanning tree for the
        void printStats(); // prints out the histogram as well as the avg distance from 'center'
        void getPath ( string s ); // returns shortest path from s to center

    private:
        struct vertex
        {
            string id = ""; // the value, either the movie title or the actors name
            bool known = false; // whether the vertex has been visited yet
            int degree = 0; // the degree away from center that vertex is
            string parent = ""; // the vertex's parent vertex
            vertex ( string s ) : id ( s ) { }; // constructor for the vertex struct
        };
        unordered_map<string, vertex*> table; // hash table of actors containing the degree and parent vertex
        unordered_map<string, list<string>*> actors; // hash table of actors containing a list of their movies
        unordered_map<string, list<string>*> movies; // hash table of movies containing the actors in them
        string center = "Bacon, Kevin", movie = ""; // the 'center of universe' and the current movie
        int histogram[9] = { 0 }; // array containing the number of actors in degree i at position i
};

#endif
