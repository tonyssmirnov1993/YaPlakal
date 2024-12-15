#include <iostream>

using namespace std;

/* Допишите класс в соответствии с требованиями задания*/
class TV {
public:
    // Включает телевизор.
    void TurnOn() {
        // Напишите код этого метода
        is_turned_on_ = true;
    }

    // Выключает телевизор
    void TurnOff() {
        // Напишите код этого метода
        is_turned_on_ = false;
    }

    // Возвращает true, если телевизор включен и false, если телевизор выключен
    bool IsTurnedOn() {
        // Напишите код этого метода
        if (is_turned_on_ == true) {
            return true;
        }
        return false;
    }

    // Возвращает номер текущего канала, либо 0, если телевизор был выключен.
    // Телевизор при выключении «запоминает» номер текущего канала,
    // а при включении — «восстанавливает» его.
    // При первом включении телевизор показывает канал №1.
    int GetCurrentChannel() {
        // Напишите код этого метода
        if (is_turned_on_ == true && current_channel_ > 0) {
            return current_channel_;
        }
        return 0;
    }

    // Выбирает канал с указанным номером. Номер канала должен быть в диапазоне [1..99].
    // Если указан недопустимый номер канала, либо телевизор выключен, возвращает false и не меняет
    // текущий канал. В противном случае возвращает true.
    bool SelectChannel(int channel) {
        // Напишите код этого метода
        if (is_turned_on_ == true && (channel >= 1 && channel <= 99)) {
            current_channel_ = channel;
            return true;
        }
        return false;
    }
    
    private:
    bool is_turned_on_ = false;
    int current_channel_ = 1;
};

int main() {
    TV tv;
    cout << tv.IsTurnedOn() << ", channel:"s << tv.GetCurrentChannel() << endl;
    tv.TurnOn();
    cout << tv.IsTurnedOn() << ", channel: "s << tv.GetCurrentChannel() << endl;
    tv.SelectChannel(25);
    cout << tv.IsTurnedOn() << ", channel: "s << tv.GetCurrentChannel() << endl;
    tv.TurnOff();
    cout << tv.IsTurnedOn() << ", channel: "s << tv.GetCurrentChannel() << endl;
}