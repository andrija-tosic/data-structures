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

