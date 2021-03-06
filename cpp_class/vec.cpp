//vec.cpp
#include <iostream>
#include "vec.h"
using namespace std;
int main() {
    cout<<"**********测试不同类型的构造函数和拷贝构造函数************"<<endl;
    Vector<double> v1(1.5,10);
    Vector<double> v2(3,10);
    Vector<int>v3;//空向量
    Vector<int>v4(2,10);//空向量
    Vector<int>v5(v4);//空向量
    Vector<double> v6(2,3);
    Vector<float> v7(1.1,10);
    cout<<"***************************************************"<<endl;
    cout<<"*****************测试重载的输出流********************"<<endl;
    cout<<v5;
    cout<<v1<<v2;//测试重载输出流
    cout<<"*****************测试重载的+ * 友元* - += []**************"<<endl;
    cout<<v1+v2<<"重载+"<<endl;//测试重载+
    cout<<v1*v2<<"重载×"<<endl;//测试重载叉乘
    cout<<(-1)*v2<<"重载友元的×"<<endl;//测试友元函数
    cout<<v2-v1<<"重载-";//测试重载-
    v2+=2;//测试迭代运算符
    cout<<v2<<"重载+="<<endl;
    cout<<v2[9]<<"  重载[]"<<endl;//测试重载[]
    cout<<"**************************************************"<<endl;
    cout<<"*******************测试重载的逻辑运算符***************"<<endl;
    cout<<(v1==v2)<<endl;//测试重载逻辑运算符
    cout<<(v1!=v2)<<endl;
    cout<<"********************测试empty()函数判断空向量***************"<<endl;
    cout<<v2.empty()<<endl;//测试判断空向量函数
    cout<<v3.empty()<<endl;//判断空向量测试
    cout<<"*******************测试单位化normalize*****************"<<endl;
    v2.normalize();//向量单位化
    cout<<v2<<endl;
    cout<<"*******************测试求模长module********************"<<endl;
    cout<<v2.module()<<endl;//求模长
    cout<<"***************测试维数增加函数,v3从空向量变为三维向量*****************"<<endl;
    v3.vdimup(3);//测试向量升维
    cout<<v3;
    cout<<"**************测试维数降低函数v3从三维向量降低一维向量*****************"<<endl;
    v3.vdimdown(1);//测试向量降维
    cout<<v3;
    cout<<"**************************v1和v2点乘*****************************"<<endl;
    cout<<v1.multiply(v2)<<endl;//测试点乘
    cout<<"************************求两个向量的角度***************************"<<endl;
    cout<<v1.angle(v2)<<"angle"<<endl;//测试角度计算
    cout<<"******************测试不同类型的Vector相加和相乘*********************"<<endl;
    cout<<v1+v4<<endl;//double + int
    cout<<v1*v7<<endl;//double * int
    cout<<"****************异常处理****************"<<endl;
    try{cout<<v1[11];} catch (int) {
        cout<<"out of boundary!"<<endl;
    }
    try{cout<<v1*v6<<endl;}catch(int){
        cout<<"size out of different!"<<endl;
    }
    cout<<"*******************************"<<endl;
    return 0;
}
