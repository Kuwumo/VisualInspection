# VisualInspection

# 视觉检测系统

## 编写目的
闲来无事，准备写一个视觉检测系统，用于学习C++和QT 

## 编写环境
操作系统：windows11
语言：C++\QT


## C++ 项目构建

依赖 CMake 3.20 或更高版本，以及支持 C++17 的编译器。

在本目录执行以下命令，构建项目并运行测试。

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

第三方依赖放在 `deps/`，依赖查找配置放在 `cmake/`，构建中间文件位于 `build/`。

公开接口放在 `include/inspection/`，核心实现放在 `src/`。示例程序 `src/main.cpp` 使用 spdlog 记录三个样本的检测结果。控制台显示 info 和 warn 消息，当前工作目录的 `logs/inspection.log` 还记录 trace 和 debug 细节，单个文件达到约 4 KiB 后轮转，最多保留三份备份。每个样本的审计记录异步追加到 `logs/audit.log`。测试位于 `tests/`，涵盖低于、等于和高于阈值的情况。

Release 可执行文件生成在 `dist/release/`，Debug 可执行文件生成在 `dist/debug/`。将上述命令中的 `Release` 换成 `Debug` 即可构建并测试调试版。要运行发布版示例，Windows 下执行 `.\dist\release\inspection_demo.exe`，Linux 和 macOS 下执行 `./dist/release/inspection_demo`。

本项目采用 MIT 许可证，全文见 LICENSE。
