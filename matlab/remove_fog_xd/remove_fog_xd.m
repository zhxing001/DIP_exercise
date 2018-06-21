%% remove fog test code
% zhxing 2018/6/21


%%
img=imread('test.jpg');
figure,
imshow(img),title('原图');

dc=dark_channel(img);          %获取暗通道图像
A=getA(img);                   %获取大气光值

tx=imguidedfilter(dc,img,'NeighborhoodSize',[70,70]);        %引导滤波获得透射率图

img=double(img);

Ix1=img(:,:,1);             %通道分离
Ix2=img(:,:,2);
Ix3=img(:,:,3);

Jx1_=Ix1-A(1)+A(1)*tx;
Jx1=Jx1_./tx;
figure,imshow(Jx1,[]),title('JX1');

Jx2_=Ix2-A(2)+A(2)*tx;
Jx2=Jx2_./tx;
figure,imshow(Jx2,[]),title('JX2');

Jx3_=Ix3-A(3)+A(3)*tx;
Jx3=Jx3_./tx;
figure,imshow(Jx3,[]),title('JX3');

image=cat(3,Jx1,Jx2,Jx3);

figure,imshow(uint8(image(:,:,1)));
 