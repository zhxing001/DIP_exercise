# -*- coding: utf-8 -*-
"""
Created on Sat Jun  9 11:28:14 2018

@author: zhxing
"""

import cv2  
import numpy as np


p=1.3
img=cv2.imread('test.jpg')
#cv2.imshow('cource_img',img)

Min_img=np.min(img,2)      # 暗通道
#cv2.imshow('dark_channel',Min_img)


M_mfilter=cv2.blur(Min_img,(7,7))   #暗通道进行均值滤波，这个半径
cv2.imshow('blur',M_mfilter)

M_av=np.mean(Min_img)       # 暗通道取均值



cv2.waitKey(1000)



'''

def zmMinFilterGray(src, r=7):  
   
    return cv2.erode(src,np.ones((2*r-1,2*r-1)))
# =============================================================================
#     if r <= 0:  
#         return src  
#     h, w = src.shape[:2]  
#     I = src  
#     res = np.minimum(I  , I[[0]+range(h-1)  , :])  
#     res = np.minimum(res, I[range(1,h)+[h-1], :])  
#     I = res  
#     res = np.minimum(I  , I[:, [0]+range(w-1)])  
#     res = np.minimum(res, I[:, range(1,w)+[w-1]])  
# =============================================================================
 #   return zmMinFilterGray(res, r-1)  
   
def guidedfilter(I, p, r, eps):  
    
    height, width = I.shape  
    m_I = cv2.boxFilter(I, -1, (r,r))  
    m_p = cv2.boxFilter(p, -1, (r,r))  
    m_Ip = cv2.boxFilter(I*p, -1, (r,r))  
    cov_Ip = m_Ip-m_I*m_p  
   
    m_II = cv2.boxFilter(I*I, -1, (r,r))  
    var_I = m_II-m_I*m_I  
   
    a = cov_Ip/(var_I+eps)  
    b = m_p-a*m_I  
   
    m_a = cv2.boxFilter(a, -1, (r,r))  
    m_b = cv2.boxFilter(b, -1, (r,r))  
    return m_a*I+m_b  
   
def getV1(m, r, eps, w, maxV1):  #输入rgb图像，值范围[0,1]  
    

'''