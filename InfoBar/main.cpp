#include "infobar-window.h"

int main(int argc, char *argv[]) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.pillowsky.md5calculator");
	
	InfobarWindow infobar;

	return app->run(infobar.create());
}
