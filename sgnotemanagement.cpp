#include "sgnotemanagement.h"

bool SGNoteManagement::noteisopen = false;
QVector<SGPermanentObject*>* SGNoteManagement::notedata = nullptr;
QHash<int, SGRenderingRange*>* SGNoteManagement::renderingdata = nullptr;
QHash<int, SGColliderRange*>* SGNoteManagement::collidersdata = nullptr;
int SGNoteManagement::penstrokezindex = 0;
int SGNoteManagement::highlighterstrokezindex = 0;
