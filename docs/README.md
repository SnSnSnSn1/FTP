基于您提供的文件结构，以下是`README.md`文件的内容，它提供了项目的简要介绍以及如何构建和运行项目的指南：

---

# 简易HTTP服务器项目

## 概述

本项目是一个简易的HTTP服务器，用于处理GET请求并提供静态文件服务。项目包括服务器的初始化、运行、请求处理、URL解析以及内容类型的确定。同时，项目还包含了单元测试来验证功能的正确性。

## 功能

- 创建和配置套接字
- 监听和接受客户端连接
- 解析HTTP请求
- 提供静态文件服务
- 根据文件扩展名确定MIME类型
- 单元测试验证功能正确性

## 构建和运行指南

### 环境要求

- Linux操作系统
- GCC编译器
- Make工具

### 安装依赖

在Ubuntu系统上，可以通过以下命令安装必要的依赖：

```bash
sudo apt-get update
sudo apt-get install libcheck-dev
```

### 构建项目

在`project_root`目录下，运行以下命令来构建项目：

```bash
make
```

这将编译源代码并生成可执行文件`http_server`，存放在`bin`目录下。

### 运行服务器

构建完成后，运行以下命令来启动HTTP服务器：

```bash
./bin/http_server
```

服务器将在默认端口8080上监听。

### 测试

运行单元测试以验证各个模块的功能：

```bash
./tests/test_http_server
./tests/test_url_parser
```

## 文件结构

```
project_root/
|-- bin/                     # 存放编译后的可执行文件
|   |-- http_server
|-- obj/                     # 存放编译过程中的中间文件
|   |-- main.o
|   |-- http_server.o
|   |-- url_parser.o
|-- src/                     # 源代码目录
|   |-- main.c               # 主程序入口
|   |-- http_server.c         # 模块1的实现
|   |-- url_parser.c          # 模块2的实现
|   |-- include/             # 头文件目录
|       |-- http_server.h     # 模块1的头文件
|       |-- url_parser.h     # 模块2的头文件
|-- tests/                   # 单元测试代码目录
|   |-- test_http_server.c    # 模块1的单元测试
|   |-- test_url_parser.c    # 模块2的单元测试
|-- Makefile                 # 构建和测试项目的Makefile
|-- public/                  # 静态文件服务目录
|   |-- index.html
```


## 许可证

本项目采用[MIT许可证](LICENSE)。

---
