#include "request_queue.h"

RequestQueue::RequestQueue(const SearchServer& search_server):searcher_(search_server){}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status)
{
    std::vector<Document> result = searcher_.FindTopDocuments(raw_query, status);

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

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query)
{
    std::vector<Document> result = searcher_.FindTopDocuments(raw_query);

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

int RequestQueue::GetNoResultRequests() const
{
    return static_cast<int>(requests_.size());
}