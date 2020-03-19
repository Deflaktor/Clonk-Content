/*-- Blitz --*/

#strict
#include _POV

Dmg:
  return(4);

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
  // Geräusch
  if (!Random(5)) Sound("Thunder*");
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
 /* while(i<GetVertexNum()-1)
  {
    DrawParticleLine ("LightningSpark", GetVertex(i)-GetX(), GetVertex(i, 1)-GetY(), 
		    GetVertex(i+1)-GetX(), GetVertex(i+1,1)-GetY(), 6, 60, RGB(0,100,255));
    DrawParticleLine ("LightningSpark", GetVertex(i)-GetX(), GetVertex(i, 1)-GetY(), 
		    GetVertex(i+1)-GetX(), GetVertex(i+1,1)-GetY(),  3, 25, RGB(250,250,255));
    i++;
  }*/
}

/* Bewegung */

private func Advance()
{
  var obj;
  
  // Einschlag
  var iVtx = GetVertexNum()-1, iVtxX = GetVertex(iVtx, 0), iVtxY = GetVertex(iVtx, 1);
  if (GBackSolid(iVtxX-GetX(), iVtxY-GetY() ))
    return(Remove());

  // Neuen Eckpunkt
  if (!AddVertex( iVtxX+iAdvX+RandomX(-5,5), iVtxY+iAdvY+RandomX(-3,3)))
    return(Remove());

  SetPosition(GetVertex(GetVertexNum()), GetVertex(GetVertexNum(), 1));
  
  // Im Wasser?
  if (GBackLiquid(iVtxX-GetX(), iVtxY-GetY() ))
  {
    // Alle Lebewesen in der Nähe bekommen was ab
	while(obj=FindObject(0,iVtxX-GetX()-400, iVtxY-GetY()-400, 800, 800,OCF_Alive(),0,0,NoContainer(),obj))
    {
      if(!PathFree(iVtxX, iVtxY, GetX(obj), GetY(obj))) continue;
      if(!GBackLiquid(GetX(obj)-GetX(), GetY(obj)-GetY())) continue;
      // Selber so ausrichten, dass die Schlagrichtung stimmt
      var xdiff = GetX(obj) - GetVertex(Max(GetVertexNum()-3, 0), 0);
      if (!xdiff) xdiff = iAdvX;
      if (xdiff > 0) SetDir(DIR_Right); else SetDir(DIR_Left);
      obj->~LightningStrike(this());
      Punch(obj, 6);
      DrawParticleLine ("LightningSpark2", iVtxX-GetX(), iVtxY-GetY(), 
           GetX(obj)-GetX(), GetY(obj)-GetY(), 6, 60, RGB(0,100,255));
      DrawParticleLine ("LightningSpark2", iVtxX-GetX(), iVtxY-GetY(), 
            GetX(obj)-GetX(), GetY(obj)-GetY(),  3, 25, RGB(250,250,255));
    }
    return(Remove());
  }
  
  // Objektanziehung
  iVtx = GetVertexNum()-1; iVtxX = GetVertex(iVtx, 0); iVtxY = GetVertex(iVtx, 1);
  if (iVtx>5)
  {
    var obj;
    if(obj=CheckHit(iVtxX-GetX()-15, iVtxY-GetY()-15, 30, 30))
    {
      if(!PathFree(iVtxX, iVtxY, GetX(obj), GetY(obj))) continue;
      Attraction(obj);
      break;
    }
	if (obj = FindObject( 0, iVtxX-GetX()-50, iVtxY-GetY()-50, 100, 100, OCF_AttractLightning(), 0,0, NoContainer()  ) )
      Attraction(obj);
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
  if (GetAlive(obj)) Punch(obj, Dmg());
  DoDamage(Dmg()*2, obj);
}

public func LightningStrike(obj)
{
  // Einschlag in Objekt
  AddVertex( GetVertex(GetVertexNum(obj)-1,0,obj),
             GetVertex(GetVertexNum(obj)-1,1,obj) );
  SetAction("Connect");
}

private func AttractionLightning(obj)
{
  // Einschlag in Objekt
  AddVertex( GetVertex(GetVertexNum(obj)-1,0,obj),
             GetVertex(GetVertexNum(obj)-1,1,obj) );
  obj->~LightningStrike(this());
  SetAction("Connect");
}

/* Ende */

private func Remove()
{
  var i=0;
  // Nachleuchten
 /* while(i<GetVertexNum()-1)
  {
    DrawParticleLine ("LightningSpark2", GetVertex(i)-GetX(), GetVertex(i, 1)-GetY(), 
		    GetVertex(i+1)-GetX(), GetVertex(i+1,1)-GetY(), 6, 60, RGB(0,100,255));
    DrawParticleLine ("LightningSpark2", GetVertex(i)-GetX(), GetVertex(i, 1)-GetY(), 
		    GetVertex(i+1)-GetX(), GetVertex(i+1,1)-GetY(),  3, 25, RGB(250,250,255));
    i++;
  }*/
  
  RemoveObject();
}
