function [rms2,mean2,max_abs,mean_abs,rms_abs,var2,std2,spl,ppv]=time_anslysis(sig)

%有效值
rms2=rms(sig);

%平均值
mean2=mean(sig);

%最大幅值
max_abs=max(abs(sig));

%平均幅值
mean_abs=mean(abs(sig));

%方根幅值
rms_abs=(mean(abs(sig))).^.5;

%方差
var2=var(sig);

%均方差
std2=std(sig);

%计算有效声压
% 根据定义计算有效声压，pa = sqrt((x(1)^2+x(2)^2+...+x(M)^2)/M)
% 单位为Pa
pp = 0;
M=length(sig);
for i = 1:M
   pp = pp + sig(i)^2;%下面公式2-5
end
pa = sqrt(pp/M);

%%计算声压级
% 声压级值spl=20*log10(pa/p0),单位为dB
% 基准声压p0，单位为Pa
p0 = 2*10^-5;
spl = 20*log10(pa/p0);%下面公式2-6

ppv=max(sig)-min(sig);


