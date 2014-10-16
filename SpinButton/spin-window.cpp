#include <iostream>
#include "spin-window.h"

SpinWindow::SpinWindow() {

}

SpinWindow::~SpinWindow() {
	delete mainWindow;
}

Window& SpinWindow::create() {
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
void SpinWindow::ui_signal_connect(Glib::RefPtr<Builder> &builder) {
	builder->get_widget("window1", mainWindow);

	builder->get_widget("checkbutton1", snapButton);
	builder->get_widget("checkbutton2", numButton);

	builder->get_widget("spinbutton4", valueSpin);
	builder->get_widget("spinbutton5", digitsSpin);

	builder->get_widget("button2", intButton);
	builder->get_widget("button3", floatButton);
	builder->get_widget("button1", closeButton);

	builder->get_widget("label8", resultLabel);

	snapButton->signal_clicked().connect(sigc::mem_fun(*this, &SpinWindow::on_snapButton_clicked));
	numButton->signal_clicked().connect(sigc::mem_fun(*this, &SpinWindow::on_numButton_clicked));
	digitsSpin->signal_value_changed().connect(sigc::mem_fun(*this, &SpinWindow::on_digitsSpin_value_changed));
	intButton->signal_clicked().connect(sigc::mem_fun(*this, &SpinWindow::on_intButton_clicked));
	floatButton->signal_clicked().connect(sigc::mem_fun(*this, &SpinWindow::on_floatButton_clicked));
	closeButton->signal_clicked().connect(sigc::mem_fun(*this, &SpinWindow::on_closeButton_clicked));
}

/* Signal handler */
void SpinWindow::on_snapButton_clicked() {
	valueSpin->set_snap_to_ticks(snapButton->get_active());
}

void SpinWindow::on_numButton_clicked() {
	valueSpin->set_numeric(numButton->get_active());
}

void SpinWindow::on_digitsSpin_value_changed() {
	valueSpin->set_digits(digitsSpin->get_value_as_int());
}

void SpinWindow::on_intButton_clicked() {
	resultLabel->set_text(to_string(valueSpin->get_value_as_int()));
}

void SpinWindow::on_floatButton_clicked() {
	resultLabel->set_text(to_string(valueSpin->get_value()));
}

void SpinWindow::on_closeButton_clicked(){
	mainWindow->hide();
}