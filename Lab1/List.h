#pragma once
#include <iostream>

using namespace std;

template <class T>
class List {
private:
    template <class T>
    class Node {
    public:
        Node(T data, Node<T>* next = nullptr) {
            this->data = data;
            this->next = next;
        };
        ~Node() {};
        T data;
        Node<T>* next;
    };
    Node<T>* head;
    Node<T>* tail;
    size_t size;
public:
    List();
    ~List();
    void push_back(T); // добавление в конец списка
    void push_front(T); // добавление в начало списка
    T pop_back(); // удаление последнего элемента
    T pop_front(); // удаление первого элемента
    void print_to_console(); // вывод элементов списка в консоль через разделитель
    void clear(); // удаление всех элементов списка
    bool isEmpty(); // проверка на пустоту списка
};

template <typename T>
List<T>::List() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
void List<T>::push_back(T data) {
    if (isEmpty()) {
        head = new Node<T>(data);
        tail = head;
    }
    else {
        tail->next = new Node<T>(data);
        tail = tail->next;
    }
    size++;
}

template <typename T>
void List<T>::push_front(T data) {
    Node<T>* temp_node;
    if (isEmpty()) {
        head = new Node<T>(data);
        tail = head;
    }
    else {
        temp_node = new Node<T>(data, head);
        head = temp_node;
    }
    size++;
}

template <typename T>
T List<T>::pop_back() {
    Node<T>* temp_node = head;
    T data;
    if (isEmpty())
        throw "this operation cannot be performed";
    else {
        if (size == 1) {
            data = temp_node->data;
            temp_node->~Node();
            head = nullptr;
            tail = nullptr;
        }
        else {
            while (temp_node->next != tail)
                temp_node = temp_node->next;
            tail = temp_node;
            data = temp_node->data;
            temp_node->next->~Node();
            tail->next = nullptr;
        }
        size--;
    }
    return data;
}

template <typename T>
T List<T>::pop_front() {
    Node<T>* temp_node = head;
    T data;
    if (isEmpty())
        throw "this operation cannot be performed";
    else {
        if (size == 1) {
            data = temp_node->data;
            temp_node->~Node();
            head = nullptr;
            tail = nullptr;
        }
        else {
            head = head->next;
            data = temp_node->data;
            temp_node->~Node();
        }
        size--;
    }
    return data;
}

template <typename T>
void List<T>::clear() {
    T rubbish;
    while (!isEmpty()) {
        rubbish = pop_front();
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename T>
void List<T>::print_to_console() {
    Node<T>* temp_node = head;
    while (temp_node) {
        cout << temp_node->data << ' ';
        temp_node = temp_node->next;
    }
    cout << endl;
}

template <typename T>
bool List<T>::isEmpty() {
    return (!size);
}
