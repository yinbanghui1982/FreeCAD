clc
clear

%% data0
data0
[freq,fuzhi]=analysis(data_0);
figure(1);semilogx(freq,fuzhi);hold on

data10
[freq,fuzhi]=analysis(data_10);
figure(1);semilogx(freq,fuzhi)

data20
[freq,fuzhi]=analysis(data_20);
figure(1);semilogx(freq,fuzhi)

data60
[freq,fuzhi]=analysis(data_60);
figure(1);semilogx(freq,fuzhi)