//
// Created by Linyxy on 16/9/25.
//

#include "pntLight.h"
pntLight::pntLight(Vec3 pos, Color co) {
    position = pos;
    color = co;
}

pntLight::pntLight() : position(Vec3()),color(Color()) {

}