clear
clc

%%
fs=16000; nfft=1024;                          % 采样频率和FFT的长度
time=(0:nfft-1)/fs;                           % 时间刻度
y=cos(2*pi*100*time);

% figure(1)
% plot(time,y,'k');     % 画出信号波形
% title('信号波形'); 
% ylabel('幅值'); xlabel(['时间/s' 10 '(a)']); grid;

%%
z=daopu_analysis(y);
figure(2); plot(time,z,'k');     % 画出倒谱图
title('信号倒谱图'); axis([0 time(512) -0.2 0.2]); grid; 
ylabel('幅值'); xlabel(['倒频率/s' 10 '(b)']);

%%
% mcep=29;                                      % 分离声门激励脉冲和声道冲激响应
% zy=z(1:mcep+1);
% zy=[zy' zeros(1,nfft-2*mcep-1) zy(end:-1:2)']; % 构建声道冲激响应的倒谱序列
% ZY=fft(zy);                                   % 计算声道冲激响应的频谱
% figure(2),                                    % 画出声道冲激响应的频谱，用灰线表示
% line(ff,real(ZY(nn)),'color',[.6 .6 .6],'linewidth',3);
% grid; hold off; ylim([-4 5]);
% title('信号频谱（黑线）和声道冲激响频谱（灰线）')
% ylabel('幅值'); xlabel(['频率/Hz' 10 '(a)']); 
% ft=[zeros(1,mcep+1) z(mcep+2:end-mcep)' zeros(1,mcep)]; % 构建声门激励脉冲的倒谱序列
% FT=fft(ft);                                  % 计算声门激励脉冲的频谱
% subplot 212; plot(ff,real(FT(nn)),'k'); grid;% 画出声门激励脉冲的频谱
% title('声门激励脉冲频谱')
% ylabel('幅值'); xlabel(['频率/Hz' 10 '(b)']); 
