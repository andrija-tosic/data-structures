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
		}
		else
		{
			while (nxt->info - prv->info > 1)
			{
				prv->next = new LListNode(prv->info + 1, nxt);
				prv = prv->next;
			}

			prv = nxt;
			nxt = nxt->next;
		}
	}
}

// jun 2 2020
void LList::Exchange(LList& list, int value, int length) 
{
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

	pPretPok->next = dPok;
	dPretPok->next = pPok;

	for (int i = 0; i < length; i++)
	{
		pPretPok = pPok;
		pPok = pPok->next;
		dPretPok = dPok;
		dPok = dPok->next;
	}

	pPretPok->next = dPok;
	dPretPok->next = pPok;
}

/*
Septembar 2020

Koriscenjem jednostruko spregnute dinamicke lancane liste
bez pokazivaca na rep koja sadrzi cvorove sa jedinstvenim
kljucem i vrednoscu je implementirana samoorganizujuca lista.
Napisati funkciju koja vrednost value dodaje postojecoj
vrednosti cvora ciji je kljuc key. Nakon svakog azuriranja
vrednosti cvora za zadati kljuc, cvor koji taj kljuc sadrzi
se pomera za jedno mesto prema glavi liste. Ukoliko je vrednost
cvora postavljena na nulu, cvor se brise iz liste, a ukoliko cvor
sa zadatim kljucem ne postoji, dodaje se na glavu liste. Voditi
racuna o efikasnosti implementacije.
*/

void LList::UpdateNode(int key, int value) {
    if (head == NULL) { // prazna lista
        return;
    }
    
    if (head->info.key == key) { // mozda head
        if (value == 0) {
            delete head;
            head = NULL;
        }
        else {
            head->value += value;
    }
    else if (head->next != NULL && head->next->info.key == key) { // mozda drugi
        if (value == 0) {
            delete head->next;
            head->next = NULL;
        }
        else {
            head->next->value += value;
            head->next = head;
            head = head->next;
        }
    }
    else if (head->next->next == NULL) { // 2 elementa, nije ni head ni head->next
        addToHead(new Node(key, value));
    }
    else { // 3 ili vise elemenata
        Node* node1 = head;
        Node* node2 = head->next;
        Node* node3 = head->next->next;

        while (node3 != NULL && node3->info.key != key) {
            node1 = node1->next;
            node2 = node2->next;
            node3 = node3->next;

        }

        if (node3 != NULL && node3->info.key == key) { // nadjen
            if (value == 0) {
                if (node3->next != NULL) { // ako node3 nije poslednji u listi
                    node2->next = node3->next;
                }
                delete node3;
            }
            else { // ako value != 0
                node3->value += value;

                node1->next = node3;
                node2->next = node3->next;
                node3->next = node2;
                }
            }
        }
        else { // nije nadjen
            addToHead(new Node(key, value));
        }
    }
}

// dva resenja da se vidi raskos

void LList::UpdateNode(int key, int value)
{
	if (head == NULL)
		throw "prazno be";

	LListNode* crt = head->next, * prv = head;

	if (head->next == NULL || head->key == key)
	{
		if (head->key == key)
		{
			if (value == 0)
			{
				head = crt;
				delete prv;
			}
			else
			{
				head->info += value;
			}
			return;
		}
	}
	else if (head->next->info == key) // crt
	{
		if (value == 0)
		{
			head->next = head->next->next;
			delete crt;
		}
		else
		{
			head->next->info += value;
			head->next = head->next->next;
			crt->next = head;
			head = crt;
		}
		return;
	}

	else
	{
		LListNode* nxt = head->next->next;

		while (nxt != NULL)
		{
			if (nxt->key == key)
			{
				if (value == 0)
				{
					crt->next = nxt->next;
					delete nxt;
				}
				else
				{
					nxt->info =+ value;
					crt->next = nxt->next;
					nxt->next = crt;
					prv->next = nxt;
				}
				return;
			}

			prv = crt;
			crt = nxt;
			nxt = nxt->next;
		}
	}
	head = new LListNode(key, value, head);
}
