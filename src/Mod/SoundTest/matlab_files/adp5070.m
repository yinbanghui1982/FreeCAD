clc
clear

Rft1=620e3;
Rfb1=120e3;

vfb1=0.8;
vpos=vfb1*(1+Rft1/Rfb1)

%% 软启动
Rss=249e3;
tss=38.4e-3-1.28e-7*Rss






