#include "wall.h"

class Painter {
public:
    // Напишите класс Painter
    auto Paint(Wall& wall, Wall::Color color) const{
        wall.SetColor(color);
    }
};