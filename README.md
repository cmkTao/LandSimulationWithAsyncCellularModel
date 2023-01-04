# QT 版本的ANN-CA土地模拟

## 开发环境

| 软件    | 版本  |
| ------- | ----- |
| Windows | 10    |
| GDAL    | 3.0.0 |
| jsoncpp | 0.5.0 |
| QT      | 14    |

## 主要功能

* tif文件的浏览

* ANN计算（此部分采用python开发）

* CA模拟（此部分采用C++开发)

  改版本将调用dll改为直接在qt中运行CA模拟

  并增加了ACA异步元细胞自动机

## 文件详细

### entity

存储相关的实体类

### thirdParty

存储第三方库

### utils

工具

### alglib

主要是相关的算法

## 待解决的问题

### 内存溢出

每一次运行模拟后，内存没有释放

解决：检测所有使用new的地方，然后手动释放delete

### ca模拟过程QGraphicView显示占用内存大（？）

目前未找到解决办法，先暂时关闭显示，通过文件：utils/mutils.h 中的`const bool showCASimulationProcessImages = false;`来控制。

### 和原版FLUS软件差异问题

经过排查为ca.cpp -> tryToAllocate() 函数最后两句，如果注释掉，则结果基本和原版一直，反之不一样

## 新增功能

* 自动加载配置
* 批量运行

