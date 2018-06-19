function [ImgS]=dehaze(Img) 
g1=GetLocalHisteq(Img(:,:,1));  
g2=GetLocalHisteq(Img(:,:,2));  
g3=GetLocalHisteq(Img(:,:,3));  
g3;
ImgS=cat(3,g1,g2,g3);  
