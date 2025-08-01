clc
clear

hckt = circuit('new_circuit1');
R=500;
hC1= add(hckt,[1 2],resistor(R));
% setterminals (hckt,[1 2]);
setports(hckt,[1 0],[2,0])
disp(hckt)

freq = 2e6:1e5:10e6;
S2 = sparameters(hckt,freq,50);

figure(1)
rfplot(S2,1,2)

figure(2)
rfplot(S2,1,1)

z0=50;
z=R;
s12=20*log10(abs((2*z0)/(2*z0+z)))
s11=20*log10(abs((z)/(2*z0+z)))


