function [psdestx,Fxx] =psd_analysis(noise,N,Fs)

[psdestx,Fxx] = periodogram(noise,rectwin(length(noise)),N,Fs);
psdestx=pow2db(psdestx);