#include <iostream>
#include "RB_Tree.h"
#include <list>

using namespace std;

int main()
{
    RB_Tree<int>* tree;
    tree = new RB_Tree<int>();
	tree->insert(55, 5);
	tree->insert(40, 6);
	tree->insert(65, 8);
	tree->insert(60, 6);
	tree->insert(75, 5);
	tree->insert(57, 6);
	list<int> keys = tree->get_keys();
	list<int> values = tree->get_values();
	for (int n : keys)
		std::cout << n << "\t";
	std::cout << std::endl;
	for (int n : values)
		std::cout << n << "\t";
	std::cout << std::endl;
	cout << endl;
	tree->print();
    delete tree;
}
