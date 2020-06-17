#include <iostream>
using namespace std;
class List
{
private:
	// Структура елемента списка
	struct Node
	{
		int data;	// дані
		Node* next;	// зв'язок з наступним елементом
		Node* prev;	// зв'язок з попереднім елементом
	};

	Node* head;	// вказівник на голову списка
	Node* tail; // вказівник на хвіст списка

	int size;	// розмір списка
public:
	List() : head(nullptr), tail(nullptr), size(0) { }
	List(const List& other)
	{
		Node* current = other.head;
		while (current != nullptr)
		{
			AddToTail(current->data);
			current = current->next;
		}
	}
	List(List&& other)
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
	List& operator=(const List& other)
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
	~List()
	{
		while (!IsEmpty())
		{
			DeleteFromHead();
		}
	}
	// Додати елемент на початок
	void AddToHead(int data)
	{
		// створення нового елемента
		Node* newElem = new Node;
		// задавання значення новогму елементу
		newElem->data = data;
		// наступним елементом буде поточна голова
		newElem->next = head;
		// попереднього елемента не існує
		newElem->prev = nullptr;

		// якщо список був порожній
		if (IsEmpty())
		{
			// новий елемент стає головою та хвостом
			head = tail = newElem;
		}
		// якщо елементи вже існують
		else
		{
			// зв'язуємо поточну голову з новим елементом
			head->prev = newElem;
			// оновлюємо вказівник на голову
			head = newElem;
		}
		++size; // збільшуємо розмір списка
	}
	// Видалити елемент з початку
	void DeleteFromHead()
	{
		// якщо список порожній, тоді видалення не відбувається
		if (IsEmpty()) return;

		// якщо елементи існують, тоді зберігаємо елемент після голови
		Node* temp = head->next;
		// видаляємо голову
		delete head;

		// якщо елемента після голови не існувало (тобто елемент був єдиним в списку)
		if (temp == nullptr)
		{
			// очищаємо голову та хвіст
			head = tail = nullptr;
		}
		// якщо елемент після голови наявний
		else
		{
			// очищаємо зв'язок з видаленою головою
			temp->prev = nullptr;
			// елемент після видаленої голови стає поточною головою
			head = temp;
		}
		--size; // зменшуємо розмір списка
	}
	// Додати елемент в кінець
	void AddToTail(int data)
	{
		// створення нового елемента
		Node* newElem = new Node;
		// задавання значення новому елементу
		newElem->data = data;
		// за хвостом елементів немає
		newElem->next = nullptr;
		// зв'язуємо новий елемент з попереднім (поточним хвостом)
		newElem->prev = tail;

		// якщо список був порожній
		if (IsEmpty())
		{
			// новий елемент стає головою та хвостом
			head = tail = newElem;
		}
		// якщо елементи вже існують
		else
		{
			// зв'язуємо останній елемен з новим хвістом
			tail->next = newElem;
			// оновлюємо вказівник на хвіст
			tail = newElem;
		}
		++size; // збільшуємо розмір списка
	}
	// Видалити елемент з кінця
	void DeleteFromTail()
	{
		// якщо список порожній, тоді видалення не відбувається
		if (IsEmpty()) return;

		// якщо елемента після голови не існує (тобто елемент єдиний в списку) 
		if (head->next == nullptr)
		{
			// видаляємо голову (єдиний елемент)
			delete head;
			// очищаємо голову та хвіст
			head = tail = nullptr;
		}
		// якщо елементи існували
		else
		{
			// знаходимо вказівник на передостанній елемент (елемент перед поточним хвостом)
			Node* temp = tail->prev;

			// видаляємо останній елемент
			delete temp->next;
			// очищаємо зв'язок з останнім елементом
			temp->next = nullptr;
			// оновлюємо хвіст
			tail = temp;
		}
		--size; // зменшуємо розмір списка
	}
	// Додавання елемента в позицію
	void AddPos(int posi, int data)
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

		++size; // збільшуємо розмір списка
	}
	// Вдалення елемента в позиції
	void DeletePos(int posi)
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

		--size; // зменшуємо розмір списка
	}
	// Видалення всіх елементів;
	void DeleteAll()
	{
		while (!IsEmpty())
		{
			DeleteFromHead();
		}
	}
	// Відображення всіх елементів
	void Show() const
	{
		for (Node* current = head; current != nullptr; current = current->next)
		{
			// print current data
			cout << current->data << ", ";
		}
	}

	bool IsEmpty() const
	{
		return size == 0;
	}
	int GetCount() const
	{
		return size;
	}
	
	int Search(int data)
	{
		Node* temp = head;
		for (int i = 0; i < size; i++)
		{
			if (temp->data == data)
			{
				return i + 1;
			}
			temp = temp->next;
		}
		return 0;
	}
	int Replace(int old, int neww)
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
	void Show() const
	{
		for (Node* current = head; current != nullptr; current = current->next)
		{
			// print current data
			cout << current->data << ", ";
		}
	}
	~List()
	{
		while (!IsEmpty())
		{
			DeleteFromHead();
		}
	}
	//##################################
	void Revers()
	{
		
	}
	List& operator+(const List& other)
	{
		
	}
};

int main()
{
	List ls;

	ls.AddToHead(10);
	ls.AddToHead(15);
	ls.AddToHead(5);
	ls.AddToHead(20);
	ls.Show();
	ls.Search(5);
	/*
	ls.Print(); cout << endl;

	ls.DeleteHead();
	ls.AddToTail(777);

	////////////////////

	ls.Print(); cout << endl;

	ls.DeleteTail();
	ls.DeleteTail();

	ls.Print(); cout << endl;

	ls.Add(3, 3);
	ls.Add(7, 7);

	ls.Print(); cout << endl;

	ls.Delete(3);
	ls.Print(); cout << endl;

	ls.Delete(7);
	ls.Print(); cout << endl;
	*/

	return 0;
}