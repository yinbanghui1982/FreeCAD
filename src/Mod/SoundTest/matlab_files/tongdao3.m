clc
clear

Rf1=20e3;
Rin1=4.7e3;
Vin=12;

Vshift=Vin*Rf1/Rin1/(1+Rf1/Rin1)