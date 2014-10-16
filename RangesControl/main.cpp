#include "ranges-window.h"
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.ranges");

	std::shared_ptr<RangesWindow> ranges = (std::shared_ptr<RangesWindow>) new RangesWindow();

	return app->run(*ranges->create());
}
