#include <iostream>

template <class TValue>
struct Node
{
    TValue value;
    Node* next;
};

Node<int>* reverse(Node<int>* head)
{
    Node<int>* previous = nullptr;
    Node<int>* current = head;

    while (current != nullptr) {
        auto t = current->next;
        current->next = previous;
        
        previous = current;
        current = t;
    }

    return previous;
}


int main()
{
    using N = Node<int>;

    N* head = new N { 10, new N { 20, new N { 30, new N { 40, nullptr } } } };

    head = reverse(head);

    for (auto current = head; current != nullptr; current = current->next) {
        std::cout << current->value << " ";
    }

    std::cout << std::endl;

    return 0;
}