# intersect_test_module
---
- Template Version: 0.0.1
- Tag: **[耦合版本模块]**

---

>>>>>>> master



# 求交自由曲线和自由曲线求交脚手架说明

## 0.源码编译

编译工具：CMAKE

流程

| 步骤                                                   | 示意图                                                       |
| ------------------------------------------------------ | ------------------------------------------------------------ |
| 1、打开CMAKE，设置源码文件夹和用于编译项目的项目文件夹 | ![image-20250109171527033](C:\Users\11295\AppData\Roaming\Typora\typora-user-images\image-20250109171527033.png) |
| 2.cmake配置项目                                        | ![image-20250109171603788](C:\Users\11295\AppData\Roaming\Typora\typora-user-images\image-20250109171603788.png) |
| 3.单击后效果图                                         | ![image-20250109171653486](C:\Users\11295\AppData\Roaming\Typora\typora-user-images\image-20250109171653486.png) |
| 4.生成项目                                             | ![image-20250109171721468](C:\Users\11295\AppData\Roaming\Typora\typora-user-images\image-20250109171721468.png) |
| 5.项目生成效果图                                       | ![image-20250109171754288](C:\Users\11295\AppData\Roaming\Typora\typora-user-images\image-20250109171754288.png) |
| 6.打开项目开始编程                                     | ![image-20250109171831369](C:\Users\11295\AppData\Roaming\Typora\typora-user-images\image-20250109171831369.png) |
| 7.线面示意图                                           | ![image-20250109172027228](C:\Users\11295\AppData\Roaming\Typora\typora-user-images\image-20250109172027228.png) |



## 1.功能代码撰写

代码撰写位置如下所示：

![image-20250109171255225](C:\Users\11295\AppData\Roaming\Typora\typora-user-images\image-20250109171255225.png)

当前接口为空实现可以基于算法设计思路实现具体功能代码块和辅助函数

## 2.预置辅助函数

预置各类辅助函数133个，代码行数6672，位置如下所示：

![image-20250109171113359](C:\Users\11295\AppData\Roaming\Typora\typora-user-images\image-20250109171113359.png)

预置辅助函数左右：

1. 可以方便学习辅助接口实现
2. 减少代码开发量
3. 初步了解各类函数和类的使用



## 3.测试

测试提供67个测例，后续可以自行添加

![image-20250109170436948](C:\Users\11295\AppData\Roaming\Typora\typora-user-images\image-20250109170436948.png)



测试使用方式：

| 步骤           | 示意图                                                       |
| -------------- | ------------------------------------------------------------ |
| 1.1设置启动项  | ![image-20250109170549863](C:\Users\11295\AppData\Roaming\Typora\typora-user-images\image-20250109170549863.png) |
| 1.2设置启动项  | ![image-20250109170650917](C:\Users\11295\AppData\Roaming\Typora\typora-user-images\image-20250109170650917.png) |
| 2执行测试      | ![image-20250109170711013](C:\Users\11295\AppData\Roaming\Typora\typora-user-images\image-20250109170711013.png) |
| 3.查看测试结果 | ![image-20250109170741653](C:\Users\11295\AppData\Roaming\Typora\typora-user-images\image-20250109170741653.png) |

