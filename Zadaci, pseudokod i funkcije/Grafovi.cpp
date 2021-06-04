// 2. kolokvijum 2016 graf
SLList* getReachable(int idAirport, int time) {
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
