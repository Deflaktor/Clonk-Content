/*-- Waffenvorlage mit Munition --*/

#strict

// Local(6) = TEMP
// Local(7) = Current AmmoPacketID
// Local(8) = Current AmmoID
// Local(9) = Current AmmoMaxNumber
// --- Customize ---

DPS:
  return(38*Dmg()/(GetActMapVal("Length", "Reload") * GetActMapVal("Delay", "Reload") + GetActMapVal("Length", "Schuss") * GetActMapVal("Delay", "Schuss")));

DPA:
  if(Local(9))
    return(Dmg()*Local(9));
  return(0);
    
Dmg:
  if(Local(8)!=-1&&Local(8))
    return(DefinitionCall(Local(8), "Dmg"));
  return(0);
  
NeedsAmmo:
  return(1);

GetAmmoID:
  return(ExtractAmmunition(0));

GetAmmoPacketID:
  return(FindAmmoPacket(0));

GetAmmoNumber:
  return(CreateAmmo(0));

SelectionSound:
  Sound("Purge2");
  return(1);

ShotSound:
  Sound("Purge1");
  return(1);

ReloadSound:
  Sound("Buckle1");
  return(1);

public func Shot(object projectile, int dir, object carrier, int phase) {
  // Ammo abfeuern
  Exit(projectile, dir*26-13,0,0, 0,0,0 );
  ObjectCall(projectile,"Launch",dir,this());
  return(1);
}

// --- Customize Ende ---

Fire:
  // Noch beim Nachladen
  if (SEqual(GetAction(),"Reload")) return(0);
  // Träger
  SetVar(0,Contained());
  // Ammo suchen
  if (!SetVar(1,Contents())) return(CheckForAmmo());
  // Besitzer des Projektils setzen
  SetOwner(GetOwner(Var(0)),Var(1)); 
  // Richtung des Trägers abfragen
  SetVar(2,GetDir(Var(0)));
  SetVar(3,GetPhase(Var(0)));
  if(!Shot(Var(1), Var(2), Var(0), Var(3)))
    return(1);
  // Sound
  ShotSound();
  // Nachladen
  SetAction("Reload");
  MunUpdate(Var(0));
  return(1);

/* Bei Bedarf Träger nach passender Munition durchsuchen */
public func CheckForAmmo(bool silent) {
  var tmp = Local(7);
  var tmp2 = Local(8);
  // Beim Träger nach Ammopaket suchen und setze dieses in Local(7)
  if (SetLocal(8,ExtractAmmoPacket())==-1) {
    Local(7)=tmp;
	  Local(8)=tmp2;
    if(!silent)
      Sound("NoAmmo");
    return(0);
  }
  // Setze die Anzahl an Ammo in Local(9)
  SetLocal(9,GetAmmoNumber());
  // Setze AmmoID in Local(8)
  SetLocal(8,GetAmmoID());
  SetVar(0,Local(7));
  // Speichere die AmmoPacketID
  SetLocal(7,GetID(Local(7)));
  // Ammopaket löschen
  RemoveObject(Var(0));
  // Ammopaket aufteilen
  var i;
  for(i=1;i<=Local(9);i++)
    CreateContents(Local(8));
  // Nachladen
  SetAction("Reload");
  // Ammo Anzeige Updaten
  MunUpdate(Contained());
  // Sound
  ReloadSound();
  // Gib zurück ob es noch weitere Pakete gibt.
  // Und natürlich Local(7) zwischenspeichern
  SetVar(0,Local(7));
  SetVar(1,ExtractAmmoPacket()>=0);
  SetLocal(7,Var(0));
  return(Var(1));
}

ExtractAmmunition:
  return(Par(Local(8)));
  
CreateAmmo:
  return(Par(Local(8)));

public func GetAmmoPacketIDPerIndex(int index) {
  var tmp = Local(6);
  Local(6) = index;
  var tmp2 = GetAmmoPacketID(index);
  Local(6) = tmp;
  return(tmp2);
}
  
FindAmmoPacket:
  return(Par(Local(6)));
  
ExtractAmmoPacket:
  if(!Local(6)) Local(6)=Contained();
  if(SetLocal(7,FindContents(GetAmmoPacketIDPerIndex(0),Local(6)))) return(0);
  if(SetLocal(7,FindContents(GetAmmoPacketIDPerIndex(1),Local(6)))) return(1);
  if(SetLocal(7,FindContents(GetAmmoPacketIDPerIndex(2),Local(6)))) return(2);
  if(SetLocal(7,FindContents(GetAmmoPacketIDPerIndex(3),Local(6)))) return(3);
  if(SetLocal(7,FindContents(GetAmmoPacketIDPerIndex(4),Local(6)))) return(4);
  if(SetLocal(7,FindContents(GetAmmoPacketIDPerIndex(5),Local(6)))) return(5);
  if(SetLocal(7,FindContents(GetAmmoPacketIDPerIndex(6),Local(6)))) return(6);
  if(SetLocal(7,FindContents(GetAmmoPacketIDPerIndex(7),Local(6)))) return(7);
  if(SetLocal(7,FindContents(GetAmmoPacketIDPerIndex(8),Local(6)))) return(8);
  if(SetLocal(7,FindContents(GetAmmoPacketIDPerIndex(9),Local(6)))) return(9);
  // in proximity
  if(Local(6) == this())
    return(-1);
  var dist=5;
  if(GetAmmoPacketIDPerIndex(0))
    if(SetLocal(7,FindObject(GetAmmoPacketIDPerIndex(0),-dist,-dist,2*dist,2*dist,0,0,0,NoContainer()))) return(0);
  if(GetAmmoPacketIDPerIndex(1))
    if(SetLocal(7,FindObject(GetAmmoPacketIDPerIndex(1),-dist,-dist,2*dist,2*dist,0,0,0,NoContainer()))) return(1);
  if(GetAmmoPacketIDPerIndex(2))
    if(SetLocal(7,FindObject(GetAmmoPacketIDPerIndex(2),-dist,-dist,2*dist,2*dist,0,0,0,NoContainer()))) return(2);
  if(GetAmmoPacketIDPerIndex(3))
    if(SetLocal(7,FindObject(GetAmmoPacketIDPerIndex(3),-dist,-dist,2*dist,2*dist,0,0,0,NoContainer()))) return(3);
  if(GetAmmoPacketIDPerIndex(4))
    if(SetLocal(7,FindObject(GetAmmoPacketIDPerIndex(4),-dist,-dist,2*dist,2*dist,0,0,0,NoContainer()))) return(4);
  if(GetAmmoPacketIDPerIndex(5))
    if(SetLocal(7,FindObject(GetAmmoPacketIDPerIndex(5),-dist,-dist,2*dist,2*dist,0,0,0,NoContainer()))) return(5);
  if(GetAmmoPacketIDPerIndex(6))
    if(SetLocal(7,FindObject(GetAmmoPacketIDPerIndex(6),-dist,-dist,2*dist,2*dist,0,0,0,NoContainer()))) return(6);
  if(GetAmmoPacketIDPerIndex(7))
    if(SetLocal(7,FindObject(GetAmmoPacketIDPerIndex(7),-dist,-dist,2*dist,2*dist,0,0,0,NoContainer()))) return(7);
  if(GetAmmoPacketIDPerIndex(8))
    if(SetLocal(7,FindObject(GetAmmoPacketIDPerIndex(8),-dist,-dist,2*dist,2*dist,0,0,0,NoContainer()))) return(8);
  if(GetAmmoPacketIDPerIndex(9))
    if(SetLocal(7,FindObject(GetAmmoPacketIDPerIndex(9),-dist,-dist,2*dist,2*dist,0,0,0,NoContainer()))) return(9);
  return(-1);

/* Objekt wurde ausgewählt */
public Selection:
  MunUpdate(Contained());
  SelectionSound();
  return(1);

Collection:
  CheckAmmoPacketInside();
  MunUpdate(Contained());
  return(1);

private CheckAmmoPacketInside:
  var i,count=0;
  Local(6)=this();
  var tmp = Local(7);
  var tmp2 = Local(8);
  while((i = ExtractAmmoPacket()) != -1) {
    Local(8) = i;
	if(GetAmmoID()==GetID(Local(7))) {
	  Local(7) = tmp;
	  Local(8) = tmp2;
	  return(0);
	}
    // Setze die Anzahl an Ammo in Local(9)
    Local(9) = GetAmmoNumber();
    // Setze AmmoID in Local(8)
    Local(8) = GetAmmoID();
    Var(0) = Local(7);
    // Speichere die AmmoPacketID
    Local(7) = GetID(Local(7));
    // Ammopaket löschen
    RemoveObject(Var(0));
    // Ammopaket aufteilen
    var i;
    for(i=1;i<=Local(9);i++)
      CreateContents(Local(8));
	count+=Local(9);
  }
  if(count)
    Local(9)=count;
  Local(6)=0;
  return(1);
  
/* Objekt ist eine Waffe */
public IsWeapon:
  return(LongRangeWeapon());

public MinRange:
  return(0);

public MaxRange:
  return(100);

/* Objekt Munition */
public MaxAmmo:
  return(Local(9));
public Ammo:
  if(Local(8)==-1)
    return(0);
  return(ContentsCount(Local(8)));

Timer:
  if(GBackSolid(0,0)) if(GBackLiquid(0,-2)) SetPosition(GetX(),GetY()-1);
  return(1);
  
MunUpdate:
  CheckAmmoPacketInside();
  if(Contents(0,Par(0))!=this())
    return(1);
  SetPhysical("Magic",0,2,Par(0));
  DoMagicEnergy(0,Par(0));
  if(Local(8)==-1)
    return(1);
  SetPhysical("Magic",100000,2,Par(0));
  DoMagicEnergy((ContentsCount(Local(8))*100)/Local(9),Par(0));
  return(1);
