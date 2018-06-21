%% remove fog test code
% zhxing 2018/6/21



%%
img=imread('img_left.jpg');
figure,
imshow(img),title('原图');
sz=size(img);

kernelsz=(floor(max([sz(1)*0.01,sz(2)*0.01,3])));

dc=dark_channel(img,kernelsz);          %获取暗通道图像
A=getA(img);                   %获取大气光值
A=[240,240,240];



r = kernelsz*4;
eps = 10^-6;
tx=guidedfilter(double(rgb2gray(img))/255,double(dc)/255.0,r,eps);        %引导滤波获得透射率图
figure,imshow(tx,[]),title('透射率图')

img=double(img);

Ix1=(img(:,:,1));             %通道分离
Ix2=(img(:,:,2));
Ix3=(img(:,:,3));

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


figure,imshow(uint8(image)),title('defog');


%映射到0-255


 