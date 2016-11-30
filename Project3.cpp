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

// Enumerate the directions/moves
enum {N, E, S, W, U, D};

struct Vertex {
	int x;
	int y;
	int z;
	int cellNumber;
	bool start;
	bool end;
	bool visited;
	string data;
	vector<Vertex> adjList;
};

struct Edge {
	int weight;
};

int main()
{
	cout << "Hello World!" << endl;
	cout << "Welcome to COT 4400 - Project 3" << endl;

	int sizeX, sizeY, sizeZ;
	int startX, startY, startZ;
	int endX, endY, endZ;
	int volume;
	int cellCount = 0;
	vector<Vertex> adjList;

	// Open input.txt
	string fileLine;
	ifstream inputFile;
	inputFile.open("input3.txt");
	if (!inputFile.is_open())
	{
		cout << "Error opening file. Terminating program." << endl;
		return -1;
	}

	// Gets the size of the dimensions of the maze
	inputFile >> sizeZ;
	inputFile >> sizeX;
	inputFile >> sizeY;

	// Gets the start coordinates of the maze
	inputFile >> startZ;
	inputFile >> startX;
	inputFile >> startY;

	// Gets the end coordinates of the maze
	inputFile >> endZ;
	inputFile >> endX;
	inputFile >> endY;

	// Gets the total number of cells in the maze
	volume = sizeX * sizeY * sizeZ;

	// Declare a 3D vector
	//vector < vector < vector < Vertex > > > maze;
	vector <vector <vector <Vertex> > > maze(sizeZ, vector < vector <Vertex> > (sizeX, vector <Vertex> (sizeY)));

	// Resize the vector into the size described
/*	maze.resize(sizeZ);
	for (int k = 0; k < sizeZ; k++)
	{
		maze[k].resize(sizeX);
		for (int i = 0; i < sizeX; i++)
		{
			maze[k][i].resize(sizeY);
		}
	}*/

	// Populate every cell in the maze with a number [0...n] where n is the
	// number of cells in the 
	for (int k = 0; k < sizeZ; k++)
	{
		for (int i = 0; i < sizeX; i++)
		{
			for (int j = 0; j < sizeY; j++)
			{
				// Assign numbers
				maze[k][i][j].z = k;
				maze[k][i][j].x = i;
				maze[k][i][j].y = j;

				// Give each cell a direction string
				inputFile >> maze[k][i][j].data;

				// Give each cell a cell number
				maze[k][i][j].cellNumber = cellCount;
				cellCount++;
			}
		}
	}

	for (int k = 0; k < sizeZ; k++)
	{
		for (int i = 0; i < sizeX; i++)
		{
			for (int j = 0; j < sizeY; j++)
			{
				cout << "(" << maze[k][i][j].z << ", ";
				cout << maze[k][i][j].x << ", ";
				cout << maze[k][i][j].y << ")";
				cout << " = ";
				for (int l = 0; l < 6; l++)
				{
					cout << maze[k][i][j].data[l];
				}
				cout << endl;
			}
		}
	}

	int movePos;
	int moveDirection;

	// Now we need to go through each cell and get the adjacency list from the
	// binary string that holds the directions -> data
	for (int k = 0; k < sizeZ; k++)
	{
		for (int i = 0; i < sizeX; i++)
		{
			for (int j = 0; j < sizeY; j++)
			{
				for (int l = 0; l < 6; l++)
				{
					if (maze[k][i][j].data[l] == '1')
					{
						movePos = l;
						switch (movePos)
						{
							case 0:
								moveDirection = N;
								maze[k][i][j].adjList.push_back(maze[k][i-1][j]);
								//maze[k][i][j].edge.direction = moveDirection
								//maze[k][i][j].edge.destination = maze[k][i-1][j]
								//maze[k][i][j].vertexpointer = &maze[k][i-1][j]
								break;
							case 1:
								moveDirection = E;
								maze[k][i][j].adjList.push_back(maze[k][i][j+1]);
								break;
							case 2:
								moveDirection = S;
								maze[k][i][j].adjList.push_back(maze[k][i+1][j]);
								break;
							case 3:
								moveDirection = W;
								maze[k][i][j].adjList.push_back(maze[k][i][j-1]);
								break;
							case 4:
								moveDirection = U;
								maze[k][i][j].adjList.push_back(maze[k+1][i][j]);
								break;
							case 5:
								moveDirection = D;
								maze[k][i][j].adjList.push_back(maze[k-1][i][j]);
								break;
							default:
								break;
						}
					}
					movePos = 0;
				}
			}
		}
	}


/*	int vectorSize = 0;
	vectorSize = maze[0][0][0].adjList.size();
	cout << "Vector Size: " << vectorSize << endl;
	cout << "maze[2][2][2].cellNumber = " << maze[2][2][2].cellNumber << endl;
	
	for (int i = 0; i < vectorSize; i++)
	{
		cout << "(" << maze[0][0][0].adjList[i].z << ", ";
		cout << maze[0][0][0].adjList[i].x << ", ";
		cout << maze[0][0][0].adjList[i].y << ")";
		cout << endl;
	}
*/
	inputFile.close();
	return 0;
}

// Start with end -> push onto stack
// Build DFS keep pushing onto stack and then keep doing it until you hit
// the start and then pop() 