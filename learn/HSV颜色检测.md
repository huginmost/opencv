[->cpp](../src/checkColor_HSV.cpp)

Chapter6 颜色检测
`void cv::inRange (InputArray src, InputArray lowerb, InputArray upperb, OutputArray dst)`
检查数组元素是否位于其他两个数组的元素之间。

`void cv::namedWindow (const String &winname, int flags = WINDOW_AUTOSIZE)`
创建一个窗口。函数namedWindow创建一个可用作图像和轨迹栏占位符的窗口。创建的窗口由它们的名称引用。如果同名的窗口已经存在，则该函数不执行任何操作。

`int cv::createTrackbar (const String &trackbarname, const String &winname, int *value, int count, TrackbarCallback onChange = 0, void *userdata = 0)`
创建一个trackbar并将其附加到指定窗口。函数createTrackbar创建一个具有指定名称和范围的trackbar（滑块或范围控件），分配一个变量值作为与trackbar同步的位置，并指定回调函数onChange为 在跟踪栏位置变化时被调用。创建的轨迹栏显示在指定的窗口winname中。


---


代码解析
1. **`Scalar upper(hmax, smax, vmax);`**
- 功能：创建一个表示 HSV 最大范围的 Scalar 对象。
- 详细：
  - hmax、smax、vmax 分别表示：
  - hmax：色调（Hue）的最大值。
  - smax：饱和度（Saturation）的最大值。
  - vmax：亮度（Value）的最大值。
- 结果：upper 表示 HSV 范围的上界，例如 (19, 240, 255)。
2. **`inRange(imgHSV, lower, upper, mask);`**
- 功能：根据定义的 HSV 范围（lower 和 upper），对图像进行二值化处理，将符合范围的像素标记为白色（255），不符合的标记为黑色（0）。
- 参数解析：
  - imgHSV：输入图像，已经转换为 HSV 色彩空间。
  - lower：HSV 范围的下界。
  - upper：HSV 范围的上界。
  - mask：输出的二值掩膜图像，大小和 imgHSV 相同。
结果：
输出的 mask 是一个单通道的二值图像：
像素值为 255 的区域：imgHSV 中符合 lower 和 upper 范围的像素。
像素值为 0 的区域：imgHSV 中不符合范围的像素。
- **HSV 范围的作用**
HSV（Hue-Saturation-Value）是一种更适合描述颜色的色彩空间：

  - **Hue（色调）**：颜色的基本属性，用角度表示，范围 [0, 179]（在 OpenCV 中）。
例如，红色约为 0-10 和 160-179，黄色约为 20-30。
  - **Saturation（饱和度）**：颜色的鲜艳程度，范围 [0, 255]。
低饱和度接近灰色，高饱和度颜色鲜艳。
  - **Value（亮度）**：颜色的明暗程度，范围 [0, 255]。
低亮度接近黑色，高亮度接近白色。
通过调整 lower 和 upper 的范围，可以提取特定颜色区域。例如，代码中：

**`hmin = 0, hmax = 19`：提取接近红色的色调范围。**
**`smin = 110, smax = 240`：限制颜色的饱和度，去除灰色。**
**`vmin = 153, vmax = 255`：限制颜色的亮度，排除过暗的区域。**


工作流程总结
- 输入图像 imgHSV 是一个已经转换为 HSV 色彩空间的图像。
- 定义颜色范围：
  - 下界 lower(hmin, smin, vmin)
  - 上界 upper(hmax, smax, vmax)
使用 inRange 将图像中符合颜色范围的像素标记为白色（255），其他像素标记为黑色（0）。
输出的 mask 是一个二值图像，可用于进一步处理（例如颜色提取、形状检测等）。
示例可视化
假设输入图像是以下颜色区域：

像素区域	HSV 值	是否在范围内
红色	(5, 200, 200)	是
黄色	(25, 200, 200)	否
深灰色	(0, 50, 100)	否
浅红色	(10, 120, 160)	是
输出的 mask 图像将仅包含符合范围的红色区域。

