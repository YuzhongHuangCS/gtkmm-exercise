#ifndef _MD5_WINDOW_H_
#define _MD5_WINDOW_H_

#include <gtkmm.h>

using namespace std;
using namespace Gtk;

static string ui_file = "md5calculator.ui";

class Md5Window {
	public:
		Window* create();

	protected:
		//Signal handlers
		void on_calcButton_clicked();
		void on_compareButton_clicked();

		//Widget pointer in the UI file
		Window* mainWindow = NULL;		
		Button* calcButton = NULL;
		Button* compareButton = NULL;
		Entry* calcEntry = NULL;
		Gtk::Entry* compareEntry = NULL;
		FileChooserButton* calcFileButton = NULL;
		FileChooserButton* mapFileButton = NULL;
		FileChooserButton* compareFileButton = NULL;

		//Signal Connecters
		void ui_signal_connect(Glib::RefPtr<Gtk::Builder>& builder);

		//Internal functions
		vector<string> readFile(const string& fileName);
};

#endif // _MD5_WINDOW_H_
