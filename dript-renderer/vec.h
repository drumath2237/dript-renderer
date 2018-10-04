#ifndef H_VEC
#define H_VEC

#include<iostream>

struct Vec {
  double x;
  double y;
  double z;

  Vec(): x(0),y(0),z(0){}
  Vec(double d):x(d),y(d),z(d){}
  Vec(double x, double y, double z):x(x),y(y),z(z){}
};

Vec operator-(const Vec v){
  return Vec(-v.x, -v.y, -v.z);
}
Vec operator+(const Vec a, const Vec b)
{
  return Vec(a.x + b.x, a.y + b.y, a.z + b.z);
}
Vec operator-(const Vec a, const Vec b)
{
  return Vec(a.x - b.x, a.y - b.y, a.z - b.z);
}
Vec operator*(const double d, const Vec b)
{
  return Vec(d * b.x, d * b.y, d * b.z);
}
Vec operator*(const Vec b, const double d)
{
  return Vec(d * b.x, d * b.y, d * b.z);
}
Vec operator/(const Vec v, const double d)
{
  if(d==0){return Vec();} // zero devision
  return Vec(v.x/d, v.y/d, v.z/d);
}

double dot(Vec a, Vec b)
{
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

double length(Vec v)
{
  return sqrt(dot(v,v));
}

Vec normalize(Vec v)
{
  return v/length(v);
}

Vec cross(Vec a, Vec b)
{
  return Vec(
    a.y*b.z - a.z*b.y,
    a.z*b.x - a.x*b.z,
    a.x*b.y - a.y*b.x
  );
}


#endif // !H_VEC