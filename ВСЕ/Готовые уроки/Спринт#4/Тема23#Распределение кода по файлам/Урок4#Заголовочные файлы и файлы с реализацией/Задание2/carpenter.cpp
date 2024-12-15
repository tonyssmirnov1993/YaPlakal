#include "carpenter.h"
#include "square_calculation.h"

int Carpenter::CalcShelves(const Wall& wall){   
    double x=wall.GetWidth();
    double y=wall.GetHeight();
    return CalcSquare(x,y)/2;
}
int main(){
    
}