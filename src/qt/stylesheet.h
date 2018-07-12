#ifndef STYLE_SHEET_H
#define STYLE_SHEET_H

static const QString styleBtnNormal =
    QString("QPushButton{"
            "	min-width:%1px;"
            "	max-width:%1px;"
            "	min-height:%2px;"
            "	max-height:%2px;"
            "	border: 1px solid #484052;"
            "	font-size:12px;"
            "	color:#484052;"
            "	border-radius:3px;}"
            "QPushButton:hover{"
            "	color:#FFFFFF;"
            "	border: 1px solid #FFFFFF;}"
            "QPushButton:press{"
            "	color:#FFFFFF;"
            "	border: 1px solid #FFFFFF;"
            "	border-radius:3px;}"
            "QPushButton:disabled{"
            "	color:#20242B;"
            "	border: 1px solid #20242B;"
            "	border-radius:3px;}");

static const QString styleBtnRed =
    QString("QPushButton{"
            "	min-width:%1px;"
            "	max-width:%1px;"
            "	min-height:%2px;"
            "	max-height:%2px;"
            "	background-color: QLinearGradient(x1: 0, y1: 0,"
            "	x2: 1, y2: 0, stop: 0 rgba(252,172,141,1), stop: 1 "
            "rgba(229,101,143,1));"
            "	font-size:12px;"
            "	color:#FFFFFF;"
            "	border-radius:3px;}"
            "QPushButton:hover{"
            "	background-color: QLinearGradient(x1: 0, y1: 0,"
            "	x2: 1, y2: 0, stop: 0 rgba(252,172,141,0.5), stop: 1 "
            "rgba(229,101,143,0.5));}"
            "QPushButton:press{"
            "	background-color: QLinearGradient(x1: 0, y1: 0,"
            "	x2: 1, y2: 0, stop: 0 rgba(252,172,141,0.5), stop: 1 "
            "rgba(229,101,143,0.5));}");

static const QString styleLabelBlack =
    QString("QLabel#label_2{"
            "	font-size:12px;"
            "	color:rgba(130,133,138,1);}");

static const QString styleLabelWhite =
    QString("QLabel#label{"
            "	font-size:12px;"
            "	color:rgba(209,209,209,1);}");

static const QString styleFrame = QString("QFrame{background-color:rgba(25,31,41,1);}");

#endif //STYLE_SHEET_H

