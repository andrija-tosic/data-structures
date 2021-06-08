SLList* getReachable(int idAirport, int time) { // 2. kolokvijum 2016.
    SLList* list = new SLList();
    LinkedNode* ptr = findNode(idAirport);

    setStatusForAllNodes(0);

    int zbir = 0;

    getReachable(ptr, list, zbir, time);

    return list;
}

void getReachable(LinkedNode* node, SLList* lista, int zbir, int time) {
    if (node == nullptr) {
        return;
    }

    if (node->status == 0) {
        node->status = 1;

        LinkedEdge* edge = node->adj;
        while (edge != nullptr) {
            if (zbir < time) {
                lista->addToHead(node);
                getReachable(edge->dest, list, zbir += node->vremePresedanja + edge->weight, time);
            }
            edge = edge->link;
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

int GraphAsListsInt::FindMaxReachable(LinkedNodeInt* node) { // 2. kolokvijum 2017.

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


bool GraphAsListsInt::canConnectDFS(LinkedNodeInt* ptr, LinkedNodeInt* dest, int n, int count) { // jun 2020.
	bool can = false;

	if (ptr == dest && count <= n)
		return true;

	LinkedEdgeInt* edge = ptr->adj;
	while (edge != nullptr && !can) {

		if (edge->dest->status != 1) {
			edge->dest->status = 1;
			can = canConnectDFS(edge->dest, dest, n, count + 1);
		}
		edge = edge->link;
	}
	return can;
}

bool GraphAsListsInt::canConnectBFS(LinkedNodeInt* ptrA, LinkedNodeInt* ptrB, int n) { // jun 2020.
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

void GraphAsListsInt::findLeastNodesPathDFS(LinkedNodeInt* node, LinkedNodeInt* last, int c, int& min) { // jun 2 2020.
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

int GraphAsListsInt::findLeastNodesPathBFS(int a, int b) { // jun 2 2020.
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
int GraphAsListsInt::findLeastNodesPathBFS(LinkedNodeInt* start, LinkedNodeInt* last) { // jun 2 2020.
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

int GraphAsListsInt::findLeastNodesPathBFS(LinkedNodeInt* start, LinkedNodeInt* last) { // jun 2 2020.
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

int GraphAsListsInt::updateDistanceFromBFS(LinkedNodeInt* node) { // januar 2017.
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

void GraphAsListsInt::updateDistanceFromDFS(LinkedNodeInt* node, int depth) { // januar 2017.
	if (depth < node->status) {
		node->status = depth;
		LinkedEdgeInt* edge = node->adj;
		while (edge != nullptr) {
			updateDistanceFromDFS(edge->dest, depth + 1);
			edge = edge->link;
		}
	}
}
