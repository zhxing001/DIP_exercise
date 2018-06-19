
video=VideoReader('5.mp4');
video_nums=video.NumberOfFrames;

video_write=VideoWriter('5_low');
video_write.open();
for frame=1:video_nums
   img=read(video,frame);
   img_left=img(310:end,:,:);
   writeVideo(video_write,img_left);
   imshow(img_left);
   if(frame==1)
       imwrite(img_left,'img_left.jpg');
   end
   
end
%imwrite(img,'img.jpg');
video_write.close();



