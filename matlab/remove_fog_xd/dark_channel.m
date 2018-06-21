function dc=dark_channel(img,kernelsz)
sz=size(img);
dc=zeros(sz(1),sz(2));
for i=1:sz(1)
    for j=1:sz(2)
        min(img(i,j,:));
        dc(i,j)=min(img(i,j,:));   
    end
end
se = strel('rectangle',[kernelsz,kernelsz]);
dc = imerode(dc,se);
end