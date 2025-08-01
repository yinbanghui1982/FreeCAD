function [freq,fuzhi]=analysis(data)

freq=data(:,1);
fuzhi=20*log10((data(:,2).^2+data(:,3).^2).^.5/2e-5);



