function [ConvertedData,ConvertVer,ChanNames,Ts,data1,data2,data3,data4,N,time]=analysis4(filename)
[ConvertedData,ConvertVer,ChanNames]=convertTDMS(false,filename);
Ts=ConvertedData.Data.MeasuredData(4).Property(18).Value;
data1=ConvertedData.Data.MeasuredData(4).Data;
data2=ConvertedData.Data.MeasuredData(5).Data;
data3=ConvertedData.Data.MeasuredData(6).Data;
data4=ConvertedData.Data.MeasuredData(7).Data;
N=length(data1);
time=(0:N-1)*Ts;
time=time';