clc
clear


fs=126e3;
Ts=1/fs;
t=0:Ts:0.01;
f=1000;

vin=0.5e-3*sin(2*pi*f*t);
figure(1);subplot(3,1,1);plot(t,vin);title('vin')

rf=20e3;
rin=4.7e3;

v_shift=0.96;

v_danduan=zeros(1,length(t));
for i=1:length(t)
    v_danduan(i)=(1+rf/rin)*v_shift-rf/rin*vin(i);
    if v_danduan(i)<0
        v_danduan(i)=0;
    end

    if v_danduan(i)>5
        v_danduan(i)=5;
    end    
end
figure(1);subplot(3,1,2);plot(t,v_danduan);title('vdanduan')




vocm=2.57;
rf2=2e3;
rin2=750;

v_chafen=zeros(1,length(t));
for i=1:length(t)
    v_chafen(i)=(v_danduan(i)-vocm)*rf2/rin2;
    if v_chafen(i)<-5
        v_chafen(i)=-5;
    end

    if v_chafen(i)>5
        v_chafen(i)=5;
    end    
end

figure(1);subplot(3,1,3);plot(t,v_chafen);title('vchafen')
