#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QSplitter>
#include <QTabWidget>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QStatusBar>
#include <QFont>
#include <QFontDialog>
#include <QIcon>
#include <QCloseEvent>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QStyle>
#include <QToolButton>
#include <QFrame>
#include <QSizePolicy>
#include <QSettings>
#include <QTextStream>
#include <QClipboard>
#include <QTextCursor>
#include <QInputDialog>
#include <QLabel>
#include <QTreeView>
#include <QFileSystemModel>
#include <QDir>
#include <QDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QTimer>

class TextEditor : public QMainWindow {
    Q_OBJECT

public:
    enum Theme {
        LightGreen,
        DarkMode,
        LightBlue,
        Classic,
        Original
    };

    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

    void openWithArgs(int argc, char *argv[]);

private:
    void setupUI();
    void applyTheme(Theme theme);
    void createIntegratedMenuBar();
    void setupFindDialog();
    void setupFindReplaceDialog();
    void addToolButton(QHBoxLayout *layout, QAction *action);
    QTextEdit *currentTextEdit();
    void updateMenus();
    void updateWindowMenu();
    void createNewDocument(const QString &title = "未命名");
    void documentWasModified();
    void updateCursorPosition();
    void updateFontInfo();
    void openFileFromTree(const QModelIndex &index);
    void toggleSidebar();
    bool saveFile(const QString &fileName, QTextEdit *textEdit);
    void readSettings();
    void writeSettings();

private slots:
    void open();
    bool save();
    bool saveAs();
    void closeTab(int index);
    void closeAllTabs();
    void selectFont();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void openFile(const QString &fileName);
    void newFile();
    void about();
    void showFindReplaceDialog();
    void showFindDialog();
    void updateFindButtons();
    QTextDocument::FindFlags getFindFlags();
    void findNext();
    void findPrevious();
    void replace();
    void replaceAll();
    void showTreeContextMenu(const QPoint &pos);
    void createNewFileInTree();
    void createNewFolderInTree();
    void renameInTree();
    void deleteInTree();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Theme currentTheme;
    QTextCursor searchCursor;
    QModelIndex currentTreeIndex;
    QSplitter *mainSplitter;
    QTabWidget *tabWidget;
    QTreeView *treeView;
    QFileSystemModel *fileModel;
    QFont defaultFont;
    QLabel *cursorPositionLabel;
    QLabel *fontInfoLabel;

    QMenu *editMenu;
    QMenu *windowMenu;
    QMenu *viewMenu;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *closeAction;
    QAction *closeAllAction;
    QAction *exitAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *fontAction;
    QAction *findAction;
    QAction *findReplaceAction;
    QAction *toggleSidebarAction;
    QAction *nextAction;
    QAction *previousAction;

    QDialog *findDialog;
    QLineEdit *findLineEdit;
    QCheckBox *caseSensitiveCheck;
    QCheckBox *wholeWordCheck;
    QPushButton *findNextButton;
    QPushButton *findPrevButton;

    QDialog *findReplaceDialog;
    QLineEdit *findLineEditR;
    QLineEdit *replaceLineEditR;
    QCheckBox *caseSensitiveCheckR;
    QCheckBox *wholeWordCheckR;
    QPushButton *findNextButtonR;
    QPushButton *findPrevButtonR;
    QPushButton *replaceButtonR;
    QPushButton *replaceAllButtonR;
};

#endif // TEXTEDITOR_H