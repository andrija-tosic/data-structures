#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {

    template<typename K, typename V>
    friend class ChainedHashTable;

protected:
    Node<T>* start;
    Node<T>* tail;

public:
    LinkedList() { start = tail = nullptr; }
    ~LinkedList();
    void InsertToHead(const T& data);
    void InsertToTail(const T& data);
    void InsertAfter(const T& to_find, const T& data);
    void InsertBefore(const T& to_find, const T& data);
    void DeleteFromHead();
    void DeleteFromTail();
    void DeleteNode(const T& data);

    bool isEmpty() const;
    void Print() const;
    Node<T>* GetLeft(Node<T>* node) const;
    void Swap(Node<T>* node1, Node<T>* node2);
    void InsertionSort(bool rastuci);
    void BubbleSort(bool rastuci);
    void SelectionSort(bool rastuci);
};

template <typename T>
LinkedList<T>::~LinkedList()
{
    Node<T>* element = start;
    Node<T>* traveler;
    while (element) {
        traveler = element->link;
        delete element;
        element = traveler;
    }
}

template <typename T>
void LinkedList<T>::InsertToHead(const T& data)
{
    Node<T>* node = new Node<T>(data);
    if (!start) {
        start = tail = node;
    } else {
        node->link = start;
        start = node;
    }
    //cout << data << " Inserted to head" << endl;
}

template <typename T>
void LinkedList<T>::InsertToTail(const T& data)
{
    Node<T>* node = new Node<T>(data);
    if (!start) {
        start = tail = node;
    } else {
        tail->link = node;
        tail = node;
    }
    //cout << data << " Inserted to tail" << endl;
}

template <typename T>
void LinkedList<T>::InsertAfter(const T& to_find, const T& data)
{
    Node<T>* pok = start;
    while (pok && pok->info != to_find) {
        pok = pok->link;
    }
    if (pok && pok->info == to_find) {
        Node<T>* node = new Node<T>(data);
        node->info = data;
        node->link = pok->link;
        pok->link = node;

        if (pok == tail)
            tail = node;
        //cout << data << " Inserted after " << to_find << endl;
    } else {
        //cout << "node with " << to_find << " not found, not Inserting" << endl;
    }
}

template <typename T>
void LinkedList<T>::InsertBefore(const T& to_find, const T& data)
{
    if (start) {
        if (start->info == to_find) {
            InsertToHead(data);
        } else if (start != tail) {
            Node<T>* prev = start;
            Node<T>* pok = start->link;
            while (pok && pok->info != to_find) {
                pok = pok->link;
                prev = prev->link;
            }
            if (pok) {
                Node<T>* node = new Node<T>(data);
                node->info = data;
                node->link = prev->link;
                prev->link = node;
                //cout << data << " Inserted before " << to_find << endl;
            } //else
                //cout << "node with " << to_find << " not found, not Inserting" << endl;
        }
    }
}

template <typename T>
void LinkedList<T>::DeleteFromHead()
{
    if (start) {
        if (start != tail) {
            Node<T>* old_start = start;
            //cout << "Deleted " << start->info << " from head" << endl;
            start = start->link;
            delete old_start;
        } else {
            //cout << "Deleted " << start->info << " from head" << endl;
            delete start;
            start = tail = nullptr;
        }
    }
}

template <typename T>
void LinkedList<T>::DeleteFromTail()
{
    if (start) {
        if (start != tail) {
            Node<T>* pok = start;
            while (pok->link != tail) {
                pok = pok->link;
            }
            //cout << "Deleted " << tail->info << " from tail" << endl;
            delete tail;
            pok->link = nullptr;
            tail = pok;
        } else {
            //cout << "Deleted " << tail->info << " from tail" << endl;
            delete tail;
            start = tail = nullptr;
        }
    }
}

template <typename T>
void LinkedList<T>::DeleteNode(const T& data)
{
    if (start) {
        if (start->info == data) {
            DeleteFromHead();
        } else {
            Node<T>* prev = start;
            Node<T>* pok = start->link;
            while (pok && pok->info != data) {
                pok = pok->link;
            }
            if (pok) {
                if (pok == tail) {
                    tail = prev;
                } else {
                    prev->link = pok->link;
                }
                pok = nullptr;
                delete pok;
                //cout << "Deleted node " << data << endl;
            } //else
                //cout << "node " << data << " not found, not deleting" << endl;
        }
    }
}

template<typename T>
bool LinkedList<T>::isEmpty() const {
    return !start;
}

template <typename T>
void LinkedList<T>::Print() const
{
    if (start) {
        Node<T>* pok = start;
        while (pok) {
            cout << pok->info << " ";
            pok = pok->link;
        }
        cout << endl;
    } else
        cout << "list empty" << endl;
}

template <typename T>
Node<T>* LinkedList<T>::GetLeft(Node<T>* node) const
{
    Node<T>* tmp = start;
    while (tmp && tmp->link != node)
        tmp = tmp->link;
    return tmp;
}

template <typename T>
void LinkedList<T>::Swap(Node<T>* node1, Node<T>* node2)
{
    if (node1 != node2) {
        Node<T>* left1 = GetLeft(node1);
        Node<T>* left2 = GetLeft(node2);

        if (!left1) {
            start = node2;
        }
        else if (left1 != node2) {
            left1->link = node2;
        }
        if (!left2) {
            start = node1;
        }
        else if (left2 != node1) {
            left2->link = node1;
        }
        if (node1->link == node2) {
            node1->link = node2->link;
            node2->link = node1;
        }
        else if (node2->link == node1) {
            node2->link = node1->link;
            node1->link = node2;
        }
        else {
            Node<T>* tmp = node1->link;
            node1->link = node2->link;
            node2->link = tmp;
        }
    }
}

template <typename T>
void LinkedList<T>::InsertionSort(bool rastuci)
{
    if (start && start != tail) {
        Node<T>* left;
        Node<T>* element = start;
        Node<T>* traveler = element->link;
        while (traveler) {
            while (traveler && (rastuci ? (element->info <= traveler->info) : (element->info >= traveler->info))) {
                element = element->link;
                traveler = traveler->link;
            }
            Node<T>* tmp;
            left = element;
            if (traveler) {
                while (traveler && (rastuci ? (element->info >= traveler->info) : (element->info <= traveler->info)))
                    traveler = traveler->link;

                if (rastuci ? (element->info >= GetLeft(traveler)->info) : (element->info <= GetLeft(traveler)->info)) {
                    left = GetLeft(element);
                    if (!left)
                        start = element->link;
                    else
                        left->link = element->link;

                    tmp = GetLeft(traveler);
                    tmp->link = element;
                    element->link = traveler;
                }
                Print();
                element = start;
                traveler = element->link;
            }
        }
    }
}

template <typename T>
void LinkedList<T>::BubbleSort(bool rastuci)
{
    if (start && start != tail) {
        bool zamena = true;
        Node<T>* node = start;
        while (zamena) {
            if (!node || !(node->link)) {
                node = start;
            }
            zamena = false;
            while (node && node->link) {
                Node<T>* node_link = node->link;
                if (rastuci ? (node->info > (node->link)->info) : (node->info < (node->link)->info)) {
                    zamena = true;
                    Swap(node, node->link);
                    Print();
                }
                node = node_link;
            }
        }
    }
}

template <typename T>
void LinkedList<T>::SelectionSort(bool rastuci)
{
	Print();
    if (start && start != tail) {
        Node<T>* min_or_max = start;
        Node<T>* tmp = start->link;
        Node<T>* current = start;

        while (current) {
            tmp = min_or_max->link;

            while (tmp) {
                if (rastuci ? (tmp->info < min_or_max->info) : (tmp->info > min_or_max->info)) {
                    min_or_max = tmp;
                }
                tmp = tmp->link;
            }
            if (current == min_or_max) {
                //break;
            }
            Swap(current, min_or_max);
            Print();
            current = min_or_max->link;
            min_or_max = current;
        }
    }
}