#pragma once
#include <iostream>
// tracking of what it can do so far:
// remonder to add a catch for underflow for pop_front
// Double linked list
// 1. add to next - add a node to the end of the list, if the list is empty, it will be the first node
// 2. push front - add a node to the front of the list, if the list is empty, it will be the first node
// 3. forward print - print the list from the prev to the next
// 4. reverse print - print the list from the next to the prev
// 5. pop_front - delete the first node in the list
// 6. delete node at index - delete the node at the index provided
// 7. get node at index - get the node at the index provided
// 8. get data - get the data of the node
// 9. get size - get the size of the list
// 10. clear list - delete all the nodes in the list
// 11. copy constructor - copy the list
// 12. copy assignment operator - copy the list
// 13. destructor - delete the list
// 14. enque - add a node to the end of the list
// 15. dequeue - delete the first node in the list
// 16. front - get the data of the first node in the list
// 17. back - get the data of the last node in the list
// need to add these stuff later
// //           copy assignment operator - copy the list
//              move constructor - move the list
//              move assignment operator - move the list

template <typename t>
class list {
public:
    t data;
    list *head;    // Pointer to the first item in the list
    list *next;    // Pointer to the next item in the list
    list *lastptr; // Pointer to the last item in the list
    list *first;   // Pointer to the first item in the list
    int count;

    list();
    list(t data);
    list(const list &other);
    list &operator=(const list &other);
    list(list &&other);
    list &operator=(list &&n);
    
    void push_front(t data);
    void push_back(t data);
    void pop_front();
    void deleteNodeAtIndex(int index);
    t getNode(int index);
    void deleteNode(list *node);
    
    // Queue operations
    void enqueue(t data);
    void dequeue();
    t front();
    t back();
    
    void clearList();
    void forwardPrint();
    void reversePrint();
    int getSize();
    bool empty();
    
    ~list();
};







// Default constructor
template <typename t>
list<t>::list() : head(nullptr), next(nullptr), lastptr(nullptr), first(nullptr), count(0) {}

// Constructor with data
template <typename t>
list<t>::list(t data) : data(data), head(nullptr), next(nullptr), lastptr(this), first(this), count(1) {
}

// Copy constructor
template <typename t>
list<t>::list(const list &other) {
    count = 0;
    head = nullptr;
    lastptr = nullptr;
    first = nullptr;

    list *current = other.head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}

// Copy assignment operator
template <typename t>
list<t> &list<t>::operator=(const list &other) {
    if (this != &other) {
        clearList();
        list *current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }
    return *this;
}

// Move constructor
template <typename t>
list<t>::list(list &&other) 
    : head(other.head), next(other.next), lastptr(other.lastptr), first(other.first), count(other.count) {
    other.head = nullptr; 
    other.next = nullptr;
    other.lastptr = nullptr;
    other.first = nullptr;
    other.count = 0;
}

// Move assignment operator
template <typename t>
list<t> &list<t>::operator=(list &&n) {
    if (this != &n) {
        clearList(); 

        head = n.head;
        next = n.next;
        lastptr = n.lastptr;
        first = n.first;
        count = n.count;

        n.head = nullptr;
        n.next = nullptr;
        n.lastptr = nullptr;
        n.first = nullptr;
        n.count = 0;
    }
    return *this;
}
// Push front
template <typename t>
void list<t>::push_front(t data) {
    list<t> *temp = new list<t>(data);
    temp->next = this->head;
    temp->head = nullptr;

    if (this->head != nullptr) {
        this->head->head = temp;
    }
    this->head = temp;

    if (count == 0) {
        lastptr = temp; 
    }
    count++;
}


// Push back
template <typename t>
void list<t>::push_back(t data) {
    list *temp = new list(data);
    if (head == nullptr) {
        head = temp;
        first = temp;
        lastptr = temp;
    } else {
        lastptr->next = temp;
        temp->head = lastptr;
        lastptr = temp;
    }
    count++;
}

// Pop front
template <typename t>
void list<t>::pop_front() {
    if (this->head == nullptr) {
        throw std::underflow_error("list is empty");
    }

    list *p = this->head;
    this->head = p->next;

    if (this->head != nullptr) {
        this->head->head = nullptr;
    } else {
        lastptr = nullptr; 
    }

    delete p;
    count--;
}


// Delete node at index
template <typename t>
void list<t>::deleteNodeAtIndex(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Invalid range");
        return;
    }

    list *p = this->head;

    for (int i = 0; i < index; i++) {
        p = p->next;
    }

    if (p->head != nullptr) {
        p->head->next = p->next;
    } else {
        this->head = p->next;
        if (this->head == nullptr) {
            first = nullptr;
            lastptr = nullptr;
        } else {
            first = this->head;
        }
    }

    if (p->next != nullptr) {
        p->next->head = p->head;
    } else {
        lastptr = p->head;
    }

    delete p;
    count--;
}


// Get node at index
template <typename t>
t list<t>::getNode(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Invalid range");
    }

    list *p = this->head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    return p->data;
}

// Delete node
template <typename t>
void list<t>::deleteNode(list *node) {
    if (node->head != nullptr) {
        node->head->next = node->next;
    } else {
        head = node->next; 
    }

    if (node->next != nullptr) {
        node->next->head = node->head;
    } else {
        lastptr = node->head; 
    }

    delete node;
    count--;
}

// Enqueue
template <typename t>
void list<t>::enqueue(t data) {
    push_back(data);
}

// Dequeue
template <typename t>
void list<t>::dequeue() {
    pop_front();
}

// Front
template <typename t>
t list<t>::front() {
    if (this->head == nullptr) {
        throw std::out_of_range("Queue is empty");
    }
    return this->head->data;
}

// Back
template <typename t>
t list<t>::back() {
    if (lastptr == nullptr) {
        throw std::out_of_range("Queue is empty");
    }
    return lastptr->data;
}

/// Clear list
template <typename t>
void list<t>::clearList() {
    list *p = this->head;
    while (p != nullptr) {
        list *temp = p; 
        p = p->next;    
        delete temp;    
    }
    this->head = nullptr; 
    this->lastptr = nullptr; 
    this->count = 0; 
}

// Forward print
template <typename t>
void list<t>::forwardPrint() {
    list *p = this->head;

    while (p != nullptr) {
        std::cout << p->data << ", ";
        p = p->next;
    }
    std::cout << " " << std::endl;
}

// Reverse print
template <typename t>
void list<t>::reversePrint() {
    list *p = lastptr;

    while (p != nullptr) {
        std::cout << p->data << ", ";
        p = p->head;
    }
    std::cout << " " << std::endl;
}

// Get size
template <typename t>
int list<t>::getSize() { 
    return count; 
}

// Check if empty
template <typename t>
bool list<t>::empty() {
    return count <= 0;
}

// Destructor // still need fixing
template <typename t>
list<t>::~list() {
    //clearList();
}