/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2013  <copyright holder> <email>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef FLOW_H
#define FLOW_H

#include <gtk/gtk.h>
#include <memory>

//todo fanfei a.缺乏上游验证,避免逆流 b.仅支持两极(true or false)分流 c.缺乏上游数据缓存 d.缺乏延迟处理
class Flow
{
public:
  void SetDownFlow(std::shared_ptr<Flow> down,bool yes_flow = true,int timeout=0);
  void Fall();
protected:
  friend gboolean TimeoutFall(gpointer data);
  virtual bool Operate() = 0;
  void FallCall();
  std::shared_ptr<Flow> down_yes_;
  std::shared_ptr<Flow> down_no_;
  int timeout_;
};

#endif // FLOW_H
