img_path='C:\Users\zhxing\Desktop\X光\X光2\img\';
Dir=dir([img_path,'\*.bmp']);

Dir_sz=size(Dir);
for i=1:Dir_sz(1)

img=imread([img_path,Dir(i).name]);
subplot(Dir_sz(1)/4,2,2*(i-1)+1),imshow(img),title('原图');
img=double(img);    %转换成double之后方便处理

img_f=FFT(img);
subplot(Dir_sz(1)/4,2,2*(i-1)+2),imshow(uint8(img_f),[]),title('频谱');         %从频谱来看其高频都不是特别干净。

%%  去噪算法  ①普通中值   ②自适应中值  

%% 一. 3*3的中值滤波可以去除大部分的椒盐噪声
img_midFilter=medfilt2(img,[3,3]);
img_midFilter=medfilt2(img_midFilter,[3,3]);
%figure;
%subplot(3,1,1),imshow(uint8(img)),title('原图');
%subplot(3,1,2),imshow(uint8(img_midFilter)),title('中值滤波');

% dest=multiScaleSharpen(img_midFilter,5);
% subplot(3,1,3),imshow(uint8(dest)),title('多尺度对比度增强');


%% 自适应中值滤波的效果应该也是不错的。
img_adptmidian=adpmedian(img,3);
%subplot(3,1,3),imshow(uint8(img_adptmidian)),title('自适应中值滤波');

end


%% 试着用直方图均衡化增强对比度,但是这种增强实际上是不可取的，因为图片中有大量的背景，这样反而会造成图片严重失真
% img_histeq=histeq(uint8(img_midFilter));
% figure,imshow(uint8(img_histeq)),title('hist_eq');


%% 拉普拉斯增强效果非常一般。
% L_8=[1,1,1;1,-8,1;1,1,1];        %拉普拉斯算子，用来增强图像
% img_laplace=imfilter(img,L_8);
% img_lap=img+(-1)*img_laplace;
% figure
% subplot(2,1,1),imshow(uint8(img_laplace)),title('拉普拉斯算子滤波图像');
% subplot(2,1,2),imshow(uint8(img_lap)),title('拉普拉斯算子增强');

