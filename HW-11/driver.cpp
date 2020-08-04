#include <iostream>
#include "Node.h"
#include "DoublyLinkedList.h"

using namespace std;

int main()
{

  DoublyLinkedList<int> dll1(1);

  dll1.push_back(3);
  dll1.insert(2, 1);
  dll1.push_front(0);

  cout << dll1 << endl;

  DoublyLinkedList<int> dll2(dll1);

  cout << dll2 << endl;
  if (dll1==dll2)
  cout << "YES" << endl;

  dll2.pop_front();

  dll2.pop_back();

  cout << dll1 << endl;

  cout << dll2 << endl;




}
