img=imread('1-noise.bmp');
img_cut=img(:,1:630);
imshow(img_cut);
imwrite(img_cut,'1_noise.bmp');