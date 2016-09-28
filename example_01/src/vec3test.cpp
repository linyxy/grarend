//
// Created by Linyxy on 16/9/27.
//

#include "Vec3.h"
#include <iostream>
using namespace std;

void prfloatVec(Vec3 &vec)
{
    cout << "["
         << vec.x << ","
         << vec.y << ","
         << vec.z << "]" << endl;
}

int main()
{
    cout << "hello vector" << endl;

    //测试构造函数
    Vec3 v1(10,20,30);
    prfloatVec(v1);

    //测试默认拷贝构造函数
    Vec3 v2(v1);
    prfloatVec(v2);

    //测试负向量
    Vec3 v3 = -v1;
    prfloatVec(v3);

    //测试零向量
    v2.Zero();
    prfloatVec(v2);

    //测试计算向量长度
    Vec3 v4(5,-4,7);
    float r = v4.Length();
    cout << r << endl;

    //测试向量乘以标量
    Vec3 v5(-5,0,0.4f);
    Vec3 v6 = v5 * -3;
    prfloatVec(v6);

    //测试向量乘等于标量
    v5 *= -3;
    prfloatVec(v5);

    //测试向量除以标量
    Vec3 v7(4.7f,-6,8);
    Vec3 v8 = v7 / 2;
    prfloatVec(v8);

    //测试标量乘以向量
    Vec3 v9(1,2,3);
    Vec3 v10 = 2 * v9;
    prfloatVec(v10);

    //测试向量标准化
    Vec3 v11(12,-5,0);
    v11.Normal();
    prfloatVec(v11);

    //测试向量相加
    Vec3 a(1,2,3);
    Vec3 b(4,5,6);
    Vec3 r1 = a + b;
    prfloatVec(r1);

    //测试向量相减
    Vec3 r2 = b - a;
    prfloatVec(r2);

    //测试向量间距离
    Vec3 x(5,0,0);
    Vec3 y(-1,8,0);
    float d = x.Distance(y);
    cout << d << endl;

    //向量相乘
    Vec3 h1(3,-2,7);
    Vec3 h2(0,4,-1);
    float dp = h1 * h2;
    cout << dp << endl;

    //两向量间的角度
    float arc = static_cast<float>(acos(dp/(h1.Length()*h2.Length())) * 180 / 3.14149);
    cout << arc << endl;

    //两向量叉乘
    Vec3 t1(1,3,4);
    Vec3 t2(2,-5,8);
    Vec3 cp = t1.CrossProduct(t2);
    prfloatVec(cp);

    system("pause");
    return 0;

}