/**********|**********|**********|
Program: helpers.cpp / helpers.h
Course: Object Oriented Programming
Trimester: 2430
Name: Hazim Elamin Mohamed Ali musa
ID: 241UC2400P
Lecture Section: TC2L
Tutorial Section: TT7L
Email: HAZIM.ELAMIN.MOHAMED@student.mmu.edu.my
Phone: +60-111-871-9811
**********|**********|**********/
#pragma once
#include <iostream>
#include <stdexcept>

// tracking of what it can do so far:
// reminder: add a catch for underflow for pop_front
// Double linked list
// 1. add to end - add a node to the end of the list, if the list is empty, it will be the first node
// 2. push front - add a node to the front of the list, if the list is empty, it will be the first node
// 3. forward print - print the list from beginning to end
// 4. reverse print - print the list from end to beginning
// 5. pop_front - delete the first node in the list
// 6. delete node at index - delete the node at the index provided
// 7. get node at index - get the node at the index provided
// 8. get data - get the data of the node
// 9. get size - get the size of the list
// 10. clear list - delete all the nodes in the list
// 11. copy constructor - copy the list
// 12. copy assignment operator - copy the list
// 13. destructor - delete the list
// 14. enqueue - add a node to the end of the list
// 15. dequeue - delete the first node in the list
// 16. front - get the data of the first node in the list
// 17. back - get the data of the last node in the list
// // need to add these later(remember to update what it does since multiple refactors and fixes):
// //     move constructor - move the list
// //     move assignment operator - move the list

template <typename T>
class list {
public:
    // Node structure (each node is an instance of list<T>)
    T data;
    list* prev; // Pointer to the previous item in the list
    list* next; // Pointer to the next item in the list

    // Container pointers and counter
    list* head;   // Pointer to the first node (when this is acting as container)
    list* tail;   // Pointer to the last node (when this is acting as container)
    int count;

    // Constructors/Destructor and assignment operators
    list();
    list(T data);
    list(const list& other);
    list& operator=(const list& other);
    list(list&& other);
    list& operator=(list&& other);
    ~list();

    // Methods for list manipulation
    void insertNodeAtIndex(int index, T data);
    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void deleteNodeAtIndex(int index);
    T getNode(int index);
    void deleteNode(list* node);

    // Queue operations
    void enqueue(T data);
    void dequeue();
    T front();
    T back();

    void clearList();
    void forwardPrint();
    void reversePrint();
    int getSize();
    bool empty();
};

// ================================
// Implementation
// ================================

// Default constructor for an empty container
template <typename T>
list<T>::list() : prev(nullptr), next(nullptr), head(nullptr), tail(nullptr),
count(0) {
}

// Constructor to create a new node with data.
// This constructor is used by the push methods when creating a new node.
template <typename T>
list<T>::list(T data)
    : data(data), prev(nullptr), next(nullptr), head(nullptr), tail(nullptr),
    count(1) {
}

// Copy constructor (copies nodes from other list)
template <typename T>
list<T>::list(const list& other)
    : head(nullptr), tail(nullptr), count(0) {
    list* current = other.head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}

// Copy assignment operator
template <typename T>
list<T>& list<T>::operator=(const list& other) {
    if (this != &other) {
        clearList();
        list* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }
    return *this;
}

// Move constructor
template <typename T>
list<T>::list(list&& other)
    : head(other.head), tail(other.tail), count(other.count) {
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
}

// Move assignment operator
template <typename T>
list<T>& list<T>::operator=(list&& other) {
    if (this != &other) {
        clearList();
        head = other.head;
        tail = other.tail;
        count = other.count;

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }
    return *this;
}

// Push front: add a node to the front of the list.
template <typename T>
void list<T>::push_front(T data) {
    list<T>* temp = new list<T>(data);
    if (head == nullptr) {
        head = tail = temp;
    }
    else {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
    count++;
}

// Push back: add a node to the end of the list.
template <typename T>
void list<T>::push_back(T data) {
    list<T>* temp = new list<T>(data);
    if (head == nullptr) {
        head = tail = temp;
    }
    else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
    count++;
}

// Pop front: remove the node at the front of the list.
template <typename T>
void list<T>::pop_front() {
    if (head == nullptr) {
        throw std::underflow_error("list is empty");
    }
    list<T>* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    else {
        tail = nullptr;
    }
    delete temp;
    count--;
}

template <typename T>
void list<T>::insertNodeAtIndex(int index, T data) {
    if (index < 0 || index > count) {
        throw std::out_of_range("Invalid range");
    }

    // If inserting at the front (index 0)
    if (index == 0) {
        push_front(data);
        return;
    }

    // If inserting at the end (index == count)
    if (index == count) {
        push_back(data);
        return;
    }

    // Otherwise, traverse to the index and insert
    list<T>* temp = new list<T>(data);
    list<T>* p = head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }

    temp->prev = p->prev;
    temp->next = p;
    p->prev->next = temp;
    p->prev = temp;

    count++;
}

// Delete node at a given index.
template <typename T>
void list<T>::deleteNodeAtIndex(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Invalid range");
    }
    list<T>* p = head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    deleteNode(p);
}

// Returns the data at the node located at the given index.
template <typename T>
T list<T>::getNode(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Invalid range");
    }
    list<T>* p = head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    return p->data;
}

// Delete a given node from the list.
template <typename T>
void list<T>::deleteNode(list<T>* node) {
    if (node == nullptr)
        return;

    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
        head = node->next; 

    if (node->next != nullptr)
        node->next->prev = node->prev;
    else
        tail = node->prev; 

    delete node;
    count--;
}

// Queue operations - simply use list operations.
template <typename T>
void list<T>::enqueue(T data) {
    push_back(data);
}

template <typename T>
void list<T>::dequeue() {
    pop_front();
}

template <typename T>
T list<T>::front() {
    if (head == nullptr) {
        throw std::out_of_range("Queue is empty");
    }
    return head->data;
}

template <typename T>
T list<T>::back() {
    if (tail == nullptr) {
        throw std::out_of_range("Queue is empty");
    }
    return tail->data;
}

// Clear the entire list.
template <typename T>
void list<T>::clearList() {
    list<T>* current = head;
    while (current != nullptr) {
        list<T>* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = tail = nullptr;
    count = 0;
}

// Print list from beginning to end.
template <typename T>
void list<T>::forwardPrint() {
    list<T>* p = head;
    while (p != nullptr) {
        std::cout << p->data << ", ";
        p = p->next;
    }
    std::cout << std::endl;
}

// Print list from end to beginning.
template <typename T>
void list<T>::reversePrint() {
    list<T>* p = tail;
    while (p != nullptr) {
        std::cout << p->data << ", ";
        p = p->prev;
    }
    std::cout << std::endl;
}

// Return the number of nodes in the list.
template <typename T>
int list<T>::getSize() {
    return count;
}

// Check if the list is empty.
template <typename T>
bool list<T>::empty() {
    return count == 0;
}

// Destructor for the list container.
template <typename T>
list<T>::~list() {
    clearList();
}
