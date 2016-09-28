//
// Created by Linyxy on 16/9/25.
//

#ifndef ASSIGNMENT1_DIRLIGHT_H
#define ASSIGNMENT1_DIRLIGHT_H

#include "Vec3.h"
#include "Color.h"

class dirLight {
    public:
        Vec3 position;
        Color color;

        dirLight(Vec3 pos,Color c);
        dirLight();

};


#endif //ASSIGNMENT1_DIRLIGHT_H
