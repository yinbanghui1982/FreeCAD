clc
clear

Fs = 1000;
t = 0:1/Fs:0.296;

x = cos(2*pi*t*100)+0.05*randn(size(t));

tau = 1/400;
y = cos(2*pi*150*(t-tau))+0.05*randn(size(t));


[Pxy2,arg2,f]=cpsd_analysis(x,y,Fs)

figure(1);plot(f,Pxy2);hold on
%figure(2);plot(f,arg2)


xlabel("频率/Hz")
ylabel("幅值谱级/dB ref=1 Pa^2/Hz")
legend














