// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)
//带 stack trace 的异常基类

#include "muduo/base/Exception.h"
#include "muduo/base/CurrentThread.h"

namespace muduo
{

Exception::Exception(string msg)
  : message_(std::move(msg)),
    stack_(CurrentThread::stackTrace(/*demangle=*/false))
{
}

}  // namespace muduo
