void UpdateIfGreater(int limit, int& value) {
    if (limit > value) {
        value=limit;
    }
}

int main() {
    
}
/*Ссылки начинают вам покоряться! 
Если передать limit по ссылке, а не по значению, вызвать UpdateIfGreater(25, value) не получится. 
Ведь int& нельзя привязать к числовому литералу.*/