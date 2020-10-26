# 适合opencv 初学者的100个问题
### 问题三：大津二值化算法

描述：

​		大津算法，也被称作最大类间方差法，是一种可以自动确定二值化中阈值的算法。在[计算机视觉](https://zh.wikipedia.org/wiki/计算机视觉)和[图像处理](https://zh.wikipedia.org/wiki/图像处理)中，**大津二值化法**用来自动对基于聚类的图像进行[二值化](https://zh.wikipedia.org/wiki/二值化)，[[1\]](https://zh.wikipedia.org/wiki/大津算法#cite_note-Mehmet-1) 或者说，将一个灰度图像退化为二值图像。该算法以大津展之命名

阈值从类内方差和类间方差的比值计算得来：

* 小于阈值t的类记作0，大于阈值t的类记作1
* $w_0$和$w_1$是被阈值t分类的两个类中的像素数占总像素数的比率（满足$w_0$+$w_1$=1）
* ${S_0}^2$，${S_1}^2$是这两个类中像素值的方差；
* $m_0$，$m_1$是这两个类的像素值的平均值；

也就是：

- 类内方差：${S_w}^2=w_0\ {S_0}^2+w_1\  {S_1}^2$
- 类间方差：${S_b}^2 = w_0 \  (M_0 - M_t)^2 + w_1\ (M_1 - M_t)^2 = w_0\  w_1\  (M_0 - M_1) ^2$
- 图像所有像素的方差：${S_t}^2 = {S_w}^2 + {S_b}^2 = \text{常数}$

根据以上的式子，我们用以下的式子计算分离度$X$：
$$
xX = \frac{{S_b}^2}{{S_w}^2} = \frac{{S_b}^2}{{S_t}^2 - {S_b}^2}
$$

也就是说：
$$
\arg\max\limits_{t}\ X=\arg\max\limits_{t}\ {S_b}^2
$$
换言之，如果使${S_b}^2={w_0}\ {w_1}\ (M_0 - M_1)^2$最大，就可以得到最好的二值化阈值$t$。

## 问题五：HSV变换

$\text{HSV}$即使用**色相（Hue）、饱和度（Saturation）、明度（Value）**来表示色彩的一种方式。

* 色相：将颜色使用$0^{\circ}$到$360^{\circ}$表示，就是平常所说的颜色名称，如红色、蓝色。色相与数值按下表对应：

  | 红          | 黄           | 绿            | 青色          | 蓝色          | 品红          | 红            |
  | ----------- | ------------ | ------------- | ------------- | ------------- | ------------- | ------------- |
  | $0^{\circ}$ | $60^{\circ}$ | $120^{\circ}$ | $180^{\circ}$ | $240^{\circ}$ | $300^{\circ}$ | $360^{\circ}$ |

* 饱和度：是指色彩的纯度，饱和度越低则颜色越黯淡（$0\leq S < 1$）；
* 明度：即颜色的明暗程度。数值越高越接近白色，数值越低越接近黑色（$0\leq V < 1$）；

从$\text{RGB}$色彩表示转换到$\text{HSV}$色彩表示通过以下方式计算：

$\text{RGB}$的取值范围为$[0, 1]$，令：
$$
\text{Max}=\max(R,G,B)\\
\text{Min}=\min(R,G,B)
$$
色相：
$$
H=\begin{cases}
0&(\text{if}\ \text{Min}=\text{Max})\\
60\  \frac{G-R}{\text{Max}-\text{Min}}+60&(\text{if}\ \text{Min}=B)\\
60\  \frac{B-G}{\text{Max}-\text{Min}}+180&(\text{if}\ \text{Min}=R)\\
60\  \frac{R-B}{\text{Max}-\text{Min}}+300&(\text{if}\ \text{Min}=G)
\end{cases}
$$
饱和度：
$$
S=\text{Max}-\text{Min}
$$
明度：
$$
V=\text{Max}
$$
从$\text{HSV}$色彩表示转换到$\text{RGB}$色彩表示通过以下方式计算：
$$
C = S\\
H' = \frac{H}{60}\\
X = C\  (1 - |H' \mod 2 - 1|)\\
(R,G,B)=(V-C)\ (1,1,1)+\begin{cases}
(0, 0, 0)&  (\text{if H is undefined})\\
(C, X, 0)&  (\text{if}\quad 0 \leq H' < 1)\\
(X, C, 0)&  (\text{if}\quad 1 \leq H' < 2)\\
(0, C, X)&  (\text{if}\quad 2 \leq H' < 3)\\
(0, X, C)&  (\text{if}\quad 3 \leq H' < 4)\\
(X, 0, C)&  (\text{if}\quad 4 \leq H' < 5)\\
(C, 0, X)&  (\text{if}\quad 5 \leq H' < 6)
\end{cases}
$$
请将色相反转（色相值加$180$），然后再用$\text{RGB}$色彩空间表示图片。

## 问题六：减色处理

RGB的像素值在0~255之间，我们将图像的值由$256^3$压缩至$4^3$,即将RGB的值只取32， 96， 160， 224。这被称作色彩量化。色彩的值按照下面的方式定义：
$$
x\text{val}=\begin{cases}32& (0 \leq \text{var} <  64)\\96& (64\leq \text{var}<128)\\160&(128\leq \text{var}<192)\\224&(192\leq \text{var}<256)\end{cases}
$$

​						

### **问题七：平均池化（均值滤波）**

将图片按照固定大小网格分割，网格内的像素取值网格内所有像素的平均值。我们将这种把图片使用均等大小网格分割，并求网格内代表值的操作称为池化（pooling），池化操作是**卷积神经网络（Convolutional Neural Network）**中重要的图像处理方式，平均实话按照下式定义：
$$
v=\frac{1}{|R|}\  \sum\limits_{i=1}^R\ v_iv=\frac{1}{|R|}\  \sum\limits_{i=1}^R\ v_i
$$


![image-20201018173634197](/Users/william/Library/Application Support/typora-user-images/image-20201018173634197.png)

### **问题八：最大池化（最大值滤波）**

网格内的值不取平均值，而是去网格内的最大值进行池化操作。

![image-20201018173609806](/Users/william/Library/Application Support/typora-user-images/image-20201018173609806.png)

### **问题九：高斯滤波（Gaussian Filter）**

使用高斯滤波器（3 x 3大小，标准差σ=1.3）, 来对图像进行处理。高斯滤波器是一种可以是图像**平滑**的滤波器，用于去除噪声，可用于去除噪声的滤波器还有中值滤波器，平滑滤波器，LoG滤波器。高斯滤波器将中心像素周围的像素按照高斯分布加权平均进行平滑化。这样的（二维）权值通常被称为**卷积核（kernel）**，或者滤波器（filter）。但是，由于图像的长款可能不是滤波器的整数倍，因此我们需要在图像的边缘补0.这种方式称作（Zero Padding）并且权值g（卷积核）要按照下面的高斯分布计算权值：
$$
g(x,y,\sigma)=\frac{1}{2\  \pi\ \sigma^2}\  e^{-\frac{x^2+y^2}{2\  \sigma^2}}
$$
标准差$\sigma=1.3$的8邻域高斯滤波器如下：

（ps:4邻域:一幅图像中，位于坐标（x，y）处的像素p有4个相邻的像素，分别位于其上下左右。8邻域=4邻域+对角邻域。）
$$
K=\frac{1}{16}\  \left[ \begin{matrix}   1 & 2 & 1 \\   2 & 4 & 2 \\   1 & 2 & 1  \end{matrix}  \right]
$$

|
|
|

![image-20201018191627848](/Users/william/Library/Application Support/typora-user-images/image-20201018191627848.png)

### 问题十：中值滤波（Median Filter）

使用中值滤波器（3 * 3 大小）来对图像进行降噪吧！

中值滤波器是一种可以使图像平滑的滤波器，这种滤波器用滤波器范围内（这里是9 x 9）像素点的中值进行滤波，延续采用Zero Padding。

![image-20201018193438151](/Users/william/Library/Application Support/typora-user-images/image-20201018193438151.png)

### 问题十一：均值滤波（Mean Filter）

均值滤波器使用网格像素内的平均值。

![image-20201023220510477](/Users/william/Library/Application Support/typora-user-images/image-20201023220510477.png)

###问题十二：运动模糊：Motion filter

Motion filter取对角线方向的像素平均值，像下式这样定义：
$$
\left[\begin{matrix}\frac{1}{3}&0&0\\0&\frac{1}{3}&0\\0  & 0&  \frac{1}{3}\end{matrix}\right]
$$


![image-20201023230519418](/Users/william/Library/Application Support/typora-user-images/image-20201023230519418.png)				

## 问题十三：MAX-MIN滤波器

min-max滤波器使用网格内像素的最大值和最小值的差值对网格内像素重新赋值。通常用于边缘检测。边缘检测用于检测图像中的线，想这样提取图中信息的操作称为**特征提取**。边缘检测通常在灰度图像中进行。

![image-20201026235657242](/Users/william/Library/Application Support/typora-user-images/image-20201026235657242.png)

## 问题十四：Differential Filter

使用$3\times3$的差分滤波器来进行滤波，差分滤波器对图像亮度急剧变化的边缘有提取效果，可以获得邻接像素的差值。

纵向算子：
$$
K=\left[
\begin{matrix}
0&-1&0\\
0&1&0\\
0&0&0
\end{matrix}
\right]
$$
横向算子：
$$
K=\left[
\begin{matrix}
0&0&0\\
-1&1&0\\
0&0&0
\end{matrix}
\right]
$$
纵向结果：

![image-20201026235821547](/Users/william/Library/Application Support/typora-user-images/image-20201026235821547.png)

横向结果：

![image-20201026235840715](/Users/william/Library/Application Support/typora-user-images/image-20201026235840715.png)

###问题十五：Sobel滤波器

使用$3\times3$的差分滤波器来进行滤波

Sobel滤波器可以提取特定方向（纵向或横向）的边缘，滤波器按下式定义：

纵向算子：
$$
K=\left[
\begin{matrix}
1&2&1\\
0&0&0\\
-1&-2&-1
\end{matrix}
\right]
$$
横向算子：
$$
K=\left[
\begin{matrix}
1&0&-1\\
2&0&-2\\
1&0&-1
\end{matrix}
\right]
$$
纵向结果：

![image-20201027000019471](/Users/william/Library/Application Support/typora-user-images/image-20201027000019471.png)

横向结果：

![image-20201027000045468](/Users/william/Library/Application Support/typora-user-images/image-20201027000045468.png)

