#include "Graph.h"

/**
 * Graph(string) constructor, creates an instance of the graph class
**/
Graph::Graph ( string s ) : center ( s )
{
    cout << "Center of the universe is.. " << center << "\n";
}


Graph::~Graph() { };

bool Graph::setMovie ( string s )
{
    // set movie to s
    movie = s;

    // if movie was changed successfully, return true, else false.
    if ( movie == s )
    {
        //cout << "Movie is " << movie << "\n";
        return true;
    }

    cout << "Unable to set current movie.\n";
    return false;
}

bool Graph::addActor ( string s )
{
    // stop this and make an unordered map with key being string (actor,movie)
    // and mapped object being a vector of strings or a list or something.. will figure it out.
    vertex* v = new vertex;
    v->id = movie;

    unordered_map<string, vertex*>::const_iterator it = actors.find ( s );

    if ( it == actors.end() )
        actors.insert ( make_pair ( s, v ) );
    else
    {
        vertex* iterator = it->second;

        while ( iterator->next != nullptr )
            iterator = iterator->next;

        iterator->next = v;
    }

    //cout << "\tActor... " << s << "\n";
    return true;
}

void Graph::printActors()
{
    cout << "\n" << actors[center]->id << "\n\n";
}