//
// Created by Linyxy on 16/9/25.
//

#include "Color.h"



using namespace std;

Color::Color() {
    co =  Vec3(0,0,0);
}

GLfloat min(GLfloat a, GLfloat b){
    if(a<b)return a;
    return b;
}

GLfloat max(GLfloat a, GLfloat b){
    if(a>b)return a;
    return b;
}

Color::Color(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha) {
    //range r g b is 0 - 255
    r = max(min(255,r),0);
    g = max(min(255,g),0);
    b = max(min(255,b),0);
    co = Vec3(r,g,b);
    this->alpha = alpha;
}



GLfloat Color::R() const{
    return co.x;
}

GLfloat Color::G() const{
    return co.y;
}

GLfloat Color::B() const{
    return co.z;
}

Vec3 Color::comp() const {
    return Vec3(R(),G(),B());
}

Color Color::operator*(GLfloat &m)const {


    return Color(R()*m,G()*m,B()*m);
}


