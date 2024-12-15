struct Document {
    int id;
    int relevance;
};

/* возвращаемое значение */  /* параметры функции */
/* условие, при котором первый объект будет в векторе раньше второго */
bool HasDocumentGreaterRelevance(const Document& lhs, const Document& rhs) {
        return lhs.relevance > rhs.relevance;
} 

int main() {
   
}