clc
clear

s_11 = 0.61*exp(j*165/180*pi);
s_21 = 3.72*exp(j*59/180*pi);
s_12 = 0.05*exp(j*42/180*pi);
s_22 = 0.45*exp(j*(-48/180)*pi);
s_params = [s_11 s_12; s_21 s_22];
z0 = [50 50];
z_params = s2z(s_params,z0)