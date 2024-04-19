#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <stdexcept>

template <typename T>
class List {

public:
    struct Node{
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    class Iterator {
        
        public:
            Iterator(Node* node) : current(node) {}
            
            T& operator*() const {
                return current->data;
            }

            Iterator& operator++() {
                current = current->next;
                return *this;
            }

            bool operator!=(const Iterator& other) const {
                return current != other.current;
            }

        private:
            Node* current;
        };   

    Iterator begin() const {
        return Iterator(guard->next);
    }

    Iterator end() const {
        return Iterator(guard);
    }

    List();
    ~List(); 
    void push_front(const T& x); // Dołącza element na początek listy
    T pop_front(); // Usuwa i zwraca element z początku listy
    void push_back(const T& x); // Dołącza element na koniec listy
    T pop_back(); // Usuwa i zwraca element z końca listy
    int size_(); // Zwraca liczbę elementów w liście
    bool empty(); // Zwraca 'true' gdy lista jest pusta
    void clear(); // Czyści listę
    int find(const T& x); // Zwraca pozycję pierwszego elementu o wartości 'x'
    int erase(int i); // Usuwa i zwraca element na pozycji 'i'
    void insert(int i, const T& x); // Wstawia element 'x' przed pozycję 'i'
    int remove(const T& x); // Usuwa wystąpienia 'x' i zwraca ich liczbę
    
private:
    int size;
    Node* guard;     //wskażnik na węzeł pomocniczy, którego next wskazuje na pierwszy element, a prev na ostatni
    
};

template <typename T>
List<T>::List() : size(0) {
    guard = new Node(T());
    guard->next = guard;
    guard->prev = guard;
}

template <typename T>
List<T>::~List() {
    clear();
    delete guard;
}

template <typename T>
void List<T>::push_front(const T& x) {
    Node* newNode = new Node(x);
    newNode->prev = guard;
    newNode->next = guard->next;
    guard->next->prev = newNode;
    guard->next = newNode;
    size++;
}

template <typename T>
T List<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("The list is empty");
    }

    T value = guard->next->data;
    Node* temp = guard->next;
    guard->next = temp->next;
    temp->next->prev = guard;
    delete temp;
    size--;
    return value;
}

template <typename T>
void List<T>::push_back(const T& x) {
    Node* newNode = new Node(x);
    newNode->prev = guard->prev;
    newNode->next = guard;
    guard->prev->next = newNode;
    guard->prev = newNode;
    size++;
}

template <typename T>
T List<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("The list is empty");
    }

    T value = guard->prev->data;
    Node* temp = guard->prev;
    guard->prev = temp->prev;
    temp->prev->next = guard;
    size--;

    delete temp;
    return value;
}

template <typename T>
int List<T>::size_() {
    return size;
}

template <typename T>
bool List<T>::empty() {
    return size == 0;
}

template <typename T>
void List<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
int List<T>::find(const T& x) {
    int i = 0;
    Node* node = guard->next;
    while (node != guard) {
        if (node->data == x) {
            return i;
        }
        node = node->next;
        i++;
    }
    return -1;
}

template <typename T>
int List<T>::erase(int i) {
    if (i >= size || i < 0) {
        throw std::out_of_range("Bad index");
    }

    Node* node = guard->next;
    for (int j = 0; j < i; j++) {
        node = node->next;
    }

    T result = node->data;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    size--;
    return result;
}

template <typename T>
void List<T>::insert(int i, const T& x) {
    if (i < 0 || i > size) {
        throw std::out_of_range("Index out of bounds");
    }

    Node* newNode = new Node(x);
    Node* node = guard->next;
    for (int j = 0; j < i; j++) {
        node = node->next;
    }

    newNode->prev = node->prev;
    newNode->next = node;
    node->prev->next = newNode;
    node->prev = newNode;
    size++;
}

template <typename T>
int List<T>::remove(const T& x) {
    int counter = 0;
    Node* node = guard->next;

    while (node != guard) {
        if (node->data == x) {
            Node* temp = node;
            node->next->prev = node->prev;
            node->prev->next = node->next;
            node = node->next;

            size--;
            counter++;
            delete temp;
        } else {
            node = node->next;
        }
    }
    return counter;
}

#endif
