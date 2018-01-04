%得到汉明窗和高斯窗的c代码，不能直接写入h文件，就先写入txt再复制过去了，主要是要中间的逗号。
fid=fopen('cos.txt','wt');
fid_g=fopen('gaus.txt','wt');

cos_window = hann(64) * hann(64)';
cos_window=cos_window(:);
fprintf(fid,'float cos_window_64_64[4096]={');
fprintf(fid_g,'float gaus_window_64_64[4096]={');

%下面这段是高斯输出，这是期望的输出，
target_sz=[32,32];
sz=[64,64];
output_sigma_factor=1/16;
output_sigma = sqrt(prod(target_sz)) * output_sigma_factor;    %这里是论文里面的那个aqrt（mn）/16.
[rs, cs] = ndgrid((1:sz(1)) - floor(sz(1)/2), (1:sz(2)) - floor(sz(2)/2));
%这里实际上是去产生坐标，x和y方向，mesh一下rs和cs就懂了
y = exp(-0.5 / output_sigma^2 * (rs.^2 + cs.^2));  %高斯函数，期望的输出，
y=y(:);

for i=1:size(cos_window)
    fprintf(fid,'%f,',cos_window(i));
    fprintf(fid_g,'%f,',y(i));
end
fclose(fid);
fclose(fid_g);

