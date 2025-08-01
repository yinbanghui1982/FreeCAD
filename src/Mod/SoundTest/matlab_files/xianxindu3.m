clc
clear
data=[1	1.06335
5	5.34355
10	10.6275
15	16.0068
20	21.2705

];

input=data(:,1);
output=data(:,2);
% plot(input,output)
% xlabel('输入电压峰峰值/mV')
% ylabel('测试信号峰峰值/mV')


% 假设x和y是你的数据点
x = input;
y = output;
 
% 创建一个线性拟合模型
f = fit(x, y, 'poly1'); % 'poly1'表示一次多项式，即直线
 
% 提取直线的斜率和截距
k = f.p1
b = f.p2
 
% 可以用以下方式画出数据点和拟合的直线
plot(x, y, 'o', 'MarkerSize', 8);
hold on;
plot(f, 'r-');
xlabel('输入振动峰峰值/m/s^2')
ylabel('测试信号峰峰值/mV')
hold off;



