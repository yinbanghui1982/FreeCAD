clc
clear

%% 分析
data_hou_0_ch1
 [time,shengya,fs,N,f,Y]=analysis2(Data_hou_0_ch1)
figure(1);plot(f(1:N/2),abs(Y(1:N/2)));hold on

data_hou_0_ch2
 [time,shengya,fs,N,f,Y]=analysis2(Data_hou_0_ch2)
figure(1);plot(f(1:N/2),abs(Y(1:N/2)));hold on

data_hou_10_ch1
 [time,shengya,fs,N,f,Y]=analysis2(Data_hou_10_ch1)
figure(1);plot(f(1:N/2),abs(Y(1:N/2)));hold on

