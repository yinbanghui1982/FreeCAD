function [c,lags2]=auto_corr_analysis(x,dt)
[c,lags]=xcorr(x,'unbiased');
lags2=lags*dt;