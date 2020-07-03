#include "List.h"

List::List(const List& other)
{
	Node* current = other.head;
	while (current != nullptr)
	{
		AddToTail(current->data);
		current = current->next;
	}
}

List::List(List&& other)
{
	this->head = other.head;
	this->tail = other.tail;
	Node* current = other.head;
	while (current != nullptr)
	{
		AddToTail(current->data);
		current = current->next;
	}
	other.head = nullptr;
	other.tail = nullptr;
	delete current;
}

List& List::operator=(const List& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (this != nullptr)
	{
		while (!IsEmpty())
		{
			DeleteFromHead();
		}
	}

	Node* current = other.head;
	while (current != nullptr)
	{
		AddToTail(current->data);
		current = current->next;
	}
	return *this;
}

List::~List()
{
	while (!IsEmpty())
	{
		DeleteFromHead();
	}
}

void List::AddToHead(int data)
{
	Node* newElem = new Node;
	newElem->data = data;
	newElem->next = head;
	newElem->prev = nullptr;
	if (IsEmpty())
	{
		head = tail = newElem;
	}
	else
	{
		head->prev = newElem;
		head = newElem;
	}
	++size;
}

void List::DeleteFromHead()
{
	if (IsEmpty()) return;

	Node* temp = head->next;
	delete head;
	if (temp == nullptr)
	{
		head = tail = nullptr;
	}
	else
	{
		temp->prev = nullptr;
		head = temp;
	}
	--size;
}

void List::AddToTail(int data)
{
	Node* newElem = new Node;
	newElem->data = data;
	newElem->next = nullptr;
	newElem->prev = tail;
	if (IsEmpty())
	{
		head = tail = newElem;
	}
	else
	{
		tail->next = newElem;
		tail = newElem;
	}
	++size;
}

void List::DeleteFromTail()
{
	if (IsEmpty()) return;
	if (head->next == nullptr)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		Node* temp = tail->prev;
		delete temp->next;
		temp->next = nullptr;
		tail = temp;
	}
	--size;
}

void List::AddPos(int posi, int data)
{
	if (posi <= 0 || posi > size + 1) return;

	if (posi == 1)
	{
		AddToHead(data);
		return;
	}
	if (posi == size + 1)
	{
		AddToTail(data);
		return;
	}

	Node* newElem = new Node;
	newElem->data = data;

	Node* current = head;
	for (int i = 0; i < posi - 1; ++i)
	{
		current = current->next;
	}
	newElem->prev = current->prev;
	current->prev->next = newElem;

	current->prev = newElem;
	newElem->next = current;
	++size;
}

void List::DeletePos(int posi)
{
	if (posi <= 0 || posi > size) return;

	if (posi == 1)
	{
		DeleteFromHead();
		return;
	}
	if (posi == size)
	{
		DeleteFromTail();
		return;
	}

	Node* current = head;
	for (int i = 0; i < posi - 1; ++i)
	{
		current = current->next;
	}

	current->prev->next = current->next;
	current->next->prev = current->prev;
	delete current;

	--size;
}

void List::DeleteAll()
{
	while (!IsEmpty())
	{
		DeleteFromHead();
	}
}

void List::Show() const
{
	for (Node* current = head; current != nullptr; current = current->next)
	{
		if (current->next != 0)
		{
			cout << current->data << ", ";
		}
		else
		{
			cout << current->data << " ";
		}
	}
	cout <<"\nSize: "<< size << endl;
}

bool List::IsEmpty() const
{
	return size == 0;
}

int List::GetCount() const
{
	return size;
}

int List::Search(int data)
{
	Node* temp = head;
	for (int i = 0; i < size; i++)
	{
		if (temp->data == data)
		{
			cout << endl;
			return i + 1;
		}
		temp = temp->next;
	}
	return 0;
}

int List::Replace(int old, int neww)
{
	Node* temp = head;
	int h = 0;
	for (int i = 0; i < size; i++)
	{
		if (temp->data == old)
		{
			temp->data = neww;
			++h;

		}
		temp = temp->next;
	}
	return h;
}

void List::Revers()
{
	if (IsEmpty()) return;

	Node* tmp = nullptr;
	Node* current = nullptr;
	while (tail->next == 0)
	{
		tmp = head->next;
		head->next = current;
		current = head;
		head = tmp;
	}
}


