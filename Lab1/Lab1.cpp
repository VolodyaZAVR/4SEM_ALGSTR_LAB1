#include <iostream>
#include "RB_Tree.h"
#include "List.h"

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
	List<int> keys = tree->get_keys();
	List<int> values = tree->get_values();
	cout << "Keys of tree" << endl;
	keys.print_to_console();
	cout <<"Values of tree" << endl;
	values.print_to_console();
	tree->print();
    delete tree;
	keys.~List();
	values.~List();
}
