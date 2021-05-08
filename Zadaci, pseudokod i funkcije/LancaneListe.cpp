// Jun 2020 valjda
void InsertOrUpdate(int key, int value) {
    if (head == NULL) { // prazna lista
        head = new Node(key, value);
    }
    else if (head->next == NULL) { // samo head u listi
        if (head->key == key) {
            if (value == 0) {
                delete head;
            }
        }
        else if (key > head->key) {
            head->next = new Node(key, value);
            head->next->next = NULL;
        }
        else {
            Node node = new Node(key, value);
            node->next = head;
            head->next = NULL;
            head = node;
        }
    }
    else { // vise od 1 element u listi
        Node* prev = head;
        Node* tmp = head->next;
        while (tmp != NULL && tmp->key > key) {
            prev = prev->next;
            tmp = tmp->next;
        }
        if (tmp != NULL) {
            if (tmp->key == key) {
                if (value == 0) {
                    if (tmp->next != NULL) {
                        prev->next = tmp->next;
                    }
                    else {
                        prev->next = NULL;
                    }
                    delete tmp;
                }
                else {
                    tmp->value = value;
                }
            }
            else {
                Node* node = new Node(key, value);
                node->next = tmp->next;
                tmp->next = node;
            }
        }
        else {
            prev->next = new Node(key, value);
        }
    }
}

/* 2017 1. kol
Napisati funkciju void LList::fillInTheBlanks() koja iz dinamički implementirane
lančane liste, čiji su info delovi celi brojevi, uređene u neopadajući redosled, briše sve duple
čvorove a dodaje čvorove za sve one vrednosti koje nedostaju između vrednosti dva uzastopna
čvora liste. Na primer, ukoliko su info delovi dva uzastopna čvora vrednosti 1 i 4, između njih je
potrebno dodati i čvorove sa vrednostima 2 i 3. 
*/
void LList::fillInTheBlanks()
{
	if (head == NULL)
		return;

	LListNode* prv = head, * nxt = head->next;
	while (nxt != NULL)
	{
		if (prv->info == nxt->info)
		{
			prv->next = nxt->next;
			delete nxt;
			nxt = prv->next;
			continue;
		}

		while (nxt->info - prv->info > 1)
		{
			prv->next = new LListNode(prv->info + 1, nxt);
			prv = prv->next;
		}

		prv = nxt;
		nxt = nxt->next;
	}
}

// jun 2 2020
void LList::Exchange(LList& list, int value, int length) 
{
	if (this->head == NULL || list.head == NULL)
		throw "Empty list.";

	LListNode* pPok = this->head->next;
	LListNode* pPretPok = this->head;
	LListNode* dPok = list.head->next;
	LListNode* dPretPok = list.head;

	while (pPok != NULL && pPok->info != value)
	{
		pPretPok = pPok;
		pPok = pPok->next;
		dPretPok = dPok;
		dPok = dPok->next;
	}

	if (pPok == NULL)
		throw "Element not found";

	pPretPok->next = dPok;
	dPretPok->next = pPok;

	for (int i = 0; i < length; i++)
	{
		if (pPok == NULL || dPok == NULL)
			throw "Length out of bounds.";
		pPretPok = pPok;
		pPok = pPok->next;
		dPretPok = dPok;
		dPok = dPok->next;
	}

	pPretPok->next = dPok;
	dPretPok->next = pPok;
}
