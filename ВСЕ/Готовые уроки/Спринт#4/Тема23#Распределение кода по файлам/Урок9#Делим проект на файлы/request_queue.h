#pragma once
#include <deque>
#include <iostream>

#include "search_server.h"
#include "document.h"

class RequestQueue
{
public:
    explicit RequestQueue(const SearchServer& search_server);
    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate); 

    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);
    std::vector<Document> AddFindRequest(const std::string& raw_query);
    int GetNoResultRequests() const; 

private:
    struct QueryResult {
        std::string request;
        std::vector<Document>& result;
    };
    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    const  SearchServer& searcher_;

    int all_requests_ = 0;
    bool next_day = false;
};

template<typename DocumentPredicate>
inline std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate)
{
    {
        std::vector<Document> result = searcher_.FindTopDocuments(raw_query, document_predicate);
        if (all_requests_ == min_in_day_)
        {
            next_day = true;
        }

        if (next_day)
        {
            requests_.pop_front();
            --all_requests_;
        }

        if (result.empty())
        {
            requests_.push_back({ raw_query, result });
            ++all_requests_;
        }
        else
            ++all_requests_;
        return result;
    }
}