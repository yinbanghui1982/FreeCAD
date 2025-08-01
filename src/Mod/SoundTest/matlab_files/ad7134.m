clc
clear

mclk=24e6;
odr=4e3;

x=mclk/odr

y=fi(x,0,56,32);
hex(y)
