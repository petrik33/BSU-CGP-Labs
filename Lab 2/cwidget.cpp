#include "cwidget.h"

CWidget::CWidget(QWidget *parent) : QWidget(parent)
{
    model = new QFileSystemModel();
    model->setFilter(QDir::AllEntries);
    model->setRootPath("");

    mLayout = new QGridLayout(this);

    currentFolder = model->rootDirectory();

    ldtParams.resize(PARAM_NUM);
    lblParams.resize(PARAM_NUM);
    for(int i = 0; i < PARAM_NUM; i++) {
        QLabel* paramLbl = new QLabel(PARAM_NAMES[i]);
        lblParams[i] = paramLbl;

        layoutAddWidget(paramLbl, gridParams);
        gridParams[0] += 1;

        QLineEdit* paramLdt = new QLineEdit();
        paramLdt->setReadOnly(true);
        ldtParams[i] = paramLdt;

        layoutAddWidget(paramLdt, gridParams);
        gridParams[0] += 1; //Move next button one line down in layout
    }

    listView = new QListView();

    ldtPath = new QLineEdit();
    ldtPath->setText(currentFolder.absolutePath());

    multiChoiceButton = new QPushButton("Multi Choice");
    connect(multiChoiceButton, SIGNAL(clicked()),this,SLOT(onMultiChoiceCliked()));

    backButton = new QPushButton();
    backButton->setIcon(QIcon(":/Icons/folderup.png"));
    connect(backButton,SIGNAL(clicked(bool)),this,SLOT(onBackButtonClicked(bool)));

    listView->setModel(model);
    connect(listView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_listView_doubleClicked(QModelIndex)));

    layoutAddWidget(backButton,gridBackButton);
    layoutAddWidget(ldtPath, gridLdtPath);
    layoutAddWidget(multiChoiceButton, gridSortButton);
    layoutAddWidget(listView, gridListView);

    setLayout(mLayout);

}

void CWidget::on_listView_doubleClicked(const QModelIndex &index)
{
    QFileInfo fileInfo = model->fileInfo(index);
    if(fileInfo.fileName() == "..")
    {
        cdUP();
        return;
    }
    if (fileInfo.fileName() == ".")
    {
        toRoot();
        return;
    }
    if(fileInfo.isDir())
    {
        currentFolder.cd(fileInfo.absoluteFilePath());
        listView->setRootIndex(index);
        ldtPath->setText(model->filePath(index));
        return;
    }
    QString fileExt = model->fileName(index);
    QImageWriter a(model->filePath(index));
    QString extension = "";
    QImage img (model->filePath(index));

    for(int i = fileExt.lastIndexOf('.'); i < fileExt.size(); i++)
    {
        extension.append(fileExt[i]);
    }
    if (extension == ".JPG" || extension == ".gif" || extension == ".tif" || extension == ".bmp" ||
            extension == ".png" || extension == ".pcx" || extension == ".BMP")
    {
         ldtParams[NAME]->setText(model->fileName(index));
         ldtParams[SIZE]->setText(QString::number(img.size().width() ) + "x" + QString::number(img.size().height()));
         ldtParams[COMPRESSION]->setText(QString::number(a.compression()));
         ldtParams[COLOR_DEPTH]->setText(QString::number(img.bitPlaneCount()));
         ldtParams[RESOLUTION]->setText(QString::number(img.physicalDpiX()));
    }
}

void CWidget::onBackButtonClicked(bool clicked)
{
    cdUP();
}

void CWidget::onPathEntered(const QModelIndex &index)
{
    QString path = ldtPath->text();
    QFileInfo fileInfo = model->fileInfo(index);
    QDir temp(path);

    if (temp.exists())
    {
        QDir dir = fileInfo.dir();
        dir.cd(path);
        listView->setRootIndex(model->index(dir.absolutePath()));
    }
}

void CWidget::onMultiChoiceCliked()
{
    QFileDialog *files = new QFileDialog(nullptr,"Open Files","",
        "BMP (*.bmp);;GIF (*.gif);;ICO (*.ico);;JPEG (*.jpeg);;JPG (*.jpg);;PNG (*.png)");

    QList<QUrl> list = files->getOpenFileUrls();
    QDialog *table = new QDialog();

    table->setWindowTitle("Explorer");
    table->setWindowIcon(QPixmap(":/Icons/folder.png"));

    QGridLayout *tableLayout = new QGridLayout(table);
    table->setMinimumSize(700,700);
    twInfo = new QTableWidget(table);
    tableLayout->addWidget(twInfo);
    twInfo->setColumnCount(5);
    twInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    twInfo->setRowCount(list.size());
    twInfo->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    twInfo->setHorizontalHeaderItem(1, new QTableWidgetItem("Size"));
    twInfo->setHorizontalHeaderItem(2, new QTableWidgetItem("Extension"));
    twInfo->setHorizontalHeaderItem(3, new QTableWidgetItem("Color Depth"));
    twInfo->setHorizontalHeaderItem(4, new QTableWidgetItem("Compression"));
    twInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    twInfo->horizontalHeader()->connect(twInfo->horizontalHeader(),
        SIGNAL(sectionClicked(int)),this,SLOT(multichoiceSort(int)));

    for(int i = 0; i < list.size(); i++)
    {
        QFile temp(list[i].toLocalFile());
        QString extension = "";
        if (temp.fileName().lastIndexOf('.') == -1)
        {
            twInfo->setRowCount(twInfo->rowCount()-1);
            continue;
        }
        for(int i = temp.fileName().lastIndexOf('.'); i < temp.fileName().size(); i++)
        {
            extension.append(temp.fileName()[i]);
        }
        if (extension != ".jpg" && extension != ".gif" && extension != ".tif" && extension != ".bmp" &&
                extension != ".png" && extension != ".pcx" && extension != ".BMP") {
            twInfo->setRowCount(twInfo->rowCount()-1);
            continue;
        }
        twInfo->setItem(i, 2, new QTableWidgetItem(extension));
        QString fileName = "";
        for(int i = temp.fileName().lastIndexOf('/') + 1; i < temp.fileName().lastIndexOf('.'); i++) {
            fileName.append(temp.fileName()[i]);
        }
        twInfo->setItem(i,0,new QTableWidgetItem(fileName));
        QImage im(list[i].toLocalFile());
        QImageWriter a(list[i].toLocalFile());
        twInfo->setItem(i, 1, new QTableWidgetIntItem(double(im.size().width() * im.size().height()),
                            QString::number(im.size().width())+"x"+QString::number(im.size().height())));
        twInfo->setItem(i, 3, new QTableWidgetIntItem(QString::number(im.bitPlaneCount())));
        twInfo->setItem(i, 4, new QTableWidgetIntItem(QString::number(a.compression())));
    }
    if (twInfo->rowCount() == 0)
    {
        return;
    }
    table->show();

    connect(table, SIGNAL(rejected()), this, SLOT(dialogClose()));
    this->hide();
}

void CWidget::layoutAddWidget(QWidget* widget, const int layoutValues[])
{
    mLayout->addWidget(widget, layoutValues[0], layoutValues[1], layoutValues[2], layoutValues[3]);
}

void CWidget::cdUP()
{
    currentFolder.cdUp();
    listView->setRootIndex(model->index(currentFolder.path()));
    updatePath();
}

void CWidget::toRoot()
{
    currentFolder = model->rootDirectory();
    listView->setRootIndex(model->index(currentFolder.absolutePath()));
    updatePath();
}

void CWidget::updatePath()
{
    ldtPath->setText(currentFolder.path());
}

void CWidget::dialogClose()
{
    this->show();
}

void CWidget::multichoiceSort(int index)
{
    Qt::SortOrder order = Qt::DescendingOrder;

    if(sortAscending) {
        order = Qt::AscendingOrder;
        sortAscending = false;
    } else {
        sortAscending = true;
    }

    twInfo->sortItems(index, order);
}
