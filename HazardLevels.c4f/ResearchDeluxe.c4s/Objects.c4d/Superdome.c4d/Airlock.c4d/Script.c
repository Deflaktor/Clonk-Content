#strict

local iDir, iPos;   // iDir: welches Tor als nächstes geöffnet wird;
            // iPos: ob es die linke oder rechte Schleuse ist


public func SetLeft()  { iPos = -1; }
public func SetRight() { iPos = +1; }

protected func Initialize() { SetAction("Pump"); Close(); }


CheckEnergy:
  if(GameCall("MainEnergySupply",this())) {
    // Einmal Energie gehabt -> immer öffnen damit keine Clonks eingesperrt werden
    Local(0)=1;
    return(SetAction("Wait"));
  }
  return(1);

protected func Check()          // öffnet je nach Bedarf die Schleusen
{
  if(!GameCall("MainEnergySupply",this())&&!Local(0))
    return(SetAction("NoEnergy"));

  // will jemand aus der Schleuse raus?
  if(iDir == -1) return(SetAction("OpenLeft"));
  if(iDir == +1) return(SetAction("OpenRight"));

  // will jemand in die Schleuse rein? Hierbei haben alle die Vorrang, die von draußen (=Wasser) kommen
  if(iPos == -1) {
    if(Check4Clonk(-1)) return(SetAction("OpenLeft"));
    if(Check4Clonk(+1)) return(SetAction("OpenRight"));
  }
  else {
    if(Check4Clonk(+1)) return(SetAction("OpenRight"));
    if(Check4Clonk(-1)) return(SetAction("OpenLeft"));
  }
}

protected func WannaClose()     // soll Pumpen einschalten, will aber keine Clonks zerquetschen
{
  var iActDir;
  if(GetAction() eq "LeftOpen") iActDir = -1; else iActDir = +1;

  // Clonks gefunden: offen lassen
  if(Check4Clonk(iActDir)) return();

  // Clonks in der Schleuse
  if(Check4Clonk(0))
  {
    // Schleuse hat zum Passieren geöffnet: Warten bis der Clonk raus ist
    //if(iDir) return();
    // ansonsten schließen damit geschleust werden kann
    //iDir = -iActDir;
  }
  else iDir = 0;

  // schließen
  if(iActDir == -1) return(SetAction("CloseLeft"));
  if(iActDir == +1) return(SetAction("CloseRight"));
}

protected func Pumping()        // alles dicht: abpumpen
{
  DigFreeRect(GetX()-20,GetY()-17,40,35);

  var width = 40;
  var height = 35;
  var top = GetY() - height/2 + 4;
  var left = GetX() - width/2 + 4;
  var bottom = GetY() + height/2 - 3;
  var right = GetX() + width/2 - 4;
  DrawMaterialQuad("Wall",left,top,right,top,right,bottom,left,bottom,true);
  
  // jupp!
  SetAction("Wait");
}

protected func SoundOpen()  { Sound("Airlock1"); }
protected func SoundClose() { Sound("Airlock2"); }

private func Check4Clonk(int iD)    // sucht nach nicht verfeindeten Clonks die gerne rein oder raus möchten
{
  var pClonk;
  while(pClonk = FindObject(0,iD*30-20,-20,40,40,OCF_CrewMember(),0,0,NoContainer(),pClonk))
    if(!Hostile(GetOwner(pClonk),GetOwner()))
      // bingo!
        return(true);
  // niemand da
  return(false);
}

protected func LeftOpen()  { SetSolidMask(120,0,40,35); }
protected func RightOpen() { SetSolidMask(160,0,40,35); }
protected func Close()     { SetSolidMask(80,0,40,35);  }
