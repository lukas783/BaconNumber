/**
 * Programming Assignment #4 : Six Degrees of Kevin Bacon
 * CSC300 - Data Structures - Fall 2015
 * Professor: Dr. John Weiss
 *
 * Author: Lucas Carpenter
 *
 * Compile: g++ -O -o Bacon_Number -std=c++14 BaconGame.cpp Graph.cpp
 *
 * Usage: Bacon_Number <database_file> [alternate_start]
**/

//preprocessors
#include <iostream>
#include <fstream>
#include "Graph.h"

using namespace std;

//function prototypes
bool handleDatabase ( char* file, Graph g );

/**
 * main(int, char*), the starting point of the program, if the arguments
 *  in are 2 or 3, the program will read the input file for <database_file>
 *  and initialize the graph class, setting the 'center' to [alternate_start]
 * If an invalid number of arguments are input, it will print an error message
 *  and a usage statement.
**/
int main ( int argc, char* argv[] )
{
    if ( argc == 3 )
    {
        // starts the game with an alternate 'center'
        Graph g ( argv[2] );
        handleDatabase ( argv[1], g );
    }
    else if ( argc == 2 )
    {
        // starts the game with the default 'center'
        Graph g ( "Bacon, Kevin" );
        handleDatabase ( argv[1], g );
    }
    else
    {
        // usage statement
        cout << "Usage: Bacon_Number <database_file> [alternate_start]\n\n"
             << "database_file   - contains records of the form: \n\t          Movie Name/actor1/actor2/...\n"
             << "alternate_start - supply a different center of universe, default = \"Bacon, Kevin\"\n"
             << "\t          quotes are required\n";
        return 1;
    }

    return 0;
}

/**
 * handleDatabase(char*, Graph), takes an input file from char*, and
 *  dissects the contents into movies and actors to be stored in Graph
 * Also handles outputting onto the screen using Graph's member functions
 *  and handling the menu once the Graph has been built.
**/
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

    // while the file has information to read, read it.
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
    g.createMST();
    g.printStats();

    string prompt = "";

    while ( true )
    {
        cout << "Enter the name of an actor <Last, First> \"\" to exit: ";
        getline ( cin, prompt );

        if ( prompt == "" )
            exit ( 0 );

        g.getPath ( prompt );
    }

    return true;
}