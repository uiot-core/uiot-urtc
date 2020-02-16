# URTC ARM64 SDK DEMO

适用环境：ubuntu 16.04 18.04
编译工具: cmake make gcc g++

URTC 以动态链接库的方式提供SDK，包括两个文件：
- urtclib/libliburtcmediaengine.so
- urtclib/liburtcnetengine.so

URTC DEMO为开源，用户可以直接使用到自己的产品中，本demo使用方法：

```
cd build
# 生成Makefile等
cmake ../.
# 编译成功后，在../bin中生成可执行文件
make
# 执行
cd ..
bin/enginedemo rtsp://path/to/rtspstream
```

**注意事项**
1. 使用本库需要了解URTC的基本概念，包括应用名称，AppID, AppKey, roomid，userid, tokenid, 具体使用方法请参考[URTC文档](https://docs.ucloud.cn/video/urtc)
2. URTC在物联网场景下(参考`main.cpp`,`URTCConfig.cpp`):
   - AppID为系统自动生成;
   - 【重要】AppKey为接入平台认证Key，本demo中直接使用该Key接入，生产环境下务必将AppKey存在服务器端,[使用Token接入](https://docs.ucloud.cn/video/urtc/sdk/token)；
   - 应用名称采用 产品序列号+产品名称，比如：ozuz63kum2i4djb3_巡检无人机；
   - roomid采用设备序列号，比如：afnyhnizq9l4l9ev；
   - userid采用设备序列号+摄像头编号，比如：afnyhnizq9l4l9ev_camera3；
   - tokenid为服务器端生成，测试环境直接使用AppKey测试，生产环境务必参考本项第2条；

3. 生产、测试环境切换：
   - 生产模式使用Tokenid，配置`URTCConfig.cpp`，`mSdkMode = UCLOUD_RTC_SDK_MODE_NORMAL;`, 此时在`main.cpp	中获取tokenid;
   - 测试环境可以暂使用（不安全）AppKey，配置`URTCConfig.cpp`，`mSdkMode = UCLOUD_RTC_SDK_MODE_TRIVAL; mSeckey = "xxxxxxxxxxxxxxxxxxxxxx";`
4. 其他请自行熟悉代码；
