#include "colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QGridLayout();
    setLayout(mainLayout);

    cShow = new ColorShowWidget(this);
    mainLayout->addWidget(cShow,cShowY,cShowX,cShowRowSpan,cShowColSpan);

    cPalette = new CustomColorPalette(4,8);
    mainLayout->addWidget(cPalette,paletteY,paletteX,paletteRowSpan,paletteColSpan);
    connect(cPalette,SIGNAL(colorPicked(QColor)),this,SLOT(colorModelUpdatePalette(QColor)));

    for(int i = 0; i < int(COLOR_MODEL::MODELS_NUMBER); i++){
        QString modelName = colorModel::ColorModelName(i);
        ColorModelButton* modelButton = new ColorModelButton(modelName,COLOR_MODEL(i));
        int row = buttonsY + i / buttonsInRow;
        int col = buttonsX + (i % buttonsInRow) * buttonsColSpan;
        cSpaceButtons.push_back(modelButton);
        mainLayout->addWidget(modelButton,row,col,buttonsRowSpan,buttonsColSpan);
        modelButton->connect(modelButton,SIGNAL(modelPicked(COLOR_MODEL, bool)),this,SLOT(setColorModel(COLOR_MODEL)));
    }

    for(int i = 0; i < colorModelsMaxParams; i++) {
        cLabels.push_back(nullptr);
        cSliders.push_back(nullptr);
        cSpins.push_back(nullptr);
    }

    setColorModel(RGB);
}

void ColorWidget::setColorModel(COLOR_MODEL modelID)
{
    for(int i = 0; i < colorModelsMaxParams; i++) {
        if(cLabels[i]) {
            delete cLabels[i];
            cLabels[i] = nullptr;
        }
        if(cSliders[i]) {
            delete cSliders[i];
            cSliders[i] = nullptr;
        }
        if(cSpins[i]) {
            delete cSpins[i];
            cSpins[i] = nullptr;
        }
    }

    QVector<QString> modelParamNames = colorModelsParamNames[int(modelID)];
    int paramsNum = modelParamNames.length();
    for(int i = 0; i < paramsNum; i++){
       QLabel* label = new QLabel(modelParamNames[i]);
       cLabels[i] = label;
       mainLayout->addWidget(label,labelsY+i,labelsX,labelsRowSpan,labelsColSpan);

       QSlider* slider = new QSlider(Qt::Horizontal);
       slider->setRange(colorModelsParamRange[modelID][i][0],colorModelsParamRange[modelID][i][1]);
       cSliders[i] = slider;
       mainLayout->addWidget(slider,slidersY+i,slidersX,slidersRowSpan,slidersColSpan);
       connect(slider,SIGNAL(sliderMoved(int)),this,SLOT(colorModelUpdateSliders()));

       QSpinBox* spin = new QSpinBox();
       spin->setRange(colorModelsParamRange[modelID][i][0],colorModelsParamRange[modelID][i][1]);
       cSpins[i] = spin;
       mainLayout->addWidget(spin,spinsY+i,spinsX,spinsRowSpan,spinsColSpan);
       connect(spin,SIGNAL(valueChanged(int)),this,SLOT(colorModelUpdateSpins()));

       connect(slider,SIGNAL(sliderMoved(int)),spin,SLOT(setValue(int)));
       connect(spin,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    }

    if(colorModelInst) {
        colorModel* newModel = colorModelInst->convertColorModel(modelID);
        delete colorModelInst;
        colorModelInst = newModel;
    }
    else {
        colorModelInst = colorModel::makeColorModel(modelID);
    }

    cShow->setInaccurate(false);
    connect(colorModelInst,SIGNAL(inaccurateConversion(bool)),cShow,SLOT(setInaccurate(bool)));

    colorModelENUM = modelID;
    //To Do: Set Values
    spinsSlidersSet();
    QColor rgbPresentation = colorModelInst->getQColor();
    changeColor(rgbPresentation);
}

void ColorWidget::changeColor(QColor color)
{
    cShow->setColor(color);
}

void ColorWidget::colorModelUpdateSliders()
{
    int paramsNum = getParamsNum();
    QVector<double> newParams;
    for(int i = 0; i < paramsNum; i++) {
        QSlider* slider = cSliders[i];
        double value = slider->value();
        double min = slider->minimum();
        double max = slider->maximum();
        double range = max - min;
        double normalizedValue = (value - min) / range;
        newParams.push_back(normalizedValue);
    }
    ColorModelSet(newParams);
}

void ColorWidget::colorModelUpdateSpins()
{
    int paramsNum = getParamsNum();
    QVector<double> newParams;
    for(int i = 0; i < paramsNum; i++) {
        QSpinBox* spin = cSpins[i];
        double value = spin->value();
        double min = spin->minimum();
        double max = spin->maximum();
        double range = max - min;
        double normalizedValue = (value - min) / range;
        newParams.push_back(normalizedValue);
    }
    ColorModelSet(newParams);
}

void ColorWidget::ColorModelSet(QVector<double> params)
{
    colorModelInst->setParams(params);
    QColor color = colorModelInst->getQColor();
    changeColor(color);
}

void ColorWidget::spinsSlidersSet()
{
    int paramsNum = getParamsNum();
    QVector<double> params = colorModelInst->getParams();
    for(int i = 0; i < paramsNum; i++) {
        QSlider* slider = cSliders[i];
        QSpinBox* spin = cSpins[i];
        double min = slider->minimum();
        double max = slider->maximum();
        double range = max - min;
        double normalizedValue = params[i];
        double value = min + normalizedValue * range;
        slider->setValue(value);
        spin->setValue(value);
    }
}

void ColorWidget::colorModelUpdatePalette(QColor color)
{
    modelRGB* rgbRep = new modelRGB(color);
    colorModel* currentModel = rgbRep->convertColorModel(colorModelENUM);
    colorModelInst->setParams(currentModel->getParams());
    changeColor(color);
    spinsSlidersSet();
}

//void ColorWidget::onConversion(bool inaccurate)
//{

//}

















