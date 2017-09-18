%FOI(frames of interest)提取程序，基于直方图相似度匹配
%FOI提取是安防将空领域一个很有用的问题

clear all;
thresh=0.4;          %判断是否为关键帧的阈值，这个根据不同的视频场景要有微调
path='C:\Users\zhxing\Desktop\cv_tracking\附件3-检测前景视频\curtain\Curtain.avi';
video = VideoReader(path);                  %读取视频
frame_n=video.NumberOfFrames;               %视频帧数
video_bg=[];                 %建立一个图像用来存储背景
s=[];                        %取中值用来存数


%%%%%%%%%%用这个可以求像素点的中值。
for i=1:frame_n/10            %取全部序列的1/10的帧用来建模背景
                             
    video_frame=read(video,i);
    video_frame=rgb2gray(video_frame);      %灰度图。

    video_frame_g=medfilt2(video_frame);    %中值滤波，滤掉高频
    
    s=[s,double(video_frame_g(:))];        %把每个值存在一个矩阵的列里。最后生成一个  （640*480）*帧数  大小的矩阵
    i                                 %显示进度
end

s=s';                               %要转置，因为median函数球的是行的中值
siz=size(video_frame_g);             %大小
video_bg=median(s);                  % 求幅图像的中间值
video_bg=reshape(video_bg,siz);       %重构图像
video_bg=uint8(video_bg);             %转化成8阶灰度
subplot(2,2,1);
imshow(video_bg);                    %显示中值图像，也就是建模得到的背景
title('背景');
hist_bg=imhist(video_bg,8);         %这里取的是八段直方图，步长为32
subplot(2,2,2);
bar(hist_bg);
title('背景直方图');

hist_cha=zeros(1,frame_n);      %来存直方图的差值.每一帧都存下来

for i=1:frame_n                              %直接用每一帧和背景做差。
    current=read(video,i);                 
    current=rgb2gray(current);
    hist_bg_frame=imhist(current,8);
    hist_cha(i)=sum(abs(hist_bg_frame-hist_bg));       %求直方图差距，这里用的最简单的对应bin的差的绝对值之和
    subplot(2,2,3);
    imshow(current);
    title('当前视频');
    subplot(2,2,4);
    plot(hist_cha);
    title('当前帧与背景直方图差距');             %这里是绝对值。不是相对值
end

hist_cha=hist_cha/max(hist_cha);      %归一化，可以简化阈值选择
plot(hist_cha);                       %归一化以后的直方图之差
index=find(hist_cha>thresh);          %找到符合阈值条件的帧的标号

index_size=size(index);               %FOI的帧数

object1=VideoWriter('Curtain_FIO.avi');    %所转换成的视频名称
open(object1);
%显示提取出来的帧，并保存成avi视频，可以看出还是有些误差，不过已经很有效了
for i=1:1:index_size(2)
    frame_index=read(video,index(i));
    writeVideo(object1, frame_index);
    imshow(frame_index); 
end
close(object1);
