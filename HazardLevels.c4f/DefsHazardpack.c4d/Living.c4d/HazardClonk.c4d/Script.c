/*-- HazardClonk --*/

#strict
#include _CL_

local verbrennen, platzen, erholung, hud;

PutArmorOn:
  ChangeDef(Par(0));
  this()->SetAction("PutArmorOn");
  return(1);

Init:
  return(1);

DeathAnimation:
  // Etwas in dir? Raus damit!
  while(SetVar(0,Contents())) Exit(Var(0),0,-5,Random(360),GetXDir(),GetYDir());
  if(platzen!=2) {
    SetVar(0,CreateObject(_GTT,0,GetCon()/10));
    SetXDir(GetXDir(),Var(0));
    SetYDir(GetYDir(),Var(0));
    SetDir(GetDir(),Var(0));
    SetOwner(GetOwner(),Var(0));
    SetName(GetName(),Var(0));
    SetCon(GetCon(),Var(0));
    if(verbrennen&&Global(0))
      SetPhase(0,Var(0));
    if(platzen) {
      Sound("Zerquetschen");
      SetPhase(2,Var(0));
      RemoveObject(Var(0));
      var speed, angle;
      speed = Sqrt(GetXDir()*GetXDir()+GetYDir()*GetYDir());
      angle = Angle(0,0,GetXDir(),GetYDir());
      CastObjectsX(MEAT,1*GetCon()*GetCon()/10000,Max(speed,platzen,40),0,0,270,90,false);
      CastObjects(BL7K,20*GetCon()*GetCon()/10000,speed+20);
      CastObjectsX(BL7K,20*GetCon()*GetCon()/10000,Max(speed,platzen,20),0,0,angle,180,false);
    } else {
      ObjectCall(Var(0),"Meldung");
    }
  }
  verbrennen=false;
  return(1);
  
/* Gestorben */
Death:
  // Sound und Meldung
  SetAlive(0);
  // Irgendwo drin? Raus da!
  while(Contained())
    Exit();
  DeathAnimation();
  if(GetCrew(GetOwner()))
    return(RemoveObject());
  SetCon(100);
  ChangeDef(__DV);
  MakeCrewMember(this(),GetOwner());
  ObjectCall(this(),"Init",GetOwner());
  return(1);

Platzen:
  if(Global(0)) {
    verbrennen=false;
    platzen=true;
  }
  SetYDir(GetYDir()-50);
  Kill();
  return(1);

Delete:
  verbrennen=false;
  platzen=2;
  Kill();
  return(1);

Respawn:
  SetCrewEnabled(1);
  SetCategory(1);
  SetCategory(2056);
  SetAction("Walk");
  ResetPhysical();
  DoEnergy(+2000);
  SetVisibility(VIS_All());
  SetDir(Random(2));
  SetXDir(0);
  SetYDir(0);
  SetRDir(0);
  Fling();
  //SetPosition(Random(LandscapeWidth()),0);
  SetAlive(1);
  return(1);

protected RejectCollect:
   var abzug, inhalt;
   var granaten, magazinstreifen, minen;
   // Der Inhalt ohne Kleinteile
   inhalt = ContentsCount()-ContentsCountKleinteile()-ContentsCountNoCollectLimit();
   // Zähle die Kleinteile
   granaten = ContentsCount(_CGM)+ContentsCount(_AM5);
   magazinstreifen = ContentsCount(_AP6);
   if(magazinstreifen>0)
     abzug -= 1;
   minen = ContentsCount(_FMI)+ContentsCount(_FFM)+ContentsCount(_AM8)+ContentsCount(SWMN);
   // Was wird gerade aufgehoben?
   if(Par(0)==_CGM||Par(0)==_AM5)
     granaten++;
   else if(Par(0)==_AP6)
     magazinstreifen++;
   else if(Par(0)==_FMI||Par(0)==_FFM||Par(0)==_AM8||Par(0)==SWMN)
     minen++;
   else if(!(ObjectCall(Par(1), "NoCollectLimit")&&!FindContents(Par(0))))
     inhalt++;
   // Berechne den Abzug -> Jedes Kleinteil benötigt soviel Slots wie es als Paket verbrauchen würde:
   // Bsp: 5 Minen -> 1 Minenpaket -> 1 Slot, 6 Minen -> 1 Minenpaket und 1 Mine -> 2 Slots
   // Dabei spielt es keine Rolle, dass es zum Beispiel kein Paket gibt mit 3 Feuerminen und 2 Eisminen.
   abzug += (granaten+9)/10;
   abzug += (magazinstreifen+4)/5;
   abzug += (minen+4)/5;
   // Wenn weniger als 5 Objekte getragen werden, alles aufnehmen
   if (inhalt<=5-abzug) return(0);
   return (1);
   
ContentsCountNoCollectLimit:
  Var(2)=0;
  while(Var(1)=Contents(Var(0)++)) {
    if(ObjectCall(Var(1), "NoCollectLimit")&&FindContents(GetID(Var(1)))==Var(1))
	  Var(2)++;
  }
  return(Var(2));
   
ContentsCountKleinteile:
  Var(0)  = ContentsCount(_CGM);
  Var(0) += ContentsCount(_AM5);
  Var(0) += ContentsCount(_AP6);
  Var(0) += ContentsCount(_FMI);
  Var(0) += ContentsCount(_FFM);
  Var(0) += ContentsCount(_AM8);
  Var(0) += ContentsCount(SWMN);
  return(Var(0));

/* Punkteauswertung */

protected Damage:
  Bluten(Par(0));
  if(Par(0)>20&&Global(0)) {
    verbrennen=false;
    platzen=Par(0);
  } else {
    platzen=0;
  }
  if (Random(2)&&!OnFire()) Hurt();
  verbrennen=OnFire();
  if (!GetAlive()) return(0);
  // Jeder Treffer auf einen anderen Spieler bringt Punkte
  if (Not(Equal( Par(1), GetOwner() )))
    DoScore( Par(1), Par(0) );
  return(1);

protected Incineration:
  // Anzünden bringt 100 Punkte
  if (Not(Equal( Par(0), GetOwner() )))
    DoScore( Par(0), +100 );
  // Meldung
  if (And( GetPlayerName(Par(0)),GetPlayerName(GetOwner()) ))
    if (Not(Equal( Par(0), GetOwner() )))
      if (GameCall("HazardLogs"))
        Log("%s fackelt %s ab.",GetPlayerName(Par(0)),GetPlayerName(GetOwner()));
  if (And( GetPlayerName(Par(0)),GetPlayerName(GetOwner()) ))
    if (Equal( Par(0), GetOwner() ))
      if (GameCall("HazardLogs"))
        Log("%s fackelt sich selbst ab. Depp.",GetPlayerName(Par(0)));
  return(1);
  
Zertrampel:
  Var(0)=GetActionTarget();
  if(Var(0))
    if(SetVar(1, KannTreten(Var(0)) )>0)
      return(Trete(Var(0),Var(1)));
  while(SetVar(0,FindObject(0,-10,-5,20,40,OCF_Prey(),0,0,NoContainer(),Var(0))))
    if(SetVar(1, KannTreten(Var(0)) )>0)
      return(Trete(Var(0),Var(1)));
  return(1);


private Trete:
  Var(0)=Par(0);
  Var(1)=Par(1);
  if(Global(0))
    CastObjects(BL7K,Var(1),20,0,8);
  Fling(Var(0),(Random(2)-1),-1); 
  Sound("MFHacken2");
  if(GetEnergy(Var(0))-Var(1)<=0) {
    ObjectCall(Var(0),"Platzen");
    return(2);
  }
  DoEnergy(-Var(1),Var(0));
  DoDamage(3,Var(0));
  return(2);

public Shrink:
// wenn es nicht mehr geht, dann Error Sound
if(GetCon()>10)
// sonst Teleport Sound
  Sound("Teleport");
// schrumpfe maximal um 30
DoCon(Mul(Min(GetCon()-10,30),-1));
  // Schrumpfen bringt 10 Punkte
  if (Not(Equal( Par(0), GetOwner() )))
    DoScore( Par(0), +10 );
  // Meldung
  if (And( GetPlayerName(Par(0)),GetPlayerName(GetOwner()) ))
    if (Not(Equal( Par(0), GetOwner() )))
      if (GameCall("HazardLogs"))
        Log("%s schrumpft %s.",GetPlayerName(Par(0)),GetPlayerName(GetOwner())); 
  return(1);  

Bluten:
  if(!Global(0))
    return(2);
  if(OnFire())
    return(2);
  var speed, angle, amount;
  if(Par(0))
    amount = Par(0);
  else
    amount = 20;
  if(Par(1)) {
    speed = Sqrt(GetXDir()*GetXDir()+GetYDir()*GetYDir());
	if(Par(2))
	  speed+=Par(2);
    angle = Angle(0,0,GetXDir(),GetYDir());
    CastObjectsX(BL7K,20,speed+20,0,0,angle,160,false);
  } else
    CastObjects(BL7K,amount,20);
  return(1);

protected CatchBlow:
  Bluten(2);
  if (SEqual(GetAction(),"Dead")) return(0);
  if (Not(Random(5))) Hurt();
  // Schlagen bringt Punkte
  if (Not(Equal( GetOwner(Par(1)), GetOwner() )))
    DoScore( GetOwner(Par(1)), +2 );
  return(1);

/* Steuerung Werfen */
protected ControlThrow:
  // Bei vorherigem Doppel-Stop nur Ablegen  
  if ( GetPlrDownDouble(GetOwner()) ) return(0);
  // Steuerung an Inhalt weitergeben
  if ( Control2Contents("ControlThrow") ) return(1);
  // Sonst internen Throw-Befehl ausführen
  return(0);

/* Steuerung Richtung (an Inhalt weitergeben, sonst internen Befehl ausführen) */
protected ControlUp:
  if ( Control2Contents("ControlUp") ) return(1);
  return(0);
protected ControlDown:
  if ( Control2Contents("ControlDown") ) return(1);
  return(0);
protected ControlDownDouble:
  // NEU: Zertrampeln
  // nur Beim Gehen
  if (Or(SEqual(GetAction(),"ArmedWalk"),SEqual(GetAction(),"Walk"))) 
  // Suche Lebewesen
    while(SetVar(0,FindObject(0,-10,-5,20,15,OCF_Prey(),0,0,NoContainer(),Var(0))))
	   if(GetTarget(Var(0)))
	      // nur Lebewesen, die halb so groß sind wie der Clonk
          if(KannTreten(Var(0))>0) {
            // Eventuell Lift anhalten
            while(Var(1)=FindObject(0,0,0,0,0,0,0,0,0,Var(1)))
              if(ObjectCall(Var(1), "Passenger")==this())
                ObjectCall(Var(1), "Stop");
            // Zertrampeln
            return(SetAction("Trampel", Var(0)));
          }
  return(0);
protected ControlLeft:
  if (SEqual(GetAction(),"Jump")||SEqual(GetAction(),"ArmedJump"))
    SetDir(DIR_Left());
  if ( Control2Contents("ControlLeft") ) return(1);
  return(0);
protected ControlRight:
  if (SEqual(GetAction(),"Jump")||SEqual(GetAction(),"ArmedJump"))
    SetDir(DIR_Right());
  if ( Control2Contents("ControlRight") ) return(1);
  return(0);
protected ControlLeftDouble:
  if ( Control2Contents("ControlLeftDouble") ) return(1);
  return(0);
protected ControlRightDouble:
  if ( Control2Contents("ControlRightDouble") ) return(1);
  return(0);
protected ControlDigDouble:
  if(erholung<=0&&hud) {
    if (SEqual(GetAction(),"Jump")||SEqual(GetAction(),"ArmedJump")&&GetXDir()!=0) {
      if(GetID()!=HCK4)
        erholung = 5;
      SetXDir(0);
      SetComDir(COMD_None());
    }
    if (SEqual(GetAction(),"Tumble")) {
      if(GetID()!=HCK4)
        erholung = 5;
      SetXDir(0);
      SetAction("Walk");
      SetComDir(COMD_None());
      CheckArmed();
    }
    if (SEqual(GetAction(),"FlatUp")||SEqual(GetAction(),"KneelUp")||SEqual(GetAction(),"KneelDown")) {
      if(GetID()!=HCK4)
        erholung = 5;
      SetAction("Walk");
      CheckArmed();
    }
  }
  if(hud)
    hud->SetPhase(BoundBy(4-erholung,0,4));
  if ( Control2Contents("ControlDigDouble") ) return(1);
  return(0);
protected ControlDig:
  if ( Control2Contents("ControlDig") ) return(1);
  return(0);

SetEnabled:
  if(Par(0)==GetCrewEnabled())
    return(1);
  if(Par(0)) {
    SetCrewEnabled(1);
    SetCursor(GetOwner(),this(),1,1);
    Activity();
  } else {
    SetCrewEnabled(0);
    if(hud) RemoveObject(hud);
  }
  return(1);

Activity:
  _inherited();
  erholung--;
  CheckArmed();
  if(erholung==0)
    CreateObject(CTOT);
  if(!hud&&GetCrewEnabled()&&(GetID()==HCK3||GetID()==HCK4)&&GetCursor(GetOwner())==this()) {
    hud = CreateObject(_HUD);
    if(GetPortrait())
      hud->Activate(this(),59,27);
    else
      hud->Activate(this(),12,27);
  }
  if(hud)
    hud->SetPhase(BoundBy(4-erholung,0,4));
  return(1);

/* Steuerung Spezial */
protected ControlSpecial:
  [Inventar auswählen|Image=INVT]
  // Zielaktion abbrechen
  if (ObjectCall(Contents(),"IsAiming")) StopAiming(); 
  // Inventory verschieben
  if (Not(ShiftContents())) return(0);
  // Neues Objekt aktiviert
  if (Not(ObjectCall(Contents(),"Selection"))) // Objekteigener Aktivierungssound
    Sound("Grab"); // Genereller Aktivierungssound
  // Waffe ziehen/wegstecken
  CheckArmed();
//  if(Not(ObjectCall(Contents(),"MunUpdate",this()))) And(SetPhysical("Magic",0,2),DoMagicEnergy(0)); 
  return(1);

/* Infotaste */

protected ControlSpecial2:
  [Menu]
  AddCommand(this(),"Context",0,0,0,this());
  return(1);

/* Kontext */

public func ContextPickup(pCaller)
{
  [Extraction beantragen|Image=MI_P]
  //if (!(GetAction()S="Walk")&&!(GetAction()S="ArmedWalk")) return(1);
  //if (GetComDir()!=COMD_None()) return(1);
  if (SetVar(0,GameCall("FindPlayerShuttle",GetOwner()))) {
    ObjectCall(Var(0),"PickupCall",GetX(),GetY());
    Sound("RadioStatic");
    Message("Shuttle auf dem Weg.",this());
  } else {
    Message("Kein Shuttle in der Nähe.",this());
  }
  return(1);
}


public func ContextInfo(pCaller) 
{
  [Objektinfo|Image=INFO]
  // Behälter
  if (Contained())
    return(Message("%s: %s",this(),GetName(Contained()),GetDesc(Contained())));
  // Angefaßtes Objekt
  if (SEqual(GetAction(),"Push"))
    return(Message("%s: %s",this(),GetName(GetActionTarget()),GetDesc(GetActionTarget())));
  // Inventar
  if (Contents()) Message("%s: %s",this(),GetName(Contents()),GetDesc(Contents()));
  return(1);
}


public func ContextStatus(pCaller)
{
  [Status|Image=MI_P]
  var rank = GetObjectInfoCoreVal("Rank", "ObjectInfo");
  var exp = GetObjectInfoCoreVal("Experience", "ObjectInfo");
  var nextRankExp;
  if(rank>12)
    nextRankExp = 10*Sqrt(10000*(rank+1)**3);
  else
    nextRankExp = Sqrt(1000000*(rank+1)**3);
  var hp = GetEnergy();
  var maxHP = GetPhysical("Energy")/1000;
  var powerSuit = "";
  if(GetID()==HCK3||GetID()==HCK4)
    powerSuit = " (+50)|Power Suit installiert";
  var gravitySuit = "";
  if(GetID()==HCK2||GetID()==HCK4)
    gravitySuit = "|Gravity Suit installiert";
  var ammo = "", dps, dpa, dmg;
  if(Var(0)=Contents())
    if(ObjectCall(Var(0), "IsWeapon")) {
	    ammo = GetName(Var(0));
      Var(1)=ObjectCall(Var(0), "MaxAmmo");
      if(Var(1)==-1)
        ammo = Format("|~%s~|Munition Unbegrenzt", ammo);
      else if(Var(1)==0)
        ammo = Format("|~%s~|Munition Keine", ammo);
      else {
        Var(2)=ObjectCall(Var(0), "Ammo");
        ammo = Format("|~%s~|Munition %d/%d",ammo,Var(2),Var(1));
      }
	    dmg = Var(0)->~Dmg();
	    if(dmg)
        ammo=Format("%s|Schaden %d", ammo, dmg);
	    dps = Var(0)->~DPS();
	    if(dps) 
        ammo=Format("%s|Schaden pro Sekunde %d", ammo, dps);
	    dpa = Var(0)->~DPA();
	    if(dpa) 
        ammo=Format("%s|Schaden pro Ladung %d", ammo, dpa);
    } else if(Var(0)->~Dmg()) 
	    ammo = Format("|~%s~|Schaden %d", GetName(Var(0)), Var(0)->~Dmg());
  
  Message("Rang %d (%d/%d)|HP %d/%d%s%s%s", this(), rank, exp, nextRankExp, hp, maxHP, powerSuit, gravitySuit, ammo);
  return(1);
}

/* Leitet die Steuerung an das erste Inhaltsobjekt weiter. Rückgabewert 1 wenn erfolgreich */
private Control2Contents:
  // Getragenes Objekt hat spezielle Steuerungsauswertung
  if ( ObjectCall(Contents(),Par(0),this()) )
    return(1);
  // Werfen: Waffe abfeuern
  if (SEqual( Par(0), "ControlThrow" ))
    if (FireWeapon()) 
      return(1);
  return(0);

public StopAiming:
  SetComDir(COMD_Stop());
  SetAction("Walk");
  Sound("Grab");
  return(1);

/* Waffe abfeuern */
private FireWeapon:
   // Nicht bewaffnet
   if (Not(IsArmed())) return(0);
   // Kann zur Zeit nicht feuern
   if (Not(ReadyToFire())) return(0);
   // Feuer-Funktion der Waffe aufrufen
   if(ObjectCall(Contents(),"Fire")) {
     if(Local(68))
       ObjectCall(Local(68),"ReduceCounter",10);
     if(SetVar(0,FindContents(_FFG)))
       if(SetVar(0,GetActionTarget(0,Var(0))))
         if(GetID(Var(0))==_IFD)
           ObjectCall(Var(0),"ReduceCounter",10);
   }
   return(1);
  
/* Initialisierung */  
Initialize:
  SetAction("Walk");
  SetDir(Random(2));
  return(1);

/* Trägt der Clonk eine Waffe? */
public IsArmed: 
  return(ObjectCall(Contents(),"IsWeapon"));

/* Kann der Clonk aus der aktuellen Aktion feuern? */
public ReadyToFire:
   // Nur beim Laufen, Schwimmen oder Springen
   if (Not(Or(SEqual(GetAction(),"ArmedWalk"),SEqual(GetAction(),"Swim"),SEqual(GetAction(),"ArmedJump")))) 
     return(0);
   // Okay
   return(1);

/* Kann der Clonk aus der aktuellen Aktion zielen? */
public ReadyToAim:
   // Nur beim Laufen
   if (Not(SEqual(GetAction(),"ArmedWalk"))) return(0);
   // Okay
   return(1);

/* Bewaffnung prüfen */
private CheckArmed:
  if(Not(ObjectCall(Contents(),"MunUpdate",this()))) And(SetPhysical("Magic",0,2),DoMagicEnergy(0)); 
  if (SEqual(GetAction(),"Walk")) if (IsArmed()) return(SetAction("ArmedWalk"));
  if (SEqual(GetAction(),"Jump")) if (IsArmed()) return(SetAction("ArmedJump"));
  if (SEqual(GetAction(),"ArmedWalk")) if (Not(IsArmed())) return(SetAction("Walk"));
  if (SEqual(GetAction(),"ArmedJump")) if (Not(IsArmed())) return(SetAction("Jump"));
  if (Not(IsArmed()))
  DefinitionCall(GLAL, "SetAmmo", 0, 1, this());
  return(1);
  
protected Collection:
  CheckArmed();
  return(1);

FightProcess:
  if (Not(Random(2))) SetAction("Punch");
  return(1);
Punch:
  if (Not(Random(3))) Sound("Kime*");
  if (Not(Random(5))) Sound("Punch*");
  if (Not(Random(2))) return(1);
  Punch(GetActionTarget());
  return(1);
Hurt:
  Sound("Hurt*");
  return(1);
Chop:
  Sound("Chop*");
  return(1);
Build:
  if(Not(Random(2))) Sound("Build*");
  return(1);
Dig:
  Sound("Dig*");
  return(1);
Grab:
  Sound("Grab");
  return(1);
Get:
  Sound("Grab");
  return(1);
Put:
  Sound("Grab");
  return(1);
DeepBreath:
  Sound("Breath");
  return(1);
Redefine:
  ChangeDef(Par(0));
  SetAction("Walk");
  return(1);

/* Eingefroren */
Frozen: 
  SetXDir(0); // Bei Vereisung stehenbleiben
  if(OnFire(this())) Extinguish(); // Nötigenfalls löschen
  return(1);