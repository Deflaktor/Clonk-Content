
local weapon;

#strict
#include _KI_

local patrolPosX, patrolPosY;

Debug: return(0);

// Nick-Nack

Initialize:
  SetAction("Walk");
  SetDir(Random(2));
  SetEntrance(1);
  SetOwner(-1);
  SetPatrolPosition();
  SetColor(Random(12));
  return(_inherited());

public func SetPatrolPosition() {
  patrolPosX = GetX();
  patrolPosY = GetY();
}

private HasWeapon:
  while(Var(0)=Contents(Var(2)++)) {
    if(ObjectCall(Var(0), "IsWeapon")||ObjectCall(Var(0), "IsThrowWeapon"))
      return(1);
  }
  return(0);

protected Patrol:
  SetCommand(this(), "MoveTo", 0, patrolPosX-50+Random(100), patrolPosY-50);
  AppendCommand(this(), "Wait", 0, 0, 0, 0, 50);
  return(1);
  
/* TimerCall */
protected Activity:
  _inherited();
  // Wenn er nicht mehr lebt, abbrechen
  if(Not(GetAlive())) return(0);
  
  if(GetEnergy()<GetPhysical("Energy", 0)/1000/2)
    ObjectCall(FindContents(_MED),"Activate",this());
  // WayPoints auf Waffen, die man schon eingesammelt hat, löschen
  /*if(ObjectCall(target, "IsWeapon")&&FindContents(GetID(target)))
    target=0;*/

  // WayPoints auf Waffen, die man nicht mehr kriegen kann, löschen
  /*if(ObjectCall(target, "IsWeapon")&&!WeaponFree(target))
    target=0;*/

  // Je nach Schwierigkeitsgrad abbrechen
 // if(Not(Difficulty())) return(0);
 
  if(HasWeapon())
    SetEnemy(); // Gegner bestimmen



  if(target) {
    if(!(GetCommand() S= "MoveTo"))
      SetCommand(this(), "MoveTo", target);
  } else {
    if(lastSightTime<10&&lastSightX&&lastSightY) {
      SetCommand(this(), "MoveTo", 0, lastSightX, lastSightY);
    } else if(lastSightTime<30&&lastSightX&&lastSightY) {
      SetCommand(this(), "MoveTo", 0, lastSightX-50+Random(100), lastSightY-50+Random(100));
    } else if(lastSightTime>=30&&lastSightTime%30==0) {
      Patrol();
    }
  }

  this()->~CheckArmed(); // Grafik anpassen

  // Wenn er keine Waffe oder keinen Gegner hat, nach einer Waffe suchen
  //if(!target||!HasWeapon()) Search4Weapons();

  // Wenn er einen Gegner hat, und entweder kein Medipack da ist oder seine Energie größer
  // 10 ist, angreifen
  //if(!CheckEnergy()) 
  ForceFieldGenerator();
  AttackEnemy();
  
  WaySearch(); // Wegroutine aufrufen
  return(1);

Help1:
while(Not(Equal(ID(weapon),ID(Contents(0))))) ShiftContents();
return(1);

ForceFieldGenerator:
  var gen = FindContents(_FFG);
  if(!gen) return(0);
  if(!(gen->Ammo())) {
    if(gen->ExtractAmmoPacket()==-1)
    return(0);
  }
  var fieldId = Local(8,gen);
  var active = !(gen->ActIdle());
  if(target) {
    // normal force field not suited for attack -> deactivate
    if(fieldId==_FFD&&active)
      gen->Activate(this());
    // other force fields are activated
    if(fieldId!=_FFD&&!active)
      gen->Activate(this());
  } else {
    // normal force field suited for evasion -> activate
    if(fieldId==_FFD&&!active&&lastSightTime>10)
      gen->Activate(this());
    // other force fields are deactivated to save energy
    if(fieldId!=_FFD&&active)
      gen->Activate(this());
  }
  return(1);

SetEnemy:
  SetVar(0,FindTarget(0,0,-1,-1));
  //if(OnFire())
  //  return(target=Var(0)); // Wenn man brennt, nahesten Gegner angreifen (anzünden)

  // Wenn der naheste Gegner zu weit weg ist, Verschnaufpause
  if(GreaterThan(ObjectDistance(this(),Var(0)),600))
    return(target=0); // Gegner zu weit weg

  // Gegner angreifen, der am nahesten ist
  return(target=Var(0));

LowEnergyEnemy: //Par(0) C4Object, Par(1) C4Object, Par(2) C4Object
  // Bei nur einem Übergabeparameter
  if(Not(Par(1))) return(Par(0));

  // Bei nur zwei Übergabeparametern das Objekt, mit der geringsten Energie zurückgeben
  if(Not(Par(2))) if(LessThan(GetEnergy(Par(1)),GetEnergy(Par(0)))) return(Par(1));
  if(Not(Par(2))) return(Par(0));

  // Bei drei Übergabeparametern, ein Objekt, das nicht die geringste Energie hat, aussortieren,
  // und LowEnergyEnemy mit den beiden anderen Parametern aufrufen
  if(GreaterThan(GetEnergy(Par(0)),GetEnergy(Par(1)))) return(LowEnergyEnemy(Par(1),Par(2)));
  if(GreaterThan(GetEnergy(Par(1)),GetEnergy(Par(2)))) return(LowEnergyEnemy(Par(0),Par(2)));
  return(LowEnergyEnemy(Par(0),Par(1)));

// Hallifax
// Die Waffenauswahlroutine
ChooseWeapon:
  if(Not(target)) return();
  //if(OnFire()) return(weapon=0); // Wenn man brennt, Nahkampf (Gegner anzünden)
  //Log("Weapon");
  Var(0)=ObjectXDistance(target,this());
  if(Var(0)<100)
    Var(1)=ShortRangeWeapon()|MiddleRangeWeapon();
  else if(Var(0)<300)
    Var(1)=MiddleRangeWeapon();
  else 
    Var(1)=LongRangeWeapon();
  var mostValuedWeapon = 0;
  var weaponTooClose = 0;
  
  mostValuedWeapon = GetMostValuableWeapon(Var(0),0,0,1);
  if(!mostValuedWeapon)
    mostValuedWeapon = GetMostValuableWeapon(Var(0),0,0,0);
  if(!mostValuedWeapon)
    mostValuedWeapon = GetMostValuableWeapon(Var(0),0,1,1);
  if(!mostValuedWeapon)
    mostValuedWeapon = GetMostValuableWeapon(Var(0),0,1,0);

  if(!mostValuedWeapon)
    mostValuedWeapon = GetMostValuableWeapon(Var(0),1,1,0);
  if(!mostValuedWeapon)
    mostValuedWeapon = GetMostValuableWeapon(Var(0),1,1,1);

  // if no weapon, try to activate some items, maybe there is something to Unpack
  if(!mostValuedWeapon) {
    var currentItem;
    var i=0;
    while(currentItem=Contents(i++)) {
      if(ObjectCall(currentItem, "Activate"))
        break;
    }
  }

  // if the current weapon is Firing, switch it off
  if(weapon) 
    if(mostValuedWeapon!=weapon)
      if(weapon->~IsFiring())
        weapon->~Fire();


  return(weapon=mostValuedWeapon);

private func GetMostValuableWeapon(int distance, bool ignoreMinDistance, bool ignoreMaxDistance, bool needsAmmo) {
  var mostValuedWeapon;
  var currentItem;
  var i=0;
  while(currentItem=Contents(i++)) {
    if((ObjectCall(currentItem, "IsThrowWeapon") || ObjectCall(currentItem, "IsWeapon")) && CheckWeaponRange(currentItem, distance, ignoreMinDistance, ignoreMaxDistance)) {
      if(currentItem->~NeedsAmmo()&&needsAmmo) {
        // current item has ammo?
        if(currentItem->~Ammo()>0) {
          if(!mostValuedWeapon||(mostValuedWeapon&&GetValue(mostValuedWeapon)<GetValue(currentItem)))
            mostValuedWeapon = currentItem;
        } else if(currentItem->~ExtractAmmoPacket()!=-1) {
          // current item can get ammo
          if(!mostValuedWeapon||(mostValuedWeapon&&GetValue(mostValuedWeapon)<GetValue(currentItem)))
            mostValuedWeapon = currentItem;
        }
      } else if(!(currentItem->~NeedsAmmo())&&!needsAmmo) {
        if(!mostValuedWeapon||(mostValuedWeapon&&GetValue(mostValuedWeapon)<GetValue(currentItem)))
          mostValuedWeapon = currentItem;
      }
    }
  }
  return(mostValuedWeapon);
}

private func CheckWeaponRange(object weapon, int distance, bool ignoreMinDistance, bool ignoreMaxDistance) {
  if(distance < 0)
    return(1);
  var minRange = weapon->~MinRange(), maxRange = weapon->~MaxRange();
  if(ignoreMaxDistance)
    maxRange = 10000;
  if(ignoreMinDistance)
    minRange = 0;
  if(ObjectCall(weapon, "IsThrowWeapon"))
    if(!maxRange) maxRange = 75;
  if(!maxRange) maxRange = 400;
  if(distance > minRange && distance < maxRange)
    return(1);
  return(0);
}

private func GetMostValuableWeaponOld(int range, bool needsAmmo) {
  var mostValuedWeapon;
  var currentItem;
  var i=0;
  while(currentItem=Contents(i++)) {
    if(ObjectCall(currentItem, "IsWeapon")&range||(range&ShortRangeWeapon()&&ObjectCall(currentItem, "IsThrowWeapon"))) {
      if(currentItem->~NeedsAmmo()&&needsAmmo) {
        if(currentItem->~Ammo()>0) {
          if(!mostValuedWeapon||(mostValuedWeapon&&GetValue(mostValuedWeapon)<GetValue(currentItem)))
            mostValuedWeapon = currentItem;
        } else if(currentItem->~ExtractAmmoPacket()!=-1) {
        if(!mostValuedWeapon||(mostValuedWeapon&&GetValue(mostValuedWeapon)<GetValue(currentItem)))
          mostValuedWeapon = currentItem;
        }
      } else if(!(currentItem->~NeedsAmmo())&&!needsAmmo) {
        if(!mostValuedWeapon||(mostValuedWeapon&&GetValue(mostValuedWeapon)<GetValue(currentItem)))
          mostValuedWeapon = currentItem;
      }
    }
  }
  return(mostValuedWeapon);
}

private func DoFlamethrowerJump() {
  var obj;
  if(obj=FindContents(_WP3)) {
    if(obj->~Ammo()>10)
      obj->ControlUp();
  }
  return(1);
}
  
// Nick-Nack
/* Die Routine zum Gefahrausweichen */
private AvoidDanger:
  // Wenn die KI feststeckt, freigraben
  if(Stuck(this())) AddCommand(this(),"Dig",0,GetX(),GetY());

  // Wenn die KI springen kann und ein Geschoss auf sie zu fliegt, springen
  if(ReadyToJump())
    while(SetVar(1,FindObject(0,-100,-10,200,20,0,0,0,0,Var(1))))
      if(GetAction(Var(1))S="Travel")
        if(Not(Equal(GreaterThan(GetXDir(Var(1)),0),GetHeading(Var(1)))))
          Jump();

  // Wenn die KI nach links oder rechts geht, AvoidDanger-Rückgabewert zurückgeben
  if(Or(Equal(SetVar(1,GetComDir()),COMD_Left()),Equal(Var(1),COMD_Right())))
    return(AvoidDangerWalk());

  return(1); // Gefahr überwunden, 1 zurück geben

private AvoidDangerWalk:
  SetVar(0,1);
  // Minen überspringen
  if(FindObject(_AM8,Sub(Mul(GetDir(),20),20),-12,20,24)) Jump();
  else if(FindObject(_FMI,Sub(Mul(GetDir(),20),20),-12,20,24)) Jump();
  else if(FindObject(_FFM,Sub(Mul(GetDir(),20),20),-12,20,24)) Jump();
  else if(FindObject(SWMN,Sub(Mul(GetDir(),20),20),-12,20,24)) Jump();
  
  // Lava und Säure überspringen
  if(FindObject(0,Sub(Mul(GetDir(),20),20),-10,20,20,OCF_OnFire()))
    return(0,AddCommand(this(),"Jump"));
  if(FindMaterial("DuroLava",Sub(Mul(GetDir(),30),15),20))
    Jump();
  if(FindMaterial("Lava",Sub(Mul(GetDir(),30),15),20))
    Jump();
  if(FindMaterial("Acid",Sub(Mul(GetDir(),30),15),20))
    Jump();
  return(Var(0));

FireWeaponFailed:
return(FireWeapon());

/* Die Angriffsroutine */
private AttackEnemy:
  if(!GetTarget(target)) {
    if(weapon)
      if(weapon->~IsFiring())
        weapon->~Fire();
    return(0);
  }
  // Wenn der Gegner 40 Punkte mehr Energie hat, flüchten
  /*if(GreaterThan(Sub(GetEnergy(target),GetEnergy()),40))
    return(GoBack());*/

  if(Not(Random(100))) SaySaying();

  if(Not(GetAlive(target))) return(target=0);  // Ziel tot

  if(Not(AvoidDanger())) return(1); // Keine Aktion bei Gefahr

  ChooseWeapon();

  if(!weapon)
    return(1);

  // Waffe anwählen (oder Objekt gleicher ID, da bei ShiftContents() immer einige Objekte
  // gleicher ID übersprungen werden)
  if(weapon) Help1();
  
  weapon->~CheckForAmmo(1);

  if(weapon->~IsFiring()) {
    if(!Inside(GetY(target),GetY()-30,GetY()+10)||!PathFree(GetX(),GetY(),GetX(target),GetY(target))||!CheckWeaponRange(weapon, Abs(GetX()-GetX(target))))
      weapon->~Fire();
  }
  StraightStrike();
  return(1);

private CloseCombat:
  if ( GreaterThan( Abs(Sub(GetX(),GetX(target))), 4000) )
    if(Not(PathFree(GetX(),GetY(),GetX(target),GetY(target))))
      return(Search4Weapons());
  if(Not(Difficulty())) return(0);
  return(1);

private StraightStrike:
  if ( Abs(GetX()-GetX(target)) > 450 )
    return( 1 );  // Ziel zu weit weg: Hinlaufen
  if ( Abs(GetX()-GetX(target)) < 50 ) {
    SetComDir(COMD_None());
    if(Random(2))
      Jump();
    if(GetYDir()>0)
      DoFlamethrowerJump();
    if(ThrowAttack())
      return(1);
    AddCommand(this(), "Wait", 0,0,0,0,50);
  }
  if ( Abs(GetX()-GetX(target)) < 10 )
    return(TooClose());  // Ziel zu nah: wegspringen
  if(Inside(GetY(target),Sub(GetY(),10),GetY()+10))
    if(ShotFree(GetX(),GetY(),GetX(target),GetY(target)))
      return(FireWeapon());
  if(Inside(GetY(target),GetY()-50,GetY()-11))
    if(ShotFree(GetX(),Sub(GetY(),40),GetX(target),GetY(target)))
      return(JumpAttack());
  if(Inside(GetY(target),Sum(GetY(),50),Sum(GetY(),11)))
    if(SEqual(GetAction(),"ArmedJump"))
      return(FireWeapon());
  if(Not(Difficulty())) return(0);
  return(1); // Zum Gegner laufen

private func ThrowAttack() {
  if(ObjectCall(weapon, "IsThrowWeapon")) {
    AddCommand(this(),"Throw",weapon,GetX(target),GetY(target));
    return(1);
  }
  return(0);
}

private TooClose:
  if(GetAction() S= "Jump" || !(this()->~ReadyToFire())) return(0);
  SetXDir(20);
  SetComDir(COMD_Right());
  SetDir(DIR_Right());
  if(Random(2)) {
    SetComDir(COMD_Left());
  SetDir(DIR_Left());
    SetXDir(-20);
  }
  if(!Random(3))
    AddCommand(this(),"Jump");
  AppendCommand(this(),"Call",this(),0,0,0,0,"FireWeapon");
  return(1);

private JumpAttack:
  AppendCommand( this(), "Jump", 0,
      Sum(GetX(),Mul(40,Sub(Mul(2,GetHeading(target)),1))),
      Sum(GetY(),40) );

  if(Not(Difficulty())) return(0);
  AppendCommand( this(), "Call", this(), 0,0,0,0, "FireWeapon" );
  return(2);

// Nick-Nack
/* Waffe abfeuern */
public FireWeapon:
  // Ist nicht bewaffnet
  if (Not(this()->~IsArmed())) return(0);
  // Kann zur Zeit nicht feuern
  if (Not(this()->~ReadyToFire())) return(0);
  // Müsste sich zum Feuern im Sprung umdrehen
  if ( And(Not(Equal(GetHeading(target),GetDir())),SEqual(GetAction(),"ArmedJump")) )
     return(0);
  if(!CheckWeaponRange(weapon, Abs(GetX()-GetX(target)),0,1))
    return(0);
  // Feuer-Funktion der Waffe aufrufen
  SetDir(GetHeading(target));
  SetComDir(Sum(Mul(GetHeading(target),6),2));

  ObjectCall(weapon,"Fire");
  return(2);

/* Ist der Clonk im Nahkampf? */
IsFighting:
  return(Or(
           SEqual(GetAction(Par(0)),"Fight"),
           SEqual(GetAction(Par(0)),"Punch"),
           SEqual(GetAction(Par(0)),"GetPunched")
          ));
      
/* Gedeathmatcht */
protected Death:
  // Sound und Meldung
  SetAlive(0);
  // Irgendwo drin? Raus da!
  while(Contained())
    Exit();
  Sound("Die");
  Message("Wieder ein Bot weniger...",this());
  // Etwas in dir? Raus damit!
  this()->~DeathAnimation();
  SetCon(100);
  GameCall("RelaunchBot",GetOwner());
  return(RemoveObject());

// Clonk-Karl

/* Die Wegsuchroutine */

private WaySearch:
  if(Not(Difficulty())) return(0);
  if(Not(AvoidDanger())) return(NoWay());
  // Eventuell Medikits holen
  if(CheckEnergy())
  // Weiterer Verlauf hier abbrechen, wenn ein Medikit zu holen ist
    return(1);
  // Munition prüfen
  CheckAmmo();

  Var(0)=target;
  Var(1)=0;
  // Wartungskanäle benutzen
/*  while(SetVar(1,FindObject(_MH1,-150,-150,300,300,0,0,0,0,Var(1) )) ) 
    // Ist der Ausgang des Kanals näher am Zielobjekt als die KI selbst?
    if(ObjectDistance(Local(0,Var(1)),Var(0) ) + ObjectDistance(Var(1)) < ObjectDistance(Var(0))) {
    AddCommand(this(),"Wait",0,0,0,0,50);
      AddCommand(this(),"Enter",Var(1));
    }
  // Pipelines benutzen
  if(SEqual(GetAction(),"Swim"))
    while(SetVar(1,FindObject(_PI1,-150,-150,300,300,0,0,0,0,Var(1) )) ) 
      // Ist der Ausgang des Kanals näher am Zielobjekt als die KI selbst?
      if(ObjectDistance(Local(0,Var(1)),Var(0) ) + ObjectDistance(Var(1)) < ObjectDistance(Var(0))) {
      AddCommand(this(),"Wait",0,0,0,0,50);
        AddCommand(this(),"Enter",Var(1));
      }*/
  // Luken öffnen
  while(SetVar(1,FindObject(_HAC,-100,-100,200,200,0,0,0,0,Var(1) )) )
    if(Not(FindMaterial("DuroLava",GetX(Var(1)),Sum(GetY(Var(1)),100) )))
      if(Not(FindMaterial("Lava",GetX(Var(1)),Sum(GetY(Var(1)),100) )))
        if(Not(FindMaterial("Acid",GetX(Var(1)),Sum(GetY(Var(1)),100) )))
          if(LessThan(GetY(Var(0)),GetY()))
            if(GreaterThan(GetY(Var(1)),GetY() ))
              if(LessThan(
                ObjectDistance(Local(0,Var(1)),Var(0) ),
                ObjectDistance(Var(0) )
                ))
              And(
      AddCommand(this(),"Grab",Var(1)),
      ObjectCall(Var(1),"ControlUp")
      );
  // Hangeln
  /*if(SEqual(GetAction(),"Hangle")) {
    if(GetHeading(Var(0)))
      SetComDir(COMD_Right());
  else
    SetComDir(COMD_Left());
  if(Inside(GetX(), GetX(Var(0))-5, GetX(Var(0))+5))
    SetAction("Jump");
  }*/
  // Klettern
  /*if(SEqual(GetAction(),"Scale")) {
    if(GetY(Var(0))>GetY())
      SetAction("Jump");
    else
      SetComDir(COMD_Up());
  }*/
  return(1);

//Clonk Nukem
Search4Weapons:
  while(SetVar(0,FindObject(0,0,0,-1,-1,0,0,0,0,Var(0)))) {
    if(ObjectCall(Var(0), "IsWeapon")) {
      if(WeaponFree(Var(0)))
        return(target=Var(0));
    } 
  /*else if(ObjectCall(Var(0), "IsSpawnPoint")) {
      if(SpawnPointFree(Var(0)))
      if(DefinitionCall(Local(0,Var(0)),"IsWeapon"))
          return(target=Var(0));
  }*/
  }
  return(0);

// Gibt 1 zurück, wenn die Waffe/Munition vom Spawnpoint nicht mehr existiert
SpawnPointFree: return(And(1,Local(1,Par(0))));

// Clonk Nukem
WeaponFree:
  if(Debug()) Log("Waffe gefunden: %s",GetName(0,ID(Par(0))));

  // Waffe wird schon getragen
  if(Contained(Par(0))&&( GetOCF(Contained(Par(0))) & OCF_CrewMember() ))
    return(0);
  if(GBackSolid(GetX(Par(0))-GetX(),GetY(Par(0))-GetY()))
    return(0);
  // KI hat schon so eine Waffe
  if(Not(FindContents(ID(Par(0)))))
      // Okay
    if(PathFree(GetX(),GetY(),GetX(Par(0)),GetY(Par(0))))
        return(1);
  
  // Kein Erfolg.
  return(0);

// Clonk-Karl


// Den WayPoint und den Command löschen (Die KI wird sie in den meisten Fällen zwar gleich wieder setzten, aber besser wie nix :(

private NoWay:
  SetCommand(this(),"None");
  return(1);

/* Energie prüfen, Medikit abholen, abhauen */
private CheckEnergy:
  // Wieviel Energie noch?
  if(GreaterThan(GetEnergy(),10))
    return(0);  // Alles i.O.

  // Ist auf dem Weg zu einem Medikit
  if(GetID(target)==_MED)
    return(0); // Auch in Ordnung
  // Medikit im Inventar?
  if(ObjectCall(FindContents(_MED),"Activate",this()))
    return(0);  // Energie auffrischen: Medikit benutzen

  // Var[0]: Medikit, zu dem die KI laufen soll
  // Medikit suchen
  if(SetVar(0,FindObject(_MED,-400,-200,800,400)))
    return(target=Var(0));  // Waypoint setzten

  // Ansonsten: Weiterkämpfen
  return(0);
  
  // Ansonsten: Abhauen!
  //return(GoBack());

/* Prüfen, ob er noch Munition hat, wenn nicht, holen gehen */
private CheckAmmo:
  // Var[0]: Munition der Waffe
  // Var[1]: Munitionspack der Waffe
  // Var[2]: Zweite Munition der Waffe (Zielsuchrakete beim Raketenwerfer)
  // Var[3]: Zweites Munitionspack der Waffe
  // Var[9]: WayPoint mit Muni als ActionTarget

  // Zuerst: Bei Phaser oder Schallpistole keine Ammo vonnöten
  if(ObjectCall(weapon, "MaxAmmo")==-1)
    return(0);
// TODO
  SetVar(0,GetAmmoID(ID(Local(1))));
  SetVar(1,GetAmmoPacketID(ID(Local(1))));

  // AmmoID2 für Raketenwerfer
  SetVar(2,GetAmmoID2(ID(Local(1))));
  SetVar(3,GetAmmoPacketID2(ID(Local(1))));

  // Bei einer MG als ausgewählten Waffe MGCheck aufrufen
  if(Equal(ID(Local(1)),_WP6))
    SetVar(1,MGCheck());

  // Ist schon auf dem Weg zu Muni
  while(SetVar(9,FindObject(WP00,0,0,-1,-1,0,0,Var(1),0,Var(9))))
    if(Equal(GetActionTarget(1,Var(9)),this()))
      return(0);  // Braucht nicht mehr weiter zu suchen
  SetVar(9);
  while(SetVar(9,FindObject(WP00,0,0,-1,-1,0,0,Var(3),0,Var(9))))
    if(Equal(GetActionTarget(1,Var(9)),this()))
      return(0);  // Braucht nicht mehr weiter zu suchen
    
  // Keine Muni mehr da?
  if(And(And(
         Not(FindContents(Var(0),Local(1))),
         Not(FindContents(Var(2),Local(1)))),
     And(Not(FindContents(Var(1))),
         Not(FindContents(Var(3))))
         ))
    return(LookForAmmo(Var(1),Var(3)));

  // Noch Muni vorhanden
  return(0);

/*
  Wenn eine MG vorhanden ist, Munition auspacken und Var(1) in CheckAmmo nicht auf
  GetAmmoPacketID legen, da dies der Munitionsstreifen ist, und nicht der Kasten
*/
MGCheck:
  if(SetVar(0,FindContents(_PP6)))
    ObjectCall(Var(0),"Activate");
  // _PP6 (MG-Muni-Kiste) zurückgeben
  return(_PP6);

/* Munition suchen */

private LookForAmmo:
  // Par[0]: Passende Munition
  // Par[1]: Zweite Munition (Zielsuchraketen beim Raketenwerfer)
  // Var[0]: Die Munition, die es zu holen gilt
  // Var[9]: Hilfsvarable zum kurzen speichern von dem zu holenden Objekt
  if(Not(Par(0)))
    return();
  if(Not(Par(1)))
    if(Or( Not(FindObject(Par(0),0,0,-1,-1)), Not(FindObject(Par(1),0,0,-1,-1)) ))
      return(0);
  // Munition suchen
  while(SetVar(9,FindObject(Par(0),0,0,-1,-1,0,0,0,0,Var(9) )) )
    // Nicht in Lava
    if(Not(FindMaterial("DuroLava",GetX(Var(9)),GetY(Var(9)) )))
    // Nicht im Besitz eines anderen Clonks
      if(Not(ContentsCheck(Var(9))))
        SetVar(0,Var(9));
  // Wenn ein gültiger Par(1)-Wert übergeben wurde (Nicht 0), Zielsuchraketen ODER Mini-Raketen holen (Das, was am nähesten ist)
  if(Par(1))
    SetVar(0,LookForMissiles());
  // Keine Muni gefunden? Scheiße war's!
  if(Not(Var(0)))
    return();
  SetPosition(GetX(Var(0)),GetY(Var(0)),SetVar(2,CreateObject(WP00)));
  ObjectCall(Var(2),"SetOne",Var(0),this());
  return(1);


/* Raketen für den Raketenwerfer suchen */

private LookForMissiles:
  // Var[0]: Mini- oder Zielsuchraketenpack, welches am nähesten ist und gefunden wird
  // Sehr rechenintensiv, da die ganze Karte abgesucht wird (bzw. werden muss)
  while(SetVar(0,FindObject(0,0,0,-1,-1,0,0,0,0,Var(0) )) )
    if(Or(
          Equal(ID(Var(0)),_AP2),
          Equal(ID(Var(0)),_HMP)
          ))
        // Nicht in Lava
        if(Not(FindMaterial("DuroLava",GetX(Var(0)),GetY(Var(0)) )))
          // Nicht in einem Lebewesen enthalten
          if(Not(ContentsCheck(Var(0))))
            // Gefundenes Pack zurückgeben
            return(Var(0));
  // Keine Raketenpacks da (sollte nicht vorkommen)
  return(0);

/* Eine weniger rechenintensive Variante */
private LookForMissiles2:
  // Var[0]: Miniraketenpack, welches am nähesten ist und gefunden wird
  // Var[1]: Zielsuchraketenpack, welches am nähesten ist und gefunden wird
  // Var[2]: Indikator, um anzuzeigen, dass die Suche beendet werden kann
  while(And(Not(Var(2)),Var(0)))
    if(SetVar(0,FindObject(_HMP,0,0,-1,-1,0,0,0,0,Var(0))))
      if(Var(0))
        // Nicht in Lava
        if(Not(FindMaterial("DuroLava",GetX(Var(0)),GetY(Var(0)) )))
          // Nicht in einem Lebewesen enthalten
          if(Not(ContentsCheck(Var(0))))
            SetVar(2,1);
  SetVar(2);
  while(And(Not(Var(2)),Var(1)))
    if(SetVar(1,FindObject(_AP2,0,0,-1,-1,0,0,0,0,Var(1))))
      if(Var(1))
        // Nicht in Lava
        if(Not(FindMaterial("DuroLava",GetX(Var(0)),GetY(Var(0)) )))
          // Nicht in einem Lebewesen enthalten
          if(Not(ContentsCheck(Var(0))))
            SetVar(2,1);
  if(Not(Var(1))) return(Var(0));
  if(GreaterThan(ObjectDistance(this(),Var(1)),ObjectDistance(this(),Var(0)))) return(Var(0));
  return(Var(1));  

ContentsCheck:
  // Überprüft, ob Par[0] sich in einem Lebewesen befindet und gibt 1 zurück, wenn dem so ist
  // Par[0]: Zu prüfendes Objekt
  if(Contained(Par(0)))
    if(BitAnd(GetOCF(Contained(Par(0))),OCF_Living() ))
      return(1);
  // Befindet sich in keinem Lebewesen
  return(0);

/* Flüchten */

private GoBack:
/* Andere Befehle löschen, um nicht wieder zum Gegner zurückzuwollen,
   wenn dort Munition für die Waffe ist. Abhauen ist wichtiger */
  SetCommand(this(),"None");
  // Rechts von der KI: Nach links abhauen!
  if(GetHeading(target))
    return(SetComDir(COMD_Left()));
  // Ansonsten nach rechts verschwinden
  return(SetComDir(COMD_Right()));

/* Schuss von Punkt A nach B möglich? */
// Par(0) X des Startpunktes, Par(1) Y des Startpunktes, Par(2) X des Zielpunktes, Par(3) Y des Zielpunktes
private ShotFree:
  if ( Not( PathFree(Par(0),Par(1),Par(2),Par(3)) ) )  return(0); // Hindernis im Schussfeld
 // if ( FriendBetween(Par(2)) ) return(0);  // andere KI im Schussfeld
  return(1);

/* Überprüft, ob eine andere KI zwischen this() und dem X-Punkt Par(0) ist. Als Y wird das Y
   dieser KI angenommen. Das Suchrechteck ist so breit wie der X-Abstand zwischen KI und Ziel,
   und 30 hoch. Gibt 1 oder 0 zurück.
*/
private FriendBetween:  //X-Koordinate des Zielpunkts
  if(Not(TeamPlayEnabled())) return(0);
  if(LessThan( Par(0), Par(1)))
    if(FindObject( ID(), 0, -15, Sub(GetX(),Par(0)), 30,0,0,0, NoContainer()))
      return(1);  // Ziel ist rechts von der KI
  if(FindObject( ID(), Sub(GetX(),Par(0)), -5, Sub(Par(0),GetX()), 30,0,0,0, NoContainer()))
    return(1); // Ziel ist links von der KI
  return(0);  

// Kurzschreibweise für GetID()
public ID: // C4Object *pObj
  return(GetID(Par(0)));

// Gibt zufällig einen Spruch wieder
SaySaying:
  SetVar(0,Random(10));
  if(Equal(Var(0),0)) Message("Mal sehen, wie lange du überlebst!",this());
  if(Equal(Var(0),1)) Message("%s, du bist zu erst dran!",this(),GetPlayerName(0));
  if(Equal(Var(0),2)) Message("Wenn das kein Fest wird...",this());
  if(Equal(Var(0),3)) Message("Tja, DU hast keine Zeit, solche Sprüche ab zu lassen, %s!",this(),GetPlayerName(0));
  if(Equal(Var(0),4)) if(GetPlayerName(1)) Message("Also an deiner Stelle, %s, würde ich sofort aufgeben!",this(),GetPlayerName(1));
  if(Equal(Var(0),5)) if(GetPlayerName(2)) Message("Da kann ja selbst meine Oma besser kämpfen, %s!",this(),GetPlayerName(2));
  if(Equal(Var(0),6)) Message("Hübsche Waffe, nehm' ich mir!",this());
  if(Equal(Var(0),7)) Message("Lange niemand mehr getötet!",this());
  if(Equal(Var(0),8)) Message("Hey, sag' bloss nicht, ich wäre schlecht, weil ich ein Bot bin!",this());
  if(Equal(Var(0),9)) Message("Also, wenn du mich fragst,|du bist schon so gut wie tot!",this());
  return(1);

// Die Ammo-IDs aller Waffen
GetAmmoID:
  if(Equal(Par(0),_WP2)) return(_AM2);
  if(Equal(Par(0),_WP3)) return(_AM3);
  if(Equal(Par(0),_WP5)) return(_AM5);
  if(Equal(Par(0),_WP6)) return(_AM6);
  if(Equal(Par(0),_WP7)) return(_AM7);
  if(Equal(Par(0),_WP9)) return(_AM9);
  return(0);

GetAmmoPacketID:
  if(Equal(Par(0),_WP2)) return(_AP2);
  if(Equal(Par(0),_WP3)) return(_AP3);
  if(Equal(Par(0),_WP5)) return(_AP5);
  if(Equal(Par(0),_WP6)) return(_AP6);
  if(Equal(Par(0),_WP7)) return(_AP7);
  if(Equal(Par(0),_WP9)) return(_AP9);
  return(0);

GetAmmoID2:
  if(Equal(Par(0),_WP2)) return(_HMS);
  return(0);

GetAmmoPacketID2:
  if(Equal(Par(0),_WP2)) return(_HMP);
  return(0);

// Gibt 1 zurück, wenn pObj1 rechts von pObj2 ist, sonst 0.
private GetHeading:  // C4Object *pObj1, C4Object *pObj2
  return(GreaterThan(GetX(Par(0)),GetX(Par(1))));

// Gibt 1 zurück, wenn die KI aus der aktuellen Aktion springen kann,
// also wenn sie gerade läuft
ReadyToJump:
  return(Or(SEqual(GetAction(),"Walk"),SEqual(GetAction(),"ArmedWalk")));

// Gibt 1 oder 0 zurück, je nach Zufall: Je größer der Schwierigkeitsgrad, desto seltener 0
Difficulty:
  return(1);
  SetVar(0,10);
  if(LessThan(Var(0),5)) return(0);
  return(1);

TeamPlayEnabled:
  return(1);

IsKI:
  return(1);

// Clonk-Karl
// BOOL FindMaterial (const char *szMaterial, int iX, int iY);
// Überprüft, ob an angegebener Stelle das angegebene Material
// vorhanden ist und liefert 1 zurück, wenn das Material dort ist, ansonsten 0.
private FindMaterial:
  if (Not(Equal(SetVar(0,GetMaterial(Par(1),Par(2))),-1)))
    if (Equal( Var(0), Material(Par(0)) ))
      return(1);
  return(0);

// Hallifax
WhereToAim: //Par(0) *pObject ZielObjekt, Par(1) int iPhasen 
  SetVar(0,Angle(GetX(),GetY(),GetX(Par()),GetY(Par())));
  if (GreaterThan(Var(),180)) 
    And(SetPhase(Div(Sub(Var(),180),Par(1))),SetDir(DIR_Right()),SetComDir(COMD_Right()));
  if ( Or(LessThan(Var(),90),GreaterThan(Var(),270)) )
    And(SetDir(DIR_Left()),SetComDir(COMD_Left()),SetPhase(Div(Var(), Par(1))));
  return(1);

// Überarbeitet von Nick-Nack
ObjectXDistance:
  return(Abs(Sub(GetX(Par(0)),GetX(this()))));
