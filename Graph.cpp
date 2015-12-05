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
    mCount++;

    // if movie was changed successfully, return true, else false.
    if ( movie == s )
        return true;

    cout << "Unable to set current movie.\n";
    return false;
}

bool Graph::addActor ( string s )
{
    // stop this and make an unordered map with key being string (actor,movie)
    // and mapped object being a vector of strings or a list or something.. will figure it out.
    //vertex* a = new vertex ( movie );
    //vertex* m = new vertex ( s );
    //vertex* iterator;

    unordered_map<string, list<string>*>::const_iterator ita = actors.find ( s );
    unordered_map<string, list<string>*>::const_iterator itm = movies.find ( movie );

    if ( itm == movies.end() )
    {
        list<string>* l = new list<string>;
        l->push_back ( s );
        movies.insert ( make_pair ( movie, l ) );
    }
    else
    {
        list<string>* l = itm->second;
        l->push_back ( s );
    }

    if ( ita == actors.end() )
    {
        list<string>* l = new list<string>;
        l->push_back ( movie );
        actors.insert ( make_pair ( s, l ) );
        table.insert ( make_pair ( s, false ) );
    }
    else
    {
        list<string>* l = ita->second;
        l->push_back ( movie );
        /*
           iterator = ita->second;

           while ( iterator->next != nullptr )
               iterator = iterator->next;

           iterator->next = a;*/
    }

    return true;
}

void Graph::printCentersMovies()
{
    cout << "Reading movies: " << movies.size() << " and " << actors.size() << " actors in database.\n";
    unordered_map<string, list<string>*>::const_iterator it = actors.find ( center );

    if ( it == actors.end() )
    {
        cout << "Could not find performer named [" << center << "]\n";
        exit ( 1 );
    }
    else
    {
        cout << "\n" << it->second->size() << " " << center << " movies\n";

        for ( list<string>::const_iterator lit = it->second->begin(); lit != it->second->end(); ++lit )
            cout << *lit << "\n";
    }
}

inline int Graph::actorCount()
{
    return aCount;
}

inline int Graph::movieCount()
{
    return mCount;
}
