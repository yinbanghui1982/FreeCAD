function [time,shengya,fs,N,f,Y]=analysis2(Data_hou_0_ch1)
time=Data_hou_0_ch1(:,1);
shengya=Data_hou_0_ch1(:,2);
fs=1/(time(2)-time(1));
N=length(time); %样点个数
df=fs/(N-1);%分辨率
f=(0:N-1)*df;%其中每点的频率，第一个点对应的频率为0
Y = fft(shengya(1:N))/(N/2);%真实的幅值

Y=20*log10(Y/2e-5);
