//
// Created by Linyxy on 16/9/25.
//

#include "Material.h"

Material::Material(const Vec3 &ambient, const Vec3 &diffuse, const Vec3 &specular, int anisoFlag, GLfloat spu,
                   GLfloat spv = 0) : ambient(ambient), diffuse(diffuse), specular(specular), anisoFlag(anisoFlag),
                                  spu(spu), spv(spv) {}

Material::Material() {
    ambient = Vec3();
    specular= Vec3();
    diffuse = Vec3();
    anisoFlag = 0;
    spu = spv = 0;
}

