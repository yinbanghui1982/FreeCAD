clc
clear

%% 分析
tl_160
[freq,tl]=analysis3(Tl_160);
figure(1);plot(freq,tl,'DisplayName','160g/m^2');hold on

tl_240
[freq,tl]=analysis3(Tl_240);
figure(1);plot(freq,tl,'DisplayName','240g/m^2');hold on

xlabel("频率/Hz")
ylabel("声插入损失/dB")
legend