
%ºìÍâÀ­Éì

function [m_]=lashen(n,max_98,min_02)
 c=max_98-min_02;
 m=double((((n-min_02))/c)*255.0);
 m_=uint8(m);
end