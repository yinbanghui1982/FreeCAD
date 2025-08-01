clc
clear

R2=1000e3;
R1=110e3;


Iadj=16e-9;
Vout=0.6*(1+R2/R1)-Iadj*R2

%% Rimax

Rimax=500*0.6/0.4
