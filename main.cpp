#include "win/texteditor.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setApplicationName("Qt文本编辑器");
    app.setApplicationVersion("3.0");
    app.setOrganizationName("MyCompany");
    app.setStyle("Fusion");

    TextEditor editor;
    editor.show();
    editor.openWithArgs(argc, argv);

    return app.exec();
}