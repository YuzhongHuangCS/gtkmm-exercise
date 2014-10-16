#ifndef _RANGES_WINDOW_H_
#define _RANGES_WINDOW_H_

#include <gtkmm.h>

#define UI_FILE "ranges-window.ui"

class RangesWindow {
	public:
		RangesWindow();
		~RangesWindow();

		Gtk::Window* create();
	protected:
		//Signal handlers
		void on_quitButton_clicked();
		void on_checkButton_toggled();
		void on_comboBox_changed();
		void on_adjustment2_value_changed();
		void on_adjustment3_value_changed();

		//Widget pointer in the UI file
		Gtk::Window* mainWindow = NULL;
		Gtk::Button* quitButton = NULL;
		Gtk::CheckButton* checkButton = NULL;
		Gtk::Scale* scale1 = NULL;
		Gtk::Scale* scale2 = NULL;
		Gtk::Scale* scale3 = NULL;
		Gtk::Scale* scale4 = NULL;
		Gtk::ComboBox* comboBox = NULL;
		Glib::RefPtr<Gtk::Adjustment> adjustment1, adjustment2, adjustment3;

		//static contents
		Gtk::PositionType positionArray[4] = {
			Gtk::POS_TOP,
			Gtk::POS_BOTTOM,
			Gtk::POS_LEFT,
			Gtk::POS_RIGHT
		};
		//Signal Connecters
		void ui_signal_connect(Glib::RefPtr<Gtk::Builder> &builder);

		//utils functions
		inline void set_both_scale_value_pos(Gtk::PositionType &position);
		inline void set_both_scale_digit(int value);
};

#endif // _RANGES_WINDOW_H_
