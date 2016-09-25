//
// Created by Linyxy on 16/9/25.
//

#include "Color.h"
#include <cmath>
#include <algorithm>

using namespace std;

Color::Color() {
    co =  Vec3(0,0,0);
}

Color::Color(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha = 1) {
    //range r g b is 0 - 255
    r = max(min(255,r),0);
    g = max(min(255,g),0);
    b = max(min(255,b),0);
    co = Vec3(r,g,b);
    this->alpha = alpha;
}

Color::Color(Color c) {
    co = Vec3(c.co);
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



Color Color::operator*(const GLfloat m) {
    Color v=  Color(*this);
    v.co.scale(m);
    return v;
}
