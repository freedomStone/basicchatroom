# 说明
本是一个使用C++创建的简单聊天室程序，具备如下功能：  
- 客户端：
  - 从标准输入终端读入用户数据，并将数据发生到服务器
  - 往标准输出终端打印服务器发生给它的数据
  - 同时支持Linux和Windows
- 服务器端：
  - 接受客户数据，并把客户数据发送给每一个登录到该服务器上的客户端（发送者除外）
