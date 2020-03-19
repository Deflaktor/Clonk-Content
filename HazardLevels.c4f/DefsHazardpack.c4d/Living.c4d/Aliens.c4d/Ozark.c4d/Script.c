/*-- Ozark --*/

#strict
#include _KI_

/* Punkteauswertung */

private Walking:
  //Sound("OzarkWalk");
  SmackPrey();
  return(1);

Shrink:
  Sound("Teleport");
  // schrumpfe maximal um 25
  DoCon(Max(18-GetCon(), -25));
  // Gib Punkte
  if(Par(0)!=GetOwner())
    DoScore( Par(0), +10 );
  return(1); 
  
private SmackPrey:
  while(SetVar(0,FindObject(0, -30,-20,60,40, OCF_Prey(), 0,0,NoContainer(), Var(0))))
    if(GetTarget(Var(0)))
      if(Var(1)=KannTreten(Var(0),this()))
        return(Punch(Var(0),Var(1)));
  return(1);
 
private CheckForTarget:
  // Kein Ziel in Reichweite
  Var(0)=FindTarget(-Range(),-200,Range()*2,250);
  if(!Var(0))
    return(0);
  // Zielen
  //target=Var(0);
  SetAction("Aim",Var(0));
  return(1);

Range:
  if(target)
    return(300);
  return(200);
  
private Aiming:
  // Kurze Pause
  if (Not(Random(10))) return(SetAction("Walk"));
  // Kein Ziel mehr, außer Reichweite oder tot
  if (Not(SetVar(0,GetActionTarget()))) return(SetAction("Walk"));
  if (!target)
    if (GreaterThan(Distance(GetX(),GetY(),GetX(Var(0)),GetY(Var(0))),Range())) return(SetAction("Walk"));
  if (!GetTarget(GetActionTarget())) return(SetAction("Walk"));
  // Weiterlaufen
  if (Not(Random(25))) return(SetAction("Walk"));
  // Richtung anpassen
  SetDir(DIR_Left()); if (GreaterThan(GetX(Var(0)),GetX())) SetDir(DIR_Right());
  // Winkel anpassen
  SetVar(2,SetVar(1,Angle(GetX(),GetY(),GetX(Var(0)),GetY(Var(0)))));
  if (GreaterThan(Var(1),180)) SetVar(1,Sub(360,Var(1)));
  SetPhase(Sub(12,Div(Var(1),14)));
  // Feuern
  if (Not(Random(3))) ShootThorn(Var(2));
  return(1);

private Activity: 
  _inherited();
 /* if(lastSightTime>10) {
    walkBonus=1;
	target=0;
  }*/
  if(GetAction() eq "Frozen") return(1);
  // Über Hindernisse springen
  if(GetAction() S= "Jump") return(ChaseTarget());
  // Nur beim Gehen
  if (Not(SEqual(GetAction(),"Walk"))) return(1);
  // Fortpflanzung
  if (Not(Random(10000*(Global(5)+100)/100)))
    Reproduction();
  // Ziel suchen
  if (CheckForTarget()) return(1);
  // Target im Auge? Verfolgen
  if(ChaseTarget()) return(1);
  // Springen
  if (Not(Random(5))) return(DoJump());
  // Nur jede zweite Sekunde
  if (Random(4)) return(1);
  // Umdrehen
  if (Random(2)) return(TurnRight());
  return(TurnLeft());

private ChaseTarget:
  var x;
  if(target||lastSightTime<10) {
    if(target)
	  x=GetX(target);
	else
	  x=lastSightX;
    walkBonus=3;
    if(x>GetX()) {
	  if(GetAction() S= "Walk") TurnRight();
	  if(!GBackSolid(20,0)) SetXDir(GetXDir()+5);
	} else {
	  if(GetAction() S= "Walk") TurnLeft();
	  if(!GBackSolid(-20,0)) SetXDir(GetXDir()-5);
	}
    if(Random(2)) DoJump();
    return(1);
  }
  walkBonus=1;
  return(0);
protected ContactLeft:
  if(ChaseTarget())
    return(1);
  return(TurnRight());
protected ContactRight:
  if(ChaseTarget())
    return(1);
  return(TurnLeft());

private TurnRight:
  if (Stuck()) return(0);
  //if (Not(Equal(GetDir(),DIR_Right()))) if (Not(SetAction("Turn"))) return(0);
  SetXDir(0);
  SetDir(DIR_Right());
  SetComDir(COMD_Right()); 
  return(1);

private TurnLeft:
  if (Stuck()) return(0);
  //if (Not(Equal(GetDir(),DIR_Left()))) if (Not(SetAction("Turn"))) return (0);
  SetXDir(0);
  SetDir(DIR_Left());
  SetComDir(COMD_Left()); 
  return(1);

private DoJump:
  if (Not(Random(5))) Sound("OzarkGrowl*");
  Jump();
  return(1);

protected Death:
  SetDir(0);
  ChangeDef(_TOK);
  Sound("OzarkDeath");
  SetAction("Dead");
  return(1);

protected Initialize:
  Refit();
  if(ActIdle())
    SetAction("Lurk");
  SetComDir(COMD_Left()); if (Random(2)) SetComDir(COMD_Right());
  return(1);

public ShootThorn: // (int iAngle)
  // Projektil
  SetVar(0,CreateContents(GLOB));
  // Größe des Projektils anpassen
  SetCon(GetCon(),Var(0));
  // Austrittswinkel (Fehlerstreuung und höher)
  SetVar(8,Sum(Par(0),Random(11),-5));
  if (Equal(GetDir(),DIR_Left())) SetVar(8,Sum(Var(8),+10));
  if (Equal(GetDir(),DIR_Right())) SetVar(8,Sum(Var(8),-10));
	// X-Austritt
  SetVar(4, Sin(Var(8),20) );
  if (Equal(GetDir(),DIR_Left())) SetVar(4,Sum(Var(4),-10));
  if (Equal(GetDir(),DIR_Right())) SetVar(4,Sum(Var(4),+10));
  // Y-Austritt
  SetVar(5, Mul(Cos(Var(8),20),-1) );
  SetVar(5,Sum(Var(5),+10));
  // R-Austritt
  SetVar(7, Var(8) );  
  // XDir
  SetVar(3, Sin(Var(8),10) );
  // YDir
  SetVar(2, Mul(Cos(Var(8),10),-1) );
	// RDir
  SetVar(6, Sum(Random(61),-31));
  // Besitzer des Projektils setzen
  SetOwner(GetOwner(Contained()),Var(0)); 
  // Abfeuern
  Exit(Var(0), Var(4),Var(5),Var(7), Var(3),Var(2),Var(6) );
  ObjectSetAction(Var(0),"Travel");
  // Rückstoß
  SetPhase(Sum(GetPhase(),Random(3),-1));
  // Sound
  Sound("OzarkShoot");
  return(1);

private Lurking:
  // Beute kommt, los geht's
  while(SetVar(0,FindObject(0, -70,-70,140,140, OCF_Prey(), 0,0, NoContainer(), Var(0))))
    if (GetTarget(Var(0)))
      if (PathFree(GetX(),GetY(),GetX(Var(0)),GetY(Var(0))))
        return(RiseForPrey());
  return(0);

public RiseForPrey:
  Refit();
  Sound("OzarkGrowl1");
  // Raus aus der Kiste (und Kiste kaputtmachen)
  SetVar(0,Contained());
  if (Var(0)) Exit(this(),0,15);
  if (Var(0)) SetLocal(9,1);
  if (Var(0)) DoDamage(30,Var(0));
  SetAction("Rise");
  // Enforce Rise
  return(1);
  
private StartJump:
  // Enforce Rise
  if (Local(9)) SetAction("Rise");
  return(1);
private RiseDone:
  // Enforce Rise 
  SetLocal(9,0);
  return(1);

public StartLurking:
  SetAction("Lower");
  return(1);

/* Fortpflanzung */

public Reproduction:
 ObjectCall(CreateConstruction(GetID(this()),0,0,GetOwner(),30),"Birth");
 return(1);

public Birth:
  SetAction("Walk");
  SetComDir(COMD_Left()); if (Random(2)) SetComDir(COMD_Right());
  Refit();
  return(1);

/* Eingefroren */
Frozen: 
  SetXDir(0); // Bei Vereisung stehenbleiben
  if(OnFire(this())) Extinguish(); // Nötigenfalls löschen
  return(1);