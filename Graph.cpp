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

    cout << "\n";
}

void Graph::createMST()
{
    cout << "Building MST ... ";
    queue<vertex*> q;

    //unordered_map<string, vertex*>::const_iterator
    vertex*	parent = table.find ( center )->second;
    int degree = 0;
    q.push ( parent );
    parent->degree = degree;
    parent->known = true;
    histogram[0] = 1;

    //while the queue contains actors
    while ( !q.empty() )
    {
        //traverse the actors list of movies
        parent = q.front();
        q.pop();

        //traverse through current vertex's (actors) list of movies
        for ( list<string>::const_iterator la = actors.find ( parent->id )->second->begin();
                la != actors.find ( parent->id )->second->end(); ++la )
        {
            //traverse the current vertex's (movies) list of co-actors
            for ( list<string>::const_iterator lm = movies.find ( *la )->second->begin();
                    lm != movies.find ( *la )->second->end(); ++lm )
            {
                vertex* child = table.find ( *lm )->second;

                if ( ( ! ( child->known ) ) && ( parent->degree <= 8 ) )
                {
                    child->known = true;
                    child->degree = parent->degree + 1;
                    child->parent = parent->id;
                    histogram[child->degree]++;
                    q.push ( child );
                }
            }
        }

    }

    cout << "done!\n\n";
}

void Graph::printStats()
{
    int sum = 0;
    float avg = 0;

    for ( int i = 0; i < 9; i ++ )
    {
        cout << setw ( 4 ) << i << setw ( 10 ) << histogram[i] << "\n";
        sum += histogram[i]; // for finding inf
        avg += ( histogram[i] * i ); // avg path length
    }

    cout << setw ( 4 ) << "Inf" << setw ( 10 ) << ( actors.size() - sum ) << "\n\n";
    cout << "Avg path length : " << ( avg / ( ( float ) actors.size() ) ) << "\n\n";
}

void Graph::getPath ( string s )
{
    unordered_map<string, vertex*>::const_iterator it = table.find ( s );

    if ( it == table.end() )
    {
        cout << s << " does not exist in the actor database.\n";
    }
    else
    {
        vertex* v = it->second;

        if ( ! ( v->known ) )
            cout << s << " has no path to " << center << ".\n";
        else
        {
            cout << v->degree << ": ";

            while ( v->id != center )
            {
                cout << v->id << " => ";
                v = table.find ( v->parent )->second;
            }

            cout << v->id << "\n";
        }
    }
}