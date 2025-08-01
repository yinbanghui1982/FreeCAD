clc
clear

dt=.1;
t=[0:dt:100];
x=cos(t);

[c,lags2]=auto_corr_analysis(x,dt);

% plot(lags2,c)