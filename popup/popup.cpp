#include <iostream>
#include "popup.h"

Popup::Popup() {

}

Popup::~Popup() {
	delete mainWindow;
}

Window& Popup::create() {
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
void Popup::ui_signal_connect(Glib::RefPtr<Builder> &builder) {
	builder->get_widget("window1", mainWindow);
	builder->get_widget("menu1", popMenu);
	builder->get_widget("menuitem1", item1);
	builder->get_widget("menuitem2", item2);
	builder->get_widget("menuitem3", item3);

	mainWindow->signal_button_press_event().connect_notify(sigc::mem_fun(*this, &Popup::on_window_press));
	item1->signal_activate().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &Popup::on_item_activate), "Item1 activated."));
	item2->signal_activate().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &Popup::on_item_activate), "Item2 activated."));
	item3->signal_activate().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &Popup::on_item_activate), "Item3 activated."));
}

/* Signal handler */
void Popup::on_window_press(GdkEventButton* event) {
	if((event->type == GDK_BUTTON_PRESS) && (event->button == 3)) {
		popMenu->popup(event->button, event->time);
	}
}

void Popup::on_item_activate(Glib::ustring msg) {
	MessageDialog(*mainWindow, msg).run();
}