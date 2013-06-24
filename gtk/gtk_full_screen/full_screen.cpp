#include <gtk/gtk.h>
#include <cairo.h>
#include <windows.h> 

int main( int argc, char *argv[]);

int WINAPI WinMain(HINSTANCE hInstance, 
				   HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, 
				   int nCmdShow) 
{ 
	return main (__argc, __argv);
} 

GdkPixbuf * get_screenshot(){
    GdkPixbuf *screenshot;
    GdkWindow *root_window;
    gint x_orig, y_orig;
    gint width, height;
    root_window = gdk_get_default_root_window ();
    gdk_drawable_get_size (root_window, &width, &height);      
    gdk_window_get_origin (root_window, &x_orig, &y_orig);


    screenshot = gdk_pixbuf_get_from_drawable (NULL, root_window, NULL,
                                           x_orig, y_orig, 0, 0, width, height);
    return screenshot;
}


int main (int argc, char *argv[])
  {
    /*** The Widgets we'll be using ***/ 
    GtkWidget *win = NULL;
    GtkWidget *image;
    
    gtk_init (&argc, &argv);


    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_realize (win);
    gtk_window_fullscreen(GTK_WINDOW(win));
    
    image = gtk_image_new();


    gtk_container_add(GTK_CONTAINER(win), image);
    gtk_image_set_from_pixbuf((GtkImage*) image, get_screenshot());
    gtk_widget_queue_draw(image);
    
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);
    gtk_widget_show_all (win);
    gtk_main ();
    return 0;
}