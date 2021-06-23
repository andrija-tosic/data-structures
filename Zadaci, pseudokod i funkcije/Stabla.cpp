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


Node* maxSum(Node* p, int& maxS) { // ovo ni ne radi
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
	
	Node* maxPtr = nullptr;
	
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

int LevelDiff(int v1, int v2) { // april 2018.
	int l1  = -1, l2  = -1;
	levelDiff(root, v1, v2, l1, l2, 0);
	return a-b;
}

void levelDiff(Node* p, int v1, int v2, int& l1, int& l2, int d) { // april 2018.
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

 int Sum(Node* p, int min, int max, int d) { // decembar 2017.
 	if (!p)
 		return 0;
 		
 	int s = 0;
 	
 	s += Sum(p->left, min, max, d+1);
 	s += Sum(p->right, min, max, d+1);
 	
 	if (min < d && d < max)
 		s++;
 	
 	return s;
 }
