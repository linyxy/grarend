//
// Created by Linyxy on 16/9/25.
//

#include "dirLight.h"

dirLight::dirLight(Vec3 pos, Color c) {
    pos.normal();
    direction = pos;
    color = c;
}

dirLight::dirLight() {
    direction = Vec3();
    color = Color();
}