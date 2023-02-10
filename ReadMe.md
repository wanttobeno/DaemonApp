

##### Windows下进程守护工具

1、支持自定义配置

2、支持log

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

RunAppName：这个进程不存在，将重启软件

AppFullPath：需要重启软件的路径

CycleTime：检测间隔




