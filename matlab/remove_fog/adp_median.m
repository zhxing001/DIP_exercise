function II=adp_median(I,Smax)
%自适应中值滤波

if (Smax<=1)||(Smax/2==round(Smax/2))||(Smax~=round(Smax))%Smax约束，噪声密度越大，Smax应当设置越高
    error('Smax must be an odd integer >1');
end
%初始化
II=I;
II(:)=0;
alreadyProcessed=false(size(I));
%迭代
for k=3:2:Smax
zmin=ordfilt2(I,1,ones(k,k),'symmetric');
zmax=ordfilt2(I,k*k,ones(k,k),'symmetric');
zmed=medfilt2(I,[k k],'symmetric');
processUsingLevelB=(zmed>zmin)&(zmax>zmed)&(~alreadyProcessed);%需要转到B步骤的像素
zB=(I>zmin)&(zmax>I);
outputZxy=processUsingLevelB&zB;%满足步骤A，B的输出原值 对应的像素位置
outputZmed=processUsingLevelB&~zB;%满足A,不满足B的输出中值 对应的像素位置
II(outputZxy)=I(outputZxy);
II(outputZmed)=zmed(outputZmed);
alreadyProcessed=alreadyProcessed|processUsingLevelB;%处理过的像素
if all(alreadyProcessed(:))
    break;
end
end
II(~alreadyProcessed)=I(~alreadyProcessed);%超过窗口大小没被处理的像素位置 输出原值