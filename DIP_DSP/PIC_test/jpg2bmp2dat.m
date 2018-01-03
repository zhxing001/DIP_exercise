clear
clc
I=imread('img.bmp');
I=imresize(I,[100,100]);
[s1,s2]=size(I);
Num=s1*s2/4;
fid=fopen('img.dat','w');
fprintf(fid,'1651 1 80000000 0 %X\n',s1*s2/4);
for i=1:4:(s1*s2-3)
    fprintf(fid,'0X% 02X% 02X% 02X% 02X\n',double(I(i+3:-1:i)));
end
fclose(fid);