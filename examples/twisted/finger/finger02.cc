#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"
//接受新连接。在 1079 端口侦听新连接，接受连接后什么都不做，程序空等。muduo 会自动丢弃收到的数据
using namespace muduo;
using namespace muduo::net;

int main()
{
  EventLoop loop;
  TcpServer server(&loop, InetAddress(1079), "Finger");
  server.start();
  loop.loop();
}
