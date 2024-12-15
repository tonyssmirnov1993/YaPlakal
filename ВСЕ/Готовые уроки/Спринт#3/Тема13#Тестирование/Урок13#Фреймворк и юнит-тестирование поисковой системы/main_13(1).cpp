
// -------- Начало модульных тестов поисковой системы ----------

// Тест проверяет, что поисковая система исключает стоп-слова при добавлении документов
void TestExcludeStopWordsFromAddedDocumentContent() {
    const int doc_id = 42;
    const string content = "cat in the city"s;
    const vector<int> ratings = { 1, 2, 3 };
    {
        SearchServer server;
        server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
        const auto found_docs = server.FindTopDocuments("in"s);
        ASSERT_EQUAL(found_docs.size(), 1u);
        const Document& doc0 = found_docs[0];
        ASSERT_EQUAL(doc0.id, doc_id);
    }
    {
        SearchServer server;
        server.SetStopWords("in the"s);
        server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
        ASSERT_HINT(server.FindTopDocuments("in"s).empty(),
            "Stop words must be excluded from documents"s);
    }
}

void TestAddDocument() {
    SearchServer server;
    server.AddDocument(0, "small funny cat", DocumentStatus::ACTUAL, { 1,3,5 });
    ASSERT_EQUAL_HINT(1, server.GetDocumentCount(), "The function of adding a document does not work correctly"s);

    server.AddDocument(1, "грязный шмурдяк походный пес", DocumentStatus::ACTUAL, { -1,53,5, 3 });
    ASSERT_EQUAL_HINT(2, server.GetDocumentCount(), "The function of adding a document does not work correctly"s);

    server.AddDocument(2, "черный пес с биркой"s, DocumentStatus::BANNED, { 2, 2, 8 });
    ASSERT_EQUAL_HINT(3, server.GetDocumentCount(), "The function of adding a document does not work correctly"s);

    server.AddDocument(3, ""s, DocumentStatus::REMOVED, { -1, -4, -3 });
    ASSERT_EQUAL_HINT(4, server.GetDocumentCount(), "The function of adding a document does not work correctly"s);

    server.AddDocument(4, "ухоженный скворец евгений"s, DocumentStatus::REMOVED, { -1, -4, -3 });
    ASSERT_EQUAL_HINT(5, server.GetDocumentCount(), "The function of adding a document does not work correctly"s);

    server.AddDocument(5, "ухоженный скворец евгений"s, DocumentStatus::IRRELEVANT, { 0, 0, 0 });
    ASSERT_EQUAL_HINT(6, server.GetDocumentCount(), "The function of adding a document does not work correctly"s);
}

void TestMatchDocument() {
    SearchServer search_server;
    search_server.AddDocument(0, "пушистый ухоженный кот"s, DocumentStatus::ACTUAL, { 10, -4, 3 });
    search_server.AddDocument(1, "лысый грязный кот"s, DocumentStatus::ACTUAL, {});
    search_server.AddDocument(2, "черный пес с биркой"s, DocumentStatus::BANNED, { 2, 2, 8 });

    {
        vector<string> result = { "кот"s, "пушистый"s, "ухоженный"s };
        const auto [matched_words, document_status] = search_server.MatchDocument("пушистый ухоженный кот"s, 0);
        ASSERT_EQUAL_HINT(result, matched_words, "The MatchDocument method does not work correctly"s);
    }

    {
        vector<string> result = { "пес"s, "черный"s };
        const auto [matched_words, document_status] = search_server.MatchDocument("большой черный пес"s, 2);
        ASSERT_EQUAL_HINT(result, matched_words, "The MatchDocument method does not work correctly"s);
    }

    {
        vector<string> result;
        const auto [matched_words, document_status] = search_server.MatchDocument("лысый грязный -кот"s, 1);
        ASSERT_EQUAL_HINT(result, matched_words, "The MatchDocument method does not work correctly"s);
    }
}

void TestSetStopWords() {
    {
        SearchServer search_server;
        vector<string> result = { "мятный"s, "рюшками"s, "с"s, "шарф"s };
        search_server.SetStopWords(""s);
        search_server.AddDocument(0, "мятный шарф с рюшками"s, DocumentStatus::BANNED, { 2, 2, 8 });
        const auto [matched_words, document_status] = search_server.MatchDocument("мятный шарф с рюшками"s, 0);
        ASSERT_EQUAL_HINT(result, matched_words, "Incorrect work with stop words"s);
    }
    {
        SearchServer search_server;
        vector<string> result = { "мятный"s, "рюшками"s, "шарф"s };
        search_server.SetStopWords("с"s);
        search_server.AddDocument(0, "мятный шарф с рюшками"s, DocumentStatus::BANNED, { 2, 2, 8 });
        const auto [matched_words, document_status] = search_server.MatchDocument("мятный шарф с рюшками"s, 0);
        ASSERT_EQUAL_HINT(result, matched_words, "Incorrect work with stop words"s);
    }
    {
        SearchServer search_server;
        vector<string> result;
        search_server.SetStopWords("мятный шарф с рюшками красный"s);
        search_server.AddDocument(0, "мятный шарф с рюшками"s, DocumentStatus::BANNED, { 2, 2, 8 });
        const auto [matched_words, document_status] = search_server.MatchDocument("мятный шарф с рюшками"s, 0);
        ASSERT_EQUAL_HINT(result, matched_words, "Incorrect work with stop words"s);
    }
}

void TestFindTopDoucment() {
    vector<Document> documents;
    SearchServer search_server;
    search_server.SetStopWords("и в на"s);
    search_server.AddDocument(0, "белый кот и модный ошейник"s, DocumentStatus::ACTUAL, { 8, -3 });
    search_server.AddDocument(1, "пушистый кот пушистый хвост"s, DocumentStatus::ACTUAL, { 7, 2, 7 });
    search_server.AddDocument(3, "ухоженный скворец евгений"s, DocumentStatus::BANNED, { 9 });
    documents = search_server.FindTopDocuments("пушистый ухоженный кот"s);


    ASSERT_HINT(documents[0].relevance > documents[1].relevance, "Incorrect sorting by relevance"s);
    ASSERT_EQUAL_HINT(1, documents[0].id, "Incorrect document id"s);
    ASSERT_EQUAL_HINT(0.65067242136109593, documents[0].relevance, "Incorrect document relevance"s);
    ASSERT_EQUAL_HINT(5, documents[0].rating, "Incorrect document rating"s);

    ASSERT_EQUAL_HINT(0, documents[1].id, "Incorrect document id"s);
    ASSERT_EQUAL_HINT(0.10136627702704110, documents[1].relevance, "Incorrect document relevance"s);
    ASSERT_EQUAL_HINT(2, documents[1].rating, "Incorrect document rating"s);
}

void TestPredicate() {
    SearchServer search_server;
    search_server.SetStopWords("и в на с"s);
    search_server.AddDocument(0, "пушистый кот пушистый хвост"s, DocumentStatus::ACTUAL, {});
    search_server.AddDocument(1, "ухоженный скворец евгений"s, DocumentStatus::BANNED, { 9 });
    search_server.AddDocument(2, "пушистый пес с черной биркой"s, DocumentStatus::IRRELEVANT, { 2, 2, 8 });
    search_server.AddDocument(3, "синий цветок на красной ножке и ухоженный осел"s, DocumentStatus::REMOVED, { 1, 3, -8 });
    {
        vector<Document> documents;
        documents = search_server.FindTopDocuments("пушистый ухоженный кот"s, DocumentStatus::ACTUAL);

        ASSERT_EQUAL_HINT(0, documents[0].id, "Incorrect document id"s);
        ASSERT_EQUAL_HINT(0.69314718055994529, documents[0].relevance, "Incorrect document relevance"s);
        ASSERT_EQUAL_HINT(0, documents[0].rating, "Incorrect document rating"s);
    }
    {
        vector<Document> documents;
        documents = search_server.FindTopDocuments("пушистый ухоженный кот"s, DocumentStatus::BANNED);

        ASSERT_EQUAL_HINT(1, documents[0].id, "Incorrect document id"s);
        ASSERT_EQUAL_HINT(0.23104906018664842, documents[0].relevance, "Incorrect document relevance"s);
        ASSERT_EQUAL_HINT(9, documents[0].rating, "Incorrect document rating"s);
    }
    {
        vector<Document> documents;
        documents = search_server.FindTopDocuments("пушистый ухоженный кот"s, DocumentStatus::IRRELEVANT);

        ASSERT_EQUAL_HINT(2, documents[0].id, "Incorrect document id"s);
        ASSERT_EQUAL_HINT(0.17328679513998632, documents[0].relevance, "Incorrect document relevance"s);
        ASSERT_EQUAL_HINT(4, documents[0].rating, "Incorrect document rating"s);
    }
    {
        vector<Document> documents;
        documents = search_server.FindTopDocuments("пушистый ухоженный кот"s, DocumentStatus::REMOVED);

        ASSERT_EQUAL_HINT(3, documents[0].id, "Incorrect document id"s);
        ASSERT_EQUAL_HINT(0.11552453009332421, documents[0].relevance, "Incorrect document relevance"s);
        ASSERT_EQUAL_HINT(-1, documents[0].rating, "Incorrect document rating"s);
    }
    {
        vector<Document> documents;
        documents = search_server.FindTopDocuments("пушистый ухоженный кот"s, [](int document_id, DocumentStatus status, int rating)
            { return document_id % 2 == 0; });

        ASSERT_EQUAL_HINT(0, documents[0].id, "Incorrect document id"s);
        ASSERT_EQUAL_HINT(0.69314718055994529, documents[0].relevance, "Incorrect document relevance"s);
        ASSERT_EQUAL_HINT(0, documents[0].rating, "Incorrect document rating"s);
        ASSERT_EQUAL_HINT(2, documents[1].id, "Incorrect document id"s);
        ASSERT_EQUAL_HINT(0.17328679513998632, documents[1].relevance, "Incorrect document relevance"s);
        ASSERT_EQUAL_HINT(4, documents[1].rating, "Incorrect document rating"s);
    }
}

void TestCorrectRelevance()
{
    const double EPSILON = 1e-6;
    SearchServer server;
    server.AddDocument(1, "белый кот и модный ошейник"s, DocumentStatus::ACTUAL, { 8, -3 });
    server.AddDocument(2, "пушистый кот пушистый хвост"s, DocumentStatus::ACTUAL, { 7, 2, 7 });
    server.AddDocument(3, "ухоженный пёс выразительные глаза"s, DocumentStatus::ACTUAL, { 5, -12, 2, 1 });

    const auto docs = server.FindTopDocuments("пушистый ухоженный кот");

    ASSERT(std::abs(docs[0].relevance - 0.65067242136109593)  < EPSILON);
    ASSERT(std::abs(docs[2].relevance - 0.081093021621632885) < EPSILON);
    ASSERT(std::abs(docs[1].relevance - 0.27465307216702745)  < EPSILON);
}

void TestGetStatus() {
    SearchServer server;
    server.AddDocument(1, "a colorful parrot with green wings and red tail is lost"s, DocumentStatus::ACTUAL, { 2 });
    server.AddDocument(2, "a grey hound with black ears is found at the railway station is lost BIM"s, DocumentStatus::ACTUAL, { 3 });
    server.AddDocument(99, "a white cat with long furry tail is found near the red square"s, DocumentStatus::ACTUAL, {});
    server.AddDocument(105, "banned document BIM BAM BOM"s, DocumentStatus::BANNED, { 4 });
    server.AddDocument(107, "irrelevant document BOM BUM"s, DocumentStatus::IRRELEVANT, { 5 });
    server.AddDocument(109, "AAA CCC BBB DDD"s, DocumentStatus::REMOVED, { 5 });

    {
        const vector<Document>& documents = server.FindTopDocuments("document BIM BAM BOM"s, DocumentStatus::ACTUAL);
        ASSERT_EQUAL(documents.size(), 1u);
    }
    {
        const vector<Document>& documents = server.FindTopDocuments("document BIM BAM BOM"s, DocumentStatus::BANNED);
        ASSERT_EQUAL(documents.size(), 1u);
        ASSERT_EQUAL(documents[0].id, 105);
    }
    {
        const vector<Document>& documents = server.FindTopDocuments("document BIM BAM BOM"s, DocumentStatus::IRRELEVANT);
        ASSERT_EQUAL(documents.size(), 1u);
        ASSERT_EQUAL(documents[0].id, 107);
    }
    {
        const vector<Document>& documents = server.FindTopDocuments("document BIM BAM BOM"s, DocumentStatus::REMOVED);
        ASSERT_EQUAL(documents.size(), 0u);
    }
}

void TestComputeRelevance() {
    const double EPSILON = 0.0001;
    SearchServer server;
    server.AddDocument(1, "BIM BIM BAM BOM"s, DocumentStatus::ACTUAL, { 2 });
    server.AddDocument(2, "BAM BAM"s, DocumentStatus::ACTUAL, { 3 });
    server.AddDocument(3, "BUM BUM"s, DocumentStatus::ACTUAL, { 4 });
    double tfBIM1 = 2.0 / 4.0;
    double idfBIM1 = log(3.0 / 1.0);
    double relevance1 = tfBIM1 * idfBIM1;
    const vector<Document>& documents = server.FindTopDocuments("BIM"s, DocumentStatus::ACTUAL);
    double delta = std::abs(documents[0].relevance - relevance1);
    ASSERT(delta < EPSILON);
}

// Функция TestSearchServer является точкой входа для запуска тестов
void TestSearchServer() {
    RUN_TEST(TestExcludeStopWordsFromAddedDocumentContent);
    RUN_TEST(TestAddDocument);
    RUN_TEST(TestMatchDocument);
    RUN_TEST(TestSetStopWords);
    RUN_TEST(TestFindTopDoucment);
    RUN_TEST(TestPredicate);
    RUN_TEST(TestCorrectRelevance);
    RUN_TEST(TestComputeRelevance);
    RUN_TEST(TestGetStatus);
    // Не забудьте вызывать остальные тесты здесь
}

// --------- Окончание модульных тестов поисковой системы -----------
int main() {
    TestSearchServer();
    cout << "Search server testing finished"s << endl;
}