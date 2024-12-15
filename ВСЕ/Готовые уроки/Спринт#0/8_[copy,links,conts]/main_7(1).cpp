#include <algorithm> //не объяснено в курсе
#include <iostream>
#include <set>
#include <string>
#include <utility> //не объяснено в курсе
#include <vector>

using namespace std;

string ReadLine() { //будущие стоп-слова
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() { //будущее кол-во векторов в двумерном векторе
    int result = 0;
    cin >> result;
    ReadLine();
    return result;
}

vector<string> SplitIntoWords(const string& text) { //убираем лишние пробелы и пустоты, помещая результат в вектор
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

set<string> ParseStopWords(const string& text) { //создание мн-ва стоп-слов
    set<string> stop_words;
    for (const string& word : SplitIntoWords(text)) {
        stop_words.insert(word);
    }
    return stop_words;
}

vector<string> SplitIntoWordsNoStop(const string& text, const set<string>& stop_words) {//оставляем содержимое векторов вектора без стоп-слов
    vector<string> words;
    // проходим по всем словам из текста и проверяем, что их нет в списке стоп-слов
    for (const string& word : SplitIntoWords(text)) {
        if (stop_words.count(word) == 0) {
            words.push_back(word);
        }
    }
    // вернём результат без стоп-слов
    return words;
}

void AddDocument(vector<vector<string>>& documents, const set<string>& stop_words, 
                 const string& document) {//набиваем двумерный вектор
    const vector<string> words = SplitIntoWordsNoStop(document, stop_words);
    documents.push_back(words);//набиваем двумерный вектор без стоп слов
}

// Разбирает text на слова и возвращает только те из них, которые не входят в stop_words
set<string> ParseQuery(const string& text, const set<string>& stop_words) {
    set<string> query_words;

    // Напишите код функции
    vector<string> query = SplitIntoWordsNoStop(text, stop_words); //временно поместим содержимое вектора, после того как его перелопатило без стоп-слов в вектор
    query_words = set(query.begin(), query.end());//???????????????искомое множество
    return query_words;
}

// Возвращает true, если среди слов документа (document_words)
// встречаются слова поискового запроса query_words
bool MatchDocument(const vector<string>& document_words, const set<string>& query_words) {
    // Напишите код функции
    for (const string& line : document_words) {
        if (query_words.count(line) != 0) {
            return true;
        }
    }
    return false;
}

// Возвращает массив id документов, подходящих под запрос query
// Стоп-слова исключаются из поиска
vector<int> FindDocuments(const vector<vector<string>>& documents, const set<string>& stop_words,
                          const string& query) {
    vector<int> matched_documents;
    set parsed_query = ParseQuery(query, stop_words);
    int size = documents.size();
    for (int id=0; id < size; ++id){
        if (MatchDocument(documents[id], parsed_query)){
            matched_documents.push_back(id); 
        }
    }
       return matched_documents;
}

int main() {
    const string stop_words_joined = ReadLine(); //сохраняем в переменную введенную строку
    const set<string> stop_words = ParseStopWords(stop_words_joined); //сохраняем множество стоп-слов после парсинга, которые ввели ранее

    // Read documents
    vector<vector<string>> documents; //пустой двумерный вектор
    const int document_count = ReadLineWithNumber(); //сохраняем, после ввода кол-во векторов в векторе
    for (int document_id = 0; document_id < document_count; ++document_id) { //цикл наполнения вектора
        AddDocument(documents, stop_words, ReadLine()); //набиваем двумерный вектор, каждый со своим листом стоп-слов, считанных с Readline
    }

    const string query = ReadLine(); //поисковая строка
    for (const int document_id : FindDocuments(documents, stop_words, query)) { //поиск в двумерном векторе вектор, который содержит искомые слова, по запрашиваемой строке
        cout << "{ document_id = "s << document_id << " }"s << endl; //вывод id найденных векторов
    }
}