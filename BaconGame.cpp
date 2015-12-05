#include <iostream>
#include <fstream>
#include "Graph.h"

using namespace std;

bool handleDatabase ( char* file, Graph g );

int main ( int argc, char* argv[] )
{
    if ( argc == 4 )
    {
        Graph g ( argv[3] );
        handleDatabase ( argv[2], g );
    }
    else if ( argc == 3 )
    {
        Graph g ( argv[2] );
        handleDatabase ( argv[1], g );
    }
    else if ( argc == 2 )
    {
        Graph g ( "Bacon, Kevin" );
        handleDatabase ( argv[1], g );
    }
    else
    {
        cout << "Usage: BaconNumber [-h] <database_file> [alternate_start]\n\n"
             << "\t     -h - print histogram of path lengths and longest-shortest path\n\t          endpoints\n"
             << "database_file   - contains records of the form: \n\t          Movie Name/actor1/actor2/...\n"
             << "alternate_start - supply a different center of universe, default = \"Bacon, Kevin\"\n"
             << "\t          quotes are required\n";
        return 1;
    }

    return 0;
}

bool handleDatabase ( char* file, Graph g )
{
    ifstream in;
    in.open ( file, ios::in );

    if ( !in )
    {
        cout << "Unable to open file " << file << ". Exiting Program.\n";
        return false;
    }

    string data = "";
    int pos;

    while ( getline ( in, data ) )
    {
        pos = data.find ( '/' ); // find the end of the movie title

        if ( !g.setMovie ( data.substr ( 0, pos ) ) )
            return false;// set current movie

        data = data.substr ( pos + 1, data.length() ); // change data input to just have actors

        do
        {
            pos = data.find ( '/' );

            if ( pos == -1 )
                pos = data.length();

            if ( !g.addActor ( data.substr ( 0, pos ) ) )
                return false;

            if ( pos != data.length() )
                data = data.substr ( pos + 1, data.length() );
            else
                data = "";
        }
        while ( data != "" );
    }

    g.printCentersMovies();
    return true;
}