clear

clc

close all

kenlRatio = .01;
minAtomsLight = 240;
% image_name =  'test images\21.bmp';
image_name =  'test.jpg';
img=imread(image_name);
figure,imshow(uint8(img)), title('src');

%% 获取最小通道
sz=size(img);
w=sz(2);
h=sz(1);
dc = zeros(h,w);
for y=1:h
    for x=1:w
        dc(y,x) = min(img(y,x,:));
    end

end
figure,imshow(uint8(dc)), title('Min(R,G,B)');

%% 最小值滤波（可用腐蚀来代替）
krnlsz = floor(max([3, w*kenlRatio, h*kenlRatio]));
se = strel('rectangle',[krnlsz,krnlsz]);
dc2 = imerode(dc,se);
%dc2(h,w)=0;
figure,imshow(uint8(dc2)), title('After filter ');


%% 
t = 255 - dc2;
figure,imshow(uint8(t)),title('t');

t_d=double(t)/255;

sum(sum(t_d))/(h*w)

A = min([minAtomsLight, max(max(dc2))])


J = zeros(h,w,3);

img_d = double(img);

J(:,:,1) = (img_d(:,:,1) - (1-t_d)*A)./t_d;

J(:,:,2) = (img_d(:,:,2) - (1-t_d)*A)./t_d;

J(:,:,3) = (img_d(:,:,3) - (1-t_d)*A)./t_d;

figure,imshow(uint8(J)), title('J');
% figure,imshow(rgb2gray(uint8(abs(J-img_d)))), title('J-img_d');
% a = sum(sum(rgb2gray(uint8(abs(J-img_d))))) / (h*w)
% return;
%----------------------------------
r = krnlsz*4
eps = 10^-6;

%filtered = guidedfilter_color(double(img)/255, t_d, r, eps);
filtered = guidedfilter(double(rgb2gray(img))/255, t_d, r, eps);

t_d = filtered;

figure,imshow(t_d,[]),title('filtered t');

J(:,:,1) = (img_d(:,:,1) - (1-t_d)*A)./t_d;

J(:,:,2) = (img_d(:,:,2) - (1-t_d)*A)./t_d;

J(:,:,3) = (img_d(:,:,3) - (1-t_d)*A)./t_d;
% 

img_d(1,3,1)
imwrite(uint8(J),'11.bmp');
figure,imshow(uint8(J)), title('J_guild_filter');

%----------------------------------
%imwrite(uint8(J), ['_', image_name])