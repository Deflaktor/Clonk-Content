/*-- Wipf --*/

#strict
#include HH00


local lorry_wipf;	// Speichert das zugehörige Lorenwipf-Objekt

ControlThrow: 
   Sound("Snuff*");
var comd = COMD_Right();
    if (GetDir() == DIR_Right()) comd = COMD_Left();
    SetComDir(comd);
    Jump();
    SetAction("Tumble");


   return();

ControlDownDouble:
SetComDir(COMD_Stop());
SitDown();
return(1);

ControlDown:
SetComDir(COMD_Stop());
return(1);

ControlRight:
  if (Stuck()) return(0);
  if (GetDir()!=DIR_Right()) if (!SetAction("Turn")) return (0);
  SetXDir(0);
  SetDir(DIR_Right());
  SetComDir(COMD_Right()); 
  return(1);

ControlLeft:
  if (Stuck()) return(0);
  if (GetDir()!=DIR_Left()) if (!SetAction("Turn")) return (0);
  SetXDir(0);
  SetDir(DIR_Left());
  SetComDir(COMD_Left()); 
  return(1);

private ControlUp:
  Jump();
  return(1);

private SitDown:
  SetAction("Sit");
  SetDir(0);
  return(1);

ControlDig:
  SetAction("Dig");
  SetComDir(Sum(2,Random(7)));
  if (GetComDir()==COMD_Down()) SetComDir(COMD_Stop());
  return(1);

private DigSound:
 
  return(1);

ControlDigDouble:
ObjectCall(this(),"readyrechange");
return(1);

Sitting:
return();

/* Einwirkungen */

protected CatchBlow:
  if (GetAction()S="Dead") return(0);
  if (!Random(3)) Sound("WipfHurt");
  return(1);

protected func Death() {
  Sound("WipfDead");
  rechange();
  Kill();
  return(1);
}

public func Entrance(obj) {
  // Ist in eine Lore gegangen?
  if (ObjectCall(obj, "IsLorry")) {
    // Lorenwipf suchen, der zu der Lore gehört
    lorry_wipf = FindObject(LWPF, 0, 0, 0, 0, 0, 0, obj);
    // Lorenwipf gefunden?
    if (lorry_wipf) {
      // Benachrichtigen, dass wir jetzt in der Lore sind
      ObjectCall(lorry_wipf, "IncreaseCount");
    }
    // Keinen Lorenwipf gefunden?
    else {
      // Erzeugen wir halt einen
      lorry_wipf = CreateObject(LWPF, 0, 0, -1);
      // An die Lore kleben
      ObjectCall(lorry_wipf, "AttachTo", obj);
    }
  }
}

protected func Departure(obj) {
  LeftLorry();
}

protected func Destruction() {
  LeftLorry();
}

protected func LeftLorry() {
  // Lorenwipfobjekt informieren
  if (lorry_wipf) ObjectCall(lorry_wipf, "DecreaseCount");
  lorry_wipf = 0;
}

/* Fortpflanzung */

public Reproduction:
 																			  if (!Random(130)) CreateObject(FMEG,0,7,-1);
  return(1);

public Birth:
  SetAction("Walk");
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
  return(1);

readyrechange:
SetPhysical("Dig",Local(10), 2,this());
SetPhysical("Swim",Local(12), 2,this());
rechange();
return();

UserID:
SetLocal(11,Par());

SetLocal(12,GetPhysical("Swim", 2,this()));
if(!Local(12))
  SetLocal(12,GetPhysical( "Swim", 1, this()));


SetLocal(10,GetPhysical("Dig", 2,this()));
if(!Local(10))
	SetLocal(10,GetPhysical("Dig", 1,this()));
SetPhysical ("Dig",80000,2); 
SetPhysical ("Swim",60000,2); 
Birth();
return(1);