#include "muduo/net/EventLoop.h"
//拒绝连接。什么都不做，程序空等。
using namespace muduo;
using namespace muduo::net;

int main()
{
  EventLoop loop;
  loop.loop();
}
