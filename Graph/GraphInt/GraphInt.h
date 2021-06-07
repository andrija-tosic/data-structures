#pragma once

//#include "LinkedEdgeInt.h"
#include "LinkedNodeInt.h"
#include "QueueAsArrayInt.h"
#include <climits>

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
	void setPrevForAllNodes(LinkedNodeInt* node);
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
	double** formWeightMatrix();
	void formGraphFromWeightMatrix(double** mat, int n);
	int subGraph(LinkedNodeInt* p); // 2. kolokvijum 2019.
	void toUndirected(); // 2. kolokvijum 2019.
	int maxSubgraph(); // 2. kolokvijum 2019.
	int CalcPrevious(int subjects[], int n); // popravni 2. kolokvijum 2018.
public:
	LinkedNodeInt* FindMaxReachable(); // 2. kolokvijum 2017.
private:
	int FindMaxReachable(LinkedNodeInt* LinkedNodeInt);
public:
	void put(int A, int B, int x, LinkedNodeInt** niz, int* n);
private:
	void put(LinkedNodeInt* ptr, LinkedNodeInt* ptrB, int x, LinkedNodeInt** niz, int* n);
public:
	bool hasCycle();
private:
	bool hasCycle(LinkedNodeInt* ptr);
public:
	bool canConnect(int a, int b, int n); // jun 2020.
private:
	bool canConnect(LinkedNodeInt* ptr, LinkedNodeInt* dest, int n, int count);
	bool canConnectBFS(LinkedNodeInt* ptrA, LinkedNodeInt* ptrB, int n);
public:
	int findLeastNodesPathDFS(int a, int b); // jun 2 2020.
	int findLeastNodesPathBFS(int a, int b);
private:
	void findLeastNodesPathDFS(LinkedNodeInt* node, LinkedNodeInt* last, int c, int& min);
	int findLeastNodesPathBFS(LinkedNodeInt* start, LinkedNodeInt* last);
public:
	int FindMax(/* char* */ int airport); // januar 2017.
	void updateDistanceFrom(LinkedNodeInt* node, int depth);
};
