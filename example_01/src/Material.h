//
// Created by Linyxy on 16/9/25.
//

#ifndef ASSIGNMENT1_MATERIAL_H
#define ASSIGNMENT1_MATERIAL_H


#include "Color.h"

class Material {
public:
    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
    //under are for isotropic & anisotropic material
    // anisoFlag
    // 0 : isotropipc material
    // 1 : anisotropic material
    // for isotropic material we only use spu as sp
    int anisoFlag;
    GLfloat spu;
    GLfloat spv;

    Material(const Vec3 &ambient, const Vec3 &diffuse, const Vec3 &specular, int anisoFlag, GLfloat spu, GLfloat spv);

    Material();
};


#endif //ASSIGNMENT1_MATERIAL_H
