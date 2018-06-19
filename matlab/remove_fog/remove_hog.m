
Video=VideoReader('3_low.avi');
num_frame=Video.NumberOfFrames;

for i=1:num_frame
    frame=read(Video,i);
    frame_=dehaze(frame);
    subplot(1,2,1),imshow(frame);
    subplot(1,2,2),imshow(frame_)
    
end
