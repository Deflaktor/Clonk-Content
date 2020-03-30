#strict

#include HDTP


Initialize:
  SetAction("Walk");
  SetDir(Random(2));
  SetLocal(5,3);
  SetLocal(4,GetRank());
  SetLocal(2,50);
  return(1);

Timer:
  SetLocal(11,Local(11)+1);
  if(Local(13)<=0&&SEqual(GetAction(),"Walk"))
    Nahkampf();
  SetLocal(13,Local(13)-1);
  WegMitMagie();
  return(1);

WegMitMagie:
  if(Local(2)==0)
    return(1);
  SetLocal(2,Local(2)-1);
  DoMagicEnergy(-GetMagicEnergy());
  return(1);

protected ControlDown:
  if ( Control2Contents("ControlDown") ) return(1);
  if(SEqual(GetActMapVal("Procedure",GetAction()),"FIGHT"))
    SetLocal(13,37);
  return(0);

protected ControlSpecial:
  if (ObjectCall(Contents(),"IsAiming")) StopAiming(); 
  if (SEqual(GetAction(),"Verteidigen")) SetAction("Walk"); 
  if (Not(ShiftContents())) return(0);
  if (Not(ObjectCall(Contents(),"Selection"))) Sound("Grab");
  return(1);

ControlSpecial2:
  SetLocal(1,Par(0));
  CreateMenu(MCMS,0,0,3,"Zornattacke ausführen",GetMagicEnergy());
  SetVar(0,-1);

  AddMenuItem("Vernichtungsschlag","VernichtungsschlagSetzen",HZB9);
  AddMenuItem("Rage","Rage",KRRA);

  if(GetID()==KR3A)
    AddMenuItem("Attribute verbessern","VerbessernMenu",GetID());
  return(1);

VernichtungsschlagSetzen:
  if (Local(15)) 
    return(1);
  if (Not( DoMagicEnergy(Mul(Value(Par(0)),-1)) )) 
    return( Message("Nicht genug|Zorn!",this()), Sound("Error") );
  SetLocal(15,1);
  return(1);

Rage:
  if (Not( DoMagicEnergy(Mul(Value(Par(0)),-1)) )) 
    return( Message("Nicht genug|Zorn!",this()), Sound("Error") );
  ObjectCall(CreateObject(HZB9),"Activate",this());
  return();
		
protected Activate:
  if ( SetVar( 0, FindObject( SHIA,0,0,0,0,0,"Shield",this() ) ) ) ObjectCall( Var(0),"Unbuckle" );
  return(1);
  
public ReadyToFire:
   if (Not(Or(SEqual(GetAction(),"Walk"),SEqual(GetAction(),"Swim"),SEqual(GetAction(),"Jump")))) return(0);
   return(1);

public StopAiming:
  SetComDir(COMD_Stop());
  SetAction("Walk");
  Sound("Grab");
  return(1);

IchLebeHierInFrieden:
  SetLocal(7,0);
  return(1);

/*Mit Excalibur Zauber abwehren */
Abwehr:
  if(LessThan(Local(0,Local(1)),30)) SetAction("Walk");
  if(Equal(GetDir(),DIR_Left())) Call("LinkeDefens");
  if(Equal(GetDir(),DIR_Right())) Call("RechteDefens");
  return(1);

LinkeDefens:
  if(SetLocal(7,FindObject(BF3A,-75,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(FM3A,-75,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(GV3A,-75,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(IG3A,-75,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(BF3A,-75,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  return(1);
RechteDefens:
  if(SetLocal(7,FindObject(BF3A,0,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(FM3A,0,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(GV3A,0,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(IG3A,0,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  if(SetLocal(7,FindObject(BF3A,0,-45,75,90))) ObjectCall(Local(1),"Destroy",Local(7));
  return(1);

ExitSpear:
  if (Not(SetVar(6,FindContents(SPER)))) return(0);
  SetVar(0,+1);
  SetVar(1,+150);
  if ( Equal(GetDir(),DIR_Left()) )  SetVar(0,-1);
  if ( Equal(GetDir(),DIR_Left()) )  SetVar(1,+30);
  SetVar(2,Mul(Var(0),10));
  SetVar(3,Mul(Var(0),5));
  SetVar(4,Mul(Var(0),4));
  Exit(Var(6),Var(2),-5,Var(1),Var(3),-2,Var(4));
  return(1);
     
CatchBlow:
  if (SEqual(GetAction(),"Dead")) return(0);
  if(Not(Random(5))) Call("Hurt");
  // Magie geben in Proportion zur verlorenen HP
  SetVar(0,GetPhysical("Energy",0)/1000);
  if(GetOwner(Par(1))==-1)
    DoMagicEnergy(Min(100*Par(0)/Var(0),100-GetMagicEnergy()));
  return(0);

Damage:
  SetVar(0,GetPhysical("Energy",0)/1000);
  if(Par(1)==-1)
    DoMagicEnergy(Min(100*Par(0)/Var(0),100-GetMagicEnergy()));
  return(0);

Redefine:
  _inherited();
  SetPhysical("Magic",100000,2);
  return(1);