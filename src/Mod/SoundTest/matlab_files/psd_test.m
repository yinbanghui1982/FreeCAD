%测试维纳-辛钦定理(自相关法）,FFT法，直接法  XJTU-test
clc
clear

Nx=1;

Fs=10000; %采样频率

% noise=randn(Nx,Ny);%高斯噪声

t = 0:1/Fs:10;

noise = sin(2*pi*1000*t);

N=length(noise); 
%直接法

[psdestx,Fxx] =psd_analysis(noise,N,Fs);


%[pxx,f] = periodogram(x,window,niff,Fs)

%niff为采样点数(计算傅里叶变换的点数)，决定了结果的疏密程度，niff越大，显示的结果越精细，分辨率=Fs/niff

%Fs为采样频率（单位时间内收集到的样本数），决定了x轴输出频率的最值，因为frequence=fs/2，最大为500

% plot(Fxx,pow2db(psdestx));
plot(Fxx,psdestx);