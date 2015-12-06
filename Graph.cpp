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
        return true;

    cout << "Unable to set current movie.\n";
    return false;
}

bool Graph::addActor ( string s )
{
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
        vertex* v = new vertex ( s );
        l->push_back ( movie );
        actors.insert ( make_pair ( s, l ) );
        table.insert ( make_pair ( s, v ) );
    }
    else
    {
        list<string>* l = ita->second;
        l->push_back ( movie );
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

void Graph::createMST()
{
    // create mst, push stuff onto a queue and so forth..
    // ok, so we will create a MST by starting at center and pushing onto queue all of actors in same movies as them,
    // these actors will be set to have a degree of 1, and known to be true, then we go to all of those actors and enqueue
    // the actors in movies they are in, and so forth incrementing the degree each time till we reach a point where there is
    // nothing more to enqueue (enqueue only what is not already visited [known = false])
    queue<vertex*> q;

    //unordered_map<string, vertex*>::const_iterator
    vertex*	parent = table.find ( center )->second;
    int degree = 0;
    q.push ( parent );
    parent->degree = degree;
    parent->known = true;
    histogram[0]++;

    while ( !q.empty() )
    {
        //traverse the actors list of movies
        parent = q.front();
        q.pop();

        for ( list<string>::const_iterator la = actors.find ( parent->id )->second->begin();
                la != actors.find ( parent->id )->second->end(); ++la )
        {
            //traverse the movies for new actors to add
            for ( list<string>::const_iterator lm = movies.find ( *la )->second->begin();
                    lm != movies.find ( *la )->second->end(); ++lm )
            {
                vertex* child = table.find ( *lm )->second;

                if ( ! ( child->known ) )
                {
                    child->known = true;
                    child->degree = parent->degree + 1;
                    histogram[parent->degree + 1]++;
                    child->parent = parent;
                    q.push ( child );
                }
            }
        }

    }

    cout << "Histogram!\n";

    for ( int i = 0; i < 10; i++ )
    {
        cout << i << "\t" << histogram[i] << "\n";
    }
}