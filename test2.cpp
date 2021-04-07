/*
5 2
3 2
4 3
5 2
1 4
3

2 5 4 1
*/
#include<iostream>
#include<algorithm>
#include<list>
using namespace std;
int main() {
	int num, beg;
	while (cin >> num >> beg) {
		list<int> mylist;
		mylist.push_back(beg);
		for (int i = 0; i < num - 1; ++i) {
			int node1, node2;
			cin >> node2 >> node1;
			mylist.insert(++find(mylist.begin(), mylist.end(), node1), node2);
		}
		int nodeDel;
		cin >> nodeDel;
		mylist.erase(find(mylist.begin(), mylist.end(), nodeDel));
		for (auto s : mylist) {
			cout << s << " ";
		}
		cout << endl;
	}
	return 0;
}