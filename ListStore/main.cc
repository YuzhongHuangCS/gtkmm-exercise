#include <iostream>
#include <gtkmm.h>

using namespace std;
using namespace Glib;
using namespace Gtk;

static string UI_FILE = "listmm.ui";

class ColumnModel : public TreeModel::ColumnRecord
{
	public:
		TreeModelColumn<int> i;
		TreeModelColumn<int> x2;
		TreeModelColumn<int> x4;
		TreeModelColumn<int> x8;
		TreeModelColumn<int> x16;
		TreeModelColumn<bool> flag;

		ColumnModel() {
			add(i);
			add(x2);
			add(x4);
			add(x8);
			add(x16);
			add(flag);
		}
};

int main(int argc, char* argv[]) {
	RefPtr<Application> app = Application::create(argc, argv, "org.pillowsky.listmm");

	Window* mainWindow = NULL;
	TreeView* treeView = NULL;

	try {
		RefPtr<Builder> builder;
		builder = Builder::create_from_file(UI_FILE);
		builder->get_widget("main_window", mainWindow);
		builder->get_widget("treeview1", treeView);
	}
	catch (const FileError & ex) {
		cerr << ex.what() << endl;
		return 1;
	}

	ColumnModel col; 
	RefPtr<ListStore> refTreeModel = ListStore::create(col);
	treeView->set_model(refTreeModel);
	treeView->set_reorderable();

	//Add the TreeView's view col:
	treeView->append_column_editable("Base", col.i);
	treeView->append_column_editable("X2", col.x2);
	treeView->append_column_editable("X4", col.x4);
	treeView->append_column_editable("X8", col.x8);
	treeView->append_column_editable("X16", col.x16);
	treeView->append_column_editable("Choose", col.flag);

	TreeView::Column* pColumn = treeView->get_column(0);
	pColumn->set_sort_column(col.i);

	for(int i = 1; i < 50; i++){
		TreeModel::Row row = *(refTreeModel->append());
		row[col.i] = i;
		row[col.x2] = i*2;
		row[col.x4] = i*4;
		row[col.x8] = i*8;
		row[col.x16] = i*16;
		row[col.flag] = true;
	}

	/* Item access example
	for(auto it = refTreeModel->children().begin(); it != refTreeModel->children().end(); it++){
		auto row = *it;
		cout << row[col.i] << endl;
	}*/

	return app->run(*mainWindow);
}