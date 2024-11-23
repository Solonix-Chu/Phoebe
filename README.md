直接开放吧，有兴趣的话可以编译玩玩

- 新的 Mooncake 项目框架
- 带 UI、HAL API 绑定的 JS runtime，可用于表盘、或者 app
- 更好用的 Lvgl cpp 绑定，以及过渡动画支持

https://www.bilibili.com/video/BV1qCBBYkEXS

# 桌面端编译

拉取依赖：

```bash
python fetch_repos.py
```

编译：

```bash
mkdir build && cd build
```

```
cmake .. && make
```

运行：

```bash
cd desktop
```

```
./app_desktop_build
```

WASD 键导航