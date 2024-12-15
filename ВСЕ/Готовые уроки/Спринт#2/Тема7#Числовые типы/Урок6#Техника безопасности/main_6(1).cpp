#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Document {
    int id;
    int rating;
};

void PrintDocuments(vector<Document> documents, size_t skip_start, size_t skip_finish) {
    // отсортировать документы и вывести не все
if (!documents.empty() && skip_start < documents.size() && skip_finish < documents.size()) {
    sort(documents.begin(), documents.end(), 
         [](const Document d1, const Document d2) {return d1.rating > d2.rating;});
    for (size_t i = skip_start; i + skip_finish < documents.size(); ++i) {
        cout << "{ id = "s << documents[i].id << ", rating = "s << documents[i].rating << " }"s << endl;
        }
    }
}

int main() {
    PrintDocuments({{100, 5}, {101, 7}, {102, -4}, {103, 9}, {104, 1}}, 1, 2);
}