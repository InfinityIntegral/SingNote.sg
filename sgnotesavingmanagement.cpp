#include "sgnotesavingmanagement.h"
#include "sgcentralmanagement.h"
#include "sgfilereaderplugin.h"
#include "sgnoteobjecttypeenum.h"
#include "sgnotemanagement.h"
#include "sgpagebackgroundobject.h"
#include "sgnoteviewmanagement.h"
#include "sgviewportmanagement.h"
#include "sgtooltypeenum.h"
#include "sgtooloptionsmanagement.h"
#include "sgrenderingrange.h"
#include "sggenerallibrary.h"
#include "sgfilewriterplugin.h"
#include "sgstatusbarmanagement.h"
#include "sgfilesystemmanagementplugin.h"
#include "sgfiletypeenum.h"
#include "sgpenstrokeobject.h"
#include "sgpolylinecollider.h"
#include "sgcollidermanagement.h"
#include "sgnoteobjecttypeenum.h"
#include "sgfavouritetoolsmanagement.h"

void SGNoteSavingManagement::opennote(QString path){
    SGCentralManagement::activetooltype = SGToolTypeEnum::Move;
    SGCentralManagement::activetoolcolour = 0xFF00C8FF;
    SGCentralManagement::activetoolwidth = 2.0;
    SGToolOptionsManagement::updatechangetoolicon();
    SGNoteManagement::noteisopen = true;
    SGNoteManagement::penstrokezindex = 1;
    SGNoteManagement::highlighterstrokezindex = 1;
    SGNoteManagement::notedata = new QVector<SGPermanentObject*>();
    SGNoteManagement::renderingdata = new QHash<int, SGRenderingRange*>();
    SGNoteManagement::collidersdata = new QHash<int, SGColliderRange*>();
    SGFavouriteToolsManagement::isdeleting = false;
    SGGeneralLibrary::SetUIStyle(SGNoteViewManagement::favouritetoolsaddbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(SGNoteViewManagement::favouritetoolsremovebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGFileReaderPlugin r(path);
    r.ReadInt();
    r.ReadInt();
    r.ReadBool();
    r.ReadInt();
    r.ReadInt();
    int coverl = r.ReadInt();
    r.ReadString(coverl);
    int templatel = r.ReadInt();
    r.ReadString(templatel); // get the template
    r.ReadInt(); // number of search groups
    // get search results here
    SGCentralManagement::pagew = r.ReadFloat();
    SGCentralManagement::pageh = r.ReadFloat();
    SGCentralManagement::marginx = r.ReadFloat();
    SGCentralManagement::marginy = r.ReadFloat();
    SGCentralManagement::focusedzoom = SGCentralManagement::pagew * 1.1f;
    SGCentralManagement::focusedpositionx = 0.0f;
    SGCentralManagement::focusedpositiony = -0.5f * SGCentralManagement::focusedzoom * SGNoteViewManagement::renderh / SGNoteViewManagement::renderw;

    while(r.EndOfStream() == false){
        bool isnoteobj = r.ReadBool();
        if(isnoteobj){
            QUuid guid = r.ReadGUID();
            int objtype = r.ReadInt();
            if(objtype == SGNoteObjectTypeEnum::Background){
                int n = r.ReadInt();
                int imgl = r.ReadInt();
                r.ReadString(imgl);
                SGPageBackgroundObject* bg = new SGPageBackgroundObject(n, guid);
                (*bg).dataindex = (*SGNoteManagement::notedata).size();
                (*SGNoteManagement::notedata).push_back(bg);
                SGNoteSavingManagement::initialiserenderpagebackground(bg);
            }
            else if(objtype == SGNoteObjectTypeEnum::PenStroke){
                float x = r.ReadFloat();
                float y = r.ReadFloat();
                uint c = r.ReadUint();
                float w = r.ReadFloat();
                int z = r.ReadInt();
                SGPenStrokeObject* ps = new SGPenStrokeObject(guid, x, y, w, c, z);
                if(z > SGNoteManagement::penstrokezindex){SGNoteManagement::penstrokezindex = z;}
                int vs = r.ReadInt();
                for(int j=0; j<vs; j++){
                    (*(*ps).pointsx).push_back(r.ReadFloat());
                    (*(*ps).pointsy).push_back(r.ReadFloat());
                }
                SGNoteSavingManagement::initialisepenstroke(ps);
            }
            else if(objtype == SGNoteObjectTypeEnum::HighlighterStroke){
                float x = r.ReadFloat();
                float y = r.ReadFloat();
                uint c = r.ReadUint();
                float w = r.ReadFloat();
                int z = r.ReadInt();
                SGHighlighterStrokeObject* hs = new SGHighlighterStrokeObject(guid, x, y, w, c, z);
                if(z > SGNoteManagement::highlighterstrokezindex){SGNoteManagement::highlighterstrokezindex = z;}
                int vs = r.ReadInt();
                for(int j=0; j<vs; j++){
                    (*(*hs).pointsx).push_back(r.ReadFloat());
                    (*(*hs).pointsy).push_back(r.ReadFloat());
                }
                SGNoteSavingManagement::initialisehighlighterstroke(hs);
            }
        }
    }
    SGNoteViewManagement::updaterendering();
}

void SGNoteSavingManagement::savenote(QString path){
    //QString fn = "TEST";
    //path = SGCentralManagement::rootfilepath + "NOTES/" + SGGeneralLibrary::StringToNCL256(fn) + ".singnote";
    QString temppath = SGCentralManagement::rootfilepath + "INTERNAL/SAVEBUFFER";
    SGFileSystemManagementPlugin::CreateFile(temppath);
    {
        SGFileWriterPlugin w(temppath);
        w.WriteInt(1);
        w.WriteInt(SGFileTypeEnum::Note);
        w.WriteBool(true); // always new note
        w.WriteInt(0);
        w.WriteInt(0);
        w.WriteInt(0);
        w.WriteInt(0);
        w.WriteInt(0);
        w.WriteFloat(SGCentralManagement::pagew);
        w.WriteFloat(SGCentralManagement::pageh);
        w.WriteFloat(0.0f);
        w.WriteFloat(0.0f);
        for(int i=0; i<(*SGNoteManagement::notedata).size(); i++){
            if((*SGNoteManagement::notedata)[i] == nullptr){continue;}
            w.WriteBool(true);
            w.WriteGUID((*(*SGNoteManagement::notedata)[i]).guid);
            w.WriteInt((*(*SGNoteManagement::notedata)[i]).type);
            if((*(*SGNoteManagement::notedata)[i]).type == SGNoteObjectTypeEnum::Background){
                SGPageBackgroundObject* x = (SGPageBackgroundObject*)((*SGNoteManagement::notedata)[i]);
                w.WriteInt((*x).pagenumber);
                w.WriteInt(0);
            }
            else if((*(*SGNoteManagement::notedata)[i]).type == SGNoteObjectTypeEnum::PenStroke){
                SGPenStrokeObject* x = (SGPenStrokeObject*)((*SGNoteManagement::notedata)[i]);
                w.WriteFloat((*x).originx);
                w.WriteFloat((*x).originy);
                w.WriteUint((*x).colour);
                w.WriteFloat((*x).width);
                w.WriteInt((*x).zdepth);
                w.WriteInt((*(*x).pointsx).size());
                for(int j=0; j<(*(*x).pointsx).size(); j++){
                    w.WriteFloat((*(*x).pointsx)[j]);
                    w.WriteFloat((*(*x).pointsy)[j]);
                }
            }
            else if((*(*SGNoteManagement::notedata)[i]).type == SGNoteObjectTypeEnum::HighlighterStroke){
                SGHighlighterStrokeObject* x = (SGHighlighterStrokeObject*)((*SGNoteManagement::notedata)[i]);
                w.WriteFloat((*x).originx);
                w.WriteFloat((*x).originy);
                w.WriteUint((*x).colour);
                w.WriteFloat((*x).width);
                w.WriteInt((*x).zdepth);
                w.WriteInt((*(*x).pointsx).size());
                for(int j=0; j<(*(*x).pointsx).size(); j++){
                    w.WriteFloat((*(*x).pointsx)[j]);
                    w.WriteFloat((*(*x).pointsy)[j]);
                }
            }
        }
    }
    SGFileSystemManagementPlugin::DeleteFile(path);
    SGFileSystemManagementPlugin::MoveFile(temppath, path);
    SGStatusBarManagement::notify("saved note successfully");
}

void SGNoteSavingManagement::initialiserenderpagebackground(SGPageBackgroundObject* x){
    int pi = SGGeneralLibrary::getrenderingdataindex((*x).pagenumber, (*x).pagenumber);
    if((*SGNoteManagement::renderingdata).contains(pi) == false){(*SGNoteManagement::renderingdata)[pi] = new SGRenderingRange((*x).pagenumber, (*x).pagenumber);}
    (*SGNoteViewManagement::backgroundrenderer).makeCurrent();
    GLfloat vts[] = {-0.5f * SGCentralManagement::pagew, -1.0f * (float)((*x).pagenumber) * SGCentralManagement::pageh, 0.5f * SGCentralManagement::pagew, -1.0f * (float)((*x).pagenumber) * SGCentralManagement::pageh, -0.5f * SGCentralManagement::pagew, -1.0f * (float)((*x).pagenumber - 1) * SGCentralManagement::pageh, 0.5f * SGCentralManagement::pagew, -1.0f * (float)((*x).pagenumber - 1) * SGCentralManagement::pageh};
    GLuint ids[] = {0, 1, 2, 1, 2, 3};
    (*SGNoteViewManagement::backgroundrenderer).glGenVertexArrays(1, &((*(*SGNoteManagement::renderingdata)[pi]).pagebackgroundvao));
    (*SGNoteViewManagement::backgroundrenderer).glBindVertexArray((*(*SGNoteManagement::renderingdata)[pi]).pagebackgroundvao);
    (*SGNoteViewManagement::backgroundrenderer).glGenBuffers(1, &((*(*SGNoteManagement::renderingdata)[pi]).pagebackgroundvbo));
    (*SGNoteViewManagement::backgroundrenderer).glBindBuffer(GL_ARRAY_BUFFER, (*(*SGNoteManagement::renderingdata)[pi]).pagebackgroundvbo);
    (*SGNoteViewManagement::backgroundrenderer).glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GLfloat), vts, GL_DYNAMIC_DRAW);
    (*SGNoteViewManagement::backgroundrenderer).glGenBuffers(1, &((*(*SGNoteManagement::renderingdata)[pi]).pagebackgroundebo));
    (*SGNoteViewManagement::backgroundrenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*(*SGNoteManagement::renderingdata)[pi]).pagebackgroundebo);
    (*SGNoteViewManagement::backgroundrenderer).glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(GLuint), ids, GL_DYNAMIC_DRAW);
    (*SGNoteViewManagement::backgroundrenderer).glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
    (*SGNoteViewManagement::backgroundrenderer).glEnableVertexAttribArray(0);
    (*SGNoteViewManagement::backgroundrenderer).doneCurrent();
}

void SGNoteSavingManagement::initialiserenderpenstroke(SGPenStrokeObject *x){
    int minp = 0xFFFFFFF;
    int maxp = (-1) * 0xFFFFFFF;
    for(int i=0; i<(*(*x).pointsx).size(); i++){
        int p = 1 + std::floor((((-1) * (*(*x).pointsy)[i]) - (*x).originy - 0.05f * (*x).width) / SGCentralManagement::pageh);
        if(minp > p){minp = p;}
        p = std::ceil((((-1) * (*(*x).pointsy)[i]) - (*x).originy + 0.05f * (*x).width) / SGCentralManagement::pageh);
        if(maxp < p){maxp = p;}
    }
    if(minp < 1){minp = 1;}
    if(maxp < 1){maxp = 1;}
    int pi = SGGeneralLibrary::getrenderingdataindex(minp, maxp);
    if((*SGNoteManagement::renderingdata).contains(pi) == false){(*SGNoteManagement::renderingdata)[pi] = new SGRenderingRange(minp, maxp);}
    (*SGNoteViewManagement::penstrokerenderer).makeCurrent();
    unsigned long long k = (((unsigned long long)((uint)(*x).zdepth)) << 32) | (uint)(*x).colour;
    if((*(*(*SGNoteManagement::renderingdata)[pi]).penstrokelookuptable).contains(k) == false){
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokelookuptable)[k] = (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokezdepth).size();
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokezdepth).push_back((*x).zdepth);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokecolour).push_back((*x).colour);
        GLuint vao0;
        (*SGNoteViewManagement::penstrokerenderer).glGenVertexArrays(1, &vao0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevao).push_back(vao0);
        (*SGNoteViewManagement::penstrokerenderer).glBindVertexArray(vao0);
        GLuint vbo0;
        (*SGNoteViewManagement::penstrokerenderer).glGenBuffers(1, &vbo0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbo).push_back(vbo0);
        (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, vbo0);
        (*SGNoteViewManagement::penstrokerenderer).glBufferData(GL_ARRAY_BUFFER, 10 * 2 * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
        GLfloat zerov[2] = {0.0f, 726.0f};
        (*SGNoteViewManagement::penstrokerenderer).glBufferSubData(GL_ARRAY_BUFFER, 0 * 2 * sizeof(GLfloat), 1 * 2 * sizeof(GLfloat), zerov);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbors).push_back(1);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevboms).push_back(10);
        GLuint ebo0;
        (*SGNoteViewManagement::penstrokerenderer).glGenBuffers(1, &ebo0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebo).push_back(ebo0);
        (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo0);
        (*SGNoteViewManagement::penstrokerenderer).glBufferData(GL_ELEMENT_ARRAY_BUFFER, 10 * 3 * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebors).push_back(0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeeboms).push_back(10);
    }

    int di = (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokelookuptable)[k];
    int vs;
    if((*(*x).pointsx).size() > 1){vs = 3 * (*(*x).pointsx).size() - 2;}
    else{vs = 4;}
    GLfloat v[2 * vs];
    int ts;
    if((*(*x).pointsx).size() > 1){ts = 3 * (*(*x).pointsx).size() - 4;}
    else{ts = 2;}
    GLuint t[3 * ts];
    while((*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevboms)[di] <= (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbors)[di] + vs){SGGeneralLibrary::doublevbo(SGNoteViewManagement::penstrokerenderer, (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbo)[di], (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevboms)[di]);}
    while((*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeeboms)[di] <= (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebors)[di] + ts){SGGeneralLibrary::doubleebo(SGNoteViewManagement::penstrokerenderer, (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebo)[di], (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeeboms)[di]);}
    GLuint tofs = (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbors)[di];

    if((*(*x).pointsx).size() == 1){
        v[0] = (*x).originx - 0.05f * (*x).width;
        v[1] = (*x).originy + 0.05f * (*x).width;
        v[2] = (*x).originx + 0.05f * (*x).width;
        v[3] = (*x).originy + 0.05f * (*x).width;
        v[4] = (*x).originx - 0.05f * (*x).width;
        v[5] = (*x).originy - 0.05f * (*x).width;
        v[6] = (*x).originx + 0.05f * (*x).width;
        v[7] = (*x).originy - 0.05f * (*x).width;
        t[0] = tofs;
        t[1] = tofs + 1;
        t[2] = tofs + 2;
        t[3] = tofs + 1;
        t[4] = tofs + 2;
        t[5] = tofs + 3;
    }
    else if((*(*x).pointsx).size() == 2){
        float perpx;
        float perpy;
        SGGeneralLibrary::rotateplus90((*(*x).pointsx)[1] - (*(*x).pointsx)[0], (*(*x).pointsy)[1] - (*(*x).pointsy)[0], perpx, perpy);
        float offsetx;
        float offsety;
        SGGeneralLibrary::normalisevector(perpx, perpy, offsetx, offsety);
        offsetx *= (0.05f * (*x).width);
        offsety *= (0.05f * (*x).width);
        v[0] = (*x).originx + (*(*x).pointsx)[0] + offsetx;
        v[1] = (*x).originy + (*(*x).pointsy)[0] + offsety;
        v[2] = (*x).originx + (*(*x).pointsx)[0] - offsetx;
        v[3] = (*x).originy + (*(*x).pointsy)[0] - offsety;
        v[4] = (*x).originx + (*(*x).pointsx)[1] + offsetx;
        v[5] = (*x).originy + (*(*x).pointsy)[1] + offsety;
        v[6] = (*x).originx + (*(*x).pointsx)[1] - offsetx;
        v[7] = (*x).originy + (*(*x).pointsy)[1] - offsety;
        t[0] = tofs;
        t[1] = tofs + 1;
        t[2] = tofs + 2;
        t[3] = tofs + 1;
        t[4] = tofs + 2;
        t[5] = tofs + 3;
    }
    else{
        {
            float perpx;
            float perpy;
            SGGeneralLibrary::rotateplus90((*(*x).pointsx)[1] - (*(*x).pointsx)[0], (*(*x).pointsy)[1] - (*(*x).pointsy)[0], perpx, perpy);
            float offsetx;
            float offsety;
            SGGeneralLibrary::normalisevector(perpx, perpy, offsetx, offsety);
            offsetx *= (0.05f * (*x).width);
            offsety *= (0.05f * (*x).width);
            v[0] = (*x).originx + (*(*x).pointsx)[0] - offsetx;
            v[1] = (*x).originy + (*(*x).pointsy)[0] - offsety;
            v[2] = (*x).originx + (*(*x).pointsx)[0] + offsetx;
            v[3] = (*x).originy + (*(*x).pointsy)[0] + offsety;
        }
        {
            int sz = (*(*x).pointsx).size();
            float perpx;
            float perpy;
            SGGeneralLibrary::rotateplus90((*(*x).pointsx)[sz - 1] - (*(*x).pointsx)[sz - 2], (*(*x).pointsy)[sz - 1] - (*(*x).pointsy)[sz - 2], perpx, perpy);
            float offsetx;
            float offsety;
            SGGeneralLibrary::normalisevector(perpx, perpy, offsetx, offsety);
            offsetx *= (0.05f * (*x).width);
            offsety *= (0.05f * (*x).width);
            float det = SGGeneralLibrary::getdetsignonly((*(*x).pointsx)[sz - 3], (*(*x).pointsy)[sz - 3], (*(*x).pointsx)[sz - 2], (*(*x).pointsy)[sz - 2], (*(*x).pointsx)[sz - 1], (*(*x).pointsy)[sz - 1]);
            if(det < 0){
                v[6*sz - 8] = (*x).originx + (*(*x).pointsx)[sz - 1] - offsetx;
                v[6*sz - 7] = (*x).originy + (*(*x).pointsy)[sz - 1] - offsety;
                v[6*sz - 6] = (*x).originx + (*(*x).pointsx)[sz - 1] + offsetx;
                v[6*sz - 5] = (*x).originy + (*(*x).pointsy)[sz - 1] + offsety;
            }
            else{
                v[6*sz - 8] = (*x).originx + (*(*x).pointsx)[sz - 1] + offsetx;
                v[6*sz - 7] = (*x).originy + (*(*x).pointsy)[sz - 1] + offsety;
                v[6*sz - 6] = (*x).originx + (*(*x).pointsx)[sz - 1] - offsetx;
                v[6*sz - 5] = (*x).originy + (*(*x).pointsy)[sz - 1] - offsety;
            }
        }
        {
            int sz = (*(*x).pointsx).size();
            for(int i=1; i<sz-1; i++){
                float a1x = (*(*x).pointsx)[i-1];
                float a1y = (*(*x).pointsy)[i-1];
                float a2x = (*(*x).pointsx)[i];
                float a2y = (*(*x).pointsy)[i];
                float a3x = (*(*x).pointsx)[i+1];
                float a3y = (*(*x).pointsy)[i+1];
                float offset1x;
                float offset1y;
                float offset2x;
                float offset2y;
                float offset3x;
                float offset3y;
                float perp1x;
                float perp1y;
                float perp2x;
                float perp2y;
                float perp3x;
                float perp3y;
                SGGeneralLibrary::rotateplus90(a2x - a1x, a2y - a1y, perp1x, perp1y);
                SGGeneralLibrary::rotateplus90(a3x - a2x, a3y - a2y, perp3x, perp3y);
                SGGeneralLibrary::normalisevector(perp1x, perp1y, offset1x, offset1y);
                SGGeneralLibrary::normalisevector(perp3x, perp3y, offset3x, offset3y);
                offset1x *= (0.05f * (*x).width);
                offset1y *= (0.05f * (*x).width);
                offset3x *= (0.05f * (*x).width);
                offset3y *= (0.05f * (*x).width);
                perp2x = 0.5f * (offset1x + offset3x);
                perp2y = 0.5f * (offset1y + offset3y);
                SGGeneralLibrary::normalisevector(perp2x, perp2y, offset2x, offset2y);
                offset2x *= (0.05f * (*x).width);
                offset2y *= (0.05f * (*x).width);
                float det = SGGeneralLibrary::getdetsignonly(a1x, a1y, a2x, a2y, a3x, a3y);
                if(det < 0){
                    v[6*i - 2] = (*x).originx + (*(*x).pointsx)[i] + offset1x;
                    v[6*i - 1] = (*x).originy + (*(*x).pointsy)[i] + offset1y;
                    v[6*i] = (*x).originx + (*(*x).pointsx)[i] - offset2x;
                    v[6*i + 1] = (*x).originy + (*(*x).pointsy)[i] - offset2y;
                    v[6*i + 2] = (*x).originx + (*(*x).pointsx)[i] + offset3x;
                    v[6*i + 3] = (*x).originy + (*(*x).pointsy)[i] + offset3y;
                }
                else{
                    v[6*i - 2] = (*x).originx + (*(*x).pointsx)[i] - offset1x;
                    v[6*i - 1] = (*x).originy + (*(*x).pointsy)[i] - offset1y;
                    v[6*i] = (*x).originx + (*(*x).pointsx)[i] + offset2x;
                    v[6*i + 1] = (*x).originy + (*(*x).pointsy)[i] + offset2y;
                    v[6*i + 2] = (*x).originx + (*(*x).pointsx)[i] - offset3x;
                    v[6*i + 3] = (*x).originy + (*(*x).pointsy)[i] - offset3y;
                }
            }
        }
        {
            int sz = (*(*x).pointsx).size()-1;
            {
                t[0] = tofs;
                t[1] = tofs + 1;
                float det = SGGeneralLibrary::getdetsignonly((*(*x).pointsx)[0], (*(*x).pointsy)[0], (*(*x).pointsx)[1], (*(*x).pointsy)[1], (*(*x).pointsx)[2], (*(*x).pointsy)[2]);
                if(det >= 0){t[2] = tofs + 2;}
                else{t[2] = tofs + 3;}
                t[3] = tofs + 1;
                t[4] = tofs + 2;
                t[5] = tofs + 3;
                t[6] = tofs + 4;
                t[7] = tofs + 3;
                t[8] = tofs + 2;
            }
            for(int i=1; i<sz-1; i++){
                t[9*i] = tofs + 3*i;
                t[9*i + 1] = tofs + 3*i + 1;
                float det = SGGeneralLibrary::getdetsignonly((*(*x).pointsx)[i], (*(*x).pointsy)[i], (*(*x).pointsx)[i + 1], (*(*x).pointsy)[i + 1], (*(*x).pointsx)[i + 2], (*(*x).pointsy)[i + 2]);
                float det0 = SGGeneralLibrary::getdetsignonly((*(*x).pointsx)[i - 1], (*(*x).pointsy)[i - 1], (*(*x).pointsx)[i], (*(*x).pointsy)[i], (*(*x).pointsx)[i + 1], (*(*x).pointsy)[i + 1]);
                if((det < 0 && det0 < 0) || (det >= 0 && det0 >= 0)){t[9*i + 2] = tofs + 3*i + 3;}
                else{t[9*i + 2] = tofs + 3*i + 2;}
                t[9*i + 3] = tofs + 3*i + 1;
                t[9*i + 4] = tofs + 3*i + 2;
                t[9*i + 5] = tofs + 3*i + 3;
                t[9*i + 6] = tofs + 3*i + 4;
                t[9*i + 7] = tofs + 3*i + 3;
                t[9*i + 8] = tofs + 3*i + 2;
            }
            t[9*sz - 9] = tofs + 3*sz - 3;
            t[9*sz - 8] = tofs + 3*sz - 2;
            t[9*sz - 7] = tofs + 3*sz - 1;
            t[9*sz - 6] = tofs + 3*sz - 2;
            t[9*sz - 5] = tofs + 3*sz - 1;
            t[9*sz - 4] = tofs + 3*sz;
        }
    }

    (*x).renderrangeindex = pi;
    (*x).renderkey = di;
    (*SGNoteViewManagement::penstrokerenderer).glBindVertexArray((*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevao)[di]);
    (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbo)[di]);
    (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebo)[di]);
    (*SGNoteViewManagement::penstrokerenderer).glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
    (*SGNoteViewManagement::penstrokerenderer).glEnableVertexAttribArray(0);
    (*SGNoteViewManagement::penstrokerenderer).glBufferSubData(GL_ARRAY_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbors)[di] * 2 * sizeof(GLfloat), vs * 2 * sizeof(GLfloat), v);
    (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbors)[di] += vs;
    (*SGNoteViewManagement::penstrokerenderer).glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebors)[di] * 3 * sizeof(GLuint), ts * 3 * sizeof(GLuint), t);
    (*x).ebostartindex = (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebors)[di];
    (*x).ebolength = ts;
    (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebors)[di] += ts;
    (*SGNoteViewManagement::penstrokerenderer).doneCurrent();
}

void SGNoteSavingManagement::initialisepenstroke(SGPenStrokeObject *x){
    (*x).dataindex = (*SGNoteManagement::notedata).size();
    (*SGNoteManagement::notedata).push_back(x);
    SGNoteSavingManagement::initialiserenderpenstroke(x);
    int rangeidx;
    int idx;
    SGPolylineCollider* col = SGColliderManagement::penstrokegetcollider(x);
    SGColliderManagement::registercollider(col, SGNoteObjectTypeEnum::PenStroke, rangeidx, idx);
    (*x).colliderrangeindex = rangeidx;
    (*x).colliderindex = idx;
}

void SGNoteSavingManagement::initialisehighlighterstroke(SGHighlighterStrokeObject *x){
    (*x).dataindex = (*SGNoteManagement::notedata).size();
    (*SGNoteManagement::notedata).push_back(x);
    SGNoteSavingManagement::initialiserenderhighlighterstroke(x);
    int rangeidx;
    int idx;
    SGPolylineCollider* col = SGColliderManagement::highlighterstrokegetcollider(x);
    SGColliderManagement::registercollider(col, SGNoteObjectTypeEnum::HighlighterStroke, rangeidx, idx);
    (*x).colliderrangeindex = rangeidx;
    (*x).colliderindex = idx;
}

void SGNoteSavingManagement::initialiserenderhighlighterstroke(SGHighlighterStrokeObject *x){
    int minp = 0xFFFFFFF;
    int maxp = (-1) * 0xFFFFFFF;
    for(int i=0; i<(*(*x).pointsx).size(); i++){
        int p = 1 + std::floor((((-1) * (*(*x).pointsy)[i]) - (*x).originy - 0.05f * (*x).width) / SGCentralManagement::pageh);
        if(minp > p){minp = p;}
        p = std::ceil((((-1) * (*(*x).pointsy)[i]) - (*x).originy + 0.05f * (*x).width) / SGCentralManagement::pageh);
        if(maxp < p){maxp = p;}
    }
    if(minp < 1){minp = 1;}
    if(maxp < 1){maxp = 1;}
    int pi = SGGeneralLibrary::getrenderingdataindex(minp, maxp);
    if((*SGNoteManagement::renderingdata).contains(pi) == false){(*SGNoteManagement::renderingdata)[pi] = new SGRenderingRange(minp, maxp);}
    (*SGNoteViewManagement::highlighterstrokerenderer).makeCurrent();
    unsigned long long k = (((unsigned long long)((uint)(*x).zdepth)) << 32) | (uint)(*x).colour;
    if((*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokelookuptable).contains(k) == false){
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokelookuptable)[k] = (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokezdepth).size();
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokezdepth).push_back((*x).zdepth);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokecolour).push_back((*x).colour);
        GLuint vao0;
        (*SGNoteViewManagement::highlighterstrokerenderer).glGenVertexArrays(1, &vao0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevao).push_back(vao0);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindVertexArray(vao0);
        GLuint vbo0;
        (*SGNoteViewManagement::highlighterstrokerenderer).glGenBuffers(1, &vbo0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbo).push_back(vbo0);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, vbo0);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBufferData(GL_ARRAY_BUFFER, 10 * 2 * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
        GLfloat zerov[2] = {0.0f, 726.0f};
        (*SGNoteViewManagement::highlighterstrokerenderer).glBufferSubData(GL_ARRAY_BUFFER, 0 * 2 * sizeof(GLfloat), 1 * 2 * sizeof(GLfloat), zerov);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbors).push_back(1);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevboms).push_back(10);
        GLuint ebo0;
        (*SGNoteViewManagement::highlighterstrokerenderer).glGenBuffers(1, &ebo0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebo).push_back(ebo0);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo0);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBufferData(GL_ELEMENT_ARRAY_BUFFER, 10 * 3 * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebors).push_back(0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeeboms).push_back(10);
    }

    int di = (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokelookuptable)[k];
    int vs;
    if((*(*x).pointsx).size() > 1){vs = 3 * (*(*x).pointsx).size() - 2;}
    else{vs = 4;}
    GLfloat v[2 * vs];
    int ts;
    if((*(*x).pointsx).size() > 1){ts = 3 * (*(*x).pointsx).size() - 4;}
    else{ts = 2;}
    GLuint t[3 * ts];
    while((*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevboms)[di] <= (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbors)[di] + vs){SGGeneralLibrary::doublevbo(SGNoteViewManagement::highlighterstrokerenderer, (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbo)[di], (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevboms)[di]);}
    while((*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeeboms)[di] <= (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebors)[di] + ts){SGGeneralLibrary::doubleebo(SGNoteViewManagement::highlighterstrokerenderer, (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebo)[di], (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeeboms)[di]);}
    GLuint tofs = (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbors)[di];

    if((*(*x).pointsx).size() == 1){
        v[0] = (*x).originx - 0.05f * (*x).width;
        v[1] = (*x).originy + 0.05f * (*x).width;
        v[2] = (*x).originx + 0.05f * (*x).width;
        v[3] = (*x).originy + 0.05f * (*x).width;
        v[4] = (*x).originx - 0.05f * (*x).width;
        v[5] = (*x).originy - 0.05f * (*x).width;
        v[6] = (*x).originx + 0.05f * (*x).width;
        v[7] = (*x).originy - 0.05f * (*x).width;
        t[0] = tofs;
        t[1] = tofs + 1;
        t[2] = tofs + 2;
        t[3] = tofs + 1;
        t[4] = tofs + 2;
        t[5] = tofs + 3;
    }
    else if((*(*x).pointsx).size() == 2){
        float perpx;
        float perpy;
        SGGeneralLibrary::rotateplus90((*(*x).pointsx)[1] - (*(*x).pointsx)[0], (*(*x).pointsy)[1] - (*(*x).pointsy)[0], perpx, perpy);
        float offsetx;
        float offsety;
        SGGeneralLibrary::normalisevector(perpx, perpy, offsetx, offsety);
        offsetx *= (0.05f * (*x).width);
        offsety *= (0.05f * (*x).width);
        v[0] = (*x).originx + (*(*x).pointsx)[0] + offsetx;
        v[1] = (*x).originy + (*(*x).pointsy)[0] + offsety;
        v[2] = (*x).originx + (*(*x).pointsx)[0] - offsetx;
        v[3] = (*x).originy + (*(*x).pointsy)[0] - offsety;
        v[4] = (*x).originx + (*(*x).pointsx)[1] + offsetx;
        v[5] = (*x).originy + (*(*x).pointsy)[1] + offsety;
        v[6] = (*x).originx + (*(*x).pointsx)[1] - offsetx;
        v[7] = (*x).originy + (*(*x).pointsy)[1] - offsety;
        t[0] = tofs;
        t[1] = tofs + 1;
        t[2] = tofs + 2;
        t[3] = tofs + 1;
        t[4] = tofs + 2;
        t[5] = tofs + 3;
    }
    else{
        {
            float perpx;
            float perpy;
            SGGeneralLibrary::rotateplus90((*(*x).pointsx)[1] - (*(*x).pointsx)[0], (*(*x).pointsy)[1] - (*(*x).pointsy)[0], perpx, perpy);
            float offsetx;
            float offsety;
            SGGeneralLibrary::normalisevector(perpx, perpy, offsetx, offsety);
            offsetx *= (0.05f * (*x).width);
            offsety *= (0.05f * (*x).width);
            v[0] = (*x).originx + (*(*x).pointsx)[0] - offsetx;
            v[1] = (*x).originy + (*(*x).pointsy)[0] - offsety;
            v[2] = (*x).originx + (*(*x).pointsx)[0] + offsetx;
            v[3] = (*x).originy + (*(*x).pointsy)[0] + offsety;
        }
        {
            int sz = (*(*x).pointsx).size();
            float perpx;
            float perpy;
            SGGeneralLibrary::rotateplus90((*(*x).pointsx)[sz - 1] - (*(*x).pointsx)[sz - 2], (*(*x).pointsy)[sz - 1] - (*(*x).pointsy)[sz - 2], perpx, perpy);
            float offsetx;
            float offsety;
            SGGeneralLibrary::normalisevector(perpx, perpy, offsetx, offsety);
            offsetx *= (0.05f * (*x).width);
            offsety *= (0.05f * (*x).width);
            float det = SGGeneralLibrary::getdetsignonly((*(*x).pointsx)[sz - 3], (*(*x).pointsy)[sz - 3], (*(*x).pointsx)[sz - 2], (*(*x).pointsy)[sz - 2], (*(*x).pointsx)[sz - 1], (*(*x).pointsy)[sz - 1]);
            if(det < 0){
                v[6*sz - 8] = (*x).originx + (*(*x).pointsx)[sz - 1] - offsetx;
                v[6*sz - 7] = (*x).originy + (*(*x).pointsy)[sz - 1] - offsety;
                v[6*sz - 6] = (*x).originx + (*(*x).pointsx)[sz - 1] + offsetx;
                v[6*sz - 5] = (*x).originy + (*(*x).pointsy)[sz - 1] + offsety;
            }
            else{
                v[6*sz - 8] = (*x).originx + (*(*x).pointsx)[sz - 1] + offsetx;
                v[6*sz - 7] = (*x).originy + (*(*x).pointsy)[sz - 1] + offsety;
                v[6*sz - 6] = (*x).originx + (*(*x).pointsx)[sz - 1] - offsetx;
                v[6*sz - 5] = (*x).originy + (*(*x).pointsy)[sz - 1] - offsety;
            }
        }
        {
            int sz = (*(*x).pointsx).size();
            for(int i=1; i<sz-1; i++){
                float a1x = (*(*x).pointsx)[i-1];
                float a1y = (*(*x).pointsy)[i-1];
                float a2x = (*(*x).pointsx)[i];
                float a2y = (*(*x).pointsy)[i];
                float a3x = (*(*x).pointsx)[i+1];
                float a3y = (*(*x).pointsy)[i+1];
                float offset1x;
                float offset1y;
                float offset2x;
                float offset2y;
                float offset3x;
                float offset3y;
                float perp1x;
                float perp1y;
                float perp2x;
                float perp2y;
                float perp3x;
                float perp3y;
                SGGeneralLibrary::rotateplus90(a2x - a1x, a2y - a1y, perp1x, perp1y);
                SGGeneralLibrary::rotateplus90(a3x - a2x, a3y - a2y, perp3x, perp3y);
                SGGeneralLibrary::normalisevector(perp1x, perp1y, offset1x, offset1y);
                SGGeneralLibrary::normalisevector(perp3x, perp3y, offset3x, offset3y);
                offset1x *= (0.05f * (*x).width);
                offset1y *= (0.05f * (*x).width);
                offset3x *= (0.05f * (*x).width);
                offset3y *= (0.05f * (*x).width);
                perp2x = 0.5f * (offset1x + offset3x);
                perp2y = 0.5f * (offset1y + offset3y);
                SGGeneralLibrary::normalisevector(perp2x, perp2y, offset2x, offset2y);
                offset2x *= (0.05f * (*x).width);
                offset2y *= (0.05f * (*x).width);
                float det = SGGeneralLibrary::getdetsignonly(a1x, a1y, a2x, a2y, a3x, a3y);
                if(det < 0){
                    v[6*i - 2] = (*x).originx + (*(*x).pointsx)[i] + offset1x;
                    v[6*i - 1] = (*x).originy + (*(*x).pointsy)[i] + offset1y;
                    v[6*i] = (*x).originx + (*(*x).pointsx)[i] - offset2x;
                    v[6*i + 1] = (*x).originy + (*(*x).pointsy)[i] - offset2y;
                    v[6*i + 2] = (*x).originx + (*(*x).pointsx)[i] + offset3x;
                    v[6*i + 3] = (*x).originy + (*(*x).pointsy)[i] + offset3y;
                }
                else{
                    v[6*i - 2] = (*x).originx + (*(*x).pointsx)[i] - offset1x;
                    v[6*i - 1] = (*x).originy + (*(*x).pointsy)[i] - offset1y;
                    v[6*i] = (*x).originx + (*(*x).pointsx)[i] + offset2x;
                    v[6*i + 1] = (*x).originy + (*(*x).pointsy)[i] + offset2y;
                    v[6*i + 2] = (*x).originx + (*(*x).pointsx)[i] - offset3x;
                    v[6*i + 3] = (*x).originy + (*(*x).pointsy)[i] - offset3y;
                }
            }
        }
        {
            int sz = (*(*x).pointsx).size()-1;
            {
                t[0] = tofs;
                t[1] = tofs + 1;
                float det = SGGeneralLibrary::getdetsignonly((*(*x).pointsx)[0], (*(*x).pointsy)[0], (*(*x).pointsx)[1], (*(*x).pointsy)[1], (*(*x).pointsx)[2], (*(*x).pointsy)[2]);
                if(det >= 0){t[2] = tofs + 2;}
                else{t[2] = tofs + 3;}
                t[3] = tofs + 1;
                t[4] = tofs + 2;
                t[5] = tofs + 3;
                t[6] = tofs + 4;
                t[7] = tofs + 3;
                t[8] = tofs + 2;
            }
            for(int i=1; i<sz-1; i++){
                t[9*i] = tofs + 3*i;
                t[9*i + 1] = tofs + 3*i + 1;
                float det = SGGeneralLibrary::getdetsignonly((*(*x).pointsx)[i], (*(*x).pointsy)[i], (*(*x).pointsx)[i + 1], (*(*x).pointsy)[i + 1], (*(*x).pointsx)[i + 2], (*(*x).pointsy)[i + 2]);
                float det0 = SGGeneralLibrary::getdetsignonly((*(*x).pointsx)[i - 1], (*(*x).pointsy)[i - 1], (*(*x).pointsx)[i], (*(*x).pointsy)[i], (*(*x).pointsx)[i + 1], (*(*x).pointsy)[i + 1]);
                if((det < 0 && det0 < 0) || (det >= 0 && det0 >= 0)){t[9*i + 2] = tofs + 3*i + 3;}
                else{t[9*i + 2] = tofs + 3*i + 2;}
                t[9*i + 3] = tofs + 3*i + 1;
                t[9*i + 4] = tofs + 3*i + 2;
                t[9*i + 5] = tofs + 3*i + 3;
                t[9*i + 6] = tofs + 3*i + 4;
                t[9*i + 7] = tofs + 3*i + 3;
                t[9*i + 8] = tofs + 3*i + 2;
            }
            t[9*sz - 9] = tofs + 3*sz - 3;
            t[9*sz - 8] = tofs + 3*sz - 2;
            t[9*sz - 7] = tofs + 3*sz - 1;
            t[9*sz - 6] = tofs + 3*sz - 2;
            t[9*sz - 5] = tofs + 3*sz - 1;
            t[9*sz - 4] = tofs + 3*sz;
        }
    }

    (*x).renderrangeindex = pi;
    (*x).renderkey = di;
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindVertexArray((*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevao)[di]);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbo)[di]);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebo)[di]);
    (*SGNoteViewManagement::highlighterstrokerenderer).glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
    (*SGNoteViewManagement::highlighterstrokerenderer).glEnableVertexAttribArray(0);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBufferSubData(GL_ARRAY_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbors)[di] * 2 * sizeof(GLfloat), vs * 2 * sizeof(GLfloat), v);
    (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbors)[di] += vs;
    (*SGNoteViewManagement::highlighterstrokerenderer).glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebors)[di] * 3 * sizeof(GLuint), ts * 3 * sizeof(GLuint), t);
    (*x).ebostartindex = (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebors)[di];
    (*x).ebolength = ts;
    (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebors)[di] += ts;
    (*SGNoteViewManagement::highlighterstrokerenderer).doneCurrent();
}
