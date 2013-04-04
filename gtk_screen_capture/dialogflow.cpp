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

#include <gtk/gtk.h>
#include "dialogflow.h"

bool Dialogflow::Operate(){
    GtkWidget *dialog;
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER,GTK_BUTTONS_OK_CANCEL,"click yes to capture");
    gtk_window_set_title(GTK_WINDOW(dialog), "screen capture");
    bool result = false;
    if(GTK_RESPONSE_OK == gtk_dialog_run(GTK_DIALOG(dialog))){
      result = true;
    }else{
      gtk_exit(0);
    }
    gtk_widget_hide(dialog);
    gtk_widget_destroy(dialog);
    return result;
}