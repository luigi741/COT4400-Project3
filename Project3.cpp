//==================================================================================================
// Project3.cpp
// This program solves the Itsy Bitsy Spider Maze
// By: Luis Castro
//==================================================================================================

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <stack>
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
	vector<Vertex> charList; 
};

struct Edge {
	Vertex *head;
	Vertex *tail;
	int weight;
};

void DFS(int z, int x, int y, stack<Vertex> moveStack, stack<int> directionStack,
			vector < vector < vector<Vertex> > > maze)
{
	int tempZ = z;
	int tempX = x;
	int tempY = y;
	//cout << maze[z][x][y].z << " ";
	//cout << maze[z][x][y].x << " ";
	//cout << maze[z][x][y].y << endl;

	// Mark the passed vertex into DFS function as visited and push onto stack
	maze[z][x][y].visited = true;
	moveStack.push(maze[z][x][y]);
	
	if (maze[z][x][y].start == true)
	{
		while(!moveStack.empty())
		{
			cout << "("  << moveStack.top().z;
			cout << ", " << moveStack.top().x;
			cout << ", " << moveStack.top().y;
			cout << ")"  << endl;
			moveStack.pop();
		}
	}

	// Let's get the appropriate size for the loop
	int loopSize;
	loopSize = maze[z][x][y].adjList.size();

	// Traverse the adjacencies of the passed in vertex
	for (int i = 0; i < loopSize; i++)
	{
		tempZ = maze[z][x][y].adjList[i].z;
		tempX = maze[z][x][y].adjList[i].x;
		tempY = maze[z][x][y].adjList[i].y;
		//cout << tempZ << " " << tempX << " " << tempY << endl;

		// If the adjacent vertex is unvisited, recurse DFS()
		if (maze[tempZ][tempX][tempY].visited == false)
		{
			DFS(tempZ, tempX, tempY, moveStack, directionStack, maze);
		}
	}
}

int main()
{
	cout << "Hello World!" << endl;
	cout << "Welcome to COT 4400 - Project 3" << endl;

	int sizeX, sizeY, sizeZ;
	int startX, startY, startZ;
	int endX, endY, endZ;
	int volume;
	int cellCount = 0;
	stack<Vertex> moveStack;
	stack<int> directionStack;

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
	vector <vector <vector <Vertex> > > maze(sizeZ, vector < vector <Vertex> > 
		(sizeX, vector <Vertex> (sizeY)));

	// Populate every cell in the maze with a number [0...n] where n is the
	// number of cells in the maze
	for (int k = 0; k < sizeZ; k++)
	{
		for (int i = 0; i < sizeX; i++)
		{
			for (int j = 0; j < sizeY; j++)
			{
				// Assign coordinates
				maze[k][i][j].z = k;
				maze[k][i][j].x = i;
				maze[k][i][j].y = j;

				// Give each cell a direction string
				inputFile >> maze[k][i][j].data;

				// Give each cell a cell number
				maze[k][i][j].cellNumber = cellCount;
				cellCount++;

				// Mark each node not visited
				maze[k][i][j].visited = false;

				// Mark each node start/end as false
				maze[k][i][j].start = false;
				maze[k][i][j].end = false;
			}
		}
	}

	// Mark the beginning and end cells of the maze
	maze[startZ][startX][startY].start = true;
	maze[endZ][endX][endY].end = true;

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
				cout << "\tCell Number: " << maze[k][i][j].cellNumber;
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

	cout << "\nStart" << endl;
	DFS(endZ, endX, endY, moveStack, directionStack, maze);
	cout << "End" << endl;

	inputFile.close();
	return 0;
}