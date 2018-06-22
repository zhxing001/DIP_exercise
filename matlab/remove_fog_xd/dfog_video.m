clc,close all;

video=VideoReader('C:\Users\zhxing\Desktop\’≈–«\’≈–«\»•ŒÌ\5_low.avi');
video_nums=video.NumberOfFrames;
for frame=1:video_nums
    img=read(video,frame);
    img_dfog=remove_fog_xd(img);
    imshow([img,uint8(img_dfog)]);
end
close all;