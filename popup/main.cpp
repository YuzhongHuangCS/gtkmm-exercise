#include "popup.h"

int main(int argc, char *argv[]) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.pillowsky.md5calculator");
	
	Popup pop;
	
	return app->run(pop.create());
}
