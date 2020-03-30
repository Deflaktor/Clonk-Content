#strict

#include HDTP

local mpregen;

Initialize:
  SetAction("Walk");
  SetDir(Random(2));
  SetEntrance(1);
  SetLocal(5,YW3A);
  SetLocal(6,YG3A);
  Call("Zaub",100);
  SetLocal(4,GetRank());
  return(1);

Timer:
  SetLocal(11,Local(11)+1);
  GiveMagic();
  return(1);

ControlSpecial:
  if (Not(ShiftContents())) return(0);
  if (Not(ObjectCall(Contents(),"Selection")))
    Sound("Grab");
  return(1);

ControlSpecial2Double:
  return(0);

ControlSpecial2:
  if(GetY()<300)
    return( Message("Auf dieser Höhe kann ich nicht zaubern!",this()), Sound("Error") );
  SetLocal(1,Par(0));
  CreateMenu(MCMS,0,0,3,0,GetMagicEnergy());
  SetVar(0,-1);
  //while (SetVar(1,GetPlrMagic(GetOwner(),0,IncVar(0)))) 
  //   AddMenuItem( "%s", "DoMagic", Var(1) ); 

  			AddMenuItem("Fulminictus","DoMagic",FM3A);
 			AddMenuItem("Ignifaxius","DoMagic",IG3A);
			AddMenuItem("Kampfzauber Brechen","DoMagic",B13A);
 			AddMenuItem("Axxeleratus","DoMagic",XX3A);
 			AddMenuItem("Balsamsalabunde","DoMagic",BB3A);
 			AddMenuItem("Zorn der Elemente","DoMagic",ZE3A);
 			AddMenuItem("Band und Fessel","DoMagic",BF3A);
 			AddMenuItem("Grosse Verwirrung","DoMagic",GV3A);
  			AddMenuItem("Krötensprung","DoMagic",KG3A);
  			AddMenuItem("Armatrutz","DoMagic",AM3A);
if (FindContents(_SFE)) AddMenuItem("Eisball","DoMagic",HTB7);
if (FindContents(_SFG)) AddMenuItem("Gruppenheilung","DoMagic",HTM0);
if (FindContents(_SFM)) AddMenuItem("Manapfeil","DoMagic",HTM9);
if (FindContents(_SFS)) AddMenuItem("Schleudern","DoMagic",HTM3);

  AddMenuItem("Zauber festlegen für Werfen-Taste","MenuWerfen",YW3A);
  AddMenuItem("Zauber festlegen für Graben-Taste","MenuGraben",YG3A);
  AddMenuItem("Attribute verbessern","VerbessernMenu",GetID());
  return(1);

GiveMagic:
  // Anzahl der Sekunden bis MP voll ist
  SetVar(0,60);
  if(FindContents(ZS3A))
    SetVar(0,Var(0)/2);
  // Max MP
  SetVar(1,GetPhysical("Magic")/1000);
  // MP regenerieren pro tick
  SetVar(2,(100000*Var(1))/(Var(0)*35));
  if(Var(2)<100000) {
    mpregen += Var(2);
    if(mpregen>=100000) {
      DoMagicEnergy(1);
      mpregen -= 100000;
    }
  } else {
    DoMagicEnergy(Min(Var(2),Var(1)-GetMagicEnergy()));
  }
  
  return(1);

ControlThrow:
  if(Not(SEqual(GetAction(),"Walk"))) return(0);
  if ( Control2Contents("ControlThrow") ) return(1);
  if(Equal(Local(5),YW3A)) return(0);
  if(Equal(Local(5),0)) return(0);
  if(Not(FindContents(ZE3A))) Call("DoMagic",Local(5));
  return(0);

ControlDigSingle:
  if(Not(SEqual(GetAction(),"Walk"))) return(0);
  if(Equal(Local(6),YG3A)) return(0);
  if(Equal(Local(6),0)) return(0);
  Call("DoMagic",Local(6));
  return(1);

MenuWerfen:
  CreateMenu(MCMS,0,0,3);
  AddMenuItem("Festlegen: Werfen","SetThrow",YW3A);
  SetVar(0,-1);
  //while (SetVar(1,GetPlrMagic(GetOwner(),0,IncVar(0))))   
  //  AddMenuItem( "Festlegen: %s", "SetThrow", Var(1) ); 

  AddMenuItem("Festlegen: Fulminictus","SetThrow",FM3A);
  AddMenuItem("Festlegen: Ignifaxius","SetThrow",IG3A);
  AddMenuItem("Festlegen: Kampfzauber Brechen","SetThrow",B13A);
  AddMenuItem("Festlegen: Axxeleratus","SetThrow",XX3A);
  AddMenuItem("Festlegen: Balsamsalabunde","SetThrow",BB3A);
  AddMenuItem("Festlegen: Zorn der Elemente","SetThrow",ZE3A);
  AddMenuItem("Festlegen: Band und Fessel","SetThrow",BF3A);
  AddMenuItem("Festlegen: Grosse Verwirrung","SetThrow",GV3A);
  AddMenuItem("Festlegen: Krötensprung","SetThrow",KG3A);
  AddMenuItem("Festlegen: Armatrutz","SetThrow",AM3A);
if (FindContents(_SFE)) AddMenuItem("Festlegen: Eisball","SetThrow",HTB7);
if (FindContents(_SFG)) AddMenuItem("Festlegen: Gruppenheilung","SetThrow",HTM0);
if (FindContents(_SFM)) AddMenuItem("Festlegen: Manapfeil","SetThrow",HTM9);
if (FindContents(_SFS)) AddMenuItem("Festlegen: Schleudern","SetThrow",HTM3);

  return(1);
SetThrow:
  SetLocal(5,Par(0));
  return(1);

MenuGraben:
  CreateMenu(MCMS,0,0,3);
  AddMenuItem("Festlegen: Graben","SetGraben",YG3A);
  SetVar(0,-1);
  //while (SetVar(1,GetPlrMagic(GetOwner(),0,IncVar(0))))
  //  AddMenuItem( "Festlegen: %s", "SetGraben", Var(1) ); 
  AddMenuItem("Festlegen: Kampfzauber Brechen","SetGraben",B13A);
  AddMenuItem("Festlegen: Fulminictus","SetGraben",FM3A);
  AddMenuItem("Festlegen: Ignifaxius","SetGraben",IG3A);

  AddMenuItem("Festlegen: Axxeleratus","SetGraben",XX3A);
  AddMenuItem("Festlegen: Balsamsalabunde","SetGraben",BB3A);
  AddMenuItem("Festlegen: Zorn der Elemente","SetGraben",ZE3A);
  AddMenuItem("Festlegen: Band und Fessel","SetGraben",BF3A);
  AddMenuItem("Festlegen: Grosse Verwirrung","SetGraben",GV3A);
  AddMenuItem("Festlegen: Krötensprung","SetGraben",KG3A);
  AddMenuItem("Festlegen: Armatrutz","SetGraben",AM3A);
if (FindContents(_SFE)) AddMenuItem("Festlegen: Eisball","SetGraben",HTB7);
if (FindContents(_SFG)) AddMenuItem("Festlegen: Gruppenheilung","SetGraben",HTM0);
if (FindContents(_SFM)) AddMenuItem("Festlegen: Manapfeil","SetGraben",HTM9);
if (FindContents(_SFS)) AddMenuItem("Festlegen: Schleudern","SetGraben",HTM3);

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

IchLebeHierInFrieden:
  SetLocal(7,0);
  return(1);

/* Während des Kämpfens */
Fighting:
  SetLocal(7,1);
	if (FindContents(MT3A)) return(SetAction("MagierflorettFight",Par(0)));
	if (FindContents(ZS3A)) return(SetAction("ZauberstabFight",Par(0)));
	if (FindContents(KP3A)) return(SetAction("KampfstabFight",Par(0)));
	if (FindContents(DO3A)) return(SetAction("DolchFight",Par(0)));
  if (Not(Random(4))) SetAction("Punch");
  return(1);
  
Zaub:
  SetVar(0,Par(0));
  SetVar(1,0);
  while(GreaterThan(Var(0),Var(1))) if(IncVar(1)) DoMagicEnergy(1,Local(0));
  return(1);

//Local(3) ist der Gegenstand
Brauen:
  SetVar(1,Random(4));
  Sound("Zischen");
  if(Equal(Var(1),0)) SetAction("Wolke0");
  if(Equal(Var(1),1)) SetAction("Wolke1");
  if(Equal(Var(1),2)) SetAction("Wolke2");
  if(Equal(Var(1),3)) SetAction("Wolke3");
  return(1);

Brauenfertig:
  Exit(Local(3));
  Enter(this(),Local(3));
  return(1);