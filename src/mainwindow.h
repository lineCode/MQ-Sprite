#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QListView>
#include <QUndoStack>
#include <QMdiArea>
#include <QStackedWidget>

#include "projectmodel.h"
#include "partwidget.h"
#include "compositewidget.h"
#include "partlist.h"

class PartToolsWidget;
class CompositeToolsWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static MainWindow* Instance();
    QUndoStack* undoStack(){return mUndoStack;}

    void createActions();
    void createMenus();
    void showMessage(const QString& msg, int timeout=2000);

    // misc Command stuff
    bool renamePart(const QString& oldPartName, const QString& newPartName);

    // Notifications from commands that something has changed in the project
    void partListChanged();
    void partRenamed(const QString& oldName, const QString& newName);
    void partFrameUpdated(const QString& part, const QString& mode, int frame);
    void partFramesUpdated(const QString& part, const QString& mode);
    void partNumPivotsUpdated(const QString& part, const QString& mode);
    void partPropertiesUpdated(const QString& part);
    void partModesChanged(const QString& part);
    void partModeRenamed(const QString& partName, const QString& oldModeName, const QString& newModeName);    
    void compositeRenamed(const QString& oldName, const QString& newName);
    void compositeUpdated(const QString& compName);
    void compositeUpdatedMinorChanges(const QString& compName);
    void compPropertiesUpdated(const QString& comp);

    PartWidget* activePartWidget();
    CompositeWidget* activeCompositeWidget();

protected:
    void closeEvent(QCloseEvent* event);

public slots:
    void assetDoubleClicked(const QString& name, int type);
    void partWidgetClosed(PartWidget*);
    void openPartWidget(const QString& str);
    void compositeWidgetClosed(CompositeWidget*);
    void openCompositeWidget(const QString& str);
    void subWindowActivated(QMdiSubWindow*);
    void showViewOptionsDialog();

    // Misc actions
    void changeBackgroundColour();
    void changePivotColour();
    void setPivotsEnabled(bool);
    void setPivotsEnabledDuringPlayback(bool);
    void setDropShadowOpacity(int);
    void setDropShadowBlur(int);
    void setDropShadowXOffset(int);
    void setDropShadowYOffset(int);
    void changeDropShadowColour();
    void setOnionSkinningTransparency(int);
    void setOnionSkinningEnabledDuringPlayback(bool);

    void showAbout();
    void resetSettings();

    void newProject();
    void loadProject(const QString& fileName);
    void loadProject();
    void reloadProject();
    void saveProject();
    void saveProjectAs();

    void undoStackIndexChanged(int);
    void openEigenbom();

private:
    Ui::MainWindow *ui;
    QMdiArea* mMdiArea;
    ProjectModel* mProjectModel;
    PartList* mPartList;
    PartToolsWidget* mPartToolsWidget;
    CompositeToolsWidget* mCompositeToolsWidget;
    QDockWidget *mViewOptionsDockWidget;

    QStackedWidget *mStackedWidget;
    int mNoToolsIndex, mPToolsIndex, mCToolsIndex;

    QMultiMap<QString,PartWidget*> mPartWidgets;
    QMultiMap<QString,CompositeWidget*> mCompositeWidgets;

    QUndoStack* mUndoStack;

    QMenu *mFileMenu;
    QMenu *mEditMenu;
    QMenu *mViewMenu;
    QMenu *mHelpMenu;

    QAction* mUndoAction;
    QAction* mRedoAction;
    QAction* mAboutAction;
    QAction* mResetSettingsAction;

    bool mProjectModifiedSinceLastSave;
};

#endif // MAINWINDOW_H