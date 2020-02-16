# URTC WEB SDK DEMO

适用浏览器： [https://docs.ucloud.cn/video/urtc/sdk/VideoStart](https://docs.ucloud.cn/video/urtc/sdk/VideoStart)

本demo开源，支持angular、react、vue框架或者纯JS，可以直接运行，用户可以根据自身需求裁剪使用。

本demo界面参考：
![demo界面](image/uiot-urtc-web.png)

## uiot-urtc-web和uiot-urtc-web-advance 的区别

- uiot-urtc-web 提供URTC基本功能的实现，包括加入房间、发布本地视频流、取消发布、订阅、取消订阅、离开房间；
- uiot-urtc-web-advance 是一个基于直播教学的demo，除了支持上述功能外，还支持录制功能；
- 了解基本功能，两者均可；


## 使用方法

1. 获取web-demo
```
git clone https://github.com/ucloud/urtc-sdk-web.git
```

2. 修改AppID, AppKey, roomid，userid等
```
// 本例以纯js为例讲解，文件为：urtc-sdk-web/examples/pureJS/js/index.js
vim urtc-sdk-web/examples/pureJS/js/index.js

// 修改 RoomId、UserId
  // 此处使用固定的房间号的随机的用户ID，请自行替换
  const RoomId = "afnyhnizq9l4l9ev";
  const UserId = "afnyhnizq9l4l9ev_appuser"+Math.floor(Math.random() * 1000000).toString();

vim urtc-sdk-web/examples/pureJS/js/config.js
// 修改AppId、AppKey, 文件为：urtc-sdk-web/examples/pureJS/js/config.js
window.config = {
  AppId: 'urtc-4mb0tuor',
  AppKey: '05c8e4b931439ed161c71c8f80eba1a2'
}
``` 

3. 配置web服务器，比如nginx
```
server {
  #listen 80 default;
  listen 443 ssl http2;
  ssl_certificate /path/to/myserver.pem;
  ssl_certificate_key /path/to/myserver.key;
  ssl_protocols TLSv1 TLSv1.1 TLSv1.2;
  ssl_ciphers EECDH+CHACHA20:EECDH+AES128:RSA+AES128:EECDH+AES256:RSA+AES256:EECDH+3DES:RSA+3DES:!MD5;
  ssl_prefer_server_ciphers on;
  ssl_session_timeout 10m;
  ssl_session_cache builtin:1000 shared:SSL:10m;
  ssl_buffer_size 1400;
  add_header Strict-Transport-Security max-age=15768000;
  ssl_stapling on;
  ssl_stapling_verify on;

  server_name _;

  access_log /data/wwwlogs/access_nginx.log combined;
  root /path/to/urtc-sdk-web/examples/pureJS;
  index index.html index.htm index.php;
}

```

4. 通过上述支持的浏览器访问web


## 注意事项

1. WEB DEMO仅支持https，所以服务端需要配置TLS，使用授信证书或自签名证书；
2. 使用本库需要了解URTC的基本配置参数，包括应用名称，AppID, AppKey, roomid，userid, tokenid, 具体使用方法请参考[URTC文档](https://docs.ucloud.cn/video/urtc)
3. 使用本库需要了解URTC的基本概念，包括进入房间、离开房间、发布视频流、取消发布、订阅视频流、取消订阅，
4. URTC在物联网场景下(参考`urtc-sdk-web/examples/pureJS/js/index.js`,`urtc-sdk-web/examples/pureJS/js/config.js`):
   - AppID、AppKey为在UCloud控制台创建应用时系统自动生成;
   - 【重要】AppKey为接入平台认证Key，本demo中直接使用该Key接入，生产环境下务必将AppKey存在服务器端,[使用Token接入](https://docs.ucloud.cn/video/urtc/sdk/token)；
   - 应用名称采用 产品序列号+产品名称，比如：ozuz63kum2i4djb3_巡检无人机；
   - roomid采用设备序列号，比如：afnyhnizq9l4l9ev；
   - userid,由于web端主要以观看为主，所以可以根据业务确定用户体系；
   - tokenid为服务器端生成，测试环境直接使用AppKey测试，生产环境务必参考本项第2条；

5. 生产、测试环境切换：
   - 生产模式使用token，修改：
   ```
   // 该demo本地生成，此处修改为server端获取
   const token = UCloudRTC.generateToken(AppId, AppKey, RoomId, UserId);
   this.client = new UCloudRTC.Client(AppId, token);
   ```
   - 测试环境可以暂使用（不安全）AppKey`;
6. 其他请自行熟悉代码；

