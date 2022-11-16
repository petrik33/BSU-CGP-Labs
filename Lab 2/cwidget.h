#ifndef CWIDGET_H
#define CWIDGET_H

#include <QWidget>
#include <QListView>
#include <QUrl>
#include <QDesktopServices>
#include <QLineEdit>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include <QFileSystemModel>
#include <QImageWriter>
#include <QFileDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>

#include "qtablewidgetintitem.h"

enum PARAM {
    NAME,
    SIZE,
    COMPRESSION,
    COLOR_DEPTH,
    RESOLUTION,
    NUM
};

const int PARAM_NUM = int(PARAM::NUM);

const QVector<QString> PARAM_NAMES = {
    "File Name",
    "File Size",
    "Compression",
    "Color Depth",
    "Resolution"
};

//Grid Values Order
// Y - X - Height - Width
enum GRID {
    Y,
    X,
    HEIGHT,
    WIDTH
};

const int gridListView[] = {1,0,10,10};
const int gridBackButton[] = {0,0,1,1};
const int gridLdtPath[] = {0,1,1,gridListView[WIDTH]-1};
const int gridSortButton[] = {0,gridListView[WIDTH],1,2};

const int gridWidth = 12;
const int gridHeight = 12;


class CWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CWidget(QWidget *parent = nullptr);
public slots:
    void on_listView_doubleClicked(const QModelIndex &index);
    void onBackButtonClicked(bool clicked);
    void onPathEntered(const QModelIndex &index);
    void onMultiChoiceCliked();
protected:
    QDir currentFolder;
    QGridLayout* mLayout = nullptr;
    QListView* listView = nullptr;
    QLineEdit* ldtPath = nullptr;
    QPushButton* multiChoiceButton = nullptr;
    QPushButton* backButton = nullptr;
    QFileSystemModel *model = nullptr;
    QVector<QLabel*> lblParams;
    QVector<QLineEdit*> ldtParams;
    QTableWidget* twInfo = nullptr;
    void layoutAddWidget(QWidget* widget, const int layoutValues[]);
    int gridParams[4] = {1,gridLdtPath[WIDTH] + 1,1,2};
    bool sortAscending = false;
protected slots:
    void cdUP();
    void toRoot();
    void updatePath();
    void dialogClose();
    void multichoiceSort(int index);
};

#endif // CWIDGET_H
