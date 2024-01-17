#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"
//主动断开连接。接受连接之后主动断开。
using namespace muduo;
using namespace muduo::net;

void onConnection(const TcpConnectionPtr& conn)
{
  if (conn->connected())
  {//已连接则断开
    conn->shutdown();
  }
}

int main()
{
  EventLoop loop;
  TcpServer server(&loop, InetAddress(1079), "Finger");
  server.setConnectionCallback(onConnection);
  server.start();
  loop.loop();
}
