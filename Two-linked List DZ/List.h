#pragma once
#include <iostream>
using namespace std;
class List
{
private:
	struct Node
	{
		int data;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
	int size;
public:
	List() : head(nullptr), tail(nullptr), size(0) { }
	List(const List& other);
	List(List&& other);
	List& operator=(const List& other);
	void AddToHead(int data);
	void DeleteFromHead();
	void AddToTail(int data);
	void DeleteFromTail();
	void AddPos(int posi, int data);
	void DeletePos(int posi);
	void DeleteAll();
	void Show() const;
	bool IsEmpty() const;
	int GetCount() const;
	int Search(int data);
	int Replace(int old, int neww);
	~List();
	void Revers();
};