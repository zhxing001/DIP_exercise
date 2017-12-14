%一个检测图形黄色矩形框的脚本，用的最简单的通道减法加投影

img=imread('1.jpg');
%三个通道
img_red=double(img(:,:,1));
img_yel=double(img(:,:,2));
img_blu=double(img(:,:,3));

%可视化一下计算过程
img_r_y=img_red-img_yel;
figure(1),imshow(img_r_y,[]),title('red-yel');
sum_col=sum(img_r_y);
figure(2),subplot(2,1,1),plot(sum_col,'o');
sum_row=sum((img_r_y)');
subplot(2,1,2),plot(sum_row,'+');

%排序取差最大的两个，就是要求的两个点
[x,row_sort]=sort(sum_col);
row_s=min(row_sort(end),row_sort(end-1));
row_l=max(row_sort(end),row_sort(end-1));

[y,col_sort]=sort(sum_row);
col_s=min(col_sort(end),col_sort(end-1));
col_l=max(col_sort(end),col_sort(end-1));


%在原图上可视化
figure(3),imshow(img),title('原图');
hold on;
rectangle('position',[row_s,col_s,row_l-row_s,col_l-col_s,],'edgecolor','g','linewidth',2);

