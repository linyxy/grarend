//
// Created by Linyxy on 16/9/25.
//

#ifndef ASSIGNMENT1_SPHERE_H
#define ASSIGNMENT1_SPHERE_H

#include "Vec3.cpp"

class Sphere {
public:
    //这个类是之后写额外的球体的时候用的,暂时用不着
    Vec3 postion;
    GLfloat r;

    Sphere(const Vec3 &postion, GLfloat r);

    Sphere();
};


#endif //ASSIGNMENT1_SPHERE_H
