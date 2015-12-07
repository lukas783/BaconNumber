/** Graph.cpp  **/

#include "Graph.h"

/**
 * Graph(string) constructor, creates an instance of the graph class
**/
Graph::Graph ( string s ) : center ( s )
{
    cout << "Center of the universe is.. " << center << "\n";
}


Graph::~Graph() { };

/**
 * setMovie(string), sets the current movie to be added into actors hash
 *  table andd the key for the movies hash table. Returns true if successful
 *  returns false if the movie was not changed successfully.
**/
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

/**
 * addActor(string), adds the actor to the hash table of movies and adds
 *  the movie to the hash table of actors. Always returns true.
 * A check could be added after insertion to verify the vertex's were added
 *  correctly, returning false if unsuccessful or true if it was.
**/
bool Graph::addActor ( string s )
{
    //create our iterators
    unordered_map<string, list<string>*>::const_iterator ita = actors.find ( s );
    unordered_map<string, list<string>*>::const_iterator itm = movies.find ( movie );

    //adds the actor s to the movies hash table
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

    //adds the current movie to the actors position in the actors hash table
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

/**
 * printCentersMovies(), prints out the number of movies and actors in the database then
 *  prints out a list of movies the 'center' is in. An error message is displayed and program
 *  is exited if the performer does not exist
**/
void Graph::printCentersMovies()
{
    // print movie hash table size and actors hash table size and set iterator for traversing 'center's list
    cout << "Reading movies: " << movies.size() << " and " << actors.size() << " actors in database.\n";
    unordered_map<string, list<string>*>::const_iterator it = actors.find ( center );

    // print out the list of movies that 'center' is in, or print an error message if 'center' does not exist
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

/**
 * createMST(), creates a minimum spanning tree using breadth first search. Pushes the center
 *  onto the queue and begins looping till the queue is empty, adding all the parent vertex's
 *  children to the queue and assigning them a degree and a parent node to create a path.
 * The function also helps to populate the histogram array.
 * This function runs incredibly slow, needs to be evaluated to see if it can be made to
 *  run faster
**/
void Graph::createMST()
{

    cout << "Building MST ... ";
    queue<vertex*> q;

    // Set our initial vertex to the 'center' and push onto stack
    vertex*	parent = table.find ( center )->second;
    q.push ( parent );
    parent->degree = 0;
    parent->known = true;
    histogram[0] = 1;

    //while the queue contains actors, continue looping
    while ( !q.empty() )
    {
        // pop the front of the queue and set to the parent vertex
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
                //find the vertex to set as child to the current parent node
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

/**
 * printStats(), prints to the screen a table containing the degree and number of
 *  actors with that degree. If the actor does not have a set degree, it is counted
 *  as an inf degree. Also prints to screen the avg path length.
**/
void Graph::printStats()
{
    int sum = 0;
    float avg = 0;

    // go through the histogram array
    for ( int i = 0; i < 9; i ++ )
    {
        cout << setw ( 4 ) << i << setw ( 10 ) << histogram[i] << "\n";
        sum += histogram[i]; // for finding inf
        avg += ( histogram[i] * i ); // avg path length
    }

    cout << setw ( 4 ) << "Inf" << setw ( 10 ) << ( actors.size() - sum ) << "\n\n";
    cout << "Avg path length : " << ( avg / ( ( float ) actors.size() ) ) << "\n\n";
}

/**
 * getPath(string), finds the vertex in the table of actors that matches string,
 *  if the vertex doesn't exist, print out an error message stating that the actor
 *  searched is not in the actor database. If vertex is found it will print the
 *  degree and traverse through the path in the MST printing the actors on it's way
 *  to the 'center'.
**/
void Graph::getPath ( string s )
{
    // iterator to the vertex in the hashtable of actors
    unordered_map<string, vertex*>::const_iterator it = table.find ( s );

    /**
     * if the actor exists in the hash table, print out the degree and path
     * to the 'center' if the path exists. If the actor doesn't exist or the
     * path doesn't exist, print a proper error message.
    **/
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