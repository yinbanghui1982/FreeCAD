#ifndef CORR_H
#define CORR_H
namespace SoundTest {

void autoCorrelationAnalysis(double* data, int N, double dt, double* xlist, double* ylist);
void crossCorrelationAnalysis(double* data1, double* data2, int N, double dt, double* xlist, double* ylist);


} // namespace SoundTest
#endif // CORR_H
