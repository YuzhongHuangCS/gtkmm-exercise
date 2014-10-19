#ifndef _POPUP_H_
#define _POPUP_H_

#include <gtkmm.h>

using namespace std;
using namespace Gtk;

static string ui_file = "popup.ui";

class Popup {
	public:
		Popup();
		~Popup();
		Window& create();

	protected:
		//Signal handlers
		void on_window_press(GdkEventButton* event);
		void on_item1_activate();
		void on_item2_activate();
		void on_item3_activate();

		//Widget pointer in the UI file
		Window* mainWindow = NULL;
		Menu* popMenu = NULL;
		MenuItem* item1 = NULL;
		MenuItem* item2 = NULL;
		MenuItem* item3 = NULL;

		//Signal Connecters
		void ui_signal_connect(Glib::RefPtr<Gtk::Builder>& builder);
};

#endif // _POPUP_H_
