// 2. kolokvijum 2016 minHeap
void Update(int val, int add) {
	int i=1;
	while (i <= numOfElements && arr[i] <= arr[2*i] && arr[i] <= arr[2*i+1] && arr[i] != val) {
		i++
	}
	if (i <= numOfElements && arr[i] == val) {
		arr[i] += add;
		
		int br = arr[i];
		while(i <= numOfElements/2 && arr[2*i] < arr[i] && arr[2*i+1] < arr[i]) {
			arr[i] = arr[2*i];
			i *= 2;
		}
		arr[i] = br;
	}
}


Node* maxSum(Node* p, int& maxS) {
	if (p == nullptr) {
		maxS = -1;
		return nullptr;
	}
	
	int sumL, sumR;
	
	Node* ptrL = maxSum(p->left, sumL);
	Node* ptrR = maxSum(p->right, sumR);
	
	int lv = 0, dv = 0;
	
	if (p->left != nullptr)
		lv = p->left->key;
	
	if (p->right != nullptr)
		rv = p->right->key;
	
	maxS = lv + rv;
	
	if (sumL > maxS) {
		maxS = sumL;
		maxPtr = ptrL;
	}
	
	if (sumR > maxS) {
		maxS = sumR;
		maxPtr = ptrR;
	}
	return maxPtr;
}
