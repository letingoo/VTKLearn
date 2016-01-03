# VTKLearn
对VTK(The Visualization Toolkit)的学习

## VTK的编译
可以参考 http://blog.csdn.net/yunhaic/article/details/40653221

## 编译完成之后的配置(VTK6.3 + VS 2013)
使用Visual studio新建工程,进行以下的配置
> 1. 属性》vc目录》库目录，写上lib文件所在目录
> 2. 属性》c++》常规》外部引用目录，协商.h头文件所在目录
> 3. 属性》连接器》输入》附加依赖项，写上需要的.lib文件名
> 4. 若需要用到dll动态链接库，则应该将这些dll加入到window》system文件夹中。


## VTK6.0 还需要进行一下的配置
在cpp文件里添加如下语句:(不使用CMake编译)
`#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)`
