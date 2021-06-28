// 2. kolokvijum 2016 minHeap
void Update(int val, int add) {
	int i=1;
	while (i <= numOfElements && arr[i] <= arr[2*i] && arr[i] <= arr[2*i+1] && arr[i] != val) {
		i++
	}
	if (i <= numOfElements && arr[i] == val) {
		if (add < 0) { // slucaj za upHeap
			int pom = arr[i];
			while (arr[i/2] > arr[i] && i >= 2) {
				arr[i] = arr[i/2];
				i /= 2;
			}

			arr[i] = pom;
		}
		else if (add > 0) // slucaj za downHeap
		{
			int pom = arr[i];
			while (arr[2*i] > arr[i] || arr[2*i + 1] > arr[i] && i <= numOfElements/2) {
				if (arr[2*i] > arr[2*i + 1]) {
					arr[i] = arr[2*i];
					i = 2*i;
				}
				else {
					arr[i] = arr[2*i + 1];
					i = 2*i + 1;
				}
			}

			arr[i] = pom;
		}
	}
}


Node* maxSum(Node* p, int& maxS) {
	if (p == nullptr) {
		maxS = -1;
		return nullptr;
	}
	
	int maxL, maxR;
	
	Node* ptrL = maxSum(p->left, maxL);
	Node* ptrR = maxSum(p->right, maxR);
	
	int lv = 0, rv = 0;
	
	if (p->left != nullptr)
		lv = p->left->key;
	
	if (p->right != nullptr)
		rv = p->right->key;
	
	maxS = lv + rv;
	
	Node* maxPtr = p;
	
	if (maxL > maxS) {
		maxS = maxL;
		maxPtr = ptrL;
	}
	
	if (maxR > maxS) {
		maxS = maxR;
		maxPtr = ptrR;
	}
	return maxPtr;
}

/************* april 2018. *************/
int LevelDiff(int v1, int v2) {
	int l1  = -1, l2  = -1;
	levelDiff(root, v1, v2, l1, l2, 0);
	return abs(a-b);
}

void levelDiff(Node* p, int v1, int v2, int& l1, int& l2, int d) {
	if (!p)
		return;
	
	if (p->key == v1)
		l1 = d;
	
	if (p->key == v2)
		l2 = d;
		
	if (l1 != -1 && l2 != -1)
		return;
	else {
		levelDiff(p->left, v1, v2, l1, l2, d+1);
		levelDiff(p->right, v1, v2, l1, l2, d+1);
	}
}

/************* decembar 2017. *************/
int Sum(Node* p, int min, int max, int d) {
 	if (!p)
 		return 0;
 		
 	int s = 0;
 	
 	s += Sum(p->left, min, max, d+1);
 	s += Sum(p->right, min, max, d+1);
 	
 	if (min < d && d < max)
 		s++;
 	
 	return s;
 }

/************* oktobar 2020. *************/
int findMaxPathLeaf(BSTNode* root, BSTNode** leaf) {
	int maxSum;
	findMaxPathLeaf(root, leaf, 0, maxSum);
	return maxSum;
}

void findMaxPathLeaf(BSTNode* node, BSTNode** leaf, int sum, int& maxSum) {
	if (!node)
		return;
	
	if (!(node->left) && !(node->right)) {
		sum += node->key;
		if (sum > maxSum) {
			maxSum = sum;
			*leaf = node;
		}
	}
	
	findMaxPathLeaf(node->left, leaf, sum, maxSum);
	findMaxPathLeaf(node->right, leaf, sum, maxSum);
}

/************* oktobar 2 2018. *************/
int maxLvlNodes(Node* node, int* count) {
	int maxLvl = -1;
	int* levels = new int[height()];
	maxLvlNodes(node, maxLvl, levels, 0);
	*count = levels[maxLvl];
	delete[] levels;
	return maxLvl;
}

void maxLvlNodes(Node* node, int& maxLvl, int levels[], int d) {
	if (!node)
		return;
		
	levels[d]++;
	
	if (levels[d] > levels[maxLvl]) {
		maxLvl = d;
	}
	
	maxLvlNodes(node->left, maxCount, maxLvl, levels, d+1);
	maxLvlNodes(node->right, maxCount, maxLvl, levels, d+1);
}

/************* 2. kolokvijum 2014. *************/
int deleteRightLeaves(BSTNode* p) {
	int count = 0;
	deleteRightLeaves(root, nullptr, count);
	return count
}

BSTNode* deleteRightLeaves(BSTNode* p, BSTNode* par, int& count) {
	if (!p || !par)
		return nullptr;

	if (par->right == p && !p->left && !p->right) {
		delete p;
		count++;
		return nullptr;
	}

	p->left = deleteRightLeaves(p->left, p, count);
	p->right = deleteRightLeaves(p->right, p, count);

	return p;
}

int LevelDiff(int v1, int v2) {
	int l1  = -1, l2  = -1;
	levelDiff(root, v1, v2, l1, l2, 0);
	return a-b;
}

void levelDiff(Node* p, int v1, int v2, int& l1, int& l2, int d) {
	if (!p)
		return;
	
	if (p->key == v1)
		l1 = d;
	
	if (p->key == v2)
		l2 = d;
		
	if (l1 != -1 && l2 != -1)
		return;
	else {
		levelDiff(p->left, v1, v2, l1, l2, d+1);
		levelDiff(p->right, v1, v2, l1, l2, d+1);
	}
}

int Sum(Node* p, int min, int max, int d) {
	if (!p)
 		return 0;
 		
 	int s = 0;
 	
 	s += Sum(p->left, min, max, d+1);
 	s += Sum(p->right, min, max, d+1);
 	
 	if (min < d && d < max)
 		s++;
 	
 	return s;
}

int getDeepest(BSTNode* node, BSTNode** deepest, int depth) {
	if (!node)
		return -1;
	
	BSTNode** dl, dr;
	int l = getDeepest(node->left, dl, depth+1);
	int r = getDeepest(node->right, dr, depth+1);
	
	*deepest = node;
	int m = depth;
	if (l > m) {
		m = l;
		deepest = dl;
	}
	if (r > m) {
		m = r;
		deepest = dr;
	}
	return m;
}

