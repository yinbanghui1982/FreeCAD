function [Ya_1,Ya_2,f,fc,nfft,nc]=onethird(t,x)
%% 傅里叶变换
nfft = length(t);
fs=1/(t(2)-t(1));
 
Y1 = fft(x,nfft);     % 傅里叶变换
 
f1 = (0:nfft-1)/(nfft-1)*fs;      % 频率向量
 
f = f1(1:nfft/2);       % 根据对称性取半
 
Y = Y1(1:nfft/2)*2/nfft;   % 根据对称性取半
 
YE = abs(Y); % 频域中的能量
 
ji_Ya = 2*10^(-5);  % 声压级基底
 
%% 计算频谱声压级
Ya_1 = 20 * log10(YE/ji_Ya);  % 计算频谱声压级
    
%% 计算总声压级
% 找出10-8k
YE_z = YE(find(f>=10&f<8000));
Z_Ya = 20 * log10(sqrt(sum(YE_z.^2))/ji_Ya)-3
 
%% 三分之一倍频程
% 定义三分之一倍频程的中心频率fc
fc = [20 25 31.5 40 50 63 80 100 125 160 200 ...
    250 315 400 500 630 800 1000 1250 1600 2000 ...
    2500 3150 4000 5000 6300 8000 10000 12500 16000];
% 下限频率
fl = round(fc/(2^(1/6)));
% 上限频率
fu = round(fc*(2^(1/6)));
 
fu(end) = f(end);   % 修复fu，末尾变为16000
 
%% 
% 频率向量f中有L/2个数据，对应的频率是(0：L/2-1)/(L/2-1)*fs/2;
nl = round(fl*2/fs*(nfft/2-1) + 1); % 下限频率对应的频率向量的序号
nu = round(fu*2/fs*(nfft/2-1) + 1); % 上限频率对应的频率向量的序号
nc = length(fc); % 中心频率的长度

YE_C=zeros(1,nc);
for i = 1:nc
    nn = zeros(1,nfft)+1i*zeros(1,nfft);
    nn(nl(i):nu(i)) = Y1(nl(i):nu(i));
    nn(end-nu(i)+1:end-nl(i)+1) = Y1(end-nu(i)+1:end-nl(i)+1);
    cc = ifft(nn);
    YE_C(i) = sqrt(var(real(cc(1:nfft))));     % 求取1/3倍频程
%     YE_C(i) = sqrt(sum(YE(nl(i):nu(i)).^2)/2);    % 求取第i个中心频率的能量：频带的平均能量；
end
 
Ya_2 = 20 * log10(YE_C/ji_Ya); % 计算中心频率的声压级