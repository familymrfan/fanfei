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


#include "flow.h"

namespace
{
guint timeid;
} // namespace

gboolean TimeoutFall(gpointer data){
    auto flow = static_cast<Flow*>(data);
    flow->FallCall();
    gtk_timeout_remove(timeid);
    return true;
}

void Flow::SetDownFlow(std::shared_ptr<Flow> down,bool yes_flow,int timeout){
    yes_flow == true?down_yes_ = down:down_no_ = down;
    timeout_ = timeout;
}

void Flow::Fall(){
    bool result = Operate();
    result?down_no_=nullptr:down_yes_=nullptr;
    if(timeout_>0){
      timeid = gtk_timeout_add(timeout_,TimeoutFall,this);
    }else{
      FallCall();
    }
}

void Flow::FallCall(){
    if(down_yes_){
	down_yes_->Fall();
    }else if(down_no_){
	down_no_->Fall();
    }else{
        gtk_main_quit();
    }
}