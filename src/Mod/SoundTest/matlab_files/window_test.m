% 示例：利用加窗方法进行低通滤波
clc
clear

% 生成原始信号
fs = 1000; % 采样率
t = 0:1/fs:1-1/fs; % 时间向量
f1 = 50; % 信号频率
x = sin(2*pi*f1*t);


% 加窗处理
window = hann(length(x)); % 汉宁窗
window=window';
x_windowed = x .* window;

% DFT变换
X = fft(x_windowed);

% 设计低通滤波器
N = length(X);
cutoff_freq = 100; % 截止频率
filter = ones(1, N);
filter(cutoff_freq+1:end-cutoff_freq) = 0;

% 频域滤波
X_filtered = X .* filter;

% 反变换得到时域滤波结果
x_filtered = ifft(X_filtered);

% 绘制结果
figure;
subplot(2, 1, 1);
plot(t, x);
xlabel('时间（秒）');
ylabel('幅值');
title('原始信号');

subplot(2, 1, 2);
plot(t, abs(x_filtered));
xlabel('时间（秒）');
ylabel('幅值');
title('滤波结果');

