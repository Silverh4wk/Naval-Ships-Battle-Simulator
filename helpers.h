#pragma once
#include <iostream>
// tracking of what it can do so far:

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
// need to add these stuff later
// //           copy assignment operator - copy the list
//              move constructor - move the list
//              move assignment operator - move the list

template <typename t>
class list
{
private:
public:
    t* data;
    list *prev;
    list *next;
    static list *lastptr;
    static int count;

    list() : prev(nullptr),
             next(nullptr)
    {
        lastptr = this;
    }

    list(t* data) : data(data), prev(nullptr), next(nullptr)
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

    void push_front(t* data)
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

    void push_back(t* data)
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
            std::cout << "List is empty\n";
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
            std::cout << "Invalid range\n";
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
            std::cout << "Invalid range\n";
            return t();
        }

        list *p = this->prev;
        for (int i = 0; i < index; i++)
        {
            p = p->next;
        }
        return p->data;
    }

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
            std::cout << p->data << " <--> ";
            p = p->next;
        }
        std::cout << "NULL" << std::endl;
    }

    void reversePrint()
    {
        list *p = lastptr;

        while (p != nullptr)
        {
            std::cout << p->data << " <--> ";
            p = p->prev;
        }
        std::cout << "NULL" << std::endl;
    }

    t* getData() { return data;}
    int getSize() { return count; }

    ~list()
    {
        count--;
    }
};
template <typename t>
list<t> *list<t>::lastptr = nullptr;
template <typename t>
int list<t>::count = 0;