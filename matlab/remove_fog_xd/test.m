img=imread('1.jpg');
sz=size(img);

kernelsz=(floor(max([sz(1)*0.01,sz(2)*0.01,3])));

A=getA(img);                   %获取大气光值
for i=1:3
    if(A(1)>240) 
        A(1)=240;  
    end
    if(A(2)>240) 
        A(2)=240;  
    end 
    if(A(3)>240) 
        A(3)=240;  
    end
end

T=getT(img,kernelsz,A,0.0001);
figure,imshow(T),title('t');

r = kernelsz*4;
eps = 10^-6;
t_d=guidedfilter(double(rgb2gray(img))/255,T,r,eps);        %引导滤波获得透射率图
figure,imshow(tx,[]),title('透射率图')

%figure,imshow(img,[]),title('img');

h=sz(1);
w=sz(2);
J = zeros(h,w,3);

img_d = double(img);

J(:,:,1) = (img_d(:,:,1) - (1-t_d)*A(1))./t_d;

J(:,:,2) = (img_d(:,:,2) - (1-t_d)*A(2))./t_d;

J(:,:,3) = (img_d(:,:,3) - (1-t_d)*A(3))./t_d;

