#include "texteditor.h"
#include "themes.h"
#include <QApplication>

TextEditor::TextEditor(QWidget *parent) :
    QMainWindow(parent),
    currentTheme(LightGreen),
    searchCursor(),
    cursorPositionLabel(nullptr),
    fontInfoLabel(nullptr),
    findDialog(nullptr),
    findNextButton(nullptr),
    findPrevButton(nullptr),
    findLineEdit(nullptr),
    findReplaceDialog(nullptr),
    findLineEditR(nullptr),
    replaceLineEditR(nullptr),
    caseSensitiveCheckR(nullptr),
    wholeWordCheckR(nullptr),
    findNextButtonR(nullptr),
    findPrevButtonR(nullptr),
    replaceButtonR(nullptr),
    replaceAllButtonR(nullptr),
    findReplaceAction(nullptr)
{
    setupUI();
    setWindowTitle("Qt文本编辑器");
    resize(800, 600);
    readSettings();
    applyTheme(currentTheme);
}

TextEditor::~TextEditor() {
    writeSettings();
}

void TextEditor::openWithArgs(int argc, char *argv[]) {
    if (argc > 1) {
        QString fileName = QString::fromLocal8Bit(argv[1]);
        if (!fileName.isEmpty()) {
            openFile(fileName);
        }
    } else {
        createNewDocument();
    }
}

void TextEditor::setupUI() {
    mainSplitter = new QSplitter(this);

    treeView = new QTreeView(mainSplitter);
    treeView->setObjectName("fileTreeView");
    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath("");

    treeView->setMinimumWidth(150);
    treeView->setMaximumWidth(500);
    treeView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(treeView, &QTreeView::customContextMenuRequested,
            this, &TextEditor::showTreeContextMenu);

    treeView->setModel(fileModel);
    treeView->setRootIndex(fileModel->index(""));
    treeView->setHeaderHidden(true);
    treeView->setAnimated(true);
    treeView->setIndentation(20);
    treeView->sortByColumn(0, Qt::AscendingOrder);
    treeView->setSortingEnabled(true);

    for (int i = 1; i < fileModel->columnCount(); ++i) {
        treeView->hideColumn(i);
    }

    connect(treeView, &QTreeView::doubleClicked, this, &TextEditor::openFileFromTree);

    tabWidget = new QTabWidget(mainSplitter);
    tabWidget->setObjectName("mainTabWidget");
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &TextEditor::closeTab);
    connect(tabWidget, &QTabWidget::currentChanged, this, &TextEditor::updateMenus);

    QList<int> sizes;
    sizes << width() * 0.25 << width() * 0.75;
    mainSplitter->setSizes(sizes);
    mainSplitter->setStretchFactor(0, 1);
    mainSplitter->setStretchFactor(1, 3);
    mainSplitter->setHandleWidth(3);

    setCentralWidget(mainSplitter);

    createIntegratedMenuBar();

    statusBar()->showMessage("就绪");

    cursorPositionLabel = new QLabel(this);
    cursorPositionLabel->setObjectName("statusLabel");
    statusBar()->addPermanentWidget(cursorPositionLabel);
    updateCursorPosition();

    fontInfoLabel = new QLabel(this);
    fontInfoLabel->setObjectName("statusLabel");
    statusBar()->addPermanentWidget(fontInfoLabel);
    updateFontInfo();

    setupFindReplaceDialog();
    setupFindDialog();

    updateMenus();
}

void TextEditor::applyTheme(Theme theme) {
    currentTheme = theme;
    QString styleSheet;

    switch (theme) {
    case LightGreen:
        styleSheet = getLightGreenTheme();
        break;
    case DarkMode:
        styleSheet = getDarkTheme();
        break;
    case LightBlue:
        styleSheet = getLightBlueTheme();
        break;
    case Classic:
        styleSheet = getClassicTheme();
        break;
    case Original:
        styleSheet = getOriginalTheme();
        break;
    }

    qApp->setStyleSheet(styleSheet);
    writeSettings();
}

void TextEditor::createIntegratedMenuBar() {
    QMenuBar *menuBar = this->menuBar();

    QMenu *fileMenu = menuBar->addMenu("文件(&F)");

    newAction = new QAction(QIcon::fromTheme("document-new", style()->standardIcon(QStyle::SP_FileIcon)), "新建(&N)", this);
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, &QAction::triggered, this, &TextEditor::newFile);
    fileMenu->addAction(newAction);

    openAction = new QAction(QIcon::fromTheme("document-open", style()->standardIcon(QStyle::SP_DialogOpenButton)), "打开(&O)...", this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, [this] { open(); });
    fileMenu->addAction(openAction);

    saveAction = new QAction(QIcon::fromTheme("document-save", style()->standardIcon(QStyle::SP_DialogSaveButton)), "保存(&S)", this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &TextEditor::save);
    fileMenu->addAction(saveAction);

    saveAsAction = new QAction("另存为(&A)...", this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &TextEditor::saveAs);
    fileMenu->addAction(saveAsAction);

    closeAction = new QAction("关闭当前(&C)", this);
    closeAction->setShortcut(QKeySequence::Close);
    connect(closeAction, &QAction::triggered, this, [this] { closeTab(tabWidget->currentIndex()); });
    fileMenu->addAction(closeAction);

    closeAllAction = new QAction("关闭全部", this);
    connect(closeAllAction, &QAction::triggered, this, &TextEditor::closeAllTabs);
    fileMenu->addAction(closeAllAction);

    fileMenu->addSeparator();

    exitAction = new QAction("退出(&X)", this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QApplication::closeAllWindows);
    fileMenu->addAction(exitAction);

    editMenu = menuBar->addMenu("编辑(&E)");

    undoAction = new QAction(QIcon::fromTheme("edit-undo", style()->standardIcon(QStyle::SP_ArrowBack)), "撤销(&U)", this);
    undoAction->setShortcut(QKeySequence::Undo);
    connect(undoAction, &QAction::triggered, this, &TextEditor::undo);
    editMenu->addAction(undoAction);

    redoAction = new QAction(QIcon::fromTheme("edit-redo", style()->standardIcon(QStyle::SP_ArrowForward)), "重做(&R)", this);
    redoAction->setShortcut(QKeySequence::Redo);
    connect(redoAction, &QAction::triggered, this, &TextEditor::redo);
    editMenu->addAction(redoAction);

    editMenu->addSeparator();

    cutAction = new QAction(QIcon::fromTheme("edit-cut", style()->standardIcon(QStyle::SP_TrashIcon)), "剪切(&T)", this);
    cutAction->setShortcut(QKeySequence::Cut);
    connect(cutAction, &QAction::triggered, this, &TextEditor::cut);
    editMenu->addAction(cutAction);

    copyAction = new QAction(QIcon::fromTheme("edit-copy", style()->standardIcon(QStyle::SP_FileDialogDetailedView)), "复制(&C)", this);
    copyAction->setShortcut(QKeySequence::Copy);
    connect(copyAction, &QAction::triggered, this, &TextEditor::copy);
    editMenu->addAction(copyAction);

    pasteAction = new QAction(QIcon::fromTheme("edit-paste", style()->standardIcon(QStyle::SP_DialogOkButton)), "粘贴(&P)", this);
    pasteAction->setShortcut(QKeySequence::Paste);
    connect(pasteAction, &QAction::triggered, this, &TextEditor::paste);
    editMenu->addAction(pasteAction);

    editMenu->addSeparator();

    findAction = new QAction("查找(&F)...", this);
    findAction->setShortcut(QKeySequence::Find);
    connect(findAction, &QAction::triggered, this, &TextEditor::showFindDialog);
    editMenu->addAction(findAction);

    findReplaceAction = new QAction("替换(&R)...", this);
    findReplaceAction->setShortcut(QKeySequence("Ctrl+R"));
    connect(findReplaceAction, &QAction::triggered, this, &TextEditor::showFindReplaceDialog);
    editMenu->addAction(findReplaceAction);

    editMenu->addSeparator();

    fontAction = new QAction("字体(&F)...", this);
    connect(fontAction, &QAction::triggered, this, &TextEditor::selectFont);
    editMenu->addAction(fontAction);

    viewMenu = menuBar->addMenu("视图(&V)");

    toggleSidebarAction = new QAction("显示/隐藏侧边栏", this);
    toggleSidebarAction->setShortcut(QKeySequence("Ctrl+Shift+L"));
    connect(toggleSidebarAction, &QAction::triggered, this, &TextEditor::toggleSidebar);
    viewMenu->addAction(toggleSidebarAction);

    QMenu *themeMenu = viewMenu->addMenu("主题(&T)");

    QAction *lightGreenAction = new QAction("淡绿色主题", this);
    connect(lightGreenAction, &QAction::triggered, this, [this] { applyTheme(LightGreen); });
    themeMenu->addAction(lightGreenAction);

    QAction *darkThemeAction = new QAction("深色模式", this);
    connect(darkThemeAction, &QAction::triggered, this, [this] { applyTheme(DarkMode); });
    themeMenu->addAction(darkThemeAction);

    QAction *lightBlueAction = new QAction("浅蓝色主题", this);
    connect(lightBlueAction, &QAction::triggered, this, [this] { applyTheme(LightBlue); });
    themeMenu->addAction(lightBlueAction);

    QAction *classicAction = new QAction("经典主题", this);
    connect(classicAction, &QAction::triggered, this, [this] { applyTheme(Classic); });
    themeMenu->addAction(classicAction);

    QAction *originalAction = new QAction("原始主题", this);
    connect(classicAction, &QAction::triggered, this, [this] { applyTheme(Original); });
    themeMenu->addAction(originalAction);

    windowMenu = menuBar->addMenu("窗口(&W)");
    connect(windowMenu, &QMenu::aboutToShow, this, &TextEditor::updateWindowMenu);

    nextAction = new QAction("下一个标签(&N)", this);
    nextAction->setShortcut(QKeySequence::NextChild);
    connect(nextAction, &QAction::triggered, this, [this] {
        int next = (tabWidget->currentIndex() + 1) % tabWidget->count();
        tabWidget->setCurrentIndex(next);
    });
    windowMenu->addAction(nextAction);

    previousAction = new QAction("上一个标签(&P)", this);
    previousAction->setShortcut(QKeySequence::PreviousChild);
    connect(previousAction, &QAction::triggered, this, [this] {
        int prev = (tabWidget->currentIndex() - 1 + tabWidget->count()) % tabWidget->count();
        tabWidget->setCurrentIndex(prev);
    });
    windowMenu->addAction(previousAction);

    windowMenu->addSeparator();
    windowMenu->addAction(closeAllAction);

    QMenu *helpMenu = menuBar->addMenu("帮助(&H)");
    QAction *aboutAction = new QAction("关于(&A)...", this);
    connect(aboutAction, &QAction::triggered, this, &TextEditor::about);
    helpMenu->addAction(aboutAction);

    QWidget *toolbarContainer = new QWidget();
    toolbarContainer->setObjectName("toolbarContainer");
    QHBoxLayout *toolbarLayout = new QHBoxLayout(toolbarContainer);
    toolbarLayout->setContentsMargins(0, 0, 0, 0);
    toolbarLayout->setSpacing(2);

    addToolButton(toolbarLayout, newAction);
    addToolButton(toolbarLayout, openAction);
    addToolButton(toolbarLayout, saveAction);

    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::VLine);
    separator->setFrameShadow(QFrame::Sunken);
    toolbarLayout->addWidget(separator);

    addToolButton(toolbarLayout, cutAction);
    addToolButton(toolbarLayout, copyAction);
    addToolButton(toolbarLayout, pasteAction);

    QFrame *separator2 = new QFrame();
    separator2->setFrameShape(QFrame::VLine);
    separator2->setFrameShadow(QFrame::Sunken);
    toolbarLayout->addWidget(separator2);

    addToolButton(toolbarLayout, undoAction);
    addToolButton(toolbarLayout, redoAction);

    toolbarLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    menuBar->setCornerWidget(toolbarContainer, Qt::TopRightCorner);
}

void TextEditor::setupFindDialog() {
    findDialog = new QDialog(this);
    findDialog->setWindowTitle("查找替换");
    findDialog->setWindowFlags(findDialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    findDialog->resize(400, 200);

    QGridLayout *layout = new QGridLayout(findDialog);

    QLabel *findLabel = new QLabel("查找内容:", findDialog);
    findLineEdit = new QLineEdit(findReplaceDialog);
    findLineEdit->setMinimumWidth(250);
    connect(findLineEdit, &QLineEdit::textChanged, this, &TextEditor::updateFindButtons);

    caseSensitiveCheck = new QCheckBox("区分大小写", findDialog);
    wholeWordCheck = new QCheckBox("全字匹配", findDialog);

    findNextButton = new QPushButton("查找下一个", findDialog);
    findNextButton->setEnabled(false);
    connect(findNextButton, &QPushButton::clicked, this, &TextEditor::findNext);

    findPrevButton = new QPushButton("查找上一个", findDialog);
    findPrevButton->setEnabled(false);
    connect(findPrevButton, &QPushButton::clicked, this, &TextEditor::findPrevious);

    QPushButton *closeButton = new QPushButton("关闭", findDialog);
    connect(closeButton, &QPushButton::clicked, findDialog, &QDialog::hide);

    layout->addWidget(findLabel, 0, 0);
    layout->addWidget(findLineEdit, 0, 1, 1, 3);
    layout->addWidget(caseSensitiveCheck, 2, 0, 1, 2);
    layout->addWidget(wholeWordCheck, 2, 2, 1, 2);
    layout->addWidget(findPrevButton, 3, 0);
    layout->addWidget(findNextButton, 3, 1);
    layout->addWidget(closeButton, 3, 3);

    findDialog->setLayout(layout);
}

void TextEditor::setupFindReplaceDialog() {
    findReplaceDialog = new QDialog(this);
    findReplaceDialog->setWindowTitle("查找替换");
    findReplaceDialog->setWindowFlags(findReplaceDialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    findReplaceDialog->resize(400, 200);

    QGridLayout *layout = new QGridLayout(findReplaceDialog);

    QLabel *findLabel = new QLabel("查找内容:", findReplaceDialog);
    findLineEditR = new QLineEdit(findReplaceDialog);
    findLineEditR->setMinimumWidth(250);
    connect(findLineEditR, &QLineEdit::textChanged, this, &TextEditor::updateFindButtons);

    QLabel *replaceLabel = new QLabel("替换为:", findReplaceDialog);
    replaceLineEditR = new QLineEdit(findReplaceDialog);
    replaceLineEditR->setMinimumWidth(250);

    caseSensitiveCheckR = new QCheckBox("区分大小写", findReplaceDialog);
    wholeWordCheckR = new QCheckBox("全字匹配", findReplaceDialog);

    findNextButtonR = new QPushButton("查找下一个", findReplaceDialog);
    findNextButtonR->setEnabled(false);
    connect(findNextButtonR, &QPushButton::clicked, this, &TextEditor::findNext);

    findPrevButtonR = new QPushButton("查找上一个", findReplaceDialog);
    findPrevButtonR->setEnabled(false);
    connect(findPrevButtonR, &QPushButton::clicked, this, &TextEditor::findPrevious);

    replaceButtonR = new QPushButton("替换", findReplaceDialog);
    replaceButtonR->setEnabled(false);
    connect(replaceButtonR, &QPushButton::clicked, this, &TextEditor::replace);

    replaceAllButtonR = new QPushButton("全部替换", findReplaceDialog);
    connect(replaceAllButtonR, &QPushButton::clicked, this, &TextEditor::replaceAll);

    QPushButton *closeButton = new QPushButton("关闭", findReplaceDialog);
    connect(closeButton, &QPushButton::clicked, findReplaceDialog, &QDialog::hide);

    layout->addWidget(findLabel, 0, 0);
    layout->addWidget(findLineEditR, 0, 1, 1, 3);
    layout->addWidget(replaceLabel, 1, 0);
    layout->addWidget(replaceLineEditR, 1, 1, 1, 3);
    layout->addWidget(caseSensitiveCheckR, 2, 0, 1, 2);
    layout->addWidget(wholeWordCheckR, 2, 2, 1, 2);
    layout->addWidget(findPrevButtonR, 3, 0);
    layout->addWidget(findNextButtonR, 3, 1);
    layout->addWidget(replaceButtonR, 3, 2);
    layout->addWidget(replaceAllButtonR, 3, 3);
    layout->addWidget(closeButton, 4, 3);

    findReplaceDialog->setLayout(layout);
}

void TextEditor::addToolButton(QHBoxLayout *layout, QAction *action) {
    QToolButton *button = new QToolButton();
    button->setDefaultAction(action);
    button->setToolButtonStyle(Qt::ToolButtonIconOnly);
    button->setAutoRaise(true);
    layout->addWidget(button);
}

QTextEdit *TextEditor::currentTextEdit() {
    if (tabWidget->count() == 0) return nullptr;
    return qobject_cast<QTextEdit*>(tabWidget->currentWidget());
}

void TextEditor::updateMenus() {
    bool hasActiveTab = (tabWidget->count() > 0);

    saveAction->setEnabled(hasActiveTab);
    saveAsAction->setEnabled(hasActiveTab);
    closeAction->setEnabled(hasActiveTab);

    if (hasActiveTab) {
        QTextEdit *textEdit = currentTextEdit();
        undoAction->setEnabled(textEdit->document()->isUndoAvailable());
        redoAction->setEnabled(textEdit->document()->isRedoAvailable());
        cutAction->setEnabled(textEdit->textCursor().hasSelection());
        copyAction->setEnabled(textEdit->textCursor().hasSelection());
        pasteAction->setEnabled(!QApplication::clipboard()->text().isEmpty());
    } else {
        undoAction->setEnabled(false);
        redoAction->setEnabled(false);
        cutAction->setEnabled(false);
        copyAction->setEnabled(false);
        pasteAction->setEnabled(false);
    }

    fontAction->setEnabled(hasActiveTab);
    findAction->setEnabled(hasActiveTab);
    findReplaceAction->setEnabled(hasActiveTab);
}

void TextEditor::updateWindowMenu() {
    windowMenu->clear();
    windowMenu->addAction(nextAction);
    windowMenu->addAction(previousAction);
    windowMenu->addSeparator();
    windowMenu->addAction(closeAllAction);

    if (tabWidget->count() > 0) {
        windowMenu->addSeparator();

        for (int i = 0; i < tabWidget->count(); ++i) {
            QString title = tabWidget->tabText(i);
            if (title.length() > 20) {
                title = title.left(17) + "...";
            }

            QAction *action = windowMenu->addAction(tr("&%1 %2").arg(i + 1).arg(title));
            action->setCheckable(true);
            action->setChecked(i == tabWidget->currentIndex());
            connect(action, &QAction::triggered, [this, i] {
                tabWidget->setCurrentIndex(i);
            });
        }
    }
}

void TextEditor::createNewDocument(const QString &title) {
    QTextEdit *textEdit = new QTextEdit();
    textEdit->setFont(defaultFont);
    connect(textEdit, &QTextEdit::textChanged, this, &TextEditor::documentWasModified);
    connect(textEdit, &QTextEdit::cursorPositionChanged, this, &TextEditor::updateCursorPosition);

    int index = tabWidget->addTab(textEdit, title);
    tabWidget->setCurrentIndex(index);
    tabWidget->setTabToolTip(index, title);

    updateMenus();
    updateCursorPosition();
    updateFontInfo();
}

void TextEditor::documentWasModified() {
    if (tabWidget->count() == 0) return;

    QTextEdit *textEdit = currentTextEdit();
    QString title = tabWidget->tabText(tabWidget->currentIndex());
    if (textEdit->document()->isModified()) {
        if (!title.endsWith("*")) {
            tabWidget->setTabText(tabWidget->currentIndex(), title + "*");
        }
    } else {
        if (title.endsWith("*")) {
            tabWidget->setTabText(tabWidget->currentIndex(), title.left(title.length() - 1));
        }
    }
}

void TextEditor::updateCursorPosition() {
    if (tabWidget->count() == 0) {
        cursorPositionLabel->setText("");
        return;
    }

    QTextEdit *textEdit = currentTextEdit();
    QTextCursor cursor = textEdit->textCursor();
    int line = cursor.blockNumber() + 1;
    int column = cursor.columnNumber() + 1;

    int wordCount = textEdit->toPlainText().split(QRegularExpression("\\s+"), Qt::SkipEmptyParts).count();

    cursorPositionLabel->setText(QString("行: %1, 列: %2 | 字数: %3").arg(line).arg(column).arg(wordCount));
}

void TextEditor::updateFontInfo() {
    if (tabWidget->count() == 0) {
        fontInfoLabel->setText("");
        return;
    }

    QTextEdit *textEdit = currentTextEdit();
    QFont font = textEdit->font();

    QString style;
    if (font.bold() && font.italic()) style = "粗体 斜体";
    else if (font.bold()) style = "粗体";
    else if (font.italic()) style = "斜体";
    else style = "常规";

    fontInfoLabel->setText(QString("%1, %2pt, %3")
                          .arg(font.family())
                          .arg(font.pointSize())
                          .arg(style));
}

void TextEditor::openFileFromTree(const QModelIndex &index) {
    QString filePath = fileModel->filePath(index);
    if (QFileInfo(filePath).isFile()) {
        openFile(filePath);
    }
}

void TextEditor::toggleSidebar() {
    treeView->setVisible(!treeView->isVisible());
}

void TextEditor::open() {
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", "", "文本文件 (*.txt);;所有文件 (*.*)");
    if (!fileName.isEmpty()) {
        openFile(fileName);
    }
}

bool TextEditor::save() {
    if (tabWidget->count() == 0) return false;

    QTextEdit *textEdit = currentTextEdit();
    QString fileName = tabWidget->tabToolTip(tabWidget->currentIndex());

    if (fileName.isEmpty() || fileName == "未命名") {
        return saveAs();
    }

    return saveFile(fileName, textEdit);
}

bool TextEditor::saveAs() {
    if (tabWidget->count() == 0) return false;

    QTextEdit *textEdit = currentTextEdit();
    QString fileName = QFileDialog::getSaveFileName(this, "另存为", "", "文本文件 (*.txt);;所有文件 (*.*)");
    if (fileName.isEmpty()) return false;

    return saveFile(fileName, textEdit);
}

void TextEditor::closeTab(int index) {
    if (index < 0 || index >= tabWidget->count()) return;

    QTextEdit *textEdit = qobject_cast<QTextEdit*>(tabWidget->widget(index));
    if (textEdit && textEdit->document()->isModified()) {
        QString title = tabWidget->tabText(index).replace("*", "");
        QMessageBox::StandardButton ret = QMessageBox::warning(this, "文档已修改",
            QString("文档 \"%1\" 已被修改，是否保存更改?").arg(title),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (ret == QMessageBox::Save) {
            if (!saveFile(tabWidget->tabToolTip(index), textEdit)) {
                return;
            }
        } else if (ret == QMessageBox::Cancel) {
            return;
        }
    }

    tabWidget->removeTab(index);
    if (tabWidget->count() == 0) {
        updateMenus();
        updateCursorPosition();
        updateFontInfo();
    }
}

void TextEditor::closeAllTabs() {
    while (tabWidget->count() > 0) {
        closeTab(0);
    }
}

void TextEditor::selectFont() {
    if (tabWidget->count() == 0) return;

    QTextEdit *textEdit = currentTextEdit();
    bool ok;

    QFont initialFont = textEdit->font();
    QFont font = QFontDialog::getFont(&ok, initialFont, this, "选择字体");

    if (ok) {
        textEdit->setFont(font);
        defaultFont = font;
        updateFontInfo();
    }
}

void TextEditor::undo() {
    if (tabWidget->count() > 0) {
        currentTextEdit()->undo();
    }
}

void TextEditor::redo() {
    if (tabWidget->count() > 0) {
        currentTextEdit()->redo();
    }
}

void TextEditor::cut() {
    if (tabWidget->count() > 0) {
        currentTextEdit()->cut();
    }
}

void TextEditor::copy() {
    if (tabWidget->count() > 0) {
        currentTextEdit()->copy();
    }
}

void TextEditor::paste() {
    if (tabWidget->count() > 0) {
        currentTextEdit()->paste();
    }
}

void TextEditor::openFile(const QString &fileName) {
    for (int i = 0; i < tabWidget->count(); ++i) {
        if (tabWidget->tabToolTip(i) == fileName) {
            tabWidget->setCurrentIndex(i);
            return;
        }
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开文件: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    QTextEdit *textEdit = new QTextEdit();
    textEdit->setFont(defaultFont);
    textEdit->setPlainText(content);
    connect(textEdit, &QTextEdit::textChanged, this, &TextEditor::documentWasModified);
    connect(textEdit, &QTextEdit::cursorPositionChanged, this, &TextEditor::updateCursorPosition);

    QString title = QFileInfo(fileName).fileName();
    int index = tabWidget->addTab(textEdit, title);
    tabWidget->setCurrentIndex(index);
    tabWidget->setTabToolTip(index, fileName);

    updateMenus();
    updateCursorPosition();
    updateFontInfo();
}

void TextEditor::newFile() {
    createNewDocument();
}

void TextEditor::about() {
    QString themeName;
    switch (currentTheme) {
    case LightGreen: themeName = "淡绿色主题"; break;
    case DarkMode: themeName = "深色模式"; break;
    case LightBlue: themeName = "浅蓝色主题"; break;
    case Classic: themeName = "经典主题"; break;
    case Original: themeName = "原始主题"; break;
    }

    QMessageBox::about(this, "关于文本编辑器",
        QString("<h2>Qt文本编辑器</h2>"
        "<p>版本 3.0</p>"
        "<p>使用Qt 6开发的Tab式文本编辑器</p>"
        "<p>当前主题: <b>%1</b></p>"
        "<p>支持多文档编辑、文件管理和主题切换</p>"
        "<p>提供4种主题选择，满足不同需求</p>").arg(themeName));
}

void TextEditor::showFindReplaceDialog() {
    QTextEdit *textEdit = currentTextEdit();
    if (!textEdit) return;

    searchCursor = QTextCursor();

    if (textEdit->textCursor().hasSelection()) {
        findLineEditR->setText(textEdit->textCursor().selectedText());
    }

    findReplaceDialog->show();
    findLineEditR->setFocus();
    findLineEditR->selectAll();
}

void TextEditor::showFindDialog() {
    QTextEdit *textEdit = currentTextEdit();
    if (!textEdit) return;

    searchCursor = QTextCursor();

    if (textEdit->textCursor().hasSelection()) {
        findLineEdit->setText(textEdit->textCursor().selectedText());
    }

    findDialog->show();
    findLineEdit->setFocus();
    findLineEdit->selectAll();
}

void TextEditor::updateFindButtons() {
    bool hasTextR = !findLineEditR->text().isEmpty();
    bool hasText = !findLineEdit->text().isEmpty();
    findNextButton->setEnabled(hasText);
    findPrevButton->setEnabled(hasText);
    findNextButtonR->setEnabled(hasTextR);
    findPrevButtonR->setEnabled(hasTextR);
    replaceButtonR->setEnabled(hasTextR);
}

QTextDocument::FindFlags TextEditor::getFindFlags() {
    QTextDocument::FindFlags flags;
    if (caseSensitiveCheckR->isChecked())
        flags |= QTextDocument::FindCaseSensitively;
    if (wholeWordCheckR->isChecked())
        flags |= QTextDocument::FindWholeWords;
    return flags;
}

void TextEditor::findNext() {
    QTextEdit *textEdit = currentTextEdit();
    if (!textEdit) return;

    QString searchText = (findLineEditR->isVisible() ? findLineEditR : findLineEdit)->text();

    if (searchText.isEmpty()) return;
    QTextDocument::FindFlags flags = getFindFlags();

    if (searchCursor.isNull() || searchCursor.document() != textEdit->document()) {
        searchCursor = QTextCursor(textEdit->document());
        searchCursor.movePosition(QTextCursor::Start);
    }

    QTextCursor foundCursor = textEdit->document()->find(searchText, searchCursor, flags);

    if (!foundCursor.isNull()) {
        textEdit->setTextCursor(foundCursor);
        searchCursor = foundCursor;
        searchCursor.setPosition(foundCursor.position() + 1);
    } else {
        searchCursor = QTextCursor(textEdit->document());
        searchCursor.movePosition(QTextCursor::Start);
        foundCursor = textEdit->document()->find(searchText, searchCursor, flags);

        if (!foundCursor.isNull()) {
            textEdit->setTextCursor(foundCursor);
            searchCursor = foundCursor;
            searchCursor.setPosition(foundCursor.position() + 1);
        } else {
            QMessageBox::information(this, "查找", QString("未找到 \"%1\"").arg(searchText));
            searchCursor = QTextCursor();
        }
    }
}

void TextEditor::findPrevious() {
    QTextEdit *textEdit = currentTextEdit();
    if (!textEdit) return;

    QString searchText = findLineEditR->text();
    if (searchText.isEmpty()) return;

    QTextDocument::FindFlags flags = getFindFlags();
    flags |= QTextDocument::FindBackward;

    if (searchCursor.isNull() || searchCursor.document() != textEdit->document()) {
        searchCursor = QTextCursor(textEdit->document());
        searchCursor.movePosition(QTextCursor::End);
    }

    QTextCursor foundCursor = textEdit->document()->find(searchText, searchCursor, flags);

    if (!foundCursor.isNull()) {
        textEdit->setTextCursor(foundCursor);
        searchCursor = foundCursor;
        searchCursor.setPosition(foundCursor.position() - 1);
    } else {
        searchCursor = QTextCursor(textEdit->document());
        searchCursor.movePosition(QTextCursor::End);
        foundCursor = textEdit->document()->find(searchText, searchCursor, flags);

        if (!foundCursor.isNull()) {
            textEdit->setTextCursor(foundCursor);
            searchCursor = foundCursor;
            searchCursor.setPosition(foundCursor.position() - 1);
        } else {
            QMessageBox::information(this, "查找", QString("未找到 \"%1\"").arg(searchText));
            searchCursor = QTextCursor();
        }
    }
}

void TextEditor::replace() {
    QTextEdit *textEdit = currentTextEdit();
    if (!textEdit) return;

    QTextCursor cursor = textEdit->textCursor();

    if (cursor.hasSelection()) {
        cursor.insertText(replaceLineEditR->text());
    }

    findNext();
}

void TextEditor::replaceAll() {
    QTextEdit *textEdit = currentTextEdit();
    if (!textEdit) return;

    QString searchText = findLineEditR->text();
    QString replaceText = replaceLineEditR->text();

    if (searchText.isEmpty()) return;

    searchCursor = QTextCursor();

    QTextDocument::FindFlags flags = getFindFlags();

    QTextCursor originalCursor = textEdit->textCursor();

    QTextCursor cursor = textEdit->textCursor();
    cursor.beginEditBlock();
    cursor.movePosition(QTextCursor::Start);
    textEdit->setTextCursor(cursor);

    int replaceCount = 0;
    bool found = true;

    while (found) {
        QTextCursor foundCursor = textEdit->document()->find(searchText, cursor, flags);
        if (!foundCursor.isNull()) {
            foundCursor.beginEditBlock();
            foundCursor.insertText(replaceText);
            foundCursor.endEditBlock();
            replaceCount++;

            cursor = foundCursor;
            cursor.setPosition(cursor.position());
        } else {
            found = false;
        }
    }

    cursor.endEditBlock();

    textEdit->setTextCursor(originalCursor);

    QMessageBox::information(this, "替换完成",
                            QString("已替换 %1 处匹配项").arg(replaceCount));
}

void TextEditor::showTreeContextMenu(const QPoint &pos) {
    currentTreeIndex = treeView->indexAt(pos);

    QMenu menu;
    QAction *newFileAction = menu.addAction("新建文件");
    connect(newFileAction, &QAction::triggered, this, &TextEditor::createNewFileInTree);

    QAction *newFolderAction = menu.addAction("新建文件夹");
    connect(newFolderAction, &QAction::triggered, this, &TextEditor::createNewFolderInTree);

    menu.addSeparator();

    QAction *renameAction = menu.addAction("重命名");
    connect(renameAction, &QAction::triggered, this, &TextEditor::renameInTree);

    QAction *deleteAction = menu.addAction("删除");
    connect(deleteAction, &QAction::triggered, this, &TextEditor::deleteInTree);

    menu.exec(treeView->viewport()->mapToGlobal(pos));
}

void TextEditor::createNewFileInTree() {
    QString dirPath;

    if (currentTreeIndex.isValid()) {
        if (fileModel->isDir(currentTreeIndex)) {
            dirPath = fileModel->filePath(currentTreeIndex);
        } else {
            dirPath = fileModel->filePath(currentTreeIndex.parent());
        }
    } else {
        dirPath = fileModel->rootPath();
        if (dirPath.isEmpty()) {
            dirPath = QDir::homePath();
        }
    }

    QString newFileName = "新建文件.txt";
    QString newFilePath = QDir(dirPath).filePath(newFileName);
    int count = 1;
    while (QFile::exists(newFilePath)) {
        newFileName = QString("新建文件(%1).txt").arg(count++);
        newFilePath = QDir(dirPath).filePath(newFileName);
    }

    QFile file(newFilePath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "错误", "无法创建文件: " + file.errorString());
        return;
    }
    file.close();

    QModelIndex parentIndex = fileModel->index(dirPath);
    fileModel->fetchMore(parentIndex);

    QTimer::singleShot(100, this, [this, newFilePath]() {
        QModelIndex newIndex = fileModel->index(newFilePath);
        if (newIndex.isValid()) {
            treeView->setCurrentIndex(newIndex);
            treeView->edit(newIndex);
        }
    });
}

void TextEditor::createNewFolderInTree() {
    QString dirPath;

    if (currentTreeIndex.isValid()) {
        if (fileModel->isDir(currentTreeIndex)) {
            dirPath = fileModel->filePath(currentTreeIndex);
        } else {
            dirPath = fileModel->filePath(currentTreeIndex.parent());
        }
    } else {
        dirPath = fileModel->rootPath();
        if (dirPath.isEmpty()) {
            dirPath = QDir::homePath();
        }
    }

    QString newFolderName = "新建文件夹";
    QString newFolderPath = QDir(dirPath).filePath(newFolderName);
    int count = 1;
    while (QFile::exists(newFolderPath)) {
        newFolderName = QString("新建文件夹(%1)").arg(count++);
        newFolderPath = QDir(dirPath).filePath(newFolderName);
    }

    QDir dir;
    if (!dir.mkdir(newFolderPath)) {
        QMessageBox::critical(this, "错误", "无法创建文件夹");
        return;
    }

    QModelIndex parentIndex = fileModel->index(dirPath);
    fileModel->fetchMore(parentIndex);

    QTimer::singleShot(100, this, [this, newFolderPath]() {
        QModelIndex newIndex = fileModel->index(newFolderPath);
        if (newIndex.isValid()) {
            treeView->setCurrentIndex(newIndex);
            treeView->edit(newIndex);
        }
    });
}

void TextEditor::renameInTree() {
    if (!currentTreeIndex.isValid()) return;

    QString path = fileModel->filePath(currentTreeIndex);
    QString name = fileModel->fileName(currentTreeIndex);

    bool ok;
    QString newName = QInputDialog::getText(
        this,
        "重命名",
        "请输入新的名称:",
        QLineEdit::Normal,
        name,
        &ok
    );

    if (!ok || newName.isEmpty() || newName == name)
        return;

    QFileInfo fi(path);
    QString newPath = fi.path() + "/" + newName;

    if (QFile::exists(newPath)) {
        QMessageBox::critical(this, "错误", "已存在同名文件或文件夹");
        return;
    }

    QFile file(path);
    if (!file.rename(newPath)) {
        QMessageBox::critical(this, "错误",
            QString("重命名失败: %1").arg(file.errorString()));
    }
}

void TextEditor::deleteInTree() {
    if (!currentTreeIndex.isValid()) {
        return;
    }

    QString path = fileModel->filePath(currentTreeIndex);
    QString name = fileModel->fileName(currentTreeIndex);

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "删除",
                                QString("确定要永久删除 \"%1\" 吗？").arg(name),
                                QMessageBox::Yes | QMessageBox::No,
                                QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        bool success = false;
        QFileInfo fileInfo(path);

        if (fileInfo.isDir()) {
            QDir dir(path);
            success = dir.removeRecursively();
        } else {
            success = QFile::remove(path);
        }

        if (!success) {
            QMessageBox::critical(this, "错误", "删除操作失败");
        }
    }
}

bool TextEditor::saveFile(const QString &fileName, QTextEdit *textEdit) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法保存文件: " + file.errorString());
        return false;
    }

    QTextStream out(&file);
    out << textEdit->toPlainText();
    file.close();

    QString title = QFileInfo(fileName).fileName();
    int index = tabWidget->currentIndex();
    tabWidget->setTabText(index, title);
    tabWidget->setTabToolTip(index, fileName);

    textEdit->document()->setModified(false);
    documentWasModified();

    return true;
}

void TextEditor::readSettings() {
    QSettings settings("Company", "TextEditor");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(800, 600)).toSize();

    currentTheme = static_cast<Theme>(settings.value("theme", Classic).toInt());

    QString fontFamily = settings.value("fontFamily", "Consolas").toString();
    int fontSize = settings.value("fontSize", 10).toInt();
    bool fontBold = settings.value("fontBold", false).toBool();
    bool fontItalic = settings.value("fontItalic", false).toBool();

    defaultFont = QFont(fontFamily, fontSize);
    defaultFont.setBold(fontBold);
    defaultFont.setItalic(fontItalic);

    move(pos);
    resize(size);
    treeView->setVisible(true);

    if (settings.contains("splitterState")) {
        mainSplitter->restoreState(settings.value("splitterState").toByteArray());
    }
}

void TextEditor::writeSettings() {
    QSettings settings("Company", "TextEditor");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("theme", currentTheme);

    settings.setValue("fontFamily", defaultFont.family());
    settings.setValue("fontSize", defaultFont.pointSize());
    settings.setValue("fontBold", defaultFont.bold());
    settings.setValue("fontItalic", defaultFont.italic());

    settings.setValue("splitterState", mainSplitter->saveState());
}

void TextEditor::closeEvent(QCloseEvent *event) {
    closeAllTabs();
    if (tabWidget->count() > 0) {
        event->ignore();
    } else {
        writeSettings();
        event->accept();
    }
}