//
// Created by Linyxy on 16/9/25.
//

#ifndef ASSIGNMENT1_PNTLIGHT_H
#define ASSIGNMENT1_PNTLIGHT_H


#include "Color.h"

class pntLight {
public:
    Vec3 position;
    Color color;

    pntLight(Vec3 pos,Color co);
};


#endif //ASSIGNMENT1_PNTLIGHT_H
