clc
clear

% 设计参数
order = 6; % 滤波器阶数
cutoff_freq = 0.3; % 截止频率（normalized to fs）
fs = 1000; % 采样频率
 
% 设计高通滤波器
[b, a] = butter(order, cutoff_freq, 'high');
 
% 示例：使用设计的滤波器
data = randn(1, 1000); % 示例数据，1x1000的信号
filtered_data = filter(b, a, data); % 应用滤波器
 
% 绘制频率响应
[h, w] = freqz(b, a, 'half', 200); % 200个点
plot(w/max(w), abs(h));
title('高通滤波器频率响应');
xlabel('频率 (rad/sample)');
ylabel('幅度');