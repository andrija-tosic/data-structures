#include <iostream>
using namespace std;

#include "GraphInt.h"

inline const char* const boolToString(bool b)
{
	return b ? "true" : "false";
}

int main(int argc, char* argv[]) 
{
	GraphAsListsInt graph;
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
	graph.insertEdge(5, 4, 18);
	//graph.insertEdge(2, 1, 19);

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
	cout << "Is graph strongly connected: " << boolToString(graph.isStronglyConnected()) << endl;

	double** matrix;

	matrix = graph.formAdjacencyMatrix();
	cout << "Adj matrix: " << endl;

	for (int i=0;i<5;i++) {
		for (int j = 0; j < 5; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	GraphAsListsInt graph2;

	graph2.formGraphFromAdjacencyMatrix(matrix, 5);

	graph.print();
	cout << endl;
	graph2.print();
	matrix = graph2.formAdjacencyMatrix();
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

	return 0;
}

