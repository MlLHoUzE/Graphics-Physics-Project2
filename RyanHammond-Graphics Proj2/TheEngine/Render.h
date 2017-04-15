#ifndef _Render_HG_
#define _Render_HG_
#include  "cEntity.h"
#include "cPlayer.h"

void DrawObject(cEntity* pCurEntity, glm::mat4 matModel, bool bUseLighting = true);

void DrawObject(cPlayer* pCurPlayer, glm::mat4 matModel, bool bUseLighting = true);


#endif