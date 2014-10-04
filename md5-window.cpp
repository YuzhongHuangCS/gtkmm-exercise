#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "md5-window.h"

Window* Md5Window::create() {
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

	return mainWindow;
}

/* Connect signals */
void Md5Window::ui_signal_connect(Glib::RefPtr<Builder> &builder) {
	builder->get_widget("main_window", mainWindow);
	builder->get_widget("button1", calcButton);
	builder->get_widget("button2", compareButton);
	builder->get_widget("entry1", calcEntry);
	builder->get_widget("entry2", compareEntry);
	builder->get_widget("filechooserbutton1", calcFileButton);
	builder->get_widget("filechooserbutton2", mapFileButton);
	builder->get_widget("filechooserbutton3", compareFileButton);

	calcButton->signal_clicked().connect(sigc::mem_fun(*this, &Md5Window::on_calcButton_clicked));
	compareButton->signal_clicked().connect(sigc::mem_fun(*this, &Md5Window::on_compareButton_clicked));
}

/* Signal handler */
void Md5Window::on_calcButton_clicked() {
	string fileName = calcFileButton->get_filename();
	if(fileName.empty()){
		MessageDialog dialog(*mainWindow, "No file choosen", false, MESSAGE_ERROR);
		dialog.set_secondary_text("Please choose the file to calc md5.");
		dialog.run();
		return;
	}

	string delimiter = calcEntry->get_text();
	if(delimiter.empty()){
		MessageDialog dialog(*mainWindow, "Please specific delimiter", false, MESSAGE_ERROR);
		dialog.set_secondary_text("Please specific delimiter between plain and md5.");
		dialog.run();
		return;
	}

	vector<string> calcFile = readFile(fileName);
	string outFileName = fileName + ".md5";
	ofstream outFile(outFileName);

	for(auto it = calcFile.begin(); it != calcFile.end(); it++){
		outFile << *it << delimiter << Glib::Checksum::compute_checksum(Glib::Checksum::CHECKSUM_MD5, *it) << endl;
	}

	mapFileButton->set_filename(outFileName);
	compareEntry->set_text(delimiter);

	MessageDialog dialog(*mainWindow, "MD5 calculation complete.");
	dialog.set_secondary_text("Results has been save as " + outFileName);
	dialog.run();
}

void Md5Window::on_compareButton_clicked() {
	string mapFileName = mapFileButton->get_filename();
	if(mapFileName.empty()){
		MessageDialog dialog(*mainWindow, "No file choosen", false, MESSAGE_ERROR);
		dialog.set_secondary_text("Please choose the file to read the md5 map.");
		dialog.run();
		return;
	}
	vector<string> mapFile = readFile(mapFileName);

	string compareFileName = compareFileButton->get_filename();
	if(compareFileName.empty()){
		MessageDialog dialog(*mainWindow, "No file choosen", false, MESSAGE_ERROR);
		dialog.set_secondary_text("Please choose the file to compare.");
		dialog.run();
		return;
	}
	vector<string> compareFile = readFile(compareFileName);

	string delimiter = compareEntry->get_text();
	if(delimiter.empty()){
		MessageDialog dialog(*mainWindow, "Please specific delimiter", false, MESSAGE_ERROR);
		dialog.set_secondary_text("Please specific delimiter between plain and md5.");
		dialog.run();
		return;
	}

	map<string, string> md5Map;

	for(auto it = mapFile.begin(); it != mapFile.end(); it++){
		vector<string> parts;
		boost::split(parts, *it, boost::is_any_of(delimiter));
		// md5 => plain
		md5Map.insert(pair<string, string>(parts[1], parts[0]));
	}

	vector<string> chips;
	boost::split(chips, compareFileName, boost::is_any_of("."));
	string outFileName = chips[0] + "_patch." + chips[1];
	ofstream outFile(outFileName);

	for(auto it = compareFile.begin(); it != compareFile.end(); it++){
		vector<string> parts;
		boost::split(parts, *it, boost::is_any_of(delimiter));
		if(parts.size() == 1){
			auto find = md5Map.find(parts[0]);
			if(find != md5Map.end()){
				outFile << parts[0] << delimiter << find->second << endl;
			} else{
				outFile << parts[0] << endl;
			}
		} else{
			outFile << parts[0] << delimiter << parts[1] << endl;
		}
	}

	MessageDialog dialog(*mainWindow, "MD5 compare complete.");
	dialog.set_secondary_text("Results has been save as " + outFileName);
	dialog.run();
}

/* internal function */
vector<string> Md5Window::readFile(const string& fileName) {
	vector<string> fileContent;
	const string& body = Glib::file_get_contents(fileName);

	boost::split(fileContent, body, boost::is_any_of("\n"));

	return fileContent;
}