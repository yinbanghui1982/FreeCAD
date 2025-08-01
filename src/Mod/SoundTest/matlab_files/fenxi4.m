clc
clear
%% 0
[ConvertedData,ConvertVer,ChanNames,Ts,data1,data2,data3,data4,N,time]= ... 
    analysis4("10/Test 1_0_230829150824_GM.tdms");
% plot(time,data1)

[f,Y,fs]=pingpu(time(1:1024),data1(1:1024));
figure(2);semilogx(f,Y);hold on

[f,Y,fs]=pingpu(time(1:1024),data2(1:1024));
figure(2);semilogx(f,Y);hold on

[f,Y,fs]=pingpu(time(1:1024),data3(1:1024));
figure(2);semilogx(f,Y);hold on

[f,Y,fs]=pingpu(time(1:1024),data4(1:1024));
figure(2);semilogx(f,Y);hold on

%% 10
[ConvertedData,ConvertVer,ChanNames,Ts,data1,data2,data3,data4,N,time]= ... 
    analysis4("10/Test 1_10_230829151151_GM.tdms");
% plot(time,data1)

[f,Y,fs]=pingpu(time(1:1024),data1(1:1024));
figure(2);semilogx(f,Y);hold on

[f,Y,fs]=pingpu(time(1:1024),data2(1:1024));
figure(2);semilogx(f,Y);hold on

[f,Y,fs]=pingpu(time(1:1024),data3(1:1024));
figure(2);semilogx(f,Y);hold on

[f,Y,fs]=pingpu(time(1:1024),data4(1:1024));
figure(2);semilogx(f,Y);hold on

%% 20
% [ConvertedData,ConvertVer,ChanNames,Ts,data1,data2,data3,data4,N,time]= ... 
%     analysis4("10/Test 1_20_230829151327_GM.tdms");
% % plot(time,data1)
% 
% [f,Y,fs]=pingpu(time(1:1024),data1(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data2(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data3(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data4(1:1024));
% figure(2);semilogx(f,Y);hold on

%% 30
% [ConvertedData,ConvertVer,ChanNames,Ts,data1,data2,data3,data4,N,time]= ... 
%     analysis4("10/Test 1_30_230829155105_GM.tdms");
% % plot(time,data1)
% 
% [f,Y,fs]=pingpu(time(1:1024),data1(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data2(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data3(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data4(1:1024));
% figure(2);semilogx(f,Y);hold on

%% 30
% [ConvertedData,ConvertVer,ChanNames,Ts,data1,data2,data3,data4,N,time]= ... 
%     analysis4("10/Test 1_30_230829160146_GM.tdms");
% % plot(time,data1)
% 
% [f,Y,fs]=pingpu(time(1:1024),data1(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data2(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data3(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data4(1:1024));
% figure(2);semilogx(f,Y);hold on

%% 40
% [ConvertedData,ConvertVer,ChanNames,Ts,data1,data2,data3,data4,N,time]= ... 
%     analysis4("10/Test 1_40_230829160347_GM.tdms");
% % plot(time,data1)
% 
% [f,Y,fs]=pingpu(time(1:1024),data1(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data2(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data3(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data4(1:1024));
% figure(2);semilogx(f,Y);hold on

%% 60
% [ConvertedData,ConvertVer,ChanNames,Ts,data1,data2,data3,data4,N,time]= ... 
%     analysis4("10/Test 1_60_230829160644_GM.tdms");
% % plot(time,data1)
% 
% [f,Y,fs]=pingpu(time(1:1024),data1(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data2(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data3(1:1024));
% figure(2);semilogx(f,Y);hold on
% 
% [f,Y,fs]=pingpu(time(1:1024),data4(1:1024));
% figure(2);semilogx(f,Y);hold on