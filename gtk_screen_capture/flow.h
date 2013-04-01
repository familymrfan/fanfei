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

#include <memory>

//todo fanfei a.缺乏上游验证,避免逆流 b.仅支持两极(true or false)分流 c.缺乏上游数据缓存
class Flow
{
public:
  void SetDownFlow(std::shared_ptr<Flow> down,bool yes_flow = true){
    yes_flow == true?down_yes_ = down:down_no_ = down;
  }
  void Fall(){
    bool result = Operate();
    if(result && down_yes_){
	down_yes_->Fall();
    }else if(!result && down_no_){
	down_no_->Fall();
    }
  }
protected:
  virtual bool Operate() = 0;
  std::shared_ptr<Flow> down_yes_;
  std::shared_ptr<Flow> down_no_;
};

#endif // FLOW_H
