%FOI(frames of interest)提取程序，基于前景面积阈值化之后得到序列提取
%2017/9/18

clear all;
thresh=0.1;          %判断是否为关键帧的阈值，这个根据不同的视频场景要有微调
path0='Escalator.avi';
path1='Escalator_fore.avi';
video0 = VideoReader(path0);  
video1 = VideoReader(path1);                  %读取视频
frame_n=video1.NumberOfFrames;               %视频帧数

Area=zeros(1,frame_n);      %来存直方图的差值.每一帧都存下来

for i=1:frame_n                          %遍历视频
    current=read(video1,i);               %读取帧    
    subplot(2,1,1);
    imshow(current);
    title('前景');
    current_gray=rgb2gray(current);
    current_bw=logical(current_gray);      %二值化,因为本来获得的前景就是阈值化之后的，这里就不用im2bw了，直接逻辑化就可。
   
    Area_LTY=regionprops(current_bw,'Area');   %获得所有连通域的面积属性
    LTY_num=size(Area_LTY);                         %连通域个数
    
    if(isempty(Area_LTY))            %如果不存在连通域就直接跳出当前帧的循环
        continue;
    end
    for j=1:LTY_num
    Area(i)=Area(i)+ Area_LTY(j).Area;              %如果存在就把所有面积加起来
    end
    subplot(2,1,2);
    plot(Area)
    title('面积'); 
end


Area=Area/max(Area);      %归一化，可以简化阈值选择
plot(Area);                       %归一化以后的直方图之差
index=find(Area>thresh);          %找到符合阈值条件的帧的标号

index_size=size(index);               %FOI的帧数

object1=VideoWriter('Escalator_FIO_area.avi');    %所转换成的视频名称
open(object1);
%显示提取出来的帧，并保存成avi视频，可以看出还是有些误差，不过已经很有效了
for i=1:1:index_size(2)
    frame_index=read(video0,index(i));
    writeVideo(object1, frame_index);
    imshow(frame_index); 
end
close(object1);
