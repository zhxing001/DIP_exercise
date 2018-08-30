function img_f=FFT(img)
f=fft2(img);
f=fftshift(f);
img_f=log(1+abs(f));
end