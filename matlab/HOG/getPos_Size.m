function [pos,target_size]=getPos_Size(Image)
imshow(Image);
h=imrect;
pos_infor=getPosition(h);   %获得的是左上角的坐标以及宽和高
pos=floor([pos_infor(2)+pos_infor(4)/2,pos_infor(1)+pos_infor(3)/2]);      %得到中心位置，这里转换成行列
target_size=[pos_infor(1,4),pos_infor(1,3)];     %得到target_size，这里也是行列
end