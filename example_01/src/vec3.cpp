#include <math.h>
#include <GLFW/glfw3.h>

class Vec3
{

	private:
		GLfloat x,y,z;

	public:
		Vec3(GLfloat x,GLfloat y,GLfloat z);
		Vec3(Vec3 v);
        Vec3();
		static Vec3 copy(Vec3 v);
		Vec3 normalize(Vec3 v);
		void normalize();
        static GLfloat dot(Vec3 va,Vec3 vb);
        GLfloat getx();
        GLfloat gety();
        GLfloat getz();
        void setx(GLfloat a);
        void sety(GLfloat a);
        void setz(GLfloat a);
        void setVec(GLfloat a, GLfloat b, GLfloat c);
        static Vec3 cross(Vec3 va,Vec3 vb);
        GLfloat length();
        void add(Vec3 va);
        static Vec3 add(Vec3 va,Vec3 vb);
        void sub(Vec3 va);
        static Vec3 sub(Vec3 va,Vec3 vb);
        static Vec3 inverse(Vec3 va);
        void inverse();
        void scale(GLfloat n);
        static Vec3 scale(Vec3 va,GLfloat n);
        //重载
        Vec3 operator+(const Vec3 va);
        Vec3 operator-(const Vec3 va);
        Vec3 operator*(const GLfloat m);
        Vec3 operator=(const Vec3 va);
};

Vec3::Vec3(GLfloat x,GLfloat y,GLfloat z){
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3::Vec3() {
    x = 0;
    y = 0;
    z = 0;
}



Vec3::Vec3(Vec3 v){
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

GLfloat Vec3::getx() {
    return x;
}

GLfloat Vec3::gety() {
    return y;
}

GLfloat Vec3::getz() {
    return z;
}

void Vec3::setx(GLfloat a) {
    x = a;
}

void Vec3::sety(GLfloat a) {
    y = a;
}

void Vec3::setz(GLfloat a) {
    z = a;
}

void Vec3::setVec(GLfloat a, GLfloat b, GLfloat c) {
    setx(a);
    sety(b);
    setz(c);
}

Vec3 Vec3::copy(Vec3 v){
	Vec3 p = Vec3(v.x,v.y,v.z);
	return p;
}

Vec3 Vec3::normalize(Vec3 v){
	GLfloat length = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	return Vec3(v.x/length,v.y/length,v.z/length);
}

void Vec3::normalize(){
	GLfloat length = sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
    this->x /= length;
    this->y /= length;
    this->z /= length;
}

GLfloat Vec3::dot(Vec3 va,Vec3 vb){
    return  va.getx()*vb.getx()+
            va.gety()*vb.gety()+
            va.getz()*vb.getz();
}

Vec3 Vec3::cross(Vec3 va, Vec3 vb) {

}

GLfloat Vec3::length() {
    return sqrt(x*x+y*y+z*z);
}

Vec3 Vec3::inverse(Vec3 va) {
    return  Vec3(va.getx()*(-1),va.gety()*(-1),va.getz()*(-1));
}

void Vec3::inverse() {
    x = x*(-1);
    y = y*(-1);
    z = z*(-1);
}

void Vec3::add(Vec3 va) {
    setx(x+va.getx());
    sety(y+va.gety());
    setz(z+va.getz());
}

void Vec3::sub(Vec3 va) {
    add(inverse(va));
}

Vec3 Vec3::add(Vec3 va, Vec3 vb) {
    return     Vec3(va.getx()+vb.getx(),
                    va.gety()+vb.gety(),
                    va.getz()+vb.getz());
}

Vec3 Vec3::sub(Vec3 va, Vec3 vb) {
    return add(va,inverse(vb));
}

void Vec3::scale(GLfloat n) {
    setx(x*n);
    sety(y*n);
    setz(z*n);
}

Vec3 Vec3::scale(Vec3 va, GLfloat n) {
    Vec3 v =  Vec3(va);
    v.scale(n);
    return v;
}

Vec3 Vec3::operator+(const Vec3 va) {
    Vec3 v =  Vec3(*this);
    v.add(va);
    return v;
}

Vec3 Vec3::operator-(const Vec3 va) {
    Vec3 v =  Vec3(*this);
    v.sub(va);
    return v;
}

Vec3 Vec3::operator*(const GLfloat m) {
    Vec3 v=  Vec3(*this);
    v.scale(m);
    return v;
}

Vec3 Vec3::operator=(const Vec3 va) {
    x = va.x;
    y = va.y;
    z = va.z;
    return *this;
}