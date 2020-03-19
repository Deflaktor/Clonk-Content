#strict

/*-- Generator --*/

Initialize:
  SetAction("Stopped");
  return(1);
Transfer:
  if(Local(0)) Transfer2();
  SetLocal(0,1);
  InsertMaterial(ExtractLiquid(-106,68),106,68);
  InsertMaterial(ExtractLiquid(-106,68),106,68);
  return(1);
Transfer2:
  SetLocal(0,0);
  InsertMaterial(ExtractLiquid(106,68),-106,68);
  InsertMaterial(ExtractLiquid(106,68),-106,68);
  return(1);

ControlDownSingle:
  [Herunterfahren]
  if(Not(SEqual(GetAction(),"Running"))) return(0);
  SetVar(0,GetPhase());
  SetAction("Stopped");
  Sound("GeneratorStop");
  SetPhase(Var(0));
  return(1);

ControlUpSingle:
  [Anfahren]
  if(Not(SEqual(GetAction(),"Stopped"))) return(0);
  SetVar(0,GetPhase());
  SetAction("Running");
  Sound("GeneratorStart");
  SetPhase(Var(0));
  return(1);

Charge:
  if (Random(5)) return(0);
  LaunchLight( GetX(), Sum(GetY(),-40), Sum(Random(21),-10,-10),21, Sum(Random(30),-20),10 );
  return(1);
  
  
LaunchLight:
  ObjectCall(CreateObject(FXL1),"Activate",Par(0),Par(1),Par(2),Par(3),Par(4),Par(5));
  return(1);