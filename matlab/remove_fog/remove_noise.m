img=imread('1_noise.bmp');
img=double(img);
img_m=adp_median(img,7);    %中值滤波，去掉椒盐噪声


H=fspecial('gaussian',3);
img_a=imfilter(img_m,H);       %3*3的均值滤波


subplot(2,2,1);
imshow(img,[]);

subplot(2,2,2);
imshow(img_m,[]);

subplot(2,2,3);
imshow(img_a,[]);

subplot(2,2,4);
