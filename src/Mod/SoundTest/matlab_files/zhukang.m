clc
clear

data=[1	-31.9
3	7.1
5	47.1
7	87.7
10	147.9];


% 假设x和y是你的数据点
x = data(:,2);
y = data(:,1);
 
% 创建一个线性拟合模型
f = fit(x, y, 'poly1'); % 'poly1'表示一次多项式，即直线
 
% 提取直线的斜率和截距
k = f.p1;
b = f.p2;
 
% 可以用以下方式画出数据点和拟合的直线
plot(x, y, 'o', 'MarkerSize', 8);
hold on;
plot(f, 'r-');
xlabel('电流/uA')
ylabel('电压/V')
hold off;