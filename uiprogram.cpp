#include "uiprogram.h"
#include <QDebug>
#include <QLayout>
#include <QLabel>
#include <QScrollArea>
#include <QCheckBox>
#include <QPushButton>
#include "minotor.h"

#include "uiprogramview.h"
#include "uiprogrameditor.h"
#include "uimidiproperty.h"

UiProgram::UiProgram(MinoProgram *program, QWidget *parent) :
    QWidget(parent),
    _program(program)
{
    QVBoxLayout *lProgram = new QVBoxLayout(this);
    lProgram->setSpacing(0);
    lProgram->setMargin(0);
    lProgram->setContentsMargins(0,0,0,0);

    _border = new QWidget();
    _border->setObjectName("border");
    lProgram->addWidget(_border);

    QVBoxLayout *lBorder = new QVBoxLayout(_border);
    lBorder->setSpacing(0);
    lBorder->setMargin(0);
    lBorder->setContentsMargins(1,1,1,1);

    _wBackground = new QWidget(this);
    _wBackground->setObjectName("programbackground");


    lBorder->addWidget(_wBackground);
    QHBoxLayout *lBackground = new QHBoxLayout(_wBackground);

    QWidget *wTitle = new QWidget(_wBackground);
    wTitle->setMinimumWidth(85);
    wTitle->setMaximumWidth(85);
    lBackground->addWidget(wTitle);
    QVBoxLayout *lTitle = new QVBoxLayout(wTitle);

    QLabel *tTitle = new QLabel(wTitle);
    lTitle->addWidget(tTitle);
    tTitle->setObjectName("title");
    tTitle->setText(QString("Prg ") + QString::number(program->id()));

    UiMidiProperty *mpBeat = new UiMidiProperty(_program->properties().at(0), this);
    lTitle->addWidget(mpBeat);
    lTitle->addStretch();

    UiProgramEditor * editor = new UiProgramEditor(program, _wBackground);
    connect(editor, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customContextMenuRequested(QPoint)));
    lBackground->addWidget(editor);

    QWidget *wRightArea = new QWidget(_wBackground);
    lBackground->addWidget(wRightArea);
    wRightArea->setMaximumWidth(212);
    QVBoxLayout *lRightArea = new QVBoxLayout(wRightArea);

    QWidget *wCollapse = new QWidget(wRightArea);
    lRightArea->addWidget(wCollapse);
    QHBoxLayout *lCollapse = new QHBoxLayout(wCollapse);
    QPushButton *bOnAir = new QPushButton(wRightArea);
    bOnAir->setCheckable(true);
    bOnAir->setObjectName("bOnAir");
    bOnAir->setText("On Air");
    connect(bOnAir,SIGNAL(toggled(bool)),this,SLOT(requestMasterProgramChange(bool)));
    lCollapse->addWidget(bOnAir);
    lCollapse->addStretch();
    QCheckBox *cbCollapse = new QCheckBox(wCollapse);
    cbCollapse->setObjectName("arrow");
    cbCollapse->setChecked(false);
    lCollapse->addWidget(cbCollapse);
    connect(cbCollapse,SIGNAL(toggled(bool)),this,SLOT(setExpanded(bool)));
    connect(cbCollapse,SIGNAL(toggled(bool)),editor,SLOT(setExpanded(bool)));
    // Monitor
    _fPreview = new QFrame(this);
    lRightArea->addWidget(_fPreview);
    QVBoxLayout *lPreview = new QVBoxLayout(_fPreview);
    _fPreview->setObjectName("view");
    _fPreview->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    _fPreview->setMinimumSize(200, 150);
    UiProgramView *pView = new UiProgramView(program, _fPreview);
    QSizePolicy policy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    policy.setHeightForWidth(true);
    lPreview->addWidget(pView);
    lRightArea->addStretch();

    setExpanded(false);
    editor->setExpanded(false);

    connect(_program, SIGNAL(onAir(bool)), bOnAir, SLOT(setChecked(bool)));
    connect(_program, SIGNAL(onAir(bool)), this, SLOT(updateOnAirStatus(bool)));
    bOnAir->setChecked(_program->isOnAir());
    updateOnAirStatus(_program->isOnAir());
}

void UiProgram::setExpanded(bool expanded)
{
    _fPreview->setVisible(expanded);
    if (expanded)
    {
        _wBackground->setStyleSheet("#programbackground { background-color:#444444;}");
        //_wBackground->setObjectName("programbackgroundon");
        //_wBackground->
        //_wBackground->setStyleSheet("");
        this->setMinimumHeight(320);
        this->setMaximumHeight(320);
    }
    else
    {
       _wBackground->setStyleSheet("#programbackground { background-color:#333333;}");
       //_wBackground->setObjectName("programbackgroundoff");
       //_wBackground->setStyleSheet("");
       this->setMinimumHeight(105);
       this->setMaximumHeight(105);
    }
    QScrollArea * sa = dynamic_cast<QScrollArea*>(parentWidget()->parentWidget()->parentWidget());
//    qDebug() << "gnii" << parentWidget() << parentWidget()->parentWidget() << parentWidget()->parentWidget()->parentWidget();
    if(sa)
    {
        sa->ensureWidgetVisible(this,0,0);
    }
}

void UiProgram::requestMasterProgramChange(bool on)
{
    if(on)
        _program->minotor()->master()->setProgram(_program);
}

void UiProgram::updateOnAirStatus(bool onAir)
{
    //_bOnAir->setChecked(onAir);
    if (onAir)
    {
        _border->setStyleSheet("#border {background-color:#e75f00;}");
    }
    else
    {
        _border->setStyleSheet("#border {}");
    }
}
