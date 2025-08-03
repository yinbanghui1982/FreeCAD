#include "corr.h"

namespace SoundTest {
// 计算自相关函数
/*
N 序列长度
n 偏移位置
data 数据
*/
double AutoCorrelation(double* data, int n, int N){
    double    r= 0.0;
    if (n>=0){
        for(int i = n; i <N;i++ ) {
            r +=data[i] * data[i-n];
        }
    } else {
        for(int i = 0; i <N+n;i++ ) {
            r +=data[i] * data[i-n];
        }
    }
    return  r ;
}

void autoCorrelationAnalysis(double* data, int N, double dt, double* xlist, double* ylist){
    for (int n=-N/2;n<N/2;n++){
        *xlist=n*dt;
        *ylist=AutoCorrelation(data,n,N);
        xlist++;
        ylist++;
    }
}

double CrossCorrelation(double* data1, double* data2, int n, int N){
    double    r= 0.0;
    if (n>=0){
        for(int i = n; i <N;i++ ) {
            r +=data1[i] * data2[i-n];
        }
    } else {
        for(int i = 0; i <N+n;i++ ) {
            r +=data1[i] * data2[i-n];
        }
    }
    return  r ;
}


void crossCorrelationAnalysis(double* data1, double* data2, int N, double dt, double* xlist, double* ylist){
    for (int n=-N/2;n<N/2;n++){
        *xlist=n*dt;
        *ylist=CrossCorrelation(data1, data2,n,N);
        xlist++;
        ylist++;
    }
}
} // namespace SoundTest