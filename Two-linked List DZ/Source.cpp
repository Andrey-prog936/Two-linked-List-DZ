#include <iostream>
#include "List.h"
using namespace std;



int main()
{
	List ls;
	int df = 0;
	ls.AddToHead(10);
	ls.AddToHead(15);
	ls.AddToHead(5);
	ls.AddToHead(20);
	ls.Show();
	cout << ls.Search(5) << endl;
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