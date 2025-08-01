clc
clear
close all
%% 实验
xn(:,1) = 1:2^15;
fs = 32000;      % 采样频率
ts = 1/fs;     % 取样时间
L = size(xn,1);     % 总取样次数
t = (0:L-1) * ts;
xn(:,2) = sin(2*pi*1000*t) + sin(2*pi*5000*t);
 
%% 正文
% xn = xlsread('模拟数据.csv');
 
% 第一列为采样时刻，第二列为采样数值
 
%%%%%%%%%%%%%%%%%% 快速傅里叶变换 %%%%%%%%%%%%%%%%%%%%%
 
fs = 32000;      % 采样频率
ts = 1/fs;     % 取样时间
L = size(xn,1);     % 总取样次数
t = (0:L-1) * ts;
x = xn(:,2);
x = detrend(x,0);

 
%% 分析
[Ya_1,Ya_2,f,fc,nfft,nc]=onethird(t,x);
 
 
%% 画图
a(1) = figure(1);
set(gca,'FontSize',10);
plot(0:length(t)-1,x);
title('原始信号');
xlabel('采样序号/采样频率为32000Hz');
ylabel('x');
set(gcf,'position',[100,100, 700, 400]); %设定figure的位置和大小 get current figure
set(gcf,'color','white'); %设定figure的背景颜色
 
a(2) = figure(2);
plot(f,Ya_1); 
set(gca,'FontSize',10);
title('频谱');
xlabel('频率/Hz');
ylabel('声压级/Db');
set(gcf,'position',[100,100, 700, 400]); %设定figure的位置和大小 get current figure
set(gcf,'color','white'); %设定figure的背景颜色
 
a(3) = figure(3);
set(gcf,'color','white'); %设定figure的背景颜色
set(gca,'FontSize',10);
plot(fc,Ya_2); 
title('1/3倍频程');
xlabel('中心频率/Hz');
ylabel('声压级/Db');
set(gcf,'position',[100,100, 700, 400]); %设定figure的位置和大小 get current figure
 
 
 
%% 导出数据
write_all = zeros(L,6);
write_all(:,1:2) = xn;
write_all(1:nfft/2,3) = f;
write_all(1:nfft/2,4) = Ya_1;
write_all(1:nc,5) = fc;
write_all(1:nc,6) = Ya_2;
 
% xlswrite('matlab实验结果.xlsx',write_all);
 
% saveas(a(1),'原始信号.bmp');
% saveas(a(2),'频谱.bmp');
% saveas(a(3),'三分之一倍频程.bmp');clc
% clear
% close all
