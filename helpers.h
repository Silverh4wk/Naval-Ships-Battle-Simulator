#include <iostream>
//tracking of what it can do so far:

// Double linked list
// 1. add to tail - add a node to the end of the list, if the list is empty, it will be the first node
// 2. push front - add a node to the front of the list, if the list is empty, it will be the first node
// 3. forward print - print the list from the head to the tail
// 4. reverse print - print the list from the tail to the head
// 5. pop_front - delete the first node in the list
// 6. delete node at index - delete the node at the index provided
// 7. get node at index - get the node at the index provided
// 8. get data - get the data of the node
// 9. get size - get the size of the list
// 10. clear list - delete all the nodes in the list
// 11. copy constructor - copy the list
// 12. destructor - delete the list
// need to add these stuff later
//           copy assignment operator - copy the list
//           move constructor - move the list
//           move assignment operator - move the list

template <typename t>
class list
{
private:
public:
    t data;
    list *head;
    list *tail;
    static list *lastptr;
    static int count;
    
    list() : head(nullptr),
             tail(nullptr),
             data(0)
    {
        lastptr = this;
        count++;
    }

    list operator=(const list &n)
    {
        this->data = n.data;
        this->head = n.head;
        this->tail = n.tail;
        return *this;
    }

    list(const list &n)
    {
        this->data = n.data;
        this->head = n.head;
        this->tail = n.tail;
    }

    void push_front(t data)
    {
        list<t> *temp = new list<t>(data);
        temp->head = nullptr;
        temp->tail = this->head;

        if (this->head != nullptr)
        {
            this->head->head = temp;
        }
        this->head = temp;
        if (this->tail == nullptr)
        {
            this->tail = temp;
        }
    }

    void push_back(t data)
    {
        list<t> *temp = new list<t>(data);
        temp->tail = nullptr;

        if (this->head == nullptr)
        {
            this->head = temp;
            this->tail = temp;
        }
        else
        {
            this->tail->tail = temp;
            temp->head = this->tail;
            this->tail = temp;
        }
    }

    void pop_front()
{
    if (this->head == nullptr)
    {
        std::cout << "List is empty\n";
        return;
    }

    list* p = this->head;

    this->head = p->tail;

    if (this->head == nullptr)
    {
        this->tail = nullptr;
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

        list *p = this->head;

        for (int i = 0; i < index; i++)
        {
            p = p->tail;
        }

        if (p->head != nullptr)
        {
            p->head->tail = p->tail;
        }
        else
        {
            this->head = p->tail;
        }

        if (p->tail != nullptr)
        {
            p->tail->head = p->head;
        }
        else
        {
            this->tail = p->head;
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

        list *p = this->head;
        for (int i = 0; i < index; i++)
        {
            p = p->tail;
        }
        return p->data;
    }

    void clearList()
    {
        list *p = this->head;
        while (p != nullptr)
        {
            list *temp = p;
            p = p->tail;
            delete temp;
        }
        this->head = nullptr;
        this->tail = nullptr;
        count = 0;
    }
    
    void forwardPrint(list *head)
    {
        list *p = head;

        while (p != nullptr)
        {
            std::cout << p->data << " <--> ";
            p = p->tail;
        }
        std::cout << "NULL" << std::endl;
    }

    void reversePrint()
    {
        list *p = lastptr;

        while (p != nullptr)
        {
            std::cout << p->data << " <--> ";
            p = p->head;
        }
        std::cout << "NULL" << std::endl;
    }

   

   
    t getData() { return data; }
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