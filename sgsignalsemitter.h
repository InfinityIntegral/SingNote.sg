#ifndef SGSIGNALSEMITTER_H
#define SGSIGNALSEMITTER_H

#include <QObject>

class SGSignalsEmitter : public QObject
{
    Q_OBJECT
public:
    SGSignalsEmitter();
    void sendsignals();

signals:
    void updatescreen();
    void updatedirectorytoolbar();
    void updatenewfilemenu();
    void updatenewfilewindow();
    void updatenoteslist();
    void updatenoteview();
    void updatechangetoolsmenu();
    void updatechangepenmenu();
    void updatechangeerasermenu();
    void updatechangehighlightermenu();
    void updatechangeselectormenu();
};

#endif // SGSIGNALSEMITTER_H
