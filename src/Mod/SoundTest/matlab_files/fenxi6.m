clc
clear
% 声管测试
%% 0
% [ConvertedData,ConvertVer,ChanNames,Ts,data1,data2,data3,data4,N,time]= ... 
%     analysis4("10/Test 1_Result_IMPT.tdms");
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

%%
% [ConvertedData,ConvertVer,ChanNames,Ts,data1,data2,data3,data4,N,time]= ... 
%     analysis4("10/Test 1_test-50Hzline-T60_230829150645_GM.tdms");


%%
[ConvertedData,ConvertVer,ChanNames,Ts,data1,data2,data3,data4,N,time]= ... 
    analysis4("10/Test 1_bianjieceng_10_230830151900_GM.tdms");