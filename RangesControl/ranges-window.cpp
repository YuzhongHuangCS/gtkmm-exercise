#include "ranges-window.h"
#include <iostream>

RangesWindow::RangesWindow() {

}

RangesWindow::~RangesWindow() {

}

Gtk::Window* RangesWindow::create() {
	/* Load the Glade file and instiate its widgets */
	Glib::RefPtr<Gtk::Builder> builder;
	try {
		builder = Gtk::Builder::create_from_file(UI_FILE);
	}
	catch (const Glib::FileError & ex) {
		std::cerr << ex.what() << std::endl;
		std::abort();
	}

	ui_signal_connect(builder);

	return mainWindow;
}
/* Connect signals */
void RangesWindow::ui_signal_connect(Glib::RefPtr<Gtk::Builder> &builder) {
	builder->get_widget("main_window", mainWindow);
	builder->get_widget("button1", quitButton);
	builder->get_widget("checkbutton1", checkButton);
	builder->get_widget("scale1", scale1);
	builder->get_widget("scale2", scale2);
	builder->get_widget("comboboxtext1", comboBox);
	adjustment1 = Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(builder->get_object("adjustment1"));
	adjustment2 = Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(builder->get_object("adjustment2"));
	adjustment3 = Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(builder->get_object("adjustment3"));

	quitButton->signal_clicked().connect(sigc::mem_fun(*this, &RangesWindow::on_quitButton_clicked));
	checkButton->signal_toggled().connect(sigc::mem_fun(*this, &RangesWindow::on_checkButton_toggled));
	comboBox->signal_changed().connect(sigc::mem_fun(*this, &RangesWindow::on_comboBox_changed));
	adjustment2->signal_value_changed().connect(sigc::mem_fun(*this, &RangesWindow::on_adjustment2_value_changed));
	adjustment3->signal_value_changed().connect(sigc::mem_fun(*this, &RangesWindow::on_adjustment3_value_changed));
}

/* Signal handler */
void RangesWindow::on_quitButton_clicked(){
	mainWindow->hide();
}

void RangesWindow::on_checkButton_toggled(){
	scale1->set_draw_value(checkButton->get_active());
	scale2->set_draw_value(checkButton->get_active());
}

void RangesWindow::on_comboBox_changed(){
	set_both_scale_value_pos(positionArray[atoi((comboBox->get_active_id()).c_str())]);
}

void RangesWindow::on_adjustment2_value_changed(){
	int value = (int) adjustment2->get_value();
	set_both_scale_digit(value);
}

void RangesWindow::on_adjustment3_value_changed(){
	int value = (int) adjustment3->get_value();
	adjustment1->set_page_size(value);
	adjustment1->set_page_increment(value);
}

/* utils functions */
inline void RangesWindow::set_both_scale_value_pos(Gtk::PositionType &position){
	scale1->set_value_pos(position);
	scale2->set_value_pos(position);
}

inline void RangesWindow::set_both_scale_digit(int value){
	scale1->set_digits(value);
	scale2->set_digits(value);
}