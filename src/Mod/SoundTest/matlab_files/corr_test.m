clc
clear

dt=.1;
t=[0:dt:100];
x=cos(t);
[a,b]=xcorr(x,'unbiased');
% plot(b*dt,a)

y=cos(5*t);
[a,b]=xcorr(x,y,'unbiased');
plot(b*dt,a)