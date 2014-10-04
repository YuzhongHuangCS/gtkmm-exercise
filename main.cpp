#include "md5-window.h"

int main(int argc, char *argv[]) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.pillowsky.md5calculator");
	
	Md5Window calculator;
	
	return app->run(*(calculator.create()));
}
