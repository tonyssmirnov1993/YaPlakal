#include <iostream>

#include "paginator.h"
#include "request_queue.h"

using namespace std;

int main() {
	SearchServer search_server("and in at"s);
	
	RequestQueue request_queue(search_server); 
	
	search_server.AddDocument(1, "funny pet and nasty rat"s, DocumentStatus::ACTUAL, { 7, 2, 7 });
	search_server.AddDocument(2, "funny pet with curly hair"s, DocumentStatus::ACTUAL, { 1, 2, 3 });
	search_server.AddDocument(3, "big cat nasty hair"s, DocumentStatus::ACTUAL, { 1, 2, 8 });
	search_server.AddDocument(4, "big dog cat Vladislav"s, DocumentStatus::ACTUAL, { 1, 3, 2 });
	search_server.AddDocument(5, "big dog hamster Borya"s, DocumentStatus::ACTUAL, { 1, 1, 1 });
	const auto search_results = search_server.FindTopDocuments("curly dog"s);
	int page_size = 2;

	const auto pages = Paginate(search_results, page_size);

	for (auto page = pages.begin(); page != pages.end(); ++page) {
		cout << *page << endl;
		cout << "Page break"s << endl;
	}
	return 0;
}