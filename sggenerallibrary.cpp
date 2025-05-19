#include "sggenerallibrary.h"
#include <QRegularExpression>
#include "sgcentralmanagement.h"
#include "sgtouchinputmanagement.h"
#include "sgnoteviewmanagement.h"
#include <limits>

QString SGGeneralLibrary::stylesheetfieldbackgroundcolour = QString("background-color");
QString SGGeneralLibrary::stylesheetfieldtextcolour = QString("color");
QString SGGeneralLibrary::stylesheetfieldfontsize = QString("font-size");
QString SGGeneralLibrary::stylesheetfieldborder = QString("border");
QString SGGeneralLibrary::stylesheetfieldselectedbackgroundcolour = QString("selection-background-color");
QString SGGeneralLibrary::stylesheetfieldselectedtextcolour = QString("selection-color");
QString SGGeneralLibrary::stylesheetfieldscrollbarwidth = QString("width");
QString SGGeneralLibrary::stylesheetnoborder = QString("none");
QFont* SGGeneralLibrary::SingScriptSG = nullptr;
float SGGeneralLibrary::plusinf = std::numeric_limits<float>::infinity();
float SGGeneralLibrary::minusinf = (-1.0f) * std::numeric_limits<float>::infinity();

void SGGeneralLibrary::SetUIStyle(QWidget* obj, QString& k, QString& v){
    QString s = (*obj).styleSheet();
    QRegularExpression r(k + ":[^;]+;");
    if(s.contains(r)){s.replace(r, k + ": " + v + "; ");}
    else{s += (k + ": " + v + "; ");}
    bool x = (*obj).autoFillBackground();
    (*obj).setStyleSheet(s);
    (*obj).setAutoFillBackground(x);
}

void SGGeneralLibrary::updatefontsize(QWidget *obj){
    QString s = QString::number((*obj).size().height()) + QString("px");
    SGGeneralLibrary::SetUIStyle(obj, SGGeneralLibrary::stylesheetfieldfontsize, s);
}

QString SGGeneralLibrary::StringToNCL256(QString& s){
    QByteArray b = s.toUtf8();
    QString o(b.size(), Qt::Uninitialized);
    for(int i=0; i<b.size(); i++){o[i] = (QChar)(0xF000 | (int)b[i]);}
    return o;
}

QString SGGeneralLibrary::NCL256ToString(QString& s){
    QByteArray b(s.size(), Qt::Uninitialized);
    for(int i=0; i<s.size(); i++){b[i] = (char)s[i].unicode();}
    return QString::fromUtf8(b);
}

void SGGeneralLibrary::setscrollviewstylesheet(QWidget *obj){
    (*obj).setStyleSheet((R"(
        QScrollBar:vertical{
            width: 20px;
        }
        QScrollBar::handle:vertical{
            background: )" + SGCentralManagement::colour1 + R"(;
        }
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{
            background: )" + SGCentralManagement::colour3 + R"(;
        }
    )"));
}

void SGGeneralLibrary::updatescrollbarwidth(QWidget *obj){
    QString s = QString::number(2.0f / 3.0f * SGCentralManagement::sizeunit) + "px";
    SGGeneralLibrary::SetUIStyle(obj, SGGeneralLibrary::stylesheetfieldscrollbarwidth, s);
}

QString* SGGeneralLibrary::getwrappedtext(QString s){
    QFont f;
    f = (*SGGeneralLibrary::SingScriptSG);
    f.setPixelSize(0.66f * SGCentralManagement::sizeunit);
    QFontMetrics fm(f);
    QString* o = new QString[3];
    QString sstr = "";
    QString cw = "";
    int cnt = 0;
    int e = fm.horizontalAdvance("...");
    s += " ";
    for(int i=0; i<s.size(); i++){
        if(s[i] != ' '){cw += s[i];}
        else{
            if(cnt == 0 && fm.horizontalAdvance(sstr + " " + cw) < (int)(4.0f * SGCentralManagement::sizeunit)){
                sstr += (" " + cw);
                cw = "";
            }
            else if(cnt == 0){
                o[1] = sstr;
                sstr = cw;
                cw = "";
                cnt++;
            }
            else if(fm.horizontalAdvance(sstr + " " + cw) < (int)(4.0f * SGCentralManagement::sizeunit) - e){
                sstr += (" " + cw);
                cw = "";
            }
            else{
                o[2] = sstr + "...";
                cnt++;
                break;
            }
        }
    }
    if(cnt == 0){
        o[0] = "1";
        o[1] = sstr;
    }
    else if(cnt == 1){
        o[0] = "2";
        o[2] = sstr;
    }
    else{o[0] = "2";}
    if(o[1] != "" && o[1][0] == ' '){o[1] = o[1].right(o[1].size() - 1);}
    if(o[2] != "" && o[2][0] == ' '){o[2] = o[2].right(o[2].size() - 1);}
    return o;
}

QString SGGeneralLibrary::ColourUintToCSS(uint c){
    return ("rgba(" + QString::number(0xFF & (c >> 24)) + ", " + QString::number(0xFF & (c >> 16)) + ", " + QString::number(0xFF & (c >> 8)) + "," + QString::number(0xFF & c) + ")");
}

float SGGeneralLibrary::DrawingTouchToNoteCoordsX(){
    return ((SGTouchInputManagement::drawingtouch.x - 0.5f * (*SGNoteViewManagement::renderarea).size().width()) / (*SGNoteViewManagement::renderarea).size().width() * SGCentralManagement::focusedzoom + SGCentralManagement::focusedpositionx);
}

float SGGeneralLibrary::DrawingTouchToNoteCoordsY(){
    return ((SGTouchInputManagement::drawingtouch.y - 0.5f * (*SGNoteViewManagement::renderarea).size().height()) / (*SGNoteViewManagement::renderarea).size().width() * SGCentralManagement::focusedzoom * (-1.0f) + SGCentralManagement::focusedpositiony);
}

QUuid SGGeneralLibrary::GetNewGUID(){
    return QUuid::createUuid();
}

void SGGeneralLibrary::rotateplus90(float x, float y, float &newx, float &newy){
    newx = (-1.0f) * y;
    newy = x;
}

void SGGeneralLibrary::normalisevector(float x, float y, float &newx, float &newy){
    float d = std::sqrt(x * x + y * y);
    newx = x / d;
    newy = y / d;
}

void SGGeneralLibrary::doublevbo(QOpenGLFunctions_4_5_Core *glc, GLuint &vbo, int &ms){
    GLuint newvbo = 0;
    (*glc).glGenBuffers(1, &newvbo);
    (*glc).glBindBuffer(GL_ARRAY_BUFFER, newvbo);
    (*glc).glBufferData(GL_ARRAY_BUFFER, 2 * ms * 2 * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
    (*glc).glBindBuffer(GL_COPY_READ_BUFFER, vbo);
    (*glc).glBindBuffer(GL_COPY_WRITE_BUFFER, newvbo);
    (*glc).glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0 * 2 * sizeof(GLfloat), 0 * 2 * sizeof(GLfloat), ms * 2 * sizeof(GLfloat));
    (*glc).glDeleteBuffers(1, &vbo);
    vbo = newvbo;
    ms *= 2;
}

void SGGeneralLibrary::doubleebo(QOpenGLFunctions_4_5_Core *glc, GLuint &ebo, int &ms){
    GLuint newebo = 0;
    (*glc).glGenBuffers(1, &newebo);
    (*glc).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newebo);
    (*glc).glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * ms * 3 * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
    (*glc).glBindBuffer(GL_COPY_READ_BUFFER, ebo);
    (*glc).glBindBuffer(GL_COPY_WRITE_BUFFER, newebo);
    (*glc).glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0 * 3 * sizeof(GLuint), 0 * 3 * sizeof(GLuint), ms * 3 * sizeof(GLuint));
    (*glc).glDeleteBuffers(1, &ebo);
    ebo = newebo;
    ms *= 2;
}

int SGGeneralLibrary::getrenderingdataindex(int a, int b){
    return (b * (b-1) / 2 + a - 1);
}

uint SGGeneralLibrary::ColourCSSToUint(QString &s){
    int x = 0;
    uint r = 0;
    uint g = 0;
    uint b = 0;
    uint a = 0;
    QString ts = "";
    for(int i=0; i<s.length(); i++){
        if(s[i] >= '0' && s[i] <= '9'){ts += s[i];}
        else if(x == 0 && ts != ""){
            r = ts.toUInt();
            x++;
            ts = "";
        }
        else if(x == 1 && ts != ""){
            g = ts.toUInt();
            x++;
            ts = "";
        }
        else if(x == 2 && ts != ""){
            b = ts.toUInt();
            x++;
            ts = "";
        }
        else if(x == 3 && ts != ""){
            a = ts.toUInt();
            x++;
            ts = "";
        }
    }
    uint ans = (r << 24) | (g << 16) | (b << 8) | a;
    return ans;
}

int SGGeneralLibrary::getcolliderdataindex(int x, int y){
    return (y | (x << 26));
}

float SGGeneralLibrary::getdetsignonly(float x1, float y1, float x2, float y2, float x3, float y3){
    return (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
}
