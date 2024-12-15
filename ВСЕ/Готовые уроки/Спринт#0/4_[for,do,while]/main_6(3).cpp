#include <iostream>
#include <string>

using namespace std;

int main() {
	string query;
	getline(cin, query);
	for (int i = 0; i < query.size(); ++i) {
		if (query[i] == ' ') {
			cout << i << endl;
		}
	}
	cout << query.size() << endl;
}
// выведите все индексы символов, следующие за словами