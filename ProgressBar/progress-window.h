#ifndef _PROGRESS_WINDOW_H_
#define _PROGRESS_WINDOW_H_

#include <gtkmm.h>

using namespace std;
using namespace Gtk;

static string ui_file = "progress-window.ui";

class ProgressWindow {
	public:
		ProgressWindow();
		~ProgressWindow();
		Window& create();

	protected:
		//Signal handlers
		void on_textButton_clicked();
		void on_modeButton_clicked();
		void on_invertButton_clicked();
		void on_closeButton_clicked();
		bool on_timeout();

		//Widget pointer in the UI file
		Window* mainWindow = NULL;
		ProgressBar* progress = NULL;
		CheckButton* textButton = NULL;
		CheckButton* modeButton = NULL;
		CheckButton* invertButton = NULL;
		Button* closeButton = NULL;

		//Internal status
		bool pulseMode = false;

		//Signal Connecters
		void ui_signal_connect(Glib::RefPtr<Gtk::Builder>& builder);
};

#endif // _PROGRESS_WINDOW_H_
