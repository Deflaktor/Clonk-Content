/*-- Fisch --*/

#strict

public func IsPossessible() { return(1); }

/* Initialisierung */

protected func Initialize() { return(Birth()); }

/* TimerCall mit KI-Steuerung */

private func Activity() 
{
  if (GetAction() eq "Walk") WalkDir();
  
  // Vor Bedrohungen flüchten
  var threat, found_threat;
  if (!Contained() && InLiquid()) 
  {
    while (threat = FindObject(0, -1, -1, -1, -1, 0, 0, 0, 0, threat)) 
    {
      if (ObjectDistance(this(), threat) > 100) break;
      // Bedrohung bewegt sich nicht?
      if (Inside(GetXDir(threat), -2, +2) && Inside(GetYDir(threat), -3, +3)) continue;
      // Kontakt zum Boden?
      if (GetContact(threat, -1, 8)) continue;
      // Bedrohung nicht im Wasser oder in einem Container -> Nächstes Objekt
      if (!InLiquid(threat) || Contained(threat)) continue;
      // Keine Regelobjekte, Luftblasen etc.
      var cat = GetCategory(threat);
      if (!(cat & C4D_Living()   || cat & C4D_Object() ||
          cat & C4D_Vehicle()  || cat & C4D_Structure())) continue;
      if (cat & C4D_Background() || cat & C4D_Parallax())   continue;
      if (GetID(threat) == FXU1) continue;
      // Keine unsichtbaren Objekte
      if (GetVisibility(threat)) continue;
      // Keine toten Clonks
      if (threat->~IsClonk() && !GetAlive(threat)) continue;
      // Sind ziemlich naiv und schwimmen nicht vor anderen Tieren weg
      if (!GetAlive(threat) || threat->~IsClonk()) {
        found_threat = true;
        var xdist = GetX(threat) - GetX();
        var ydist = GetY(threat) - GetY();
        var axdist = Abs(xdist);
        var aydist = Abs(ydist);
        var xsign = xdist / axdist;
        var ysign = ydist / aydist;
        var fleex = GetX() - xsign * (1500 / BoundBy(axdist, 20, 80)); // 20..80 -> 70..15
        var fleey = GetY() - ysign * (1000 / BoundBy(aydist, 20, 80)); // 20..80 -> 50..10
        SetCommand(this(), "MoveTo", 0, fleex, fleey, 0, true);
      }
    }
  }

  // Wenn keine Bedrohung mehr oder nicht im Wasser aufhören zu fliehen
  if (!InLiquid() || Contained() || (!found_threat && GetCommand() eq "MoveTo")) 
    SetCommand(this(), "None");
  
  // Schwimmverhalten
  if (!GBackLiquid(0, -8) && GetAction() ne "Walk") return(SetComDir(COMD_Down()));
  if (Random(2)) return(1);
  if (GetAction()ne"Swim") return(1);
  if (!Random(5)) SetComDir(COMD_Up());

  // Umdrehen
  if (Random(2)) return(TurnRight());
  return(TurnLeft());
}

private func WalkDir()
{
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
  return(1);
}

/* Kontakte */

protected func ContactLeft()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  return(TurnRight());
}

protected func ContactRight()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  return(TurnLeft());
}

protected func ContactTop()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  SetComDir(COMD_Down());
  return(1);
}

protected func ContactBottom()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  if (GetAction() ne "Walk") SetComDir(COMD_Up());
  if (Random(10)) SetComDir(COMD_Right());
  if (Random(10)) SetComDir(COMD_Left());
  return(1);
}

/* Aktionen */

private func TurnRight()
{
  if (Stuck() || (GetAction() ne "Walk" && GetAction() ne "Swim")) return();
  if (GetXDir() < 0) SetXDir(0);
  SetDir(DIR_Right());
  SetComDir(COMD_Right());
  return(1);
}

private func TurnLeft()
{
  if (Stuck() || (GetAction() ne "Walk" && GetAction() ne "Swim")) return();
  if (GetXDir() > 0) SetXDir(0);
  SetDir(DIR_Left());
  SetComDir(COMD_Left());
  return(1);
}

public func Entrance(container) 
{
  // Damit der Fisch nicht aus U-Booten flieht und so.
  SetCommand(this(), "None");
}

/* Einwirkungen */

public func Eat(pByObject)
{
  pByObject->~Feed(50);
  RemoveObject();
  return(1);
}

public func Cook()
{
  ChangeDef(CFSH);
  SetAlive(0);
  return(1);
}

protected func Death()
{
  SetDir(0);
  ChangeDef(DFSH);
  SetAction("Dead");
  return(1);
}

/* Vermehrung */

private func SpecialReprodCond()
{
  return(GetAction() eq "Swim");
}

public func Birth()
{
  SetColorDw(HSL(Random(256),255,100+Random(60)));
  SetAction("Swim");
  SetComDir(COMD_Left());
  if(Random(2)) SetComDir(COMD_Right());
}
 
/* Anti-Sofort-Wieder einsammeln */

public func RejectEntrance(pContainer)
{
  // nur einsammeln lassen wenn er nicht springt
  // Aber nur von Clonks - Kochtöpfe dürfen beispielsweise immer
  if (GetAction() eq "Jump" || GetAction() eq "Walk")
    if (GetCategory(pContainer) & C4D_Living())
      if (Random(10))
        return(1);
}

/* Steuerung durch Besessenheit */

protected func RejectCollect(c4ID, pObject)
{
 var iEffectNumber, pSorcerer;
 if (iEffectNumber = GetEffect("PossessionSpell", this()))
  if (pSorcerer = EffectVar(0, this(), iEffectNumber))
   if (!GetEffect("IntCollectionDelay", this()))
    if (!pSorcerer->Contents())
     if (!(pObject->GetOCF() & OCF_Living()))
      Collect(pObject, pSorcerer);
 return(1);
}

protected func ControlCommand(szCommand, pTarget, iTx, iTy)
{
 // Bewegungskommando
 if (szCommand eq "MoveTo")
  return(SetCommand(this(),szCommand, pTarget, iTx, iTy));
 return(0);
}

protected func ContainedLeft()
{
 [$TxtMovement$]
 SetCommand(this(),"None");
 TurnLeft();
 return(1);
}

protected func ContainedRight()
{
 [$TxtMovement$]
 SetCommand(this(),"None");
 TurnRight();
 return(1);
}

protected func ContainedUp()
{
 [$TxtMovement$]
 SetCommand(this(),"None");
 SetComDir(COMD_Up());
 return(1);
}

protected func ContainedDown()
{
 [$TxtMovement$]
 SetCommand(this(),"None");
 SetComDir(COMD_Down());
 return(1);
}

protected func ContainedThrow()
{
 [$TxtDrop$]
 var iEffectNumber, pSorcerer;
 if (iEffectNumber = GetEffect("PossessionSpell", this()))
  if (pSorcerer = EffectVar(0, this(), iEffectNumber))
  {
   if (pSorcerer->Contents()) pSorcerer->Contents()->Exit(0,0,6);
   AddEffect("IntCollectionDelay", this(), 1, 70);
  }
 return(1);
}

protected func ContainedDigDouble()
{
 [$TxtLeave$]
 RemoveEffect("PossessionSpell", this());
 return(1);
}

/* Aufwertungszauberkombo: Mit Fisch wird der Clonk zum Aquaclonk */
public func GetRevaluationCombo(object pClonk) { return(ACLK); }