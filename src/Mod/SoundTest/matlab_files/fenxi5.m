clc
clear
% 张紧力分析
%% 0
[ConvertedData,ConvertVer,ChanNames,Ts,data1,data2,data3,data4,N,time]= ... 
    analysis4("10/Test 1_jiazhi_1_230830104014_GM.tdms");
% plot(time,data1)

[f,Y,fs]=pingpu(time(1:1024),data1(1:1024));
figure(2);semilogx(f,Y,'DisplayName','通道1');hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data2(1:1024));
% figure(2);semilogx(f,Y,'DisplayName','通道2');hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data3(1:1024));
% figure(2);semilogx(f,Y,'DisplayName','通道3');hold on

[f,Y,fs]=pingpu(time(1:1024),data4(1:1024));
figure(2);semilogx(f,Y,'DisplayName','通道2');hold on

xlabel("频率/Hz")
ylabel("声压级/dB")
legend

%% 0
% [ConvertedData,ConvertVer,ChanNames,Ts,data1,data2,data3,data4,N,time]= ...
%     analysis4("10/Test 1_jiazhi_song_230830104946_GM.tdms");
% % plot(time,data1)
% 
% [f,Y,fs]=pingpu(time(1:1024),data1(1:1024));
% figure(2);semilogx(f,Y,'DisplayName','通道1');hold on % %
% % [f,Y,fs]=pingpu(time(1:1024),data2(1:1024)); %
% % figure(2);semilogx(f,Y,'DisplayName','通道2');hold on % %
% % [f,Y,fs]=pingpu(time(1:1024),data3(1:1024)); %
% % figure(2);semilogx(f,Y,'DisplayName','通道3');hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data4(1:1024));
% figure(2);semilogx(f,Y,'DisplayName','通道2');hold on
% 
% xlabel("频率/Hz") 
% ylabel("声压级/dB") 
% legend