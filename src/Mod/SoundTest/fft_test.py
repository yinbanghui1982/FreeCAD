from scipy import fft
import numpy as np
import matplotlib
print(matplotlib.get_backend())
matplotlib.use('QtAgg')

import matplotlib.pyplot as plt

def fft_test2():
    ## sample frequence
    Fs=800
    Ts=1/Fs #sample interval
    N=800 #FFT sample point
    L=1000*Ts # signal length
    t=np.arange(0,L,Ts)
    #generate signal
    y=1*np.sin(2*np.pi*50*t)+0.6*np.cos(2*np.pi*80*t)+np.random.normal(0,1,len(t));
    plt.subplot(2,1,1)
    plt.plot(t,y)
    plt.xlabel('Time')
    plt.ylabel('Amplitude')
    #generate two sided spectrum
    yf=fft.fft(y,N)
    P1=abs(yf/N)
    #generate one sided spectrum
    P2=P1[0:int(N//2)]
    P2[1:int(N//2)]=2*P1[1:int(N//2)]
    xk=np.arange(0,Fs/2,Fs/N)
    plt.subplot(2,1,2)
    plt.plot(xk,P2)
    plt.xlabel('Frequency')
    plt.ylabel('Amplitude')
    plt.grid()
    plt.show()