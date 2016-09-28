//
// Created by Linyxy on 16/9/25.
//

#include "dirLight.h"

dirLight::dirLight(Vec3 pos, Color c) {
    position = pos;
    color = c;
}

dirLight::dirLight() {
    position = Vec3();
    color = Color();
}