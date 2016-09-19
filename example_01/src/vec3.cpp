#include <math.h>

class Vec3
{

	private:
		double x,y,z;

	public:
		Vec3(double x,double y,double z);
		Vec3(Vec3 v);
		Vec3 copy(Vec3 v);
		Vec3 normalize(Vec3 v);
		void normalize();
        double dot(Vec3 va,Vec3 vb);
        double getx();
        double gety();
        double getz();
        void setx(double a);
        void sety(double a);
        void setz(double a);
        void setVec(double a, double b, double c);
        static Vec3 cross(Vec3 va,Vec3 vb);
        double length();
        void add(Vec3 va);
        static Vec3 add(Vec3 va,Vec3 vb);
        void sub(Vec3 va);
        static Vec3 sub(Vec3 va,Vec3 vb);
        static Vec3 inverse(Vec3 va);

	
};

Vec3::Vec3(double x,double y,double z){
	this->x = x;
	this->y = y;
	this->z = z;
}



Vec3::Vec3(Vec3 v){
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

double Vec3::getx() {
    return x;
}

double Vec3::gety() {
    return y;
}

double Vec3::getz() {
    return z;
}

void Vec3::setx(double a) {
    x = a;
}

void Vec3::sety(double a) {
    y = a;
}

void Vec3::setz(double a) {
    z = a;
}

void Vec3::setVec(double a, double b, double c) {
    setx(a);
    sety(b);
    setz(c);
}

Vec3 Vec3::copy(Vec3 v){
	Vec3 p = new Vec3(v.x,v.y,v.z);
	return p;
}

Vec3 Vec3::normalize(Vec3 v){
	double length = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	return new Vec3(v.x/length,v.y/length,v.z/length);
}

void Vec3::normalize(){
	double length = sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
    this->x /= length;
    this->y /= length;
    this->z /= length;
}

double Vec3::dot(Vec3 va,Vec3 vb){
    return  va.getx()*vb.getx()+
            va.gety()*vb.gety()+
            va.getz()*vb.getz();
}

Vec3 Vec3::cross(Vec3 va, Vec3 vb) {

}

double Vec3::length() {
    return sqrt(x*x+y*y+z*z);
}

Vec3 Vec3::inverse(Vec3 va) {
    return  new Vec3(va.getx()*(-1),va.gety()*(-1),va.getz()*(-1));
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
    return  new Vec3(va.getx()+vb.getx(),
                    va.gety()+vb.gety(),
                    va.getz()+vb.getz());
}

Vec3 Vec3::sub(Vec3 va, Vec3 vb) {
    return add(va,inverse(vb));
}