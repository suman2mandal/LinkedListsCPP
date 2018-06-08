// Linked List implementations

#ifndef LINKED_LIST_TPP
#define LINKED_LIST_TPP

#include "linkedList.hpp"

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>
LinkedList<T>::~LinkedList() 
{
    clear();
}

template <typename T>
LinkedList<T>::LinkedList(size_t count, const T& data) : LinkedList()
{
    while (count > 0)
    {
        push_front(data);
        --count;
    }
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& origin) : LinkedList()
{
    LinkedList<T>::const_iterator it;
    for (it = origin.cbegin(); it != origin.cend(); ++it)
    {
        push_back(*it);
    }
}

// Iterators
template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::cbegin() const
{
    return const_iterator(head);
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin()
{
    return iterator(head);
} 

template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::cend() const
{
    // Prevents segmentation fault if attempt to get tails next node if tail is
    // is a nullptr. Since tail will always point to a nullptr we can just 
    // return an iterator to a nullptr
    return const_iterator(nullptr);
} 

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end()
{
    return iterator(nullptr);
} 

// Modifiers
template <typename T>
void LinkedList<T>::push_front(const T& data)
{
    Node<T>* temp = new Node<T>(data);

    temp->Next(head);
    head = temp;

    if (tail == nullptr)
    {
        tail = head;
    }

    return;
}

template <typename T>
void LinkedList<T>::push_back(const T& data)
{
    if (this->empty())
    {
        push_front(data);
        return;
    }

    Node<T>* temp = new Node<T>(data);

    tail->Next(temp);
    tail = temp;

    return;
}

template<typename T>
void LinkedList<T>::insert(const LinkedList<T>::iterator &insertionPoint, 
                           const T& data)
{
    if (insertionPoint == begin())
    {
        push_front(data);
        return;
    }

    Node<T>* newNode = new Node<T>(data);
    Node<T>* current = head;
    Node<T>* previous = head;
    
    LinkedList<T>::iterator It;
    for (It = begin(); It != insertionPoint; ++It)
    {
        previous = current;
        current = current->Next();
    }

    newNode->Next(previous->Next());
    previous->Next(newNode);

    return;
}

template <typename T>
void LinkedList<T>::clear()
{
    if (head == nullptr)
    {
        return;
    }

    Node<T>* previous = head;

    while (head != nullptr)
    {
        previous = head;
        head = head->Next();
        delete previous;
    }

    return;
}

// Capacity functions
template <typename T>
bool LinkedList<T>::empty() const
{
    return !(head);
}

template <typename T>
size_t LinkedList<T>::size() const
{
    size_t SIZE = 0;
    Node<T>* temp = head;
    while (temp != nullptr)
    {
        ++SIZE;
        temp = temp->Next();
    }
    return SIZE;
}

// Operator Overloads
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
    if (size() != rhs.size()) { return false; }

    LinkedList<T>::const_iterator left = cbegin();
    LinkedList<T>::const_iterator right = rhs.cbegin();

    while(left != cend() && right != rhs.cend())
    {
        if (*left != *right) { return false; }
        ++left;
        ++right;
    }

    return true;
}

template <typename T>
bool LinkedList<T>::operator!=(const LinkedList<T>& rhs) const
{
    return !(*this == rhs);
}


#endif // LINKED_LIST_TPP
