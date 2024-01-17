#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"
//读取用户名、输出错误信息，然后断开连接。 如果读到一行以\r\n结尾的消息，就发送一条出错信息，然后断开连接。
using namespace muduo;
using namespace muduo::net;

void onMessage(const TcpConnectionPtr& conn,
               Buffer* buf,
               Timestamp receiveTime)
{
  if (buf->findCRLF())
  {
    conn->send("No such user\r\n");
    conn->shutdown();
  }
}

int main()
{
  EventLoop loop;
  TcpServer server(&loop, InetAddress(1079), "Finger");
  server.setMessageCallback(onMessage);
  server.start();
  loop.loop();
}
