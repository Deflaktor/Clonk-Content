/*-- Blitz --*/

#strict
#include _POV

Dmg:
  return(5);


/* Locals */

local iAdvX, iVarX, // Bewegung / Abweichung X
      iAdvY, iVarY; // Bewegung / Abweichung Y

/* Aktivierung */

public func Activate(iStartX, iStartY, iAdvanceX, iRandomX, iAdvanceY, iRandomY)
{
  // Startposition
  AddVertex(iStartX,iStartY);
  // Bewegungsverhalten
  iAdvX=iAdvanceX; iVarX=iRandomX;
  iAdvY=iAdvanceY; iVarY=iRandomY;
  // Aktion setzen
  SetAction("Advance");
  // Richtung setzen für korrektes Punch
  if (iAdvX > 0) SetDir(DIR_Right); else SetDir(DIR_Left);
  return(1);
}

public func Launch(iX, iY, iAngle)
{
  var XDir;
  XDir = Cos(iAngle, 10, 10);
//  if (iDir == DIR_Left) XDir = -Cos(iAngle, 10, 10);
//  else (XDir = +Cos(iAngle, 10, 10));
  Activate(iX, iY, XDir, 0, -Sin(iAngle, 10, 10));
  return(1);
}

private func Timer()
{
  var i=0;
  // Partikel-Effekt
  while(i<GetVertexNum()-1)
  {
    DrawParticleLine ("LightningSpark", GetVertex(i)-GetX(), GetVertex(i, 1)-GetY(), 
		    GetVertex(i+1)-GetX(), GetVertex(i+1,1)-GetY(), 6, 60, RGB(255,20,0));
    DrawParticleLine ("LightningSpark", GetVertex(i)-GetX(), GetVertex(i, 1)-GetY(), 
		    GetVertex(i+1)-GetX(), GetVertex(i+1,1)-GetY(),  3, 25, RGB(255,250,250));
    i++;
  }
}



/* Bewegung */

private func Advance()
{
  var obj;
  
  // Einschlag
  var iVtx = GetVertexNum()-1, iVtxX = GetVertex(iVtx, 0), iVtxY = GetVertex(iVtx, 1);
  if (GBackSolid(iVtxX-GetX(), iVtxY-GetY() )) {
    ObjectCall(CreateObject(EXPL),"Launch",Dmg()*8/5);
    return(Remove());
  }

  // Neuen Eckpunkt
  if (!AddVertex( iVtxX+iAdvX+RandomX(-5,5), iVtxY+iAdvY+RandomX(-3,3)))
    return(Remove());

  SetPosition(GetVertex(GetVertexNum()), GetVertex(GetVertexNum(), 1));
  
  // Objektanziehung
  iVtx = GetVertexNum()-1; iVtxX = GetVertex(iVtx, 0); iVtxY = GetVertex(iVtx, 1);
  if (iVtx>2)
  {
    var obj;
    if(obj=CheckHit(iVtxX-GetX()-15, iVtxY-GetY()-15, 30, 30))
    {
      if(!PathFree(iVtxX, iVtxY, GetX(obj), GetY(obj))) continue;
      Attraction(obj);
      break;
    }
  }
  while(obj=FindObject(GetID(),iVtxX-GetX()-20, iVtxY-GetY()-20, 40, 40,0,"Advance",0,NoContainer(),obj))
  {
    if(GetOwner(obj)!=GetOwner()) {
      AttractionLightning(obj);
      break;
	}
  }
  
  Timer();
}

/* Effekte */

private func Sparkle()
{
  Timer();
  var iVtx = GetVertexNum()-1, iVtxX = GetVertex(iVtx, 0), iVtxY = GetVertex(iVtx, 1);
  CastObjects(SPRK,1,20,iVtxX-GetX(), iVtxY-GetY());
  return(true);
}

/* Anziehung */

private func Attraction(obj)
{
  // Einschlag in Objekt
  AddVertex( GetVertex(0,0,obj)+GetX(obj),
             GetVertex(0,1,obj)+GetY(obj) );
  obj->~LightningStrike(this());
  SetAction("Connect");
  if (GetAlive(obj)) Punch(obj, Dmg()/5);
  // DoDamage(Dmg(), obj);
  ObjectCall(CreateObject(EXPL),"Launch",Dmg()*8/5);
  
  Remove();
}

public func LightningStrike(obj)
{
  // Einschlag in Objekt
  AddVertex( GetVertex(GetVertexNum(obj)-1,0,obj),
             GetVertex(GetVertexNum(obj)-1,1,obj) );
  SetAction("Connect");
  ObjectCall(CreateObject(EXPL),"Launch",Dmg()*8/5);
  Remove();
}

private func AttractionLightning(obj)
{
  // Einschlag in Objekt
  AddVertex( GetVertex(GetVertexNum(obj)-1,0,obj),
             GetVertex(GetVertexNum(obj)-1,1,obj) );
  obj->~LightningStrike(this());
  SetAction("Connect");
  ObjectCall(CreateObject(EXPL),"Launch",Dmg()*8/5);
  Remove();
}

/* Ende */

private func Remove()
{
  var i=0;
  // Nachleuchten
  while(i<GetVertexNum()-1)
  {
    DrawParticleLine ("LightningSpark2", GetVertex(i)-GetX(), GetVertex(i, 1)-GetY(), 
		    GetVertex(i+1)-GetX(), GetVertex(i+1,1)-GetY(), 6, 60, RGB(255,20,0));
    DrawParticleLine ("LightningSpark2", GetVertex(i)-GetX(), GetVertex(i, 1)-GetY(), 
		    GetVertex(i+1)-GetX(), GetVertex(i+1,1)-GetY(),  3, 25, RGB(255,250,250));
    i++;
  }
  RemoveObject();
}

