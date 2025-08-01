function [f,Y,fs]=pingpu2(time,data)

fs=1/(time(2)-time(1));
N=length(time); %样点个数
df=fs/(N-1);%分辨率
f=(0:N-1)*df;%其中每点的频率，第一个点对应的频率为0
Y = fft(data(1:N))/(N/2);%真实的幅值

Y=abs(Y);

f=f(1:N/2);
Y=Y(1:N/2);