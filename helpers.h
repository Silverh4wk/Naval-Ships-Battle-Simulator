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
class list
{
public:
    t data;
    list *prev;
    list *next;
    list *lastptr;
    int count;

    list() : prev(nullptr),
             next(nullptr),
             lastptr(this),
             count(0)
    {
        lastptr = this;
        count++;
    }

    list(t data) : data(data),
                   prev(nullptr),
                   next(nullptr),
                   lastptr(this),
                   count(0)
    {
        lastptr = this;
        count++;
    }

    list operator=(const list &n)
    {
        this->data = n.data;
        this->prev = n.prev;
        this->next = n.next;
        return *this;
    }

    list(const list &n)
    {
        this->data = n.data;
        this->prev = n.prev;
        this->next = n.next;
    }

    void push_front(t data)
    {
        list<t> *temp = new list<t>(data);
        temp->prev = nullptr;
        temp->next = this->prev;

        if (this->prev != nullptr)
        {
            this->prev->prev = temp;
        }
        this->prev = temp;
        if (this->next == nullptr)
        {
            this->next = temp;
        }
    }

    void push_back(t data)
    {
        list<t> *temp = new list<t>(data);
        temp->next = nullptr;

        if (this->prev == nullptr)
        {
            this->prev = temp;
            this->next = temp;
        }
        else
        {
            this->next->next = temp;
            temp->prev = this->next;
            this->next = temp;
        }
    }

    void pop_front()
    {
        if (this->prev == nullptr)
        {
            throw std::out_of_range("list is empty");
            return;
        }

        list *p = this->prev;

        this->prev = p->next;

        if (this->prev == nullptr)
        {
            this->next = nullptr;
        }

        delete p;
    }

    void deleteNodeAtIndex(int index)
    {
        if (index < 0 || index >= count)
        {
            throw std::out_of_range("Invalid range");
            return;
        }

        list *p = this->prev;

        for (int i = 0; i < index; i++)
        {
            p = p->next;
        }

        if (p->prev != nullptr)
        {
            p->prev->next = p->next;
        }
        else
        {
            this->prev = p->next;
        }

        if (p->next != nullptr)
        {
            p->next->prev = p->prev;
        }
        else
        {
            this->next = p->prev;
        }

        delete p;
        count--;
    }

    t getNode(int index)
    {
        if (index < 0 || index >= count)
        {
            throw std::out_of_range("Invalid range");
            return t();
        }

        list *p = this->prev;
        for (int i = 0; i < index; i++)
        {
            p = p->next;
        }
        return p->data;
    }

    // queue operations
    void enqueue(t data)
    {
        push_back(data);
    }

    void dequeue()
    {
        pop_front();
    }

    t front()
    {
        if (this->prev == nullptr)
        {
            throw std::out_of_range("Queue is empty");
        }
        return this->prev->data;
    }

    t back()
    {
        if (this->next == nullptr)
        {
            throw std::out_of_range("Queue is empty");
        }
        return this->next->data;
    }
    //

    void clearList()
    {
        list *p = this->prev;
        while (p != nullptr)
        {
            list *temp = p;
            p = p->next;
            delete temp;
        }
        this->prev = nullptr;
        this->next = nullptr;
        count = 0;
    }

    void forwardPrint()
    {
        list *p = this->prev;

        while (p != nullptr)
        {
            std::cout << p->data << ", ";
            p = p->next;
        }
        std::cout << " " << std::endl;
    }

    void reversePrint()
    {
        list *p = lastptr;

        while (p != nullptr)
        {
            std::cout << p->data << ", ";
            p = p->prev;
        }
        std::cout << " " << std::endl;
    }

    t *getData() { return data; }
    int getSize() { return count; }

    bool empty()
    {
        return count < 0;
    }
    ~list()
    {
        count--;
    }
};
