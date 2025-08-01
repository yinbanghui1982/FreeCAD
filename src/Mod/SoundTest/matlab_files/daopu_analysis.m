function z=daopu_analysis(y)


% nn=1:nfft/2; 
% ff=(nn-1)*fs/nfft;               % 计算频率刻度

Y=log(abs(fft(y)));                           % 按式(3-1-8)取实数部分
% subplot 211; plot(ff,Y(nn),'k'); hold on;     % 画出信号的频谱图
z=ifft(Y);                                    % 按式(3-1-8)求取倒谱