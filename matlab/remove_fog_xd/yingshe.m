function image_=yingshe(image)
cha=max(image(:))-min(image(:));
image=image/cha*255;
image_=(image-min(image(:)));
end