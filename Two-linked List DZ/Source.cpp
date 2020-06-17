#include <iostream>
using namespace std;
class List
{
private:
	// ��������� �������� ������
	struct Node
	{
		int data;	// ���
		Node* next;	// ��'���� � ��������� ���������
		Node* prev;	// ��'���� � ��������� ���������
	};

	Node* head;	// �������� �� ������ ������
	Node* tail; // �������� �� ���� ������

	int size;	// ����� ������
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
	// ������ ������� �� �������
	void AddToHead(int data)
	{
		// ��������� ������ ��������
		Node* newElem = new Node;
		// ��������� �������� ������� ��������
		newElem->data = data;
		// ��������� ��������� ���� ������� ������
		newElem->next = head;
		// ������������ �������� �� ����
		newElem->prev = nullptr;

		// ���� ������ ��� �������
		if (IsEmpty())
		{
			// ����� ������� ��� ������� �� �������
			head = tail = newElem;
		}
		// ���� �������� ��� �������
		else
		{
			// ��'����� ������� ������ � ����� ���������
			head->prev = newElem;
			// ��������� �������� �� ������
			head = newElem;
		}
		++size; // �������� ����� ������
	}
	// �������� ������� � �������
	void DeleteFromHead()
	{
		// ���� ������ �������, ��� ��������� �� ����������
		if (IsEmpty()) return;

		// ���� �������� �������, ��� �������� ������� ���� ������
		Node* temp = head->next;
		// ��������� ������
		delete head;

		// ���� �������� ���� ������ �� �������� (����� ������� ��� ������ � ������)
		if (temp == nullptr)
		{
			// ������� ������ �� ����
			head = tail = nullptr;
		}
		// ���� ������� ���� ������ �������
		else
		{
			// ������� ��'���� � ��������� �������
			temp->prev = nullptr;
			// ������� ���� �������� ������ ��� �������� �������
			head = temp;
		}
		--size; // �������� ����� ������
	}
	// ������ ������� � �����
	void AddToTail(int data)
	{
		// ��������� ������ ��������
		Node* newElem = new Node;
		// ��������� �������� ������ ��������
		newElem->data = data;
		// �� ������� �������� ����
		newElem->next = nullptr;
		// ��'����� ����� ������� � ��������� (�������� �������)
		newElem->prev = tail;

		// ���� ������ ��� �������
		if (IsEmpty())
		{
			// ����� ������� ��� ������� �� �������
			head = tail = newElem;
		}
		// ���� �������� ��� �������
		else
		{
			// ��'����� ������� ������ � ����� ������
			tail->next = newElem;
			// ��������� �������� �� ����
			tail = newElem;
		}
		++size; // �������� ����� ������
	}
	// �������� ������� � ����
	void DeleteFromTail()
	{
		// ���� ������ �������, ��� ��������� �� ����������
		if (IsEmpty()) return;

		// ���� �������� ���� ������ �� ���� (����� ������� ������ � ������) 
		if (head->next == nullptr)
		{
			// ��������� ������ (������ �������)
			delete head;
			// ������� ������ �� ����
			head = tail = nullptr;
		}
		// ���� �������� ��������
		else
		{
			// ��������� �������� �� ������������ ������� (������� ����� �������� �������)
			Node* temp = tail->prev;

			// ��������� ������� �������
			delete temp->next;
			// ������� ��'���� � ������� ���������
			temp->next = nullptr;
			// ��������� ����
			tail = temp;
		}
		--size; // �������� ����� ������
	}
	// ��������� �������� � �������
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

		++size; // �������� ����� ������
	}
	// �������� �������� � �������
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

		--size; // �������� ����� ������
	}
	// ��������� ��� ��������;
	void DeleteAll()
	{
		while (!IsEmpty())
		{
			DeleteFromHead();
		}
	}
	// ³���������� ��� ��������
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