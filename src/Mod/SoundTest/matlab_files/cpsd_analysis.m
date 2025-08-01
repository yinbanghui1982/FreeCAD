function [Pxy2,arg2,f]=cpsd_analysis(x,y,Fs)

[Pxy, f] = cpsd(x,y,[],[],[],Fs);
Pxy2=pow2db(abs(Pxy));
arg2=angle(Pxy);