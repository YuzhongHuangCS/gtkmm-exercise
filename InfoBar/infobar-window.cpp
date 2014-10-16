#include <iostream>
#include "infobar-window.h"

InfobarWindow::InfobarWindow() {

}

InfobarWindow::~InfobarWindow() {
	delete mainWindow;
}

Window& InfobarWindow::create() {
	/* Load the Glade file and instiate its widgets */
	Glib::RefPtr<Builder> builder;
	try {
		builder = Builder::create_from_file(ui_file);
	}
	catch (const Glib::FileError & ex) {
		cerr << ex.what() << endl;
		abort();
	}

	ui_signal_connect(builder);

	return *mainWindow;
}

/* Connect signals */
void InfobarWindow::ui_signal_connect(Glib::RefPtr<Builder> &builder) {
	builder->get_widget("window1", mainWindow);
	builder->get_widget("button2", clearButton);
	builder->get_widget("button3", closeButton);
	builder->get_widget("button1", closeInfoButton);
	builder->get_widget("infobar1", clearedInfoBar);

	textContent = Glib::RefPtr<TextBuffer>::cast_dynamic(builder->get_object("textbuffer1"));

	clearButton->signal_clicked().connect(sigc::mem_fun(*this, &InfobarWindow::on_clearButton_clicked));
	closeInfoButton->signal_clicked().connect(sigc::mem_fun(*this, &InfobarWindow::on_closeInfoButton_clicked));
	closeButton->signal_clicked().connect(sigc::mem_fun(*this, &InfobarWindow::on_closeButton_clicked));
	textContent->signal_changed().connect(sigc::mem_fun(*this, &InfobarWindow::on_textContent_changed));
}

/* Signal handler */
void InfobarWindow::on_clearButton_clicked() {
	clearedInfoBar->show();
	textContent->set_text("");
}

void InfobarWindow::on_closeInfoButton_clicked() {
	clearedInfoBar->hide();
}

void InfobarWindow::on_textContent_changed() {
	if(textContent->size() > 0) {
		clearButton->set_sensitive(true);
		clearedInfoBar->hide();
	} else{
		clearButton->set_sensitive(false);
	}
}

void InfobarWindow::on_closeButton_clicked() {
	mainWindow->hide();
}
