#include "CppUnitTest.h"
#include "../Lab1/RB_Tree.h"
#include <list>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;

namespace UnitTest1
{
	TEST_CLASS(UnitTest)
	{
	public:
		RB_Tree<int>* tree;
		TEST_METHOD_INITIALIZE(setup) 
		{
			tree = new RB_Tree<int>();
		}
		TEST_METHOD_CLEANUP(MrPropper)
		{
			delete tree;
		}
		TEST_METHOD(InsertTest1)
		{
			tree->insert(6, 5);
			Assert::IsNotNull(tree->find(6));
		}
		TEST_METHOD(InsertTest2)
		{
			tree->insert(6, 5);
			tree->insert(7, 6);
			Assert::IsNotNull(tree->find(6));
			Assert::IsNotNull(tree->find(7));
			Assert::IsNull(tree->find(5));
		}
		TEST_METHOD(InsertTest3)
		{
			tree->insert(6, 5);
			tree->insert(7, 6);
			tree->insert(5, 8);
			tree->insert(10, 15);
			tree->insert(15, 10);
			Assert::IsNotNull(tree->find(10));
			Assert::IsNotNull(tree->find(15));
			Assert::IsNull(tree->find(11));
		}
		TEST_METHOD(RemoveTest1)
		{
			tree->insert(6, 5);
			tree->insert(7, 6);
			tree->insert(5, 8);
			tree->insert(4, 6);
			tree->insert(3, 5);
			tree->insert(8, 6);
			tree->insert(10, 15);
			tree->insert(15, 10);
			Assert::IsNotNull(tree->find(6));
			tree->remove(6);
			Assert::IsNull(tree->find(6));
			Assert::IsNotNull(tree->find(15));
			tree->remove(15);
			Assert::IsNull(tree->find(15));
			Assert::IsNotNull(tree->find(5));
			tree->remove(5);
			Assert::IsNull(tree->find(5));
		}
		TEST_METHOD(RemoveTest2)
		{
			tree->insert(55, 5);
			tree->insert(40, 6);
			tree->insert(65, 8);
			tree->insert(60, 6);
			tree->insert(75, 5);
			tree->insert(57, 6);
			tree->remove(40);
			Assert::IsFalse(tree->find(65)->parent);
		}
		TEST_METHOD(RemoveTest3)
		{
			tree->insert(55, 5);
			tree->insert(40, 6);
			tree->insert(65, 8);
			tree->insert(60, 6);
			tree->insert(75, 5);
			tree->insert(57, 6);
			tree->remove(55);
			Assert::IsFalse(tree->find(57)->parent);
		}
		TEST_METHOD(ErrorTest1)
		{
			try {
				tree->remove(55);
			}
			catch (char* message) {
				Assert::AreEqual("There is no such element!", message);
			}
		}
		TEST_METHOD(ErrorTest2)
		{
			try {
				tree->insert(' ', 5);
			}
			catch (char* message) {
				Assert::AreEqual("Key error: the key cannot have the given value", message);
			}
		}
		TEST_METHOD(TestClearMethod)
		{
			tree->insert(55, 5);
			tree->insert(40, 6);
			tree->insert(65, 8);
			tree->insert(60, 6);
			tree->insert(75, 5);
			tree->insert(57, 6);
			tree->clear();
			list<int> keys;
			keys = tree->get_keys();
			Assert::IsTrue(keys.empty());
		}
		TEST_METHOD(TestGetKeysMethod)
		{
			tree->insert(55, 5);
			tree->insert(40, 6);
			tree->insert(65, 8);
			tree->insert(60, 6);
			tree->insert(75, 5);
			tree->insert(57, 6);
			list<int> keys = tree->get_keys();
			Assert::AreEqual(55, keys.front());
			keys.pop_front();
			Assert::AreEqual(40, keys.front());
			keys.pop_front();
			Assert::AreEqual(65, keys.front());
			keys.pop_front();
			Assert::AreEqual(60, keys.front());
			keys.pop_front();
			Assert::AreEqual(57, keys.front());
			keys.pop_front();
			Assert::AreEqual(75, keys.front());
			keys.pop_front();
			Assert::AreEqual(0, int(keys.size()));
		}
		TEST_METHOD(TestGetValuesMethod)
		{
			tree->insert(55, 5);
			tree->insert(40, 6);
			tree->insert(65, 8);
			tree->insert(60, 7);
			tree->insert(75, 3);
			tree->insert(57, 4);
			list<int> values = tree->get_values();
			Assert::AreEqual(5, values.front());
			values.pop_front();
			Assert::AreEqual(6, values.front());
			values.pop_front();
			Assert::AreEqual(8, values.front());
			values.pop_front();
			Assert::AreEqual(7, values.front());
			values.pop_front();
			Assert::AreEqual(4, values.front());
			values.pop_front();
			Assert::AreEqual(3, values.front());
			values.pop_front();
			Assert::AreEqual(0, int(values.size()));
		}
	};
}
