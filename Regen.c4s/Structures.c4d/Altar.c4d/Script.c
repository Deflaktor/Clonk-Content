/*-- Altar --*/

#strict

local castle,standalone;

protected func Completion()
{
 // Nach dem Bauen Clonks nach oben versetzen? 
 for(var clnk in FindObjects(Find_Distance(20,0,0),Find_Or(Find_OCF(OCF_Alive),Find_Category(16))))
 {
  var cnt=0;
  while(cnt < 10 && Stuck(clnk)){SetPosition(GetX(clnk),GetY(clnk)-1,clnk);cnt++;}
  // Nicht, dass es nachher in irgendeine Decke versetzt..
  if(Stuck(clnk))SetPosition(GetX(clnk),GetY(clnk)+cnt,clnk);
 }
 if(!castle) standalone = true;
}

public func InitializeConstruction() {
 castle = FindCastlePart(0, +10);
 if(castle)
   SetObjectOrder(this(),castle,1);
 return(castle);
}

public func Activity() {
  if(!castle&&!standalone) {
    Split2Components();
  }
  if(castle&&!standalone) {
    if(!(GetOCF(castle) & OCF_Fullcon()))
	  Split2Components();
  }
  if(!(GetOCF()&OCF_Fullcon()))
    return(1);
  // Gegner vertreiben  
  var enemy;
  while(enemy = FindObject(KIL1, -180, -180, 360, 360, OCF_Alive(), 0, 0, 0, enemy) )
  {
    var angl = Angle(GetX(), GetY(), GetX(enemy), GetY(enemy) );
    var dist = 400;
    SetCommand(enemy, "MoveTo", 0, GetX() + Sin(angl, dist), GetY() - Cos(angl, dist) );
  }
}

public func ControlDigDouble(object pClonk)
{
  [$TxtDeconstruct$|Image=SG01:5]
  Sound("CloseViewport");
  CreateObject(CNKT,0,20,GetOwner(pClonk) );
  Split2Components();
}

// Anderes Bauteil in entsprechender Richtung suchen
public func FindCastlePart(int iX, int iY, object pObj)
{
  while (pObj = FindObject(0, iX,iY,0,0, OCF_Fullcon(),0,0, NoContainer(), pObj))
    if (GetID(pObj)==CST1||GetID(pObj)==CST2)
      return(pObj);
  // Keins gefunden
  return(0);
}

private func CheckPlacement(int x, int y)
{
  // Nur vor Burgteile
  var castle = FindCastlePart(x, y - 10);
  if(!castle) return("Kann nur auf Burgen aufgebaut werden.");

  // Nur oben drauf
  if(GetY(castle)<y-15) return("Muss auf die Plattform der Burg aufgebaut werden.");
  
  // Nicht zu weit Außen
  if(!(GetX(castle)-20<x&&x<20+GetX(castle))) return("Nicht genug Platz.");
  
  return(castle);
}

/* Callback vom Bausatz */

public func RejectConstruction(int x, int y, object clonk)
{
  var err = CheckPlacement(GetX(clonk) + x, GetY(clonk) + y);
  if(GetType(err) == C4V_String() )
  {
    Message(err, clonk);
    Sound("Error", 0, clonk);
    return(1);
  }
  else
  {
    return(0);
  }
}

public func NoConstructionCheck() {
  return(1);
}