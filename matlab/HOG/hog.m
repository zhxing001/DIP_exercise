clear all;
clc;

img=imread('1.jpg');
figure
imshow(img),title('原图');
figure
img=rgb2gray(img);
imshow(img),title('灰度图')
[m, n]=size(img);
img=sqrt(double(img));      %伽马校正
figure
imshow(uint8(img)),title('gamma矫正之后')

%下面是求边缘
fy=[-1 0 1];        %定义竖直模板
fx=fy';             %定义水平模板
Iy=imfilter(img,fy,'replicate');    %竖直边缘
figure,imshow(Iy),title('竖直边缘,梯度');
Ix=imfilter(img,fx,'replicate');    %水平边缘
figure,imshow(Ix),title('水平边缘,梯度');
Ied=sqrt(Ix.^2+Iy.^2);              %边缘强度
Iphase=Iy./Ix;              %边缘斜率，有些为inf,-inf,nan，其中nan需要再处理一下，这里是正切值


%下面是求cell
step=16;                %step*step个像素作为一个单元 16*16=256个点
orient=9;               %方向直方图的方向个数  9个方向。40度分辨率
jiao=360/orient;        %每个方向包含的角度数
Cell=cell(1,1);              %所有的角度直方图,cell是可以动态增加的，所以先设了一个
ii=1;                      
jj=1;
for i=1:step:m-step   %行分块           %如果处理的m/step不是整数，最好是i=1:step分块处理，这样得话肯定是有边界效应的，管不着了
    ii=1;
    for j=1:step:n-step      %列分块，注释同上
        tmpx=Ix(i:i+step-1,j:j+step-1);      %块的所有x梯度
        tmped=Ied(i:i+step-1,j:j+step-1);     %强度
        tmped=tmped/sum(sum(tmped));        %局部边缘强度归一化,左右值加起来归一化
        tmpphase=Iphase(i:i+step-1,j:j+step-1);   %相位，正切值
        Hist=zeros(1,orient);               %当前step*step像素块统计角度直方图,就是cell，存到cell里
        for p=1:step      %把每个的角度算出来
            for q=1:step
                if isnan(tmpphase(p,q))==1  %0/0会得到nan，如果像素是nan，重设为0
                    tmpphase(p,q)=0;
                end
                ang=atan(tmpphase(p,q));    %atan求的是[-90 90]度之间
                ang=mod(ang*180/pi,360);    %全部变正，-90变270 ，这里是个取余操作
                if tmpx(p,q)<0              %根据x方向确定真正的角度，所以上面拿来x方向的相位主要是用来确定真正的角度的
                    if ang<90               %如果是第一象限
                        ang=ang+180;        %移到第三象限
                    end
                    if ang>270              %如果是第四象限
                        ang=ang-180;        %移到第二象限
                    end
                end        
                ang=ang+0.0000001;          %防止ang为0，嗯，全部化为非零的角度。
                Hist(ceil(ang/jiao))=Hist(ceil(ang/jiao))+tmped(p,q)*1;   
                %ceil向上取整，使用边缘强度加权，如果加权的话应该就是1，这里是加权过的，也就是说，强度越大，在直方图中的贡献就越大
            end
        end
        Hist=Hist/sum(Hist);    %方向直方图归一化
        Cell{ii,jj}=Hist;       %放入Cell中
        ii=ii+1;                %针对Cell的y坐标循环变量
    end
    jj=jj+1;                    %针对Cell的x坐标循环变量
end

%下面是求feature,2*2个cell合成一个block,没有显式的求block
[m ,n]=size(Cell);
feature=cell(1,(m-1)*(n-1));
for i=1:m-1
   for j=1:n-1           
        f=[];
        f=[f Cell{i,j}(:)' Cell{i,j+1}(:)' Cell{i+1,j}(:)' Cell{i+1,j+1}(:)'];  %四个单元合成一个
        %这样做的话是有很多重叠的。
        feature{(i-1)*(n-1)+j}=f;         %这里也可以用其他的变量来计数。反正是连续的
   end
end

%到此结束，feature即为所求
%下面是为了显示而写的
l=length(feature);
f=[];
for i=1:l
    f=[f;feature{i}(:)'];  
end 
figure
mesh(f)