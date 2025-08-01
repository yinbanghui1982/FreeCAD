clc 
clear
close all
 
%% 高斯白噪声信号
fs = 1000;                  % 采样频率
Ns = 128;                   % 数据点数
t = 0:1/fs:1/fs*(Ns-1);     % 时间向量
N = length(t);              % 设置噪声序列的长度
num=200;                     % 平均次数

for i=1:num
    x(i,:)= randn(N, 1);    % 生成高斯白噪声序列
end


%% 带通滤波器
fc_low = 60;    % 低截止频率
fc_high = 150;  % 高截止频率 
N = 11;         % 滤波器阶数 
% [b, a] = butter(N, fc_low/(fs/2), 'low'); % 计算低通滤波器系数
[b, a] = butter(N, [fc_low/(fs/2), fc_high/(fs/2)], 'bandpass'); % 计算中通滤波器系数
% [b, a] = butter(N, fc_high/(fs/2), 'high'); % 计算中高通滤波器系数
 
 
%% 使用带通通滤波器对信号进行滤波
for i=1:num
    y(i,:) = filter(b, a, x(i,:));
end
 

% 傅里叶变换，画频谱图
delta_f = fs/Ns;            % 频率分辨率
x_f = (0:Ns-1)*delta_f;     % 频域信号横轴
for i=1:num
    S_f(i,:) = abs(fft(x(i,1:Ns)));
end

S_f_av=mean(S_f);

figure(1)
subplot(2,1,1)
stem(x_f(1:Ns/2), S_f_av(1:Ns/2), 'filled');
title('原信号频谱')
xlabel('f/Hz')
ylabel('幅值')
 
y_f = (0:Ns-1)*delta_f; % 频域信号横轴
for i=1:num
    Y_f(i,:)  = abs(fft(y(i,1:Ns)));
end
Y_f_av=mean(Y_f);

subplot(2,1,2)
stem(y_f(1:Ns/2), Y_f_av(1:Ns/2), 'filled');
title('滤波信号频谱')
xlabel('f/Hz')
ylabel('幅值')


%% 存入wav文件
% y=y';
% fname = 'band_noise.wav';        % 设定文件名称 注意格式
% audiowrite(fname,y,fs);     % 输出文件




