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
