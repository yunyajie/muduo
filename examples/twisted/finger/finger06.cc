#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"

#include <map>
/*
从空的UserMap里查找用户。 从一行消息中拿到用户名
（L33），在UserMap里查找，然后返回结果。
*/
using namespace muduo;
using namespace muduo::net;

typedef std::map<string, string> UserMap;
UserMap users;

string getUser(const string& user)
{
  string result = "No such user";
  UserMap::iterator it = users.find(user);
  if (it != users.end())
  {
    result = it->second;
  }
  return result;
}

void onMessage(const TcpConnectionPtr& conn,
               Buffer* buf,
               Timestamp receiveTime)
{
  const char* crlf = buf->findCRLF();
  if (crlf)
  {
    string user(buf->peek(), crlf);
    conn->send(getUser(user) + "\r\n");
    buf->retrieveUntil(crlf + 2);
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
