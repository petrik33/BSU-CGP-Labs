#include "colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QGridLayout();
    setLayout(mainLayout);

    cShow = new ColorShowWidget(this);
    mainLayout->addWidget(cShow,cShowX,cShowY,cShowRowSpan,cShowColSpan);
    //Remove
    cShow->setColor(QColor(0,0,0));
    cShow->update();

    for(int i = 0; i < int(MODELS_NUMBER); i++){
        QString modelName = "ColorModelName(i);";
        QPushButton* modelButton = new QPushButton(modelName);
        int row = buttonsY + i / buttonsInRow;
        int col = buttonsX + ((i+1) % buttonsInRow) * buttonsColSpan;
        cSpaceButtons.push_back(modelButton);
        mainLayout->addWidget(modelButton,row,col,buttonsRowSpan,buttonsColSpan);
        //To Do: Connect
    }

    setColorModel(RGB);

}

void ColorWidget::setColorModel(ColorModel modelID)
{
    cLabels.clear();
    cSliders.clear();
    cSpins.clear();

    QVector<QString> modelParamNames = colorModelsParamNames[int(modelID)];
    int paramsNum = modelParamNames.length();
    for(int i = 0; i < paramsNum; i++){
       QLabel* label = new QLabel(modelParamNames[i]);
       cLabels.push_back(label);
       mainLayout->addWidget(label,labelsY+i,labelsX,labelsRowSpan,labelsColSpan);

       QSlider* slider = new QSlider(Qt::Horizontal);
       cSliders.push_back(slider);
       mainLayout->addWidget(slider,slidersY+i,slidersX,slidersRowSpan,slidersColSpan);
       //To Do: Set Range, Connect

       QSpinBox* spin = new QSpinBox();
       cSpins.push_back(spin);
       mainLayout->addWidget(spin,spinsY+i,spinsX,spinsRowSpan,spinsColSpan);
       //To Do: Set Range, Connect
    }

    //To Do: Set Values
}

















