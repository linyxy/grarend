//
// Created by Linyxy on 16/9/25.
//

#include "Color.h"
#include <cmath>


Color::Color() {
    co =  Vec3(0,0,0);
}

Color::Color(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha = 1) {
    //max r g b is 255
    r = min(255,r);
    co = Vec3(r,g,b);
    this->alpha = alpha;
}

GLfloat Color::R() {
    return co.getx();
}

GLfloat Color::G() {
    return co.gety();
}

GLfloat Color::B() {
    return co.getz();
}

