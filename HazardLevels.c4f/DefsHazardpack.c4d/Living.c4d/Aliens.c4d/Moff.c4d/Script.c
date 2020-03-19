/* Initialisierung */
#strict
#include _KI_

protected Initialize:
  Refit();
  SetAction("Start");
  return(1);

public Frisch:
  SetAction("Walk");
  ChangeDir();
  return(1);

/* Aktivität */

protected Activity:
  _inherited();
  if(GetAction() eq "Frozen") return(1);
  if(GetEnergy() <= 0)
    if(GetAction() ne "Dead") return(Remove());
  if(GetAction() eq "Wait") return(0);
  if(GetAction() eq "Dead") return(0);


  // Richtung ändern
  if (Not(Random(20))) ChangeDir();


  // Anhalten
  if (Not(Random(10))) Stop();



  // Feinde verfolgen
  while(Var(0)=GetTarget(FindObject(0,0,0,-1,-1,OCF_Prey(),0,0,NoContainer(),Var(0))))
    if(GetTarget(Var(0)))
      SetLocal(0,Var(0));

  if(Not(PathFree(GetX(),GetY(),GetX(Local(0)),GetY(Local(0))-1))) SetLocal(0,0);

  if(Local(0)) SetCommand(this(),"Follow",Local(0));


  // An Abgründen oder Wänden anhalten
  if (GetComDir() == COMD_Right())
    if (And(Not(GBackSolid(30,10)),Not(GBackSolid(30,20)))) 
      if (And(Not(FindObject(_LFP,0,0,50,25)),Not(FindObject(_LFS,0,0,50,25)))) 
        Hindernis(COMD_Left());

  if (GetComDir() == COMD_Left())
    if (And(Not(GBackSolid(-30,10)),Not(GBackSolid(-30,20)))) 
      if (And(Not(FindObject(_LFP,-50,0,50,25)),Not(FindObject(_LFS,-50,0,50,25)))) 
        Hindernis(COMD_Right());

  if (GetComDir() == COMD_Right())
    if (Not(PathFree(GetX(),GetY(),GetX()+20,GetY()))) Hindernis(COMD_Left());

  if (GetComDir() == COMD_Left())
    if (Not(PathFree(GetX(),GetY(),GetX()-20,GetY()))) Hindernis(COMD_Right());


  Var(0)=0;
  // Feinde angreifen(Zuschlagen)
  if(GetAction() eq "Hacken") return(1);
  while (SetVar(0,FindObject(0,-25,-30,50,60,OCF_Prey(),0,0,NoContainer(),Var(0))))
    if(GetTarget(Var(0)))
      if(KannTreten(Var(0)))
        if(PathFree(GetX()-5,GetY(),GetX(Var(0)),GetY(Var(0)))||PathFree(GetX()+5,GetY(),GetX(Var(0)),GetY(Var(0)))) 
          return(Angriff(Var(0)));

  if(SetVar(0,FindObject(_VT1,-30,-25,50,60))) 
    if(PathFree(GetX(),GetY(),GetX(Var(0)),GetX(Var(0)))) Angriff(Var(0));
  if(SetVar(0,FindObject(_VT2,-30,-25,50,60))) 
    if(PathFree(GetX(),GetY(),GetX(Var(0)),GetX(Var(0)))) Angriff(Var(0)); 
  if(SetVar(0,FindObject(_DR1,-25,-30,50,60))) Angriff(Var(0));
  if(SetVar(0,FindObject(GATE,-25,-30,50,60))) Angriff(Var(0));
  if(SetVar(0,FindObject(GAT2,-25,-30,50,70))) Angriff(Var(0));
  if(SetVar(0,FindObject(GAT3,-25,-30,50,70))) Angriff(Var(0));
  if(SetVar(0,FindObject(BTBL,-35,-25,70,60))) Angriff(Var(0));
  if(SetVar(0,FindObject(BTB2,-35,-25,70,60))) Angriff(Var(0));



  // Fertig
  return(1);

/* Aktionen */

private Hindernis:
  SetCommand(this(),"None");
  ChgDirTo(Par(0));
  return(1);

private ChgDirTo:
  if(GetAction() S= "Jump") return(0);
  SetComDir(Par(0));
  SetAction("Walk");
  return(1);

private ChangeDir:
  if(GetAction() S= "Jump") return(0);
  SetVar(0,COMD_Left());
  if (Random(2)) SetVar(0,COMD_Right());
  SetComDir(Var(0));
  SetAction("Walk");
  return(1);

Angriff:
  SetAction("Hacken",Par(0));
  SetVar(0,Sub(GetX(Par(0)),GetX()));
  if(GreaterThan(Var(0))) return(SetDir(DIR_Right()));
  return(SetDir(DIR_Left()));

Hacken:
  SetVar(0,GetActionTarget());
  if(GetOCF(Var(0)) & OCF_Living())
    if(Not(GetAlive(Var(0))))                    return(Sound("MFHacken1"));
  if(Contained(Var(0)))                          return(Sound("MFHacken1"));
  if(Not(Inside(ObjectDistance(Var(0),0),0,35))) return(Sound("MFHacken1"));
  DoEnergy(-40*(KannTreten(Var(0))+100)/100,Var(0));
  DoDamage(25*GetCon()/100,Var(0));
  if(Equal(GetDir(),DIR_Left()))  SetVar(1,-1);
  if(Equal(GetDir(),DIR_Right())) SetVar(1,1);
  Fling(Var(0),Var(1),1);
  return(Sound("MFHacken2"));
 
Death:
  SetXDir(0);
  SetYDir(0);
  SetAction("Dead");
  return(1);

Remove:
  return(RemoveObject());

Damage:
  Bluten(Par(0));
  return(Sound("MFSchaden*"));

Stop:
  SetCommand(this(),"None");
  return(SetComDir(COMD_Stop()));

Auflauf:
  if(Not(SetVar(0,FindObject(MF5B,0,0,-1,-1))))                                    return(0);
  if(Not(Inside(ObjectDistance(Var(0),0),0,100)))                                  return(0);
  if(Not(GreaterThan(ObjectDistance(Local(0),0),ObjectDistance(Local(0),Var(0))))) return(0);
  return(1);

Frei:
  return(Not(GBackSemiSolid()));

/* Eingefroren */
Frozen: 
  if(OnFire(this())) Extinguish(); // Nötigenfalls löschen
  return(1);