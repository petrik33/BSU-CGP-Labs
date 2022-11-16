#ifndef EXPLORERWIDGET_H
#define EXPLORERWIDGET_H

#include <QDir>
#include <QModelIndex>
#include <QIcon>
#include <QFileSystemModel>


class ExplorerWidget: public QAbstractListModel
{
public:
    ExplorerWidget(QObject *parent=nullptr);
    int rowCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;

    void getFolderList(QString folderPath, QFileInfoList *dirList);

private:
    QFileSystemModel *model;
};

#endif // EXPLORERWIDGET_H
