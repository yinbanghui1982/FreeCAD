clc
clear

Fs = 1000;
t = 0:1/Fs:0.296;

x = cos(2*pi*t*100)+0.05*randn(size(t));

tau = 1/400;
y = cos(2*pi*150*(t-tau))+0.05*randn(size(t));
 
% 计算互相关
[r, lags] = xcorr(x, y);
 
% 绘制互相关图
figure;
plot(lags, abs(r));
title('Mutual Correlation');
xlabel('Lags');
ylabel('Mutual Correlation');