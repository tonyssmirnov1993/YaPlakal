#pragma once
#include "ptrvector.h"
#include "scopedptr.h"

// Щупальце
class Tentacle {
public:
    explicit Tentacle(int id) noexcept
        : id_(id) {
    }

    int GetId() const noexcept {
        return id_;
    }

    Tentacle* GetLinkedTentacle() const noexcept {
        return linked_tentacle_;
    }
    void LinkTo(Tentacle& tentacle) noexcept {
        linked_tentacle_ = &tentacle;
    }
    void Unlink() noexcept {
        linked_tentacle_ = nullptr;
    }

private:
    int id_ = 0;
    Tentacle* linked_tentacle_ = nullptr;
};

// Осьминог
class Octopus {
public:
    Octopus()
        : Octopus(8) {
    }

    explicit Octopus(int num_tentacles) {
        for (int i = 1; i <= num_tentacles; ++i) {
            AddTentacle();  // Может выбросить исключение
        }
    }

    // Конструктор копирования класса PtrVector корректно скопирует щупальца,
    // поэтому сгенерированный компилятором конструктор копирования нас вполне устроит

    Tentacle& AddTentacle() {
        ScopedPtr<Tentacle> tentacle(
            new Tentacle(GetTentacleCount() + 1));  // Может выбросить исключение
        tentacles_.GetItems().push_back(tentacle.GetRawPtr());  // Может выбросить исключение

        tentacle.Release();
        return *tentacles_.GetItems().back();
    }

    int GetTentacleCount() const noexcept {
        return static_cast<int>(tentacles_.GetItems().size());
    }

    const Tentacle& GetTentacle(size_t index) const {
        return *tentacles_.GetItems().at(index);
    }
    Tentacle& GetTentacle(size_t index) {
        return *tentacles_.GetItems().at(index);
    }

private:
    PtrVector<Tentacle> tentacles_;
};