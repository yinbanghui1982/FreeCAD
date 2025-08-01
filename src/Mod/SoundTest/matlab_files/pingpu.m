function [f,Y,fs]=pingpu(time,data,w)

if w==1 % 汉宁窗
    window = hann(length(data)); % 汉宁窗
    window=window';
    data = data .* window;
end

fs=1/(time(2)-time(1));
N=length(time); %样点个数
df=fs/(N-1);%分辨率
f=(0:N-1)*df;%其中每点的频率，第一个点对应的频率为0
Y = fft(data(1:N))/(N/2);%真实的幅值

Y=20*log10(abs(Y)/2e-5);

f=f(1:N/2);
Y=Y(1:N/2);


