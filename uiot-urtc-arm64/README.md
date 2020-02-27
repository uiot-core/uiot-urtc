# URTC ARM64 SDK DEMO

适用环境：ubuntu 16.04 18.04
编译工具: cmake make gcc g++

URTC 以动态链接库的方式提供SDK，包括头文件和动态链接库文件：
- urtclib/interface/UCloudRtcComDefine.h
- urtclib/interface/UCloudRtcEngine.h
- urtclib/interface/UCloudRtcErrorCode.h
- urtclib/interface/UCloudRtcMediaDevice.h
- urtclib/lib/libliburtcmediaengine.so
- urtclib/lib/liburtcnetengine.so

URTC DEMO为开源，用户可以直接使用到自己的产品中，本demo使用方法, 本demo的YUV源为读取y4m文件，模拟获取yuv视频源：

### DEMO及SDK使用注意事项
- 该SDK-yuv分支的视频源为用户自定义视频源，有YUV和ARGB两种模式
- 推流成功，用户可以处理回调函数`URTCEventHandler.cpp`中的`onLocalPublish`处理，如果`code==0`，则推流成功
- 比特率设置需要小于3000

### 如果在目标机器上编译使用下面的命令
```
# 修改视频源获取接口，修改文件RTCVideoFrameSource.cpp中的
bool VideoFrameSource::doCaptureVideoFrame(tUCloudRtcVideoFrame* videoframe) {}接口
# 进入编译目录
cd build
# 生成Makefile等
cmake ../.
# 编译成功后，在../bin中生成可执行文件
make
# 执行
cd ..
bin/enginedemo rtsp://path/to/rtspstream
```

### 如果使用交叉编译，需要修改CMakeList.txt （交叉编译速度会有所提高）
```
# 打开文件CMakeList.txt中下面的注释
SET(CROSS_COMPILE 1)

IF(CROSS_COMPILE)
SET(TOOLCHAIN_DIR "/path/to/compile-toolchain/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu")
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/aarch64-linux-gnu-g++)
set(CMAKE_C_COMPILER   ${TOOLCHAIN_DIR}/bin/aarch64-linux-gnu-gcc)

SET(CMAKE_FIND_ROOT_PATH  ${TOOLCHAIN_DIR}
 ${TOOLCHAIN_DIR}/include
 ${TOOLCHAIN_DIR}/lib )
ENDIF(CROSS_COMPILE)
```

## 创建URTC应用快速入门
参考：[快速上手](https://docs.ucloud.cn/video/urtc/quick)


## **注意事项**
1. 使用本库需要了解URTC的基本配置参数，包括应用名称，AppID, AppKey, roomid，userid, tokenid, 具体使用方法请参考[URTC文档](https://docs.ucloud.cn/video/urtc)
2. 使用本库需要了解URTC的基本概念，包括进入房间、离开房间、发布视频流、取消发布、订阅视频流、取消订阅，
3. URTC在物联网场景下(参考`main.cpp`,`URTCConfig.cpp`):
   - AppID、AppKey为在UCloud控制台创建应用时系统自动生成;
   - 【重要】AppKey为接入平台认证Key，本demo中直接使用该Key接入，生产环境下务必将AppKey存在服务器端,[使用Token接入](https://docs.ucloud.cn/video/urtc/sdk/token)；
   - 应用名称采用 产品序列号+产品名称，比如：ozuz63kum2i4djb3_巡检无人机；
   - roomid采用设备序列号，比如：afnyhnizq9l4l9ev；
   - userid采用设备序列号+摄像头编号，比如：afnyhnizq9l4l9ev_camera3；
   - tokenid为服务器端生成，测试环境直接使用AppKey测试，生产环境务必参考本项第2条；

4. 生产、测试环境切换：
   - 生产模式使用Tokenid，配置`URTCConfig.cpp`，`mSdkMode = UCLOUD_RTC_SDK_MODE_NORMAL;`, 此时在`main.cpp中获取tokenid;
   - 测试环境可以暂使用（不安全）AppKey，配置`URTCConfig.cpp`，`mSdkMode = UCLOUD_RTC_SDK_MODE_TRIVAL; mSeckey = "xxxxxxxxxxxxxxxxxxxxxx";`
5. 其他请自行熟悉代码；
