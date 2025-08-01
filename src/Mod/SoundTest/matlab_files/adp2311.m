clc
clear

%% PFI
vcc_5v_2=5;
R1=499e3;
R2=200e3;
pfi=vcc_5v_2/(R1+R2)*R2

%% vm2

R3=499e3;
R4=200e3;
vm2=vcc_5v_2/(R3+R4)*R4

%% 通道1
rt1=22;
rb1=3;
v1=0.6*(1+rt1/rb1)

v1*0.965



