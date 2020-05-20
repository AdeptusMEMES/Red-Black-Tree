#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <Windows.h>
#include "RBTree.h"

using namespace std;

void randomFilling()
{
	T a;
	int n;
	cout << endl << "Numbers count:";
	cin >> n;
	Node *t;
	for (int i = 0; i < n;)
	{
		a = rand() % (n*n) + 1;
		if ((t = findNode(a)) == NULL)
		{
			insertNode(a);
			i++;
		}
	}
	cout << "Tree is created." << endl;
}

void printTree(Node *current, int k)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (current != NULL)
	{
		printTree(current->left, k + 3);
		for (unsigned i = 0; i < k; i++)
			cout << "  ";
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | (current->color) * 4));
		if (current != NIL)
			cout << current->data;
		else
			cout << "NIL";
		cout << endl;
		printTree(current->right, k + 3);
	}

}

int main()
{
	int choice = 0, num;
	system("color F0");
	srand(time(0));

	while (choice != 8)
	{
		cout << "\n 1.Fill random\n 2.Clear\n 3.Insert\n 4.Find\n 5.Delete\n 6.Go-round in order\n 7.Print\n 8.Exit\n";
		cin >> choice;
		switch (choice)
		{
			case 1: randomFilling(); break;
			case 2: clearTree(root); break;
			case 3: 
			{
				cout << "Insert num:\n";
				cin >> num;
				insertNode(num);
			} break;
			case 4:
			{
				cout << "Insert num:\n";
				cin >> num;
				if (findNode(num) != NULL)
				{
					cout << "\n Data: " << findNode(num)->data << endl << " Color: ";
					if (findNode(num)->color == RED)
						cout << "RED";
					else
						cout << "BLACK";
				}
				else
					cout << "Node is not founded.";
				cout << endl;
			} break;
			case 5:
			{
				cout << "Insert num:\n";
				cin >> num;
				deleteNode(findNode(num));
			} break;
			case 6:
			{
				cout << endl;
				inOrder(root);
				cout << endl;
			} break;
			case 7: printTree(root, 0); break;
			default:break;
		}
	}
}