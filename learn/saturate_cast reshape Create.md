#### 1.2.1 saturate_cast()
在 opencv中，saturate_cast的作用是防止数据溢出，作出保护。原理可理解为如下代码功能：

> if(data < 0)
>      data = 0;
> else if(data > 255)
>  data = 255;

#### 1.2.2 reshape()
`C++: Mat Mat::reshape(int cn, int rows=0) const`

> cn: 表示通道数(channels), 如果设为0，则表示保持通道数不变，否则则变为设置的通道数。
> rows: 表示矩阵行数。 如果设为0，则表示保持原有的行数不变，否则则变为设置的行数。

#### 1.2.3 Create()
函数原型:
> inline void Mat::create(int _rows, int _cols, int _type)
> inline void Mat::create(Size _sz, int _type)
> void Mat::create(int ndims, const int* sizes, int type)
函数功能:
1)如果需要，分配新的数组数据
2)创建一个图像矩阵的矩阵体