#include "explorerwidget.h"

void ExplorerWidget::getFolderList(QString folderPath, QFileInfoList *dirList)
{
    QDir dir = QDir(folderPath);

    *dirList = dir.entryInfoList(QDir::NoDot | QDir::Files | QDir::Dirs, QDir::DirsFirst);

    beginResetModel();
        this->aDirList = dirList;
    endResetModel();

    this->aDirList = dirList;
}

ExplorerWidget::ExplorerWidget(QObject *parent) : QAbstractListModel(parent)
{
    //
}

int ExplorerWidget::rowCount(const QModelIndex &) const
{
    return this->aDirList->count();
}

QVariant ExplorerWidget::data( const QModelIndex &index, int role ) const
{

    QVariant value;

        switch ( role )
        {
            case Qt::DisplayRole: //string
            {
                value = this->aDirList->at(index.row()).fileName();
            }
            break;

            case Qt::DecorationRole: //icon
            {
                if (this->aDirList->at(index.row()).isDir()) {
                    QPixmap icon = QPixmap(":/Icons/folder.png");
                    QPixmap tmp = icon.scaled(30, 30, Qt::KeepAspectRatio);
                    value = tmp;
                    break;
                }

                if (this->aDirList->at(index.row()).isFile()) {
                    QString fileExt = this->aDirList->at(index.row()).completeSuffix();
                    QPixmap icon;
                    QPixmap tmp;
                    if (fileExt == "zip") {
                        icon = QPixmap(":/Icons/zip.png");
                        tmp = icon.scaled(30, 30, Qt::KeepAspectRatio);
                    }
                    else {
                        icon = QPixmap(":/Icons/file.png");
                        tmp = icon.scaled(30, 30, Qt::KeepAspectRatio);
                    }

                    value = tmp;
                    break;
                }

                value = this->aDirList->at(index.row()).fileName();
            }
            break;

            case Qt::UserRole: //data
            {
                value = this->aDirList->at(index.row()).fileName();
            }
            break;

            default:
                break;
        }

    return value;
}
