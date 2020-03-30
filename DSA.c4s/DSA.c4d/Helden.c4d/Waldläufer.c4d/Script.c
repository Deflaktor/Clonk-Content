#strict

#include HDTP


Initialize:
  SetAction("Walk");
  SetDir(Random(2));
  SetLocal(5,3); // Vorgabe Bogen-Zielrichtung
  Call("Zaub",100);
  SetLocal(4,GetRank());
  return(1);

/* Steuerung Richtung (an Inhalt weitergeben, sonst internen Befehl ausführen) */
protected ControlUp:
  if ( Control2Contents("ControlUp") ) return(1);
  return(0);
protected ControlDown:
  if ( Control2Contents("ControlDown") ) return(1);
  return(0);
protected ControlLeft:
  if ( Control2Contents("ControlLeft") ) return(1);
  return(0);
protected ControlRight:
  if ( Control2Contents("ControlRight") ) return(1);
  return(0);
protected ControlLeftDouble:
  if ( Control2Contents("ControlLeftDouble") ) return(1);
  return(0);
protected ControlRightDouble:
  if ( Control2Contents("ControlRightDouble") ) return(1);
  return(0);
protected ControlDigDouble:
  if ( Control2Contents("ControlDigDouble") ) return(1);
  return(0);

/* Steuerung Inventar */
protected ControlSpecial:
  if (ObjectCall(Contents(),"IsAiming")) StopAiming(); 
  if (Not(ShiftContents())) return(0);
  if (Not(ObjectCall(Contents(),"Selection"))) // Objekteigener Aktivierungssound
    Sound("Grab"); // Genereller Aktivierungssound
  return(1);

ControlSpecial2:
  if(GetY()<300)
    return( Message("Auf dieser Höhe kann ich nicht zaubern!",this()), Sound("Error") );
  SetLocal(1,Par(0));
  CreateMenu(MCMS,0,0,3,0,GetMagicEnergy());
  SetVar(0,-1);
  //while (SetVar(1,GetPlrMagic(GetOwner(),0,IncVar(0))))
  //  AddMenuItem( "%s", "DoMagic", Var(1) ); 

  AddMenuItem("Fulminictus","DoMagic",FM3A);
  //AddMenuItem("Ignifaxius","DoMagic",IG3A);
  AddMenuItem("Kampfzauber Brechen","DoMagic",B13A);
  AddMenuItem("Axxeleratus","DoMagic",XX3A);
  AddMenuItem("Armatrutz","DoMagic",AM3A);
  AddMenuItem("Balsamsalabunde","DoMagic",BB3A);
  AddMenuItem("Zorn der Elemente","DoMagic",ZE3A);
  AddMenuItem("Band und Fessel","DoMagic",BF3A);
  AddMenuItem("Grosse Verwirrung","DoMagic",GV3A);
  AddMenuItem("Krötensprung","DoMagic",KG3A);
  AddMenuItem("Doppelpower","DoMagic",HZB9);

  AddMenuItem("Zauber festlegen für Graben-Taste","MenuGraben",YG3A);
  AddMenuItem("Attribute verbessern","VerbessernMenu",GetID());
  return(1);

ControlDigSingle:
  if(Not(SEqual(GetAction(),"Walk"))) return(0);
  if(Equal(Local(6),YG3A)) return(0);
  if(Equal(Local(6),0)) return(0);
  Call("DoMagic",Local(6));
  return(1);

MenuGraben:
  CreateMenu(MCMS,0,0,3);
  AddMenuItem("Festlegen: Graben","SetGraben",YG3A);
  SetVar(0,-1);
  //while (SetVar(1,GetPlrMagic(GetOwner(),0,IncVar(0))))
  //  AddMenuItem( "Festlegen: %s", "SetGraben", Var(1) ); 

  AddMenuItem("Festlegen: Fulminictus","SetGraben",FM3A);
  //AddMenuItem("Festlegen: Ignifaxius","SetGraben",IG3A);
  AddMenuItem("Festlegen: Kampfzauber Brechen","SetGraben",B13A);
  AddMenuItem("Festlegen: Axxeleratus","SetGraben",XX3A);
  AddMenuItem("Festlegen: Armatrutz","SetGraben",AM3A);
  AddMenuItem("Festlegen: Balsamsalabunde","SetGraben",BB3A);
  AddMenuItem("Festlegen: Zorn der Elemente","SetGraben",ZE3A);
  AddMenuItem("Festlegen: Band und Fessel","SetGraben",BF3A);
  AddMenuItem("Festlegen: Grosse Verwirrung","SetGraben",GV3A);
  AddMenuItem("Festlegen: Krötensprung","SetGraben",KG3A);
  AddMenuItem("Festlegen: Doppelpower","SetGraben",HZB9);
if (FindContents(_SFE)) AddMenuItem("Festlegen: Eisball","SetThrow",HTB7);
if (FindContents(_SFG)) AddMenuItem("Festlegen: Gruppenheilung","SetThrow",HTM0);
if (FindContents(_SFM)) AddMenuItem("Festlegen: Manapfeil","SetThrow",HTM9);
if (FindContents(_SFS)) AddMenuItem("Festlegen: Schleudern","SetThrow",HTM3);

  return(1);
SetGraben:
  SetLocal(6,Par(0));
  return(1);

DoMagic:
  if(GetY()<300)
    return( Message("Auf dieser Höhe kann ich nicht zaubern!",this()), Sound("Error") );
  if (Not(SEqual(GetAction(),"Walk"))) return(0);
  if (Contained()) return(0);
  if (Not( DoMagicEnergy(Mul(Value(Par(0)),-1)) )) 
    return( Message("Nicht genug|Zauberenergie!",this()), Sound("Error") );
  SetAction("Magic");
  ObjectCall(CreateObject(Par(0)),"Activate",this());
  return(1);

/* Wenn ControlDigDouble nicht anderweitig ausgewertet wurde */
protected Activate:
  // Schild wieder einpacken
  if ( SetVar( 0, FindObject( SHIA,0,0,0,0,0,"Shield",this() ) ) )
    ObjectCall( Var(0),"Unbuckle" );
  return(1);
  
/* Kann der Clonk aus der aktuellen Aktion feuern? */
public ReadyToFire:
   if (Not(Or(SEqual(GetAction(),"Walk"),SEqual(GetAction(),"Swim"),SEqual(GetAction(),"Jump"))))  return(0);
   return(1);

/* Zielaktion abbrechen */
public StopAiming:
  SetComDir(COMD_Stop());
  SetAction("Walk");
  Sound("Grab");
  return(1);

IchLebeHierInFrieden:
  SetLocal(7,0);
  return(1);

/* Während des Kämpfens */
Fighting:
  SetLocal(7,1);
	if (FindContents(RA3A)) return(SetAction("RapierFight",Par(0)));
	if (FindContents(DO3A)) return(SetAction("DolchFight",Par(0)));
	if (FindContents(KP3A)) return(SetAction("KampfstabFight",Par(0)));
  if (Not(Random(4))) SetAction("Punch");
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

Zaub:
  SetVar(0,Par(0));
  SetVar(1,0);
  while(GreaterThan(Var(0),Var(1))) if(IncVar(1)) DoMagicEnergy(1,Local(0));
  return(1);
