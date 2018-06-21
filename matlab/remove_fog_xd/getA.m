%% 获取大气光值，根据四叉树迭代法来求。
% 首先把所述原始图像I划分成四个矩形区域，然后为每个子区域进行评分，
% 这个评分的计算方法是“用区域内像素的平均值减去这些像素的标准差”，
% 选择得分最高的区域，并将其继续划分为更小的四个子矩形，重复这个过程
% 直到被选中的区域小于某个提前指定的阈值。图6中的红色方框部分就是最终
% 被选定的区域。在这被选定的区域里，选择使得距离 
% ||(Ir(p),Ig(p),Ib(p))-(255,255,255)|| 最小化的颜色（包含 r,g,b 三个分量）
% 来作为大气光的参考值。


%% 输入为三通道彩色图像 uint8格式
function A=getA(img)
   img=double(img);             %转换为double
   SZ=size(img);
   row=floor(SZ(1)/2);
   col=floor(SZ(2)/2);
   while(row*col>25)
       %%  图像分块
        up_left=img(1:row,1:col,:);                             %左上
        up_right=img(1:row,col:end,:);                          %右上
        down_left=img(row:end,1:col,:);                         %左下
        down_right=img(row:end,col:end,:);                      %右下
        cost1=mean(up_left(:))-sqrt(std(up_left(:)));
        cost2=mean(up_right(:))-sqrt(std(up_right(:)));
        cost3=mean(down_left(:))-sqrt(std(down_left(:)));
        cost4=mean(down_right(:))-sqrt(std(down_right(:)));
        [ ~,index]=max([cost1,cost2,cost3,cost4]);
        switch index
            case 1
                img=up_left;
            case 2
                img=up_right;
            case 3
                img=down_left;
            case 4
                img=down_right;
        end
        SZ=size(img);
        row=floor(SZ(1)/2);
        col=floor(SZ(2)/2);
   end
   A_1=img(:,:,1)-255;
   A_2=img(:,:,2)-255;
   A_3=img(:,:,3)-255;
   A_=A_1.*A_1+A_2.*A_2+A_3.*A_3;
   [x,y]=find(A_==min(A_(:)));
   A=(img(x(1),y(1),:));
end