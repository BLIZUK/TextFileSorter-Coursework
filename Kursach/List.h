//  Header file: List.h


#ifndef LIST_H
#define LIST_H


#include <iostream>
#include <stdexcept>


template <typename T>
class List
{

private:

    struct Node
    {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    Node* tail;
    size_t size;


public:


    //>>> Метод: Конструктор
    List() : head(nullptr), tail(nullptr), size(0) {}


    //>>> Метод: Деструктор
    ~List()
    {
        while (head)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }


    //>>> Метод: Добавление элемента в лист
    void append(const T& value)
    {
        Node* newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }


    //>>> Метод: Вставка узла перед указанным индексом
    void push(size_t index, const T& value) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Выход индекса за границу");
        }

        if (index == 0) {
            pushBefore(value); // Если индекс 0, вызываем pushBefore
            return;
        }

        Node* newNode = new Node(value);
        Node* current = head;

        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }

        // Связываем новый узел с существующим
        newNode->next = current->next;
        newNode->prev = current;

        if (current->next) {
            current->next->prev = newNode;
        }
        else {
            tail = newNode; // Если это последний узел, обновляем указатель на хвост
        }

        current->next = newNode;
        size++;
    }


    //>>> Метод: добавление элемента вперед листа
    void pushBefore(const T& value)
    {
        Node* newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }


    //>>> Метод: Удалить первый элемент из списка
    void popf()
    {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        size--;
    }


    //>>> Метод: Удалить последний элемент из списка
    void pop()
    {
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        size--;
    }


    //>>> Метод: Удаление определенного узла по значению
    void remove(const T& value)
    {
        Node* current = head;

        while (current)
        {
            if (current->data == value)
            {
                if (current->prev)
                {
                    current->prev->next = current->next; // Соединяем предыдущий узел с следующим
                }
                else
                {
                    head = current->next; // Если удаляем голову, обновляем указатель на голову
                }

                if (current->next)
                {
                    current->next->prev = current->prev; // Соединяем следующий узел с предыдущим
                }
                else
                {
                    tail = current->prev; // Если удаляем хвост, обновляем указатель на хвост
                }

                delete current; // Освобождаем память
                size--;
                return; // Выходим после удаления первого найденного узла
            }
            current = current->next; // Переходим к следующему узлу
        }

        throw std::invalid_argument("Не найдено значение в List"); // Если значение не найдено
    }


    //>>> Метод: Удаление узла по индексу
    void del(size_t index)
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Выход за границы");
        }
        Node* current = head;

        for (size_t i = 0; i < index; ++i)
        {
            current = current->next;
        }
        if (current->prev)
        {
            current->prev->next = current->next; // Соединяем предыдущий узел с следующим
        }
        else
        {
            head = current->next; // Если удаляем голову, обновляем указатель на голову
        }
        if (current->next)
        {
            current->next->prev = current->prev; // Соединяем следующий узел с предыдущим
        }
        else
        {
            tail = current->prev; // Если удаляем хвост, обновляем указатель на хвост
        }
        delete current; // Освобождаем память
        size--;
    }


    //>>> Метод: Получить первый элемент списка
    T& front()
    {
        if (!head) throw std::out_of_range("List пуст");
        return head->data;
    }


    //>>> Метод: Получить последний элемент списка
    T& back()
    {
        if (!tail) throw std::out_of_range("List пуст");
        return tail->data;
    }


    //>>> Метод: Проверить, пуст ли список
    bool empty() const
    {
        return size == 0;
    }


    //>>> Метод: Получить размер списка
    int getSize() const
    {
        return size;
    }


    //>>> Метод: Вывести список
    void print() const
    {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }


    //>>> Метод: Оператор индексации
    T& operator[](const size_t index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        Node* t = head;
        for (size_t i = 0; i < index; i++) {
            t = t->next;
        }
        return t->data;
    }

    // Оператор индексации для получения значений по индексу 
    const T& operator[](const size_t index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        Node* t = head;
        for (size_t i = 0; i < index; i++) {
            t = t->next;
        }
        return t->data;
    }


    // Метод: Сортировка структуры данных
    void sort() {
        if (!head || !head->next) return; // Если список пуст или содержит один элемент

        Node* current = head->next;

        while (current) {
            Node* nextNode = current->next; // Сохраняем следующий узел
            Node* j = current;

            // Сортируем с помощью insertion sort (Сортировка вставками)
            while (j->prev && j->data < j->prev->data) {
                // Меняем местами данные, если текущий меньше предыдущего
                std::swap(j->data, j->prev->data);
                j = j->prev; // Переходим к предыдущему узлу
            }

            current = nextNode; // Переходим к следующему узлу
        }
    }
};

#endif