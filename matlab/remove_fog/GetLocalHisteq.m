function g = GetLocalHisteq(I)  
x=mat2gray(I);  
f=im2double(x);  
w=4;  
k=0.06;  
M=mean2(f);  
z=colfilt(f,[w w],'sliding',@std);  
m=colfilt(f,[w w],'sliding',@mean);  
A=k*M./z;  
g=A.*(f-m)+m;
g=im2uint8(mat2gray(g));  
end  