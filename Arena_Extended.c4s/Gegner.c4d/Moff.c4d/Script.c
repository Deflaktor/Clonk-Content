/* Initialisierung */
#strict
#include _PEM

protected Initialize:
  SetOwner(-1);
  SetColor(7);
  SetAction("Start");
  return(1);

public Redefine:
  ChangeDef(Par(0));
  SetAction("Walk");
  return(1);

public Frisch:
  SetAction("Walk");
  ChangeDir();
  return(1);

/* Aktivit�t */

protected Activity:
  if(GetEnergy() <= 0)
    if(GetAction() ne "Dead") return(Remove());
  if(GetAction() eq "Wait") return(0);
  if(GetAction() eq "Dead") return(0);

  // Richtung �ndern
  if (Not(Random(30))) ChangeDir();


  // Anhalten
  if (Not(Random(10))) Stop();




  // Feinde verfolgen
  
  while(Var(0)=FindObject(0,0,0,-1,-1,OCF_Prey(),0,0,0,Var(0)))
    if(GetOwner(Var(0))!=GetOwner()) {
      Local(0)=Var(0);
      break;
    }

  if(Not(PathFree(GetX(),GetY(),GetX(Local(0)),GetY(Local(0))-1))) SetLocal(0,0);

  if(Local(0)) SetCommand(this(),"Follow",Local(0));

  // Feinde angreifen(Zuschlagen)
  if(GetAction() eq "Hacken") return(1);
  if(Local(0)) if(Distance(GetX(),GetY(),GetX(Local(0)),GetY(Local(0)))<40) return(Angriff(Local(0)));
 /*if(SetVar(0,FindObject(0,-25,-30,50,60,OCF_CrewMember(),0,0,NoContainer()))) 
    if(PathFree(GetX(),GetY(),GetX(Var(0)),GetX(Var(0)))) Angriff(Var(0));
  if(SetVar(0,FindObject(_VT1,-30,-25,50,60))) 
    if(PathFree(GetX(),GetY(),GetX(Var(0)),GetX(Var(0)))) Angriff(Var(0));
  if(SetVar(0,FindObject(_VT2,-30,-25,50,60))) 
    if(PathFree(GetX(),GetY(),GetX(Var(0)),GetX(Var(0)))) Angriff(Var(0)); 
  if(SetVar(0,FindObject(_DR1,-25,-30,50,60))) Angriff(Var(0));
  if(SetVar(0,FindObject(PM7K,-25,-30,50,60))) Angriff(Var(0));
  if(SetVar(0,FindObject(PN7K,-25,-30,50,70))) Angriff(Var(0));
  if(SetVar(0,FindObject(GAT3,-25,-30,50,70))) Angriff(Var(0));
  if(SetVar(0,FindObject(BTBL,-35,-25,70,60))) Angriff(Var(0));
  if(SetVar(0,FindObject(BTB2,-35,-25,70,60))) Angriff(Var(0));
  while (SetVar(0,FindObject(0,-25,-35,50,70,OCF_Living(),0,0,NoContainer(),Var(0)))) 
    if(Not(Equal(GetID(Var(0)),ZAP1)))  
      if(Not(Equal(GetID(Var(0)),SR5B))) 
        if(Not(Equal(GetID(Var(0)),ST5B))) 
          if(Not(Equal(GetID(Var(0)),KG5B)))
            if(Not(Equal(GetID(Var(0)),MF5B)))
              if(Not(Equal(GetID(Var(0)),MI5B)))
                if(Not(Equal(GetID(Var(0)),_PLT)))
                  if(GetAlive(Var(0))) Angriff(Var(0));*/


  // Fertig
  return(1);






/* Aktionen */

private Hindernis:
  SetCommand(this(),"None");
  ChgDirTo(Par(0));
  return(1);

private ChgDirTo:
  SetComDir(Par(0));
  SetAction("Walk");
  return(1);

private ChangeDir:
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
  DoEnergy(-25,Var(0));
  DoDamage(25,Var(0));
  if(Equal(GetDir(),DIR_Left()))  SetVar(1,-1);
  if(Equal(GetDir(),DIR_Right())) SetVar(1,1);
  Fling(Var(0),Var(1),1);
  return(Sound("MFHacken2"));
  return(1);
 


CatchBlow:
  return(Damage());


Death:
  SetAction("Dead");
  return(1);

Remove:
  var threattype = Random(5);
  if(threattype == 10)
  CreateObject(S582,0,0,GetOwner(this()));
  if(threattype < 10)
  CreateObject(ST58,0,0,GetOwner(this()));
  RemoveObject();
  return(1);

Damage:
  Sound("MFSchaden*");
  return(_inherited());

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

