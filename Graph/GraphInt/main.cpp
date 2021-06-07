#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;


#include "GraphInt.h"

inline const char* const boolToString(bool b)
{
	return b ? "true" : "false";
}

int main(int argc, char* argv[]) 
{
	GraphAsListsInt graph;
	graph.insertNode(6);
	
	graph.insertNode(5);
	graph.insertNode(4);
	graph.insertNode(3);
	graph.insertNode(2);
	graph.insertNode(1);
	
	graph.insertEdge(1, 3, 12);
	graph.insertEdge(1, 2, 13);
	graph.insertEdge(3, 5, 14);
	graph.insertEdge(3, 2, 15);
	graph.insertEdge(4, 3, 16);
	graph.insertEdge(4, 2, 17);

	graph.insertEdge(5, 6, 19);
	graph.insertEdge(5, 4, 18);
	// graph.insertEdge(2, 1, 19);

	graph.breadthFirstTraversal(1);
	cout << endl;
	graph.depthFirstTraversalRecursive(1);
	cout << endl << endl;
	graph.depthFirstTraversalIterative(1);
	cout << endl;
	graph.print();
	cout << "Max input degree node: " << graph.maxInputDegree() << endl;
	cout << "Max output degree node: " << graph.maxOutputDegree() << endl;
	cout << "No input degree node: " << graph.noInputDegree() << endl;
	cout << "No output degree node: " << graph.noOutputDegree() << endl;
	// cout << "Is graph strongly connected: " << boolToString(graph.isStronglyConnected()) << endl;

	double** matrix;

	matrix = graph.formWeightMatrix();
	cout << "Adj matrix: " << endl;

	for (int i=0;i<5;i++) {
		for (int j = 0; j < 5; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	GraphAsListsInt graph2;

	graph2.formGraphFromWeightMatrix(matrix, 5);

	graph.print();
	cout << endl;
	graph2.print();
	matrix = graph2.formWeightMatrix();
	cout << "Adj matrix2: " << endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	graph2.setStatusForAllNodes(0);
	cout << "Graph2 subgraph" << " " << graph2.subGraph(graph2.findNode(1)) << endl;
	cout << "Graph2 max subgraph" << " " << graph2.maxSubgraph() << endl;
	graph2.toUndirected();

	graph2.print();

	int niz[] = { 1, 2, 3 };

	cout << "CalcPrevious: " << graph2.CalcPrevious(niz, 3) << endl;

	cout << "Max reachable node from Graph1: " << graph.FindMaxReachable()->node << endl;

	for (int i = 0; i < 5; i++)
		delete[] matrix[i];

	delete[] matrix;

	LinkedNodeInt** cvorovi = new LinkedNodeInt * [5];

	int br;
	graph.put(1, 4, 20, cvorovi, &br);

	for (int i = br-1; i >= 0; i--) {
		cout << cvorovi[i]->node << " ";
	}

	cout << endl;
	cout << "Graph1 has cycle: " << boolToString(graph.hasCycle()) << endl;

	cout << "Can connect 1 to 4 with length(path) <= 3: " << boolToString(graph.canConnect(1, 4, 3)) << endl;
	cout << "Can connect 1 to 4 with length(path) <= 2: " << boolToString(graph.canConnect(1, 4, 2)) << endl;

	auto startDFS = high_resolution_clock::now();
	cout << "Least nodes path 1 to 2: " << graph.findLeastNodesPathDFS(1, 2) << endl;
	cout << "Least nodes path 1 to 3: " << graph.findLeastNodesPathDFS(1, 3) << endl;
	cout << "Least nodes path 1 to 4: " << graph.findLeastNodesPathDFS(1, 4) << endl;
	cout << "Least nodes path 1 to 5: " << graph.findLeastNodesPathDFS(1, 5) << endl;
	cout << "Least nodes path 3 to 2: " << graph.findLeastNodesPathDFS(3, 2) << endl;
	cout << "Least nodes path 3 to 4: " << graph.findLeastNodesPathDFS(3, 4) << endl;
	cout << "Least nodes path 4 to 2: " << graph.findLeastNodesPathDFS(4, 2) << endl;
	
	cout << "Least nodes path 1 to 2: " << graph.findLeastNodesPathDFS(1, 2) << endl;
	cout << "Least nodes path 1 to 3: " << graph.findLeastNodesPathDFS(1, 3) << endl;
	cout << "Least nodes path 1 to 4: " << graph.findLeastNodesPathDFS(1, 4) << endl;
	cout << "Least nodes path 1 to 5: " << graph.findLeastNodesPathDFS(1, 5) << endl;
	cout << "Least nodes path 3 to 2: " << graph.findLeastNodesPathDFS(3, 2) << endl;
	cout << "Least nodes path 3 to 4: " << graph.findLeastNodesPathDFS(3, 4) << endl;
	cout << "Least nodes path 4 to 2: " << graph.findLeastNodesPathDFS(4, 2) << endl;
	auto stopDFS = high_resolution_clock::now();

	cout << endl;

	auto startBFS = high_resolution_clock::now();
	cout << "Least nodes path 1 to 2: " << graph.findLeastNodesPathBFS(1, 2) << endl;
	cout << "Least nodes path 1 to 3: " << graph.findLeastNodesPathBFS(1, 3) << endl;
	cout << "Least nodes path 1 to 4: " << graph.findLeastNodesPathBFS(1, 4) << endl;
	cout << "Least nodes path 1 to 5: " << graph.findLeastNodesPathBFS(1, 5) << endl;
	cout << "Least nodes path 3 to 2: " << graph.findLeastNodesPathBFS(3, 2) << endl;
	cout << "Least nodes path 3 to 4: " << graph.findLeastNodesPathBFS(3, 4) << endl;
	cout << "Least nodes path 4 to 2: " << graph.findLeastNodesPathBFS(4, 2) << endl;
	
	cout << "Least nodes path 1 to 2: " << graph.findLeastNodesPathBFS(1, 2) << endl;
	cout << "Least nodes path 1 to 3: " << graph.findLeastNodesPathBFS(1, 3) << endl;
	cout << "Least nodes path 1 to 4: " << graph.findLeastNodesPathBFS(1, 4) << endl;
	cout << "Least nodes path 1 to 5: " << graph.findLeastNodesPathBFS(1, 5) << endl;
	cout << "Least nodes path 3 to 2: " << graph.findLeastNodesPathBFS(3, 2) << endl;
	cout << "Least nodes path 3 to 4: " << graph.findLeastNodesPathBFS(3, 4) << endl;
	cout << "Least nodes path 4 to 2: " << graph.findLeastNodesPathBFS(4, 2) << endl;
	auto stopBFS = high_resolution_clock::now();

	cout << "DFS time: " << duration_cast<milliseconds>(stopDFS - startDFS).count() << " ms" << endl;
	cout << "BFS time: " << duration_cast<milliseconds>(stopBFS - startBFS).count() << " ms" << endl;

	cout << "Ekscentricitet cvora 1: " << graph.FindMax(1) << endl;
	cout << "Ekscentricitet cvora 2: " << graph.FindMax(2) << endl;
	cout << "Ekscentricitet cvora 3: " << graph.FindMax(3) << endl;
	cout << "Ekscentricitet cvora 4: " << graph.FindMax(4) << endl;
	cout << "Ekscentricitet cvora 5: " << graph.FindMax(5) << endl;

	return 0;
}
