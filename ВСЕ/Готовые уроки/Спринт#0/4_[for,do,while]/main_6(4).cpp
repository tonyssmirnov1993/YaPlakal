#include <iostream>
#include <string>

using namespace std;

int main() {
	string query;
	string word;
	getline(cin, query);
	for (int i = 0; i < query.size(); ++i) {
		if (query[i] != ' ') {
			word += query[i];
		}
		if (query[i] == ' ') {
			cout << "["s << word << "]" << endl;
			word = ""s;
		}
	}
	cout << "["s << word << "]" << endl;
}