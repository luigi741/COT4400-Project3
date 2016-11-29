//==================================================================================================
// Project3.cpp
// This program solves the Itsy Bitsy Spider Maze
// By: Luis Castro
//==================================================================================================

/*#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/directed_graph.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
using namespace boost;*/

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#define DIRECTION 6
using namespace std;

struct Vertex {
	int x;
	int y;
	int z;
	bool start;
	bool end;
	bool visited;
};

struct Edge {
	int weight;
};

int main(int argc, char* argv[])
{
	cout << "Hello World!" << endl;
	cout << "Welcome to COT 4400 - Project 3" << endl;
	enum {N, E, S, W, U, D};

	int sizeX, sizeY, sizeZ;
	int startX, startY, startZ;
	int endX, endY, endZ;
	int volume;
	string directions[DIRECTION];

	// Open input.txt
	string fileLine;
	ifstream inputFile;
	inputFile.open("input2.txt");
	if (!inputFile.is_open())
	{
		cout << "Error opening file. Terminating program." << endl;
		return -1;
	}

	inputFile >> sizeX;
	inputFile >> sizeY;
	inputFile >> sizeZ;

	inputFile >> startX;
	inputFile >> startY;
	inputFile >> startZ;

	inputFile >> endX;
	inputFile >> endY;
	inputFile >> endZ;


	volume = sizeX * sizeY * sizeZ;
	vector < vector < vector < Vertex > > > maze;
	maze.resize(sizeX);
	
	for (int i = 0; i < sizeX; i++)
	{
		maze[i].resize(sizeY);

		for (int j = 0; j < sizeY; j++)
		{
			maze[i][j].resize(sizeZ);
		}
	}

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			for (int k = 0; k < sizeZ; k++)
			{
				maze[i][j][k].x = i;
				maze[i][j][k].y = j;
				maze[i][j][k].z = k;
			}
		}
	}

	while (!EOF)
	{
		inputFile >> directions;
	}

	inputFile.close();

	return 0;
}