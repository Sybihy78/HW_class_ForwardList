#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

template <typename T>
class ForwardList {
	struct node {
		T data;
		node* next = nullptr;
	};
	node* head;
	node* tail;
	size_t list_size;

public:
	ForwardList();
	ForwardList(const ForwardList<T>&);
	ForwardList(ForwardList<T>&&);
	~ForwardList();

	ForwardList<T>& operator=(const ForwardList<T>&);
	ForwardList<T>& operator=(ForwardList<T>&&);

	size_t listSize() const {
		return list_size;
	}
	size_t size() const;
	bool empty() const;

	void push_back(const T&);
	void push_front(const T&);
	bool insert(const T&, const T&);

	T pop_back();
	T pop_front();
	bool erase(const T&);

	void print();

private:
	node * create_node(const T& value) {
		node* elem = new node;
		elem->data = value;
		elem->next = nullptr;
		++list_size;
		return elem;
	};

	void create_first_node(const T&);

	node* find_node(const T& value) {
		if (head != nullptr) {
			for (node* tmp = head; tmp != nullptr; tmp = tmp->next) {
				if (tmp->data == value) {
					return tmp;
				}
			}
		}
		return nullptr;
	};
	
	node* find_previous_node(const T& value) {
		if (tail != nullptr) {
			node* previous = head;
			for (node* tmp = head->next; tmp != nullptr; tmp = tmp->next) {
				if (tmp->data == value) {
					return previous;
				}
				else {
					previous = previous->next;
				}
			}
		}
		return nullptr;
	};
};

template <typename T>
ForwardList<T>::ForwardList() :
	head(nullptr),
	tail(nullptr)
{};

template <typename T>
ForwardList<T>::ForwardList(const ForwardList<T>& obj) :
	head(obj.head),
	tail(obj.tail),
	list_size(obj.list_size)
{
	for (node* tmp = obj.head; tmp != nullptr; tmp = tmp->next) {
		node* elem = new node;
		elem->data = tmp->data;
		elem->next = tmp->next;
	}
};

template <typename T>
ForwardList<T>::ForwardList(ForwardList<T>&& obj) :
	head(obj.head),
	tail(obj.tail),
	list_size(obj.list_size)
{
	obj.head = nullptr;
	obj.tail = nullptr;
	obj.list_size = 0;
	for (node* tmp = obj.head; tmp != nullptr; tmp = tmp->next) {
		tmp = nullptr;
	}
};

template <typename T>
ForwardList<T>::~ForwardList() {
	delete tail;
	tail = nullptr;
	delete head;
	head = nullptr;
};

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& obj) {
	if (this == &obj) {
		return *this;
	}
	for (node* tmp = head; tmp != nullptr; tmp = tmp->next) {
		delete tmp;
		tmp = nullptr;
	}
	head = obj.head;
	tail = obj.tail;
	list_size = obj.list_size;
	for (node* tmp = obj.head; tmp != nullptr; tmp = tmp->next) {
		node* elem = new node;
		elem = tmp;
	}
	return *this;
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(ForwardList<T>&& obj) {
	if (this == &obj) {
		return *this;
	}
	head = obj.head;
	tail = obj.tail;
	list_size = obj.list_size;
	obj.head = nullptr;
	obj.tail = nullptr;
	obj.list_size = 0;
	for (node* tmp = obj.head; tmp != nullptr; tmp = tmp->next) {
		tmp = nullptr;
	}
	return *this;
}


template <typename T>
size_t ForwardList<T>::size() const {
	size_t count = 0;
	for (node* tmp = head; tmp != nullptr; tmp = tmp->next) {
		++count;
	}
	return count;
};


template <typename T>
bool ForwardList<T>::empty() const {
	return list_size == 0;
};

template <typename T>
void ForwardList<T>::push_back(const T& value) {
	if (tail == nullptr) {
		ForwardList<T>::create_first_node(value);
	}
	else {
		node* elem = new node;
		elem->data = value;
		elem->next = nullptr;
		tail->next = elem;
		tail = elem;
		++list_size;
	}
};

template <typename T>
void ForwardList<T>::push_front(const T& value) {
	if (head == nullptr) {
		ForwardList<T>::create_first_node(value);
	}
	else {
		node* elem = new node;
		elem->data = value;
		elem->next = head;
		head = elem;
		++list_size;
	}
};

template <typename T>
bool ForwardList<T>::insert(const T& new_value, const T& prev_value) {
	for (node* tmp = head; tmp != nullptr; tmp = tmp->next) {
		if (tmp->data == prev_value) {
			node* elem = new node;
			elem->data = new_value;
			elem->next = tmp->next;
			tmp->next = elem;
			if (tmp == tail) {
				tail = elem;
			}
			++list_size;
			return true;
		}
	}
	return false;
};

template <typename T>
T ForwardList<T>::pop_back() {
	if (size() >= 2) {
		node* back = tail;
		for (node* tmp = head; tmp != nullptr; tmp = tmp->next) {
			if (tmp->next == tail) {
				tmp->next = nullptr;
				tail = tmp;
				return back->data;
				--list_size;
				delete back;
				back = nullptr;
			}
		}
	}
	else if (size() == 1) {
		pop_front();
	}
	else {
		std::cout << "Not elements for delete" << std::endl;
		return -1;
	}
};

template <typename T>
T ForwardList<T>::pop_front() {
	if (head != nullptr) {
		node* front = head;
		head = front->next;
		return front->data;
		--list_size;
		delete front;
		front = nullptr;
	}
	else {
		std::cout << "Not elements for delete" << std::endl;
		return -1;
	}
};

template <typename T>
bool ForwardList<T>::erase(const T& value) {
	if (find_node(value) != nullptr && find_node(value) != head) {
		node* prev = find_previous_node(value);
		node* del = find_node(value);
		prev->next = del->next;
		--list_size;
		delete del;
		del = nullptr;
		return true;
	}
	else if (find_node(value) != nullptr && find_node(value) == head) {
		node* front = head;
		head = front->next;
		--list_size;
		delete front;
		front = nullptr;
		return true;
	}
	throw std::out_of_range("Element not found");
};

template <typename T>
void ForwardList<T>::print() {
	if (head == nullptr) {
		std::cout << "Not elements" << std::endl;
		return;
	}
	else {
		for (node* tmp = head; tmp != nullptr; tmp = tmp->next) {
			std::cout << tmp->data << " ";
		}
	}
};

template <typename T>
void ForwardList<T>::create_first_node(const T& value) {
	node* elem = new node;
	elem->data = value;
	elem->next = nullptr;
	head = elem;
	tail = elem;
	++list_size;
};

