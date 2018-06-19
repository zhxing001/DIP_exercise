%% 图像的分段线性变换  
% 作者：杨宇东  
% 日期：2014.09.23  
% 参数：待均衡化的图片的文件名  
% 输出：均衡化处理之后的图片数组  
%%  
function f = PiecewiseLinearTransform(imgFile)  
img = imread(imgFile);  
imshow(img);  
height = size(img, 1);  
width = size(img, 2);  
% 所给函数图像中的分界点  
c = 32;  
a = 64;  
d = 128;  
b = 128;  
mf = 256;  
mg = 256;  
% 初始化数组  
f = uint8(zeros(height, width));  
% 根据函数做出变换，这里的判断写得有待优化  
for i = 1:height  
    for j = 1:width  
        if (img(i, j) > 0) && (img(i, j) < a)  
            f(i, j) = round((c / a) * img(i, j));  
        elseif (img(i, j) >= a) && (img(i, j) <= b)  
            f(i, j) = round((d / b) * (img(i, j)));  
        elseif (img(i, j) > b)  
            f(i, j) = round((mg / mf) * img(i, j));  
        end  
    end  
end  
figure, imshow(f);  