#ifndef _INFOBAR_WINDOW_H_
#define _INFOBAR_WINDOW_H_

#include <gtkmm.h>

using namespace std;
using namespace Gtk;

static string ui_file = "infobar-window.ui";

class InfobarWindow {
	public:
		InfobarWindow();
		~InfobarWindow();
		Window& create();

	protected:
		//Signal handlers
		void on_clearButton_clicked();
		void on_closeInfoButton_clicked();
		void on_textContent_changed();
		void on_closeButton_clicked();

		//Widget pointer in the UI file
		Window* mainWindow = NULL;
		Button* clearButton = NULL;
		Button* closeButton = NULL;
		Button* closeInfoButton = NULL;
		InfoBar* clearedInfoBar = NULL;

		Glib::RefPtr<TextBuffer> textContent;

		//Signal Connecters
		void ui_signal_connect(Glib::RefPtr<Gtk::Builder>& builder);
};

#endif // _INFOBAR_WINDOW_H_
