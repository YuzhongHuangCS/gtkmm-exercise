#include <iostream>
#include "progress-window.h"

ProgressWindow::ProgressWindow() {

}

ProgressWindow::~ProgressWindow() {
	delete mainWindow;
}

Window& ProgressWindow::create() {
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
void ProgressWindow::ui_signal_connect(Glib::RefPtr<Builder> &builder) {
	builder->get_widget("window1", mainWindow);
	builder->get_widget("progressbar1", progress);
	builder->get_widget("checkbutton1", textButton);
	builder->get_widget("checkbutton2", modeButton);
	builder->get_widget("checkbutton3", invertButton);
	builder->get_widget("button1", closeButton);

	textButton->signal_clicked().connect(sigc::mem_fun(*this, &ProgressWindow::on_textButton_clicked));
	modeButton->signal_clicked().connect(sigc::mem_fun(*this, &ProgressWindow::on_modeButton_clicked));
	invertButton->signal_clicked().connect(sigc::mem_fun(*this, &ProgressWindow::on_invertButton_clicked));
	closeButton->signal_clicked().connect(sigc::mem_fun(*this, &ProgressWindow::on_closeButton_clicked));
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &ProgressWindow::on_timeout), 50);
}

/* Signal handler */
void ProgressWindow::on_textButton_clicked() {
	progress->set_show_text(textButton->get_active());
}

void ProgressWindow::on_modeButton_clicked() {
	pulseMode = modeButton->get_active();
	if(pulseMode == true){
		progress->pulse();
	} else{
		progress->set_fraction(0.0);
	}
}

void ProgressWindow::on_invertButton_clicked() {
	progress->set_inverted(invertButton->get_active());
}

void ProgressWindow::on_closeButton_clicked() {
	mainWindow->hide();
}

bool ProgressWindow::on_timeout() {
	if(pulseMode == true) {
		progress->pulse();
	} else {
		double new_val = (progress->get_fraction() + 0.01);
		if(new_val > 1.0) {
			new_val = 0.0;
		}
		progress->set_fraction(new_val);
	}

	//As this is a timeout function, return true so that it
	//continues to get called
	return true;
}