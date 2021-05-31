#pragma once

//#include "LinkedEdgeInt.h"
#include "LinkedNodeInt.h"

class GraphAsListsInt
{
protected:
	LinkedNodeInt* start;
	long nodeNum;
public:
	GraphAsListsInt();
	~GraphAsListsInt();

	LinkedNodeInt* findNode(const int& data) const;
	LinkedEdgeInt* findEdge(const int& dataSrc, const int& dataDest) const;

	void insertNode(const int& data);
	bool insertEdge(const int& dataSrc, const int& dataDest, const double& weight = 0);

private:
	void deleteEdgeToNode(const LinkedNodeInt* pDest);
public:
	bool deleteEdge(const int& dataSrc, const int& dataDest);
	bool deleteNode(const int& data);

	void print() const;

public:
	void setStatusForAllNodes(int status) const;
public:
	long breadthFirstTraversal(const int& data) const;
	long depthFirstTraversalIterative(const int& data) const;
private:
	long depthFirstTraversalRecursive(LinkedNodeInt* ptr) const;
public:
	long depthFirstTraversalRecursive(const int& data) const;

	long topologicalOrderTravrsal() const;

	int maxInputDegree();
	int maxOutputDegree();
	int noOutputDegree();
	int noInputDegree();
	bool isStronglyConnected();
	double** formAdjacencyMatrix();
	void formGraphFromAdjacencyMatrix(double** mat, int n);
	int subGraph(LinkedNodeInt* p); // 2. kolokvijum 2019.
	void toUndirected(); // 2. kolokvijum 2019.
	int maxSubgraph(); // 2. kolokvijum 2019.
	int CalcPrevious(int subjects[], int n); // popravni 2. kolokvijum 2018.
	LinkedNodeInt* FindMaxReachable(); // 2. kolokvijum 2017.
	int FindMaxReachable(LinkedNodeInt* node);
};

