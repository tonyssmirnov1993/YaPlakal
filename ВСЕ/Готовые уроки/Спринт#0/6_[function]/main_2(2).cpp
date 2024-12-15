#include <iostream>
#include <vector>

using namespace std;

void IsPalindrome(string s) {//Нужно понять, будет ли s палиндромом
	int razmer = s.size() - 1;
	string slovo;
	for (int i= razmer; i >= 0; --i) {
		slovo += s[i];
	}
	if (slovo == s) {
		cout << "1"s << endl;
	}
	else {
		cout << "0"s << endl;
	}
}

int main() {
	IsPalindrome("ara"s);
	IsPalindrome("deer"s);
}