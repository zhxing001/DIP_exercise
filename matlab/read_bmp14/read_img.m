
%% 读入二进制bmp图像然后，14位格式，高位在后，拉伸并存储


img_path='C:\Users\zhxing\Desktop\';       
write_path='C:\Users\zhxing\Desktop\img\'
img_dir=dir([img_path,'*.bmp']);   
num_img=length(img_dir);

video=VideoWriter('baji');
video.open();


%% 读取----------------------------
for j=1:num_img


f=fopen([img_path img_dir(j).name],'r'); 
f_2=fread(f);              %二进制读入数据
fclose(f);

img16=f_2(1143:end);       %头文件去掉
sz=size(img16);

img_8=zeros(sz(1)/2,1);            %开辟存储空间存储处理后的数据
 k=1;
for i=1:2:sz(1)-1
    high=uint16(img16(i+1));       %高8位
    low=uint16(img16(i));          %低8位
    h_l=bitshift(high,8)+low;      %移位相加
    img_8(k)=h_l;                  %存储
    k=k+1;
end

[,sort_img]=sort(img_8);                    %排序
index_min=floor(double(sz(1)/2)*0.002);     %去掉最暗的千分之二
index_max=floor(double(sz(1)/2)*0.998);     %去掉最亮的千分之二（实际上这里面是乱码,去掉之后好做拉伸）
max_98=sort_img(index_max);                 %最亮的千分之二的最小值
min_02=sort_img(index_min);                 %最暗的千分之二中的最大值

img_shape=reshape(img_8,[320,256]);         %重构图像
img_shape=img_shape';                       %reshape默认是按列存储的，所以转置一下
img_l=lashen(img_shape,max_98,min_02);      %拉伸

imshow(img_l);
imwrite(img_l,[write_path,num2str(j),'.bmp']);
writeVideo(video,img_l);              %写入视频
j                                     %进度
end 
video.close();