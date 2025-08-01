clc
clear


time=0.001:0.001:1;
f=2;
sig=sin(2*pi*f*time);
plot(time,sig)

[rms2,mean2,max_abs,mean_abs,rms_abs,var2,std2,spl,ppv]=time_anslysis(sig)