
//#include <GLFW/glfw3.h>
#include "Vec3.h"


Vec3::Vec3(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}

Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}

void Vec3::zero() {
    x = y = z = 0;
}

Vec3 Vec3::operator-() const {
    return Vec3(-x,-y,-z);
}

Vec3 Vec3::operator+(Vec3 va) const {
    return Vec3(x+va.x,y+va.y,z+va.z);
}

Vec3& Vec3::operator+=(Vec3 &va) {
    *this = *this + va;
    return *this;
}

Vec3 Vec3::operator-(Vec3 &va) const {
    return Vec3(x-va.x,y-va.y,z-va.z);
}

Vec3 Vec3::operator-=(Vec3 &va) {
    *this = *this - va;
    return *this;
}

Vec3 Vec3::operator*(GLfloat m) const {
    return Vec3(x*m,y*m,z*m);
}

GLfloat Vec3::operator*(Vec3 &va) const {
    return x*va.x+y*va.y+z*va.z;
}

Vec3& Vec3::operator*=(GLfloat m) {
    return *this = *this * m;
}

GLfloat Vec3::length() const {
    return sqrt(x*x+y*y+z*z);
}

void Vec3::normal() {
    GLfloat t = 1 / length();
    x = x * t;
    y = y * t;
    z = z * t;
}

Vec3 Vec3::indi_scale(Vec3 &va) const {
    return Vec3(x*va.x,y*va.y,z*va.z);
}

GLfloat Vec3::dist(Vec3 &va) const {
    return (*this - va).length();
}

Vec3 Vec3::cross(Vec3 &va) const {
    return Vec3(this->y * va.z - this->z * va.y,
                   this->z * va.x - this->x * va.z,
                   this->x * va.y - this->y * va.x);
}