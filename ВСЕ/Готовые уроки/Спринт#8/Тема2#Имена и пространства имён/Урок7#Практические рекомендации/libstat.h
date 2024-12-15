#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
 
using namespace std::literals;
namespace statistics {
namespace aggregations {
    
class Sum { // сумма
public:
    void PutValue(double value);
    std::optional<double> Get() const;
 
    static std::string_view GetValueName() {
        return "sum"sv;
    }
 
private:
    double sum_ = 0;
};
 
class Max { // максимум
public:
    void PutValue(double value);
    std::optional<double> Get() const;
 
    static std::string_view GetValueName() {
        return "max"sv;
    }
 
private:
    std::optional<double> cur_max_;
};
 
class Mean { // среднее арифметическое
public:
    void PutValue(double value);
    std::optional<double> Get() const;
 
    static std::string_view GetValueName() {
        return "mean"sv;
    }
 
private:
    aggregations::Sum sum_;
    size_t count_ = 0;
};
 
class StandardDeviation { // стандартное отклонение
public:
    void PutValue(double value);
    std::optional<double> Get() const;
 
    static std::string_view GetValueName() {
        return "standard deviation"sv;
    }
 
private:
    aggregations::Sum sum_;
    aggregations::Sum sum_sq_;
    size_t count_ = 0;
};
 
class Mode { // мода
public:
    void PutValue(double value);
    std::optional<double> Get() const;
 
    static std::string_view GetValueName() {
        return "mode"sv;
    }
 
private:
    std::unordered_map<double, size_t> counts_;
    std::optional<double> cur_max_;
    size_t cur_count_ = 0;
};
 
} // конец namespace statistics::aggregations
 
namespace tests {
    
void AggregSum();
void AggregMax();
void AggregMean();
void AggregStandardDeviation();
void AggregMode();
void AggregPrinter();
    
} // конец namespace tests
 
template <typename Aggreg>
class AggregPrinter {
public:
    void PutValue(double value) {
        inner_.PutValue(value);
    }
 
    void Print(std::ostream& out) const {
        auto val = inner_.Get();
        out << inner_.GetValueName() << " is "sv;
        if (val) {
            out << *val;
        } else {
            out << "undefined"sv;
        }
        out << std::endl;
    }
 
private:
    Aggreg inner_;
};
    
} // конец namespace statistics