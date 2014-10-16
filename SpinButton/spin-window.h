#ifndef _SPIN_WINDOW_H_
#define _SPIN_WINDOW_H_

#include <gtkmm.h>

using namespace std;
using namespace Gtk;

static string ui_file = "spin-window.ui";

class SpinWindow {
	public:
		SpinWindow();
		~SpinWindow();
		Window& create();

	protected:
		//Signal handlers
		void on_snapButton_clicked();
		void on_numButton_clicked();
		void on_digitsSpin_value_changed();
		void on_intButton_clicked();
		void on_floatButton_clicked();
		void on_closeButton_clicked();

		//Widget pointer in the UI file
		Window* mainWindow = NULL;		

		SpinButton* valueSpin = NULL;
		SpinButton* digitsSpin = NULL;

		CheckButton* snapButton = NULL;
		CheckButton* numButton = NULL;
	
		Button* intButton = NULL;
		Button* floatButton = NULL;
		Button* closeButton = NULL;

		Label* resultLabel = NULL;

		//Signal Connecters
		void ui_signal_connect(Glib::RefPtr<Gtk::Builder>& builder);
};

#endif // _SPIN_WINDOW_H_
