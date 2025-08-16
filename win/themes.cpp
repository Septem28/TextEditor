#include "themes.h"

//TODO: Implement the themes in a more structured way, possibly using QSS files or a theme manager.
QString getLightGreenTheme() {
    return R"(
        /* 淡绿色主题 */
        QMainWindow {
            background-color: #f0f9f0;
        }

        QMenuBar {
            background-color: #e0f2e0;
            border-bottom: 1px solid #c0e0c0;
            padding: 4px;
            color: #2c5f2c;
        }

        QMenuBar::item {
            background: transparent;
            padding: 4px 8px;
            border-radius: 4px;
            color: #2c5f2c;
        }

        QMenuBar::item:selected {
            background: #d0e8d0;
            color: #1e441e;
        }

        QMenuBar::item:pressed {
            background: #c0e0c0;
        }

        QMenu {
            background-color: #f0f9f0;
            border: 1px solid #c0e0c0;
            padding: 4px;
            color: #2c5f2c;
        }

        QMenu::item {
            padding: 6px 24px 6px 20px;
            background-color: transparent;
        }

        QMenu::item:selected {
            background-color: #d8f0d8;
            color: #1e441e;
        }

        QMenu::item:disabled {
            color: #a0c0a0;
        }

        QMenu::separator {
            height: 1px;
            background: #d0e8d0;
            margin: 4px 0;
        }

        QToolButton {
            background: transparent;
            border: 1px solid transparent;
            border-radius: 4px;
            padding: 4px;
        }

        QToolButton:hover {
            background: #d8f0d8;
            border: 1px solid #b0d8b0;
        }

        QToolButton:pressed {
            background: #c0e0c0;
        }

        QListView {
            background: #f0f9f0;
            border: 1px solid #c0e0c0;
            border-radius: 4px;
            color: #2c5f2c;
            font-family: 'Microsoft YaHei UI';
            font-size: 10pt;
        }

        QListView::item {
            padding: 4px 1px;
            border: none;
            color: #2c5f2c;
        }

        QListView::item:selected {
            background: #c0e0c0;
            color: #1e441e;
        }

        QListView::item:hover {
            background: #d8f0d8;
        }

        QScrollBar:vertical {
            border: 1px solid #c0e0c0;
            background: #f0f9f0;
            width: 16px;
        }

        QScrollBar::handle:vertical {
            background: #c0e0c0;
            min-height: 20px;
            border-radius: 4px;
        }

        QScrollBar::handle:vertical:hover {
            background: #b0d8b0;
        }

        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            background: #f0f9f0;
            height: 0px;
        }

        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: #f0f9f0;
        }

        QScrollBar:horizontal {
            border: 1px solid #c0e0c0;
            background: #f0f9f0;
            height: 16px;
        }

        QScrollBar::handle:horizontal {
            background: #c0e0c0;
            min-width: 20px;
            border-radius: 4px;
        }

        QScrollBar::handle:horizontal:hover {
            background: #b0d8b0;
        }

        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
            background: #f0f9f0;
            width: 0px;
        }

        QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
            background: #f0f9f0;
        }

        QComboBox {
            background-color: #f8fdf8;
            border: 1px solid #c0e0c0;
            border-radius: 4px;
            padding: 4px;
            color: #2c5f2c;
            font-family: 'Microsoft YaHei UI';
        }

        QComboBox::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 20px;
            border-left: 1px solid #c0e0c0;
        }

        QTabWidget::pane {
            border: 1px solid #c0e0c0;
            background: #f8fdf8;
        }

        QTabBar::tab {
            background: #e0f2e0;
            border: 1px solid #c0e0c0;
            border-bottom: none;
            padding: 6px 12px;
            margin-right: 2px;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
            color: #2c5f2c;
        }

        QTabBar::tab:selected {
            background: #f8fdf8;
            border-bottom-color: #f8fdf8;
            margin-bottom: -1px;
            color: #1e441e;
            font-weight: bold;
        }

        QTabBar::tab:!selected:hover {
            background: #d0e8d0;
        }

        QStatusBar {
            background-color: #e0f2e0;
            border-top: 1px solid #c0e0c0;
            color: #2c5f2c;
        }

        #statusLabel {
            padding: 0 8px;
            color: #3a703a;
        }

        QTextEdit {
            background-color: #f8fdf8;
            color: #1e441e;
            font-family: 'Consolas', 'Microsoft YaHei UI';
            font-size: 12pt;
            selection-background-color: #a0d0a0;
            selection-color: black;
        }

        #fileTreeView {
            background-color: #f0f9f0;
            border: none;
            border-right: 1px solid #d0e8d0;
            font-family: 'Microsoft YaHei UI';
            font-size: 10pt;
            color: #2c5f2c;
            alternate-background-color: #e8f5e8;
        }

        #fileTreeView::item {
            padding: 4px 1px;
            border: none;
            color: #2c5f2c;
        }

        #fileTreeView::item:selected {
            background: #c0e0c0;
            color: #1e441e;
        }

        #fileTreeView::item:hover {
            background: #d8f0d8;
        }

        QDialog {
            background-color: #f0f9f0;
        }

        QLabel {
            color: #2c5f2c;
        }

        QLineEdit, QTextEdit {
            background: white;
            border: 1px solid #b0d8b0;
            border-radius: 3px;
            padding: 4px;
            font-family: 'Microsoft YaHei UI';
            color: #1e441e;
        }

        QLineEdit:focus, QTextEdit:focus {
            border: 1px solid #80c080;
        }

        QPushButton {
            background-color: #e0f2e0;
            border: 1px solid #b0d8b0;
            border-radius: 4px;
            padding: 6px 12px;
            font-family: 'Microsoft YaHei UI';
            min-width: 80px;
            color: #2c5f2c;
        }

        QPushButton:hover {
            background-color: #d0e8d0;
            border: 1px solid #a0d0a0;
        }

        QPushButton:pressed {
            background-color: #c0e0c0;
        }

        QPushButton:disabled {
            color: #a0c0a0;
            background-color: #e8f5e8;
        }

        QCheckBox {
            spacing: 5px;
            color: #2c5f2c;
            font-family: 'Microsoft YaHei UI';
        }

        QCheckBox::indicator {
            width: 16px;
            height: 16px;
        }

        QCheckBox::indicator:unchecked {
            border: 1px solid #b0d8b0;
            background: white;
        }

        QCheckBox::indicator:checked {
            border: 1px solid #80c080;
            background: #a0d0a0;
        }

        QSplitter::handle {
            background: #d0e8d0;
            width: 3px;
        }

        QSplitter::handle:hover {
            background: #c0e0c0;
        }

        #toolbarContainer {
            background: transparent;
        }

        QMessageBox {
            background-color: #f0f9f0;
        }

        QMessageBox QLabel {
            color: #2c5f2c;
        }

        QMessageBox QPushButton {
            background-color: #e0f2e0;
            border: 1px solid #b0d8b0;
            color: #2c5f2c;
            min-width: 80px;
        }

        QMessageBox QPushButton:hover {
            background-color: #d0e8d0;
        }
    )";
}

//TODO: Implement the dark theme and light blue theme in a similar structured way.
QString getDarkTheme() {
    return R"(
        /* 深色主题 */
        QMainWindow {
            background-color: #2d2d2d;
        }

        QMenuBar {
            background-color: #252526;
            border-bottom: 1px solid #1e1e1e;
            padding: 4px;
            color: #d4d4d4;
        }

        QMenuBar::item {
            background: transparent;
            padding: 4px 8px;
            border-radius: 4px;
            color: #d4d4d4;
        }

        QMenuBar::item:selected {
            background: #3c3c3c;
            color: #ffffff;
        }

        QMenuBar::item:pressed {
            background: #1e1e1e;
        }

        QMenu {
            background-color: #252526;
            border: 1px solid #1e1e1e;
            padding: 4px;
            color: #d4d4d4;
        }

        QMenu::item {
            padding: 6px 24px 6px 20px;
            background-color: transparent;
        }

        QMenu::item:selected {
            background-color: #094771;
            color: #ffffff;
        }

        QMenu::item:disabled {
            color: #6d6d6d;
        }

        QMenu::separator {
            height: 1px;
            background: #3c3c3c;
            margin: 4px 0;
        }

        QToolButton {
            background: transparent;
            border: 1px solid transparent;
            border-radius: 4px;
            padding: 4px;
        }


        QToolButton:hover {
            background: #3c3c3c;
            border: 1px solid #5a5a5a;
        }

        QToolButton:pressed {
            background: #1e1e1e;
        }

        QListView {
            background: #252526;
            border: 1px solid #1e1e1e;
            color: #d4d4d4;
            font-family: 'Microsoft YaHei UI';
            font-size: 10pt;
        }

        QListView::item {
            padding: 4px 1px;
            border: none;
            color: #d4d4d4;
        }

        QListView::item:selected {
            background: #094771;
            color: #ffffff;
        }

        QListView::item:hover {
            background: #3c3c3c;
        }

        QScrollBar:vertical {
            border: 1px solid #1e1e1e;
            background: #252526;
            width: 16px;
        }

        QScrollBar::handle:vertical {
            background: #3c3c3c;
            min-height: 20px;
            border-radius: 4px;
        }

        QScrollBar::handle:vertical:hover {
            background: #5a5a5a;
        }

        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            background: #252526;
            height: 0px;
        }

        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: #252526;
        }

        QScrollBar:horizontal {
            border: 1px solid #1e1e1e;
            background: #252526;
            height: 16px;
        }

        QScrollBar::handle:horizontal {
            background: #3c3c3c;
            min-width: 20px;
            border-radius: 4px;
        }

        QScrollBar::handle:horizontal:hover {
            background: #5a5a5a;
        }

        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
            background: #252526;
            width: 0px;
        }

        QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
            background: #252526;
        }

        QComboBox {
            background-color: #333333;
            border: 1px solid #5a5a5a;
            border-radius: 4px;
            padding: 4px;
            color: #d4d4d4;
            font-family: 'Microsoft YaHei UI';
        }

        QComboBox::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 20px;
            border-left: 1px solid #5a5a5a;
        }

        QTabWidget::pane {
            border: 1px solid #1e1e1e;
            background: #1e1e1e;
        }

        QTabBar::tab {
            background: #252526;
            border: 1px solid #1e1e1e;
            border-bottom: none;
            padding: 6px 12px;
            margin-right: 2px;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
            color: #d4d4d4;
        }

        QTabBar::tab:selected {
            background: #1e1e1e;
            border-bottom-color: #1e1e1e;
            margin-bottom: -1px;
            color: #ffffff;
            font-weight: bold;
        }

        QTabBar::tab:!selected:hover {
            background: #3c3c3c;
        }

        QStatusBar {
            background-color: #252526;
            border-top: 1px solid #1e1e1e;
            color: #d4d4d4;
        }

        #statusLabel {
            padding: 0 8px;
            color: #b0b0b0;
        }

        QTextEdit {
            background-color: #1e1e1e;
            color: #d4d4d4;
            font-family: 'Consolas', 'Microsoft YaHei UI';
            font-size: 12pt;
            selection-background-color: #264f78;
            selection-color: white;
        }

        #fileTreeView {
            background-color: #252526;
            border: none;
            border-right: 1px solid #1e1e1e;
            font-family: 'Microsoft YaHei UI';
            font-size: 10pt;
            color: #d4d4d4;
            alternate-background-color: #2d2d2d;
        }

        #fileTreeView::item {
            padding: 4px 1px;
            border: none;
            color: #d4d4d4;
        }

        #fileTreeView::item:selected {
            background: #094771;
            color: #ffffff;
        }

        #fileTreeView::item:hover {
            background: #3c3c3c;
        }

        QDialog {
            background-color: #252526;
        }

        QLabel {
            color: #d4d4d4;
        }

        QLineEdit, QTextEdit {
            background: #333333;
            border: 1px solid #5a5a5a;
            border-radius: 3px;
            padding: 4px;
            font-family: 'Microsoft YaHei UI';
            color: #d4d4d4;
        }

        QLineEdit:focus, QTextEdit:focus {
            border: 1px solid #0078d7;
        }

        QPushButton {
            background-color: #333333;
            border: 1px solid #5a5a5a;
            border-radius: 4px;
            padding: 6px 12px;
            font-family: 'Microsoft YaHei UI';
            min-width: 80px;
            color: #d4d4d4;
        }

        QPushButton:hover {
            background-color: #3c3c3c;
            border: 1px solid #707070;
        }

        QPushButton:pressed {
            background-color: #1e1e1e;
        }

        QPushButton:disabled {
            color: #6d6d6d;
            background-color: #2d2d2d;
        }

        QCheckBox {
            spacing: 5px;
            color: #d4d4d4;
            font-family: 'Microsoft YaHei UI';
        }

        QCheckBox::indicator {
            width: 16px;
            height: 16px;
        }

        QCheckBox::indicator:unchecked {
            border: 1px solid #5a5a5a;
            background: #333333;
        }

        QCheckBox::indicator:checked {
            border: 1px solid #5a5a5a;
            background: #0078d7;
        }

        QSplitter::handle {
            background: #3c3c3c;
            width: 3px;
        }

        QSplitter::handle:hover {
            background: #5a5a5a;
        }

        #toolbarContainer {
            background: transparent;
        }

        QMessageBox {
            background-color: #252526;
        }

        QMessageBox QLabel {
            color: #d4d4d4;
        }

        QMessageBox QPushButton {
            background-color: #333333;
            border: 1px solid #5a5a5a;
            color: #d4d4d4;
            min-width: 80px;
        }

        QMessageBox QPushButton:hover {
            background-color: #3c3c3c;
        }
    )";
}


//TODO: Implement the light blue theme in a similar structured way.
QString getLightBlueTheme() {
    return R"(
        /* 浅蓝色主题 */
        QMainWindow {
            background-color: #f0f8ff;
        }

        QMenuBar {
            background-color: #e0f0ff;
            border-bottom: 1px solid #c0d8f0;
            padding: 4px;
            color: #2a5a8c;
        }

        QMenuBar::item {
            background: transparent;
            padding: 4px 8px;
            border-radius: 4px;
            color: #2a5a8c;
        }

        QMenuBar::item:selected {
            background: #d0e8ff;
            color: #1a3a6c;
        }

        QMenuBar::item:pressed {
            background: #c0d8f0;
        }

        QMenu {
            background-color: #f0f8ff;
            border: 1px solid #c0d8f0;
            padding: 4px;
            color: #2a5a8c;
        }

        QMenu::item {
            padding: 6px 24px 6px 20px;
            background-color: transparent;
        }

        QMenu::item:selected {
            background-color: #d8e8ff;
            color: #1a3a6c;
        }

        QMenu::item:disabled {
            color: #a0b0c0;
        }

        QMenu::separator {
            height: 1px;
            background: #d0e0f0;
            margin: 4px 0;
        }

        QToolButton {
            background: transparent;
            border: 1px solid transparent;
            border-radius: 4px;
            padding: 4px;
        }

        QToolButton:hover {
            background: #d8e8ff;
            border: 1px solid #b0d0f0;
        }

        QToolButton:pressed {
            background: #c0d8f0;
        }

        QListView {
            background: #f0f8ff;
            border: 1px solid #c0d8f0;
            color: #2a5a8c;
            font-family: 'Microsoft YaHei UI';
            font-size: 10pt;
        }

        QListView::item {
            padding: 4px 1px;
            border: none;
            color: #2a5a8c;
        }

        QListView::item:selected {
            background: #c0d8f0;
            color: #1a3a6c;
        }

        QListView::item:hover {
            background: #d8e8ff;
        }

        QScrollBar:vertical {
            border: 1px solid #c0d8f0;
            background: #f0f8ff;
            width: 16px;
        }

        QScrollBar::handle:vertical {
            background: #c0d8f0;
            min-height: 20px;
            border-radius: 4px;
        }

        QScrollBar::handle:vertical:hover {
            background: #b0d0f0;
        }

        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            background: #f0f8ff;
            height: 0px;
        }

        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: #f0f8ff;
        }

        QScrollBar:horizontal {
            border: 1px solid #c0d8f0;
            background: #f0f8ff;
            height: 16px;
        }

        QScrollBar::handle:horizontal {
            background: #c0d8f0;
            min-width: 20px;
            border-radius: 4px;
        }

        QScrollBar::handle:horizontal:hover {
            background: #b0d0f0;
        }

        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
            background: #f0f8ff;
            width: 0px;
        }

        QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
            background: #f0f8ff;
        }

        QComboBox {
            background-color: #f8fcff;
            border: 1px solid #c0d8f0;
            border-radius: 4px;
            padding: 4px;
            color: #2a5a8c;
            font-family: 'Microsoft YaHei UI';
        }

        QComboBox::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 20px;
            border-left: 1px solid #c0d8f0;
        }

        QTabWidget::pane {
            border: 1px solid #c0d8f0;
            background: #f8fcff;
        }

        QTabBar::tab {
            background: #e0f0ff;
            border: 1px solid #c0d8f0;
            border-bottom: none;
            padding: 6px 12px;
            margin-right: 2px;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
            color: #2a5a8c;
        }

        QTabBar::tab:selected {
            background: #f8fcff;
            border-bottom-color: #f8fcff;
            margin-bottom: -1px;
            color: #1a3a6c;
            font-weight: bold;
        }

        QTabBar::tab:!selected:hover {
            background: #d0e8ff;
        }

        QStatusBar {
            background-color: #e0f0ff;
            border-top: 1px solid #c0d8f0;
            color: #2a5a8c;
        }

        #statusLabel {
            padding: 0 8px;
            color: #3a6a9c;
        }

        QTextEdit {
            background-color: #f8fcff;
            color: #1a3a6c;
            font-family: 'Consolas', 'Microsoft YaHei UI';
            font-size: 12pt;
            selection-background-color: #a0c8ff;
            selection-color: black;
        }

        #fileTreeView {
            background-color: #f0f8ff;
            border: none;
            border-right: 1px solid #d0e0f0;
            font-family: 'Microsoft YaHei UI';
            font-size: 10pt;
            color: #2a5a8c;
            alternate-background-color: #e8f4ff;
        }

        #fileTreeView::item {
            padding: 4px 1px;
            border: none;
            color: #2a5a8c;
        }

        #fileTreeView::item:selected {
            background: #c0d8f0;
            color: #1a3a6c;
        }

        #fileTreeView::item:hover {
            background: #d8e8ff;
        }

        QDialog {
            background-color: #f0f8ff;
        }

        QLabel {
            color: #2a5a8c;
        }

        QLineEdit, QTextEdit {
            background: white;
            border: 1px solid #b0d0f0;
            border-radius: 3px;
            padding: 4px;
            font-family: 'Microsoft YaHei UI';
            color: #1a3a6c;
        }

        QLineEdit:focus, QTextEdit:focus {
            border: 1px solid #80a8e0;
        }

        QPushButton {
            background-color: #e0f0ff;
            border: 1px solid #b0d0f0;
            border-radius: 4px;
            padding: 6px 12px;
            font-family: 'Microsoft YaHei UI';
            min-width: 80px;
            color: #2a5a8c;
        }

        QPushButton:hover {
            background-color: #d0e8ff;
            border: 1px solid #a0c0e0;
        }

        QPushButton:pressed {
            background-color: #c0d8f0;
        }

        QPushButton:disabled {
            color: #a0b0c0;
            background-color: #e8f4ff;
        }

        QCheckBox {
            spacing: 5px;
            color: #2a5a8c;
            font-family: 'Microsoft YaHei UI';
        }

        QCheckBox::indicator {
            width: 16px;
            height: 16px;
        }

        QCheckBox::indicator:unchecked {
            border: 1px solid #b0d0f0;
            background: white;
        }

        QCheckBox::indicator:checked {
            border: 1px solid #80a8e0;
            background: #a0c8ff;
        }

        QSplitter::handle {
            background: #d0e0f0;
            width: 3px;
        }

        QSplitter::handle:hover {
            background: #c0d8f0;
        }

        #toolbarContainer {
            background: transparent;
        }

        QMessageBox {
            background-color: #f0f8ff;
        }

        QMessageBox QLabel {
            color: #2a5a8c;
        }

        QMessageBox QPushButton {
            background-color: #e0f0ff;
            border: 1px solid #b0d0f0;
            color: #2a5a8c;
            min-width: 80px;
        }

        QMessageBox QPushButton:hover {
            background-color: #d0e8ff;
        }
    )";
}


//TODO: Implement the classic theme in a similar structured way.
QString getClassicTheme() {
    return R"(
        /* 经典主题 */
        QMainWindow {
            background-color: #ffffff;
        }

        QMenuBar {
            background-color: #f0f0f0;
            border-bottom: 1px solid #d0d0d0;
            padding: 4px;
            color: #000000;
        }

        QMenuBar::item {
            background: transparent;
            padding: 4px 8px;
            border-radius: 4px;
            color: #000000;
        }

        QMenuBar::item:selected {
            background: #e0e0e0;
            color: #000000;
        }

        QMenuBar::item:pressed {
            background: #d0d0d0;
        }

        QMenu {
            background-color: #ffffff;
            border: 1px solid #d0d0d0;
            padding: 4px;
            color: #000000;
        }

        QMenu::item {
            padding: 6px 24px 6px 20px;
            background-color: transparent;
        }

        QMenu::item:selected {
            background-color: #c8c8c8;
            color: #000000;
        }

        QMenu::item:disabled {
            color: #808080;
        }

        QMenu::separator {
            height: 1px;
            background: #d0d0d0;
            margin: 4px 0;
        }

        QToolButton {
            background: transparent;
            border: 1px solid transparent;
            border-radius: 4px;
            padding: 4px;
        }

        QToolButton:hover {
            background: #e8e8e8;
            border: 1px solid #b8b8b8;
        }

        QToolButton:pressed {
            background: #d0d0d0;
        }

        QListView {
            background: #ffffff;
            border: 1px solid #d0d0d0;
            color: #000000;
            font-family: 'Microsoft YaHei UI';
            font-size: 10pt;
        }

        QListView::item {
            padding: 4px 1px;
            border: none;
            color: #000000;
        }

        QListView::item:selected {
            background: #c8c8c8;
            color: #000000;
        }

        QListView::item:hover  {
            background: #e0e0e0;
        }

        QScrollBar:vertical {
            border: 1px solid #d0d0d0;
            background: #f0f0f0;
            width: 16px;
        }

        QScrollBar::handle:vertical {
            background: #d0d0d0;
            min-height: 20px;
            border-radius: 4px;
        }

        QScrollBar::handle:vertical:hover {
            background: #b8b8b8;
        }

        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            background: #f0f0f0;
            height: 0px;
        }

        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: #f0f0f0;
        }

        QScrollBar:horizontal {
            border: 1px solid #d0d0d0;
            background: #f0f0f0;
            height: 16px;
        }

        QScrollBar::handle:horizontal {
            background: #d0d0d0;
            min-width: 20px;
            border-radius: 4px;
        }

        QScrollBar::handle:horizontal:hover {
            background: #b8b8b8;
        }

        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
            background: #f0f0f0;
            width: 0px;
        }

        QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
            background: #f0f0f0;
        }

        QComboBox {
            background-color: #f8f8f8;
            border: 1px solid #d0d0d0;
            border-radius: 4px;
            padding: 4px;
            color: #000000;
            font-family: 'Microsoft YaHei UI';
        }

        QComboBox::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 20px;
            border-left: 1px solid #d0d0d0;
        }

        QTabWidget::pane {
            border: 1px solid #d0d0d0;
            background: #f8f8f8;
        }

        QTabBar::tab {
            background: #e0e0e0;
            border: 1px solid #d0d0d0;
            border-bottom: none;
            padding: 6px 12px;
            margin-right: 2px;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
            color: #000000;
        }

        QTabBar::tab:selected {
            background: #f8f8f8;
            border-bottom-color: #f8f8f8;
            margin-bottom: -1px;
            color: #000000;
            font-weight: bold;
        }

        QTabBar::tab:!selected:hover {
            background: #d0d0d0;
        }

        QStatusBar {
            background-color: #e0e0e0;
            border-top: 1px solid #d0d0d0;
            color: #000000;
        }

        #statusLabel {
            padding: 0 8px;
            color: #404040;
        }

        QTextEdit {
            background-color: #f8f8f8;
            color: #000000;
            font-family: 'Consolas', 'Microsoft YaHei UI';
            font-size: 12pt;
            selection-background-color: #a0c0e0;
            selection-color: black;
        }

        #fileTreeView {
            background-color: #f0f0f0;
            border: none;
            border-right: 1px solid #d0d0d0;
            font-family: 'Microsoft YaHei UI';
            font-size: 10pt;
            color: #000000;
            alternate-background-color: #e8e8e8;
        }

        #fileTreeView::item {
            padding: 4px 1px;
            border: none;
            color: #000000;
        }

        #fileTreeView::item:selected {
            background: #c8c8c8;
            color: #000000;
        }

        #fileTreeView::item:hover {
            background: #e0e0e0;
        }

        QDialog {
            background-color: #f0f0f0;
        }

        QLabel {
            color: #000000;
        }

        QLineEdit, QTextEdit {
            background: white;
            border: 1px solid #b0b0b0;
            border-radius: 3px;
            padding: 4px;
            font-family: 'Microsoft YaHei UI';
            color: #000000;
        }

        QLineEdit:focus, QTextEdit:focus {
            border: 1px solid #80a0c0;
        }

        QPushButton {
            background-color: #e0e0e0;
            border: 1px solid #b0b0b0;
            border-radius: 4px;
            padding: 6px 12px;
            font-family: 'Microsoft YaHei UI';
            min-width: 80px;
            color: #000000;
        }

        QPushButton:hover {
            background-color: #d0d0d0;
            border: 1px solid #a0a0a0;
        }

        QPushButton:pressed {
            background-color: #c0c0c0;
        }

        QPushButton:disabled {
            color: #808080;
            background-color: #e8e8e8;
        }

        QCheckBox {
            spacing: 5px;
            color: #000000;
            font-family: 'Microsoft YaHei UI';
        }

        QCheckBox::indicator {
            width: 16px;
            height: 16px;
        }

        QCheckBox::indicator:unchecked {
            border: 1px solid #b0b0b0;
            background: white;
        }

        QCheckBox::indicator:checked {
            border: 1px solid #80a0c0;
            background: #a0c0e0;
        }

        QSplitter::handle {
            background: #d0d0d0;
            width: 3px;
        }

        QSplitter::handle:hover {
            background: #c0c0c0;
        }

        #toolbarContainer {
            background: transparent;
        }

        QMessageBox {
            background-color: #f0f0f0;
        }

        QMessageBox QLabel {
            color: #000000;
        }

        QMessageBox QPushButton {
            background-color: #e0e0e0;
            border: 1px solid #b0b0b0;
            color: #000000;
            min-width: 80px;
        }

        QMessageBox QPushButton:hover {
            background-color: #d0d0d0;
        }

        QMessageBox QPushButton:pressed {
            background-color: #c0c0c0;
        }

        QMessageBox QPushButton:disabled {
            color: #808080;
            background-color: #e8e8e8;
        }
    )";
}

//TODO: Implement the original theme in a similar structured way.
QString getOriginalTheme() {
    return R"(
        /* 原始主题 */
    )";
}