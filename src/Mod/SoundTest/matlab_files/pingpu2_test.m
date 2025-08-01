%测试维纳-辛钦定理(自相关法）,FFT法，直接法  XJTU-test
clc
clear

Fs=10e3; %采样频率
time = 0:1/Fs:10;
sig = 3*sin(2*pi*300*time);
[f,Y,fs]=pingpu2(time,sig);
figure(2);plot(f,Y,'DisplayName','通道1')
xlabel("频率/Hz")
ylabel("幅值谱/Pa/Hz")





