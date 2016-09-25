//
// Created by Linyxy on 16/9/25.
//

#include "Sphere.h"

Sphere::Sphere(const Vec3 &postion, GLfloat r) : postion(postion), r(r) {}

Sphere::Sphere() {
    postion = Vec3();
    r = 0;
}
