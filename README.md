# SC-GC
Spatial Crowdsourcing using Garbled Circuits and Homomorphic Encryption

此程序需要安装openssl, GMP的依赖包

目录说明：
SCPro/LOG文件夹里面记录的是运行时间
SCPro/DATA文件夹里面的xy_LA是测试数据
SCPro的main.cpp中可以设置TOTAL来设置测试的数据大小，设置task_x, task_y来设置任务坐标。

使用说明：
使用cmake编译,运行命令cmake .
然后再运行 make
最后生成可执行文件SCPro
