#ifndef SGFAVOURITETOOLSMANAGEMENT_H
#define SGFAVOURITETOOLSMANAGEMENT_H

#include <QObject>

class SGFavouriteToolsManagement : public QObject
{
    Q_OBJECT
public:
    static void addfavouritetool();
    static void togglefavouritetool();
    static bool isdeleting;
    static void savefavouritetools();
    static void loadfavouritetools();
    static void createfavouritetoolbutton(int type, uint col, float width);
private:
    SGFavouriteToolsManagement(){}
    ~SGFavouriteToolsManagement(){}
};

#endif // SGFAVOURITETOOLSMANAGEMENT_H
