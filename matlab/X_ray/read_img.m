
img_path='C:\Users\zhxing\Desktop\X光\X光3\';
write_path='C:\Users\zhxing\Desktop\X光\X光3\img\';
img_dir=dir([img_path,'*.out']);   
num_img=length(img_dir);


%% 读取----------------------------
for j=1:num_img


f=fopen([img_path img_dir(j).name],'r'); 
f_2=fread(f);              %二进制读入数据
sz=size(f_2)
fclose(f);
if(sz(1)==207360)
    img_8=f_2(1:end);
end
% if j==1
%     
% elseif j==6
%     img_8=f_2(1:end);
% else
% img_8=f_2(1:end);         %头文件去掉  
% end


% [,sort_img]=sort(img_8);                    %排序
% index_min=floor(double(sz(1)/2)*0.002);     %去掉最暗的千分之二
% index_max=floor(double(sz(1)/2)*0.998);     %去掉最亮的千分之二（实际上这里面是乱码,去掉之后好做拉伸）
% max_98=sort_img(index_max);                 %最亮的千分之二的最小值
% min_02=sort_img(index_min);                 %最暗的千分之二中的最大值

img_shape=reshape(img_8,[720,288]);         %重构图像
img_shape=img_shape';                       %reshape默认是按列存储的，所以转置一下
img=img_shape;
imshow(img,[]);
img=uint8(img);
imwrite(img,[write_path,img_dir(j).name(1:end-4),'.bmp']);

           %写入视频
j                                     %进度
end 
