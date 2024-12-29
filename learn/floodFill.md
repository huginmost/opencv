```cpp
int floodFill(
    InputOutputArray image, 
    Point seedPoint, 
    Scalar newVal, 
    Rect* rect = 0, 
    Scalar loDiff = Scalar(), 
    Scalar upDiff = Scalar(), 
    int flags = 4
);
```
实例：
```cpp
floodFill(image, Point(5, 50), Scalar(255), 0, FLOODFILL_FIXED_RANGE);
```

参数解析：
image:

- 输入图像，此处是经过二值化处理的 image。
  - Point(5, 50):

- 从图像坐标 (5, 50) 开始填充。
假设这点在二值化图像中是背景或连通区域的一部分。
  - Scalar(255):

- 使用灰度值 255（白色）进行填充。
  - 0:

- 未使用填充区域的边界矩形。
  - FLOODFILL_FIXED_RANGE:
---
- 指定固定颜色范围模式，填充只考虑种子点与相邻像素的颜色差异，差异由默认值控制。
- **功能效果**
这段代码会从 (5, 50) 开始，查找与该点像素值相近的所有像素，并用灰度值 255 填充这些像素
- **结果**
将目标区域（例如背景区域）变成白色。
只考虑种子点的初始颜色，不会动态更新颜色差异。
---

- **应用场景**
  1.去除小孔或背景区域：
  - 在二值化后，可能存在一些小的背景区域，通过填充可以消除这些区域。
  2. 目标分割：
  - 可以用于快速分割具有一致灰度或颜色的区域。
  3. 后处理操作：
  - 准备更高质量的图像输入，例如消除杂点或小区域。