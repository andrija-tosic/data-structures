#include "GraphInt.h"

#include <iostream>
using namespace std;

#include "QueueAsArrayInt.h"
#include "StackAsArrayInt.h"

GraphAsListsInt::GraphAsListsInt() : start(nullptr), nodeNum()
{
}

GraphAsListsInt::~GraphAsListsInt()
{
	LinkedNodeInt* ptr = start;
	LinkedNodeInt* ptr_tmp;
	while (ptr != nullptr) {
		LinkedEdgeInt* edge = ptr->adj;
		LinkedEdgeInt* tmp;
		while (edge != nullptr) {
			tmp = edge;
			edge = edge->link;
			delete tmp;
		}
		ptr_tmp = ptr;
		ptr = ptr->next;
		delete ptr_tmp;
	}
}

LinkedNodeInt* GraphAsListsInt::findNode(const int& data) const
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr && ptr->node != data)
		ptr = ptr->next;
	return ptr;
}

LinkedEdgeInt* GraphAsListsInt::findEdge(const int& dataSrc, const int& dataDest) const
{
	LinkedNodeInt* ptr = findNode(dataSrc);
	if (ptr == nullptr)
		return nullptr;
	LinkedEdgeInt* pEdge = ptr->adj;
	while (pEdge != nullptr && pEdge->dest->node != dataDest)
		pEdge = pEdge->link;
	return pEdge;
}

void GraphAsListsInt::insertNode(const int& data)
{
	start = new LinkedNodeInt(data, nullptr, start);
	nodeNum++;
}

bool GraphAsListsInt::insertEdge(const int& dataSrc, const int& dataDest, const double& weight /*= 0*/)
{
	LinkedNodeInt* pSrc = nullptr;
	LinkedNodeInt* pDest = nullptr;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr && (pSrc == nullptr || pDest == nullptr)) {
		if (ptr->node == dataSrc) {
			pSrc = ptr;
		}
		else if (ptr->node == dataDest) {
			pDest = ptr;
		}
		ptr = ptr->next;
	}
	if (pSrc == nullptr || pDest == nullptr)
		return false;
	pSrc->adj = new LinkedEdgeInt(pDest, weight, pSrc->adj);
	return true;
}

bool GraphAsListsInt::deleteEdge(const int& dataSrc, const int& dataDest)
{
	LinkedNodeInt* pSrc = findNode(dataSrc);
	if (pSrc == nullptr)
		return false;

	LinkedEdgeInt* pEdgePrev = nullptr;
	LinkedEdgeInt* pEdge = pSrc->adj;
	while (pEdge != nullptr && pEdge->dest->node != dataDest) {
		pEdgePrev = pEdge;
		pEdge = pEdge->link;
	}
	if (pEdge == nullptr)
		return false;

	if (pEdgePrev == nullptr)
		pSrc->adj = pEdge->link;
	else
		pEdgePrev->link = pEdge->link;

	delete pEdge;

	return true;
}

void GraphAsListsInt::deleteEdgeToNode(const LinkedNodeInt* pDest)
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr)
	{
		LinkedEdgeInt* pEdgePrev = nullptr;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr && pEdge->dest != pDest) {
			pEdgePrev = pEdge;
			pEdge = pEdge->link;
		}
		if (pEdge != nullptr)
		{
			if (pEdgePrev == nullptr)
				ptr->adj = pEdge->link;
			else
				pEdgePrev->link = pEdge->link;
		}
		ptr = ptr->next;
	}
}

bool GraphAsListsInt::deleteNode(const int& data)
{
	LinkedNodeInt* prev = nullptr;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr && ptr->node != data) {
		prev = ptr;
		ptr = ptr->next;
	}
	if (ptr == nullptr)
		return false;

	LinkedEdgeInt* pEdge = ptr->adj;
	while (pEdge != nullptr) {
		LinkedEdgeInt* pEdgeTmp = pEdge->link;
		delete pEdge;
		pEdge = pEdgeTmp;
	}
	ptr->adj = nullptr;

	deleteEdgeToNode(ptr);

	if (prev == nullptr)
		start = start->next;
	else
		prev->next = ptr->next;

	delete ptr;
	nodeNum--;

	return true;
}

void GraphAsListsInt::print() const
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr)
	{
		cout << ptr->node << " -> ";
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			cout << pEdge->dest->node << " | ";
			pEdge = pEdge->link;
		}
		cout << endl;
		ptr = ptr->next;
	}
}

void GraphAsListsInt::setStatusForAllNodes(int status) const
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		ptr->status = status;
		ptr = ptr->next;
	}
}

long GraphAsListsInt::breadthFirstTraversal(const int& data) const
{
	long retVal = 0;

	LinkedNodeInt* ptr = findNode(data);
	if (ptr == nullptr)
		return 0;

	setStatusForAllNodes(1);

	QueueAsArrayLinkedNodeInt queue(nodeNum);
	queue.enqueue(ptr);
	ptr->status = 2;
	while (!queue.isEmpty()) {
		ptr = queue.dequeue();
		ptr->status = 3;
		ptr->visit();
		retVal += 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			if (pEdge->dest->status == 1) {
				queue.enqueue(pEdge->dest);
				pEdge->dest->status = 2;
			}
			pEdge = pEdge->link;
		}
	}
	cout << endl;
	return retVal;
}

long GraphAsListsInt::depthFirstTraversalIterative(const int& data) const
{
	long retVal = 0;

	LinkedNodeInt* ptr = findNode(data);
	if (ptr == nullptr)
		return 0;

	setStatusForAllNodes(1);

	StackAsArrayLinkedNodeInt stack(nodeNum);
	stack.push(ptr);
	ptr->status = 2;
	while (!stack.isEmpty()) {
		ptr = stack.pop();
		ptr->status = 3;
		ptr->visit();
		retVal += 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			if (pEdge->dest->status == 1) {
				stack.push(pEdge->dest);
				pEdge->dest->status = 2;
			}
			pEdge = pEdge->link;
		}
	}
	cout << endl;
	return retVal;
}

long GraphAsListsInt::depthFirstTraversalRecursive(LinkedNodeInt* ptr) const
{
	int retVal = 0;
	if (ptr->status != 1) {
		ptr->visit();
		ptr->status = 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			retVal += depthFirstTraversalRecursive(pEdge->dest);
			pEdge = pEdge->link;
		}
		retVal++;
	}
	return retVal;
}

long GraphAsListsInt::depthFirstTraversalRecursive(const int& data) const
{
	LinkedNodeInt* pNode = nullptr;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		ptr->status = 0;
		if (ptr->node == data) {
			pNode = ptr;
		}
		ptr = ptr->next;
	}

	if (pNode == nullptr)
		return 0;

	return depthFirstTraversalRecursive(pNode);
}

long GraphAsListsInt::topologicalOrderTravrsal() const
{
	int retVal = 0;

	setStatusForAllNodes(0);

	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			pEdge->dest->status += 1;
			pEdge = pEdge->link;
		}
		ptr = ptr->next;
	}

	QueueAsArrayLinkedNodeInt queue(nodeNum);
	ptr = start;
	while (ptr != nullptr) {
		if (ptr->status == 0)
			queue.enqueue(ptr);
		ptr = ptr->next;
	}

	while (!queue.isEmpty()) {
		ptr = queue.dequeue();
		ptr->visit();
		retVal += 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			pEdge->dest->status--;
			if (pEdge->dest->status == 0)
				queue.enqueue(pEdge->dest);
			pEdge = pEdge->link;
		}
	}
	cout << endl;
	return retVal;
}

int GraphAsListsInt::maxInputDegree()
{
	LinkedNodeInt* ptr = start;
	setStatusForAllNodes(0);
	while (ptr != nullptr) {
	LinkedEdgeInt* edge = ptr->adj;
		while (edge != nullptr) {
			edge->dest->status++;
			edge = edge->link;
		}
		ptr = ptr->next;
	}
	int max = 0;
	int maxNode = 0;
	ptr = start;
	while (ptr != nullptr) {
		if (ptr->status > max) {
			max = ptr->status;
			maxNode = ptr->node;
		}
		ptr = ptr->next;
	}
	return maxNode;
}

int GraphAsListsInt::maxOutputDegree()
{
	LinkedNodeInt* ptr = start;
	setStatusForAllNodes(0);
	while (ptr != nullptr) {
		LinkedEdgeInt* edge = ptr->adj;
		while (edge != nullptr) {
			ptr->status++;
			edge = edge->link;
		}
		ptr = ptr->next;
	}
	int max = 0;
	int maxNode = 0;
	ptr = start;
	while (ptr != nullptr) {
		if (ptr->status > max) {
			max = ptr->status;
			maxNode = ptr->node;
		}
		ptr = ptr->next;
	}
	return maxNode;
}

int GraphAsListsInt::noOutputDegree()
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		if (ptr->adj == nullptr) {
			return ptr->node;
		}
		ptr = ptr->next;
	}
	return -1;
}

int GraphAsListsInt::noInputDegree()
{
	LinkedNodeInt* ptr = start;
	setStatusForAllNodes(0);
	while (ptr != nullptr) {
		LinkedEdgeInt* edge = ptr->adj;
		while (edge != nullptr) {
			edge->dest->status++;
			edge = edge->link;
		}
		ptr = ptr->next;
	}
	ptr = start;
	while (ptr != nullptr) {
		if (ptr->status == 0) {
			return ptr->node;
		}
		ptr = ptr->next;
	}
	return -1;
}

double** GraphAsListsInt::formWeightMatrix()
{
	double** matrix = new double*[nodeNum]();
	for (int i = 0; i < nodeNum; i++) {
		matrix[i] = new double[nodeNum]();
	}

	LinkedNodeInt* ptr = start;
	int i = 0;
	while (ptr != nullptr) {
		ptr->status = i;
		ptr = ptr->next;
		i++;
	}

	ptr = start;
	i = 0;
	while (ptr != nullptr) {
		LinkedEdgeInt* edge = ptr->adj;
		while (edge != nullptr) {
			matrix[i][edge->dest->status] = edge->weight;
			edge = edge->link;
		}	
		i++;
		ptr = ptr->next;
	}

	return matrix;
}

void GraphAsListsInt::formGraphFromWeightMatrix(double** mat, int n)
{
	for (int i = n-1; i>=0; i--)
		insertNode(i+1);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mat[i][j] != 0) {
				insertEdge(i + 1, j + 1, mat[i][j]);
			}
		}
	}
}  

int GraphAsListsInt::subGraph(LinkedNodeInt* p) // 2. kolokvijum 2019.
{
	int value = 0;
	
	if (p->status == 1)
		return value;
	else
		p->status = 1;

	LinkedEdgeInt* edge = p->adj;
	while (edge != nullptr) {
		value += subGraph(edge->dest);
		edge = edge->link;
	}
	value++;
	return value;
}

void GraphAsListsInt::toUndirected() // 2. kolokvijum 2019.
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		LinkedEdgeInt* edge = ptr->adj;
		while (edge != nullptr) {
			bool alreadyContains = false;
			LinkedEdgeInt* edge2 = edge->dest->adj;
			while (edge2 != nullptr && !alreadyContains) {
				if (edge2->dest == ptr) {
					alreadyContains = true;
				}
				edge2 = edge2->link;
			}
			if (!alreadyContains) {
				insertEdge(edge->dest->node, ptr->node);
			}
			edge = edge->link;
		}
		ptr = ptr->next;
	}
}

int GraphAsListsInt::maxSubgraph() // 2. kolokvijum 2019.
{
	int max = 0;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		setStatusForAllNodes(0);
		int br = subGraph(ptr);
		if (br > max)
			max = br;

		ptr = ptr->next;
	}
	return max;
}

int GraphAsListsInt::CalcPrevious(int subjects[], int n) // popravni 2. kolokvijum 2018.
{
	int	brUslova = 0;
	setStatusForAllNodes(0);
	for (int i = 0; i < n; i++) {
		LinkedNodeInt* ptr = findNode(subjects[i]);
		if (ptr != nullptr) {
			LinkedEdgeInt* edge = ptr->adj;
			while (edge != nullptr) {
				if (edge->dest->status == 0) {
					edge->dest->status = 1;
					brUslova++;
				}
				edge = edge->link;
			}
		}
	}
	return brUslova;
}

LinkedNodeInt* GraphAsListsInt::FindMaxReachable() // 2. kolokvijum 2017.
{
	LinkedNodeInt* maxNode = nullptr;
	int max = 0;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		ptr->status = 0;
		int a = FindMaxReachable(ptr);

		if (a > max) {
			max = a;
			maxNode = ptr;
		}

		ptr = ptr->next;
	}
	return maxNode;
}

int GraphAsListsInt::FindMaxReachable(LinkedNodeInt* node) {

	int br = 0;

	if (node == nullptr)
		return br;

	if (node->status == 0) {
		node->status = 1;
		LinkedEdgeInt* edge = node->adj;
		while (edge != nullptr) {
			br += FindMaxReachable(edge->dest);
			edge = edge->link;
		}
		br++;
	}
	return br;
}

void GraphAsListsInt::put(int A, int B, int x, LinkedNodeInt** niz, int* n) {
	LinkedNodeInt* ptr = start;
	LinkedNodeInt* ptrA = nullptr, * ptrB = nullptr;
	while (ptr != nullptr) {
		ptr->status = 0;

		if (ptr->node == A)
			ptrA = ptr;

		if (ptr->node == B)
			ptrB = ptr;

		ptr = ptr->next;
	}
	if (ptrA != nullptr && ptrB != nullptr && ptrA != ptrB) {
		*n = 0;
		return put(ptrA, ptrB, x, niz, n);
	}
	else {
		return;
	}
}

void GraphAsListsInt::put(LinkedNodeInt* ptr, LinkedNodeInt* ptrB, int x, LinkedNodeInt** niz, int* n) {
	LinkedEdgeInt* edge = ptr->adj;
	while (edge != nullptr) {
		if (edge->dest->status == 0 && edge->weight < x && *n == 0) {
			edge->dest->status = 1; // obidjen
			put(edge->dest, ptrB, x, niz, n);
		}
		if (ptr == ptrB || *n > 0) {
			niz[(*n)++] = ptr;
			return;
		}
		edge = edge->link;
	}
}

bool GraphAsListsInt::hasCycle()
{
	bool cycle = false;
	setStatusForAllNodes(0);
	LinkedNodeInt* ptr = start;
	if (ptr != nullptr) {
		cycle = hasCycle(ptr);
	}
	return cycle;
}

bool GraphAsListsInt::hasCycle(LinkedNodeInt* ptr) {
	bool ciklus = false;
	LinkedEdgeInt* edge = ptr->adj;
	while (edge != nullptr && !ciklus) {
		if (edge->dest->status == 1) {
			return true;
		}
		ptr->status = 1;
		ciklus = hasCycle(edge->dest);
		edge = edge->link;
	}
	return ciklus;
}

bool GraphAsListsInt::canConnect(int a, int b, int n) { // jun 2020.
	LinkedNodeInt* ptr = start;
	LinkedNodeInt* ptrA = nullptr, * ptrB = nullptr;
	while (ptr != nullptr) {
		ptr->status = 0;
		if (ptr->node == a)
			ptrA = ptr;
		if (ptr->node == b)
			ptrB = ptr;

		ptr = ptr->next;
	}

	if (ptrA == ptrB)
		return true;

	// return canConnect(ptrA, ptrB, n, 0);
	return canConnectBFS(ptrA, ptrB, n);
}


bool GraphAsListsInt::canConnect(LinkedNodeInt* ptr, LinkedNodeInt* dest, int n, int count) {
	bool can = false;

	if (ptr == dest && count <= n)
		return true;

	LinkedEdgeInt* edge = ptr->adj;
	while (edge != nullptr && !can) {

		if (edge->dest->status != 1) {
			edge->dest->status = 1;
			can = canConnect(edge->dest, dest, n, count + 1);
		}
		edge = edge->link;
	}
	return can;
}

bool GraphAsListsInt::canConnectBFS(LinkedNodeInt* ptrA, LinkedNodeInt* ptrB, int n) {
	QueueAsArrayLinkedNodeInt queue(nodeNum);
	int count = 0;
	queue.enqueue(ptrA);

	setStatusForAllNodes(0);

	while (!queue.isEmpty()) {
		LinkedNodeInt* ptr = queue.dequeue();
		count++;
		if (ptr == ptrB && count <= n) {
			return true;
		}

		LinkedEdgeInt* edge = ptr->adj;
		while (edge != nullptr) {
			if (edge->dest->status != 1) {
				edge->dest->status = 1;
				queue.enqueue(edge->dest);
			}
			edge = edge->link;
		}
	}

	return false;
}

int GraphAsListsInt::findLeastNodesPathDFS(int a, int b) { // jun 2 2020.
	LinkedNodeInt* first = findNode(a);
	LinkedNodeInt* last = findNode(b);

	int min = INT_MAX;
	if (first == last)
		return 0;

	setStatusForAllNodes(0);
	findLeastNodesPathDFS(first, last, 0, min);
	return min;
}

void GraphAsListsInt::findLeastNodesPathDFS(LinkedNodeInt* node, LinkedNodeInt* last, int c, int& min) {
	LinkedEdgeInt* edge = node->adj;
	if (c < min && node == last)
		min = c;

	if (node != last && node->status == 0 && c < min) {
		node->status = 1;
		while (edge != nullptr) {
			findLeastNodesPathDFS(edge->dest, last, c + 1, min);
			edge = edge->link;
		}
	}
}

/*
void GraphAsListsInt::setPrevForAllNodes(LinkedNodeInt* node)
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		ptr->BFSprev = nullptr;
		ptr = ptr->next;
	}
}
*/

int GraphAsListsInt::findLeastNodesPathBFS(int a, int b) {
	LinkedNodeInt* first = nullptr, *last = nullptr;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		ptr->status = 0;
		if (ptr->node == a)
			first = ptr;
		if (ptr->node == b)
			last = ptr;

		ptr = ptr->next;
	}

	if (first == last)
		return 0;

	// setPrevForAllNodes(nullptr);
	return findLeastNodesPathBFS(first, last);
}

/*
int GraphAsListsInt::findLeastNodesPathBFS(LinkedNodeInt* start, LinkedNodeInt* last) {
	QueueAsArrayLinkedNodeInt queue(nodeNum);

	LinkedNodeInt* node = start;
	queue.enqueue(node);

	while (!queue.isEmpty()) {
		node = queue.dequeue();
		if (node == last) {
			break;
		}
		if (node->status == 0) {
			node->status = 1;

			LinkedEdgeInt* edge = node->adj;
			while (edge != nullptr) {
				queue.enqueue(edge->dest);
				edge->dest->BFSprev = node;
				edge = edge->link;
			}
		}
	}

	int length = 0;
	while (node->BFSprev != nullptr) {
		length++;
		node = node->BFSprev;
	}
	
	return length;
}
*/

int GraphAsListsInt::findLeastNodesPathBFS(LinkedNodeInt* start, LinkedNodeInt* last) {
	setStatusForAllNodes(-1);
	QueueAsArrayLinkedNodeInt queue(nodeNum);
	LinkedNodeInt* node = start;
	node->status = 0;
	queue.enqueue(node);
	while (!queue.isEmpty()) {
		node = queue.dequeue();
		if (node == last) {
			return node->status;
		}
		LinkedEdgeInt* edge = node->adj;
		while (edge) {
			if (edge->dest->status == -1) {
				edge->dest->status = node->status + 1;
				queue.enqueue(edge->dest);
			}
			edge = edge->link;
		}
	}
	return -1;
}

/*
int GraphAsListsInt::FindMax(char* airport) { // januar 2017.
	int max = 0;
	LinkedNodeInt* port = findNode(airport);
	setStatusForAllNodes(INT_MAX);
	port->status = INT_MAX;
	updateDistanceFrom(port, 0);
	LinkedNodeInt* ptr = start;
	while (ptr) {
		if (ptr != port && ptr->status != INT_MAX && ptr->status > max)
			max = ptr->status;

		ptr = ptr->next;
	}
	return max;
}
*/

int GraphAsListsInt::FindMax(/* char* */ int airport) { // januar 2017.
	return updateDistanceFromBFS(findNode(airport));
}

int GraphAsListsInt::updateDistanceFromBFS(LinkedNodeInt* node) {
	setStatusForAllNodes(-1);
	int max = 0;
	QueueAsArrayLinkedNodeInt queue(nodeNum);
	LinkedNodeInt* ptr = node;
	ptr->status = 0;
	queue.enqueue(ptr);
	while (!queue.isEmpty()) {
		ptr = queue.dequeue();

		LinkedEdgeInt* edge = ptr->adj;
		while (edge) {
			if (edge->dest->status == -1) {
				edge->dest->status = ptr->status + 1;
				
				if (ptr->status + 1 > max)
					max = ptr->status + 1;

				queue.enqueue(edge->dest);
			}
			edge = edge->link;
		}
	}
	return max;
}

void GraphAsListsInt::updateDistanceFrom(LinkedNodeInt* node, int depth) {
	if (depth < node->status) {
		node->status = depth;
		LinkedEdgeInt* edge = node->adj;
		while (edge != nullptr) {
			updateDistanceFrom(edge->dest, depth + 1);
			edge = edge->link;
		}
	}
}
