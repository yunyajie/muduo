#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"
/*读取用户名，然后断开连接。如果读到一行以\r\n结尾的消
息，就断开连接。注意这段代码有安全问题，如果恶意客户端不断发送
数据而不换行，会撑爆服务端的内存。另外，Buffer::findCRLF()是线性
查找，如果客户端每次发一个字节，服务端的时间复杂度为O(N^2)，会
消耗CPU资源。*/

using namespace muduo;
using namespace muduo::net;

void onMessage(const TcpConnectionPtr& conn,
               Buffer* buf,
               Timestamp receiveTime)
{
  if (buf->findCRLF())
  {
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
