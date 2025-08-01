clc
clear

t=1e-3:1e-3:1;
x=sin(t)+sin(5000*t);
y=fft_test_fun(x);
plot(y)