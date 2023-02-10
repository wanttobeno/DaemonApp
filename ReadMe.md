

##### Windows下进程守护工具

1、支持自定义配置

2、软件强制关闭，重启

3、支持log

##### 配置文件Setting.ini

```
[AppSetting]
CheckAppName=osk.exe
RunAppName=notepad.exe
AppFullPath="C:\Windows\System32\notepad.exe"
CycleTime=5000
```

##### 配置文件说明

CheckAppName:出现这个进程，将重启软件

RunAppName：这个进程不存在，说明软件未开启，将重启软件

AppFullPath：守护的软件全路径，执行软件重启需要的参数

CycleTime：检测间隔


##### 使用说明

配置Setting.ini，启动本程序。

