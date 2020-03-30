Initialize:
  SetAction("Los");
  return(1);

Test:
  if(Equal(Local(9),0)) return(0);
  if(SetLocal(1,FindObject(0,-120,-70,280,150,OCF_Prey()))) if(Equal( GetComDir(FindObject(FT3A,-200,-100,150,200)), 5))  SetAction("AbdiePost");
  return(1);


Start:
  SetLocal(9,1,FindObject(FT3A,-200,-100,150,200));
  if(LessThan(Local(0),14)) SetLocal(0,Sum(Local(0),1));
  Message("Es geht los, Stufe %d",0,Local(0));
  return(1);

Demon:
  SetVar(6,GetX());
  SetVar(7,GetY());
  SetPosition(0,0);
  if(GreaterThan(Local(0),0)) CreateObject(KS3A,2890,490,-1);
  if(GreaterThan(Local(0),1)) CreateObject(KA3A,2820,510,-1);
  if(GreaterThan(Local(0),2)) CreateObject(KS3A,2950,460,-1);
  if(GreaterThan(Local(0),3)) CreateObject(KB3A,3010,470,-1);
  if(GreaterThan(Local(0),4)) CreateObject(KS3A,2980,540,-1);

  if(GreaterThan(Local(0),6)) CreateObject(KS3A,2890,490,-1);
  if(GreaterThan(Local(0),7)) CreateObject(KA3A,2950,460,-1);
  if(GreaterThan(Local(0),8)) CreateObject(KA3A,2920,640,-1);

  if(GreaterThan(Local(0),9)) CreateObject(KB3A,2760,470,-1);
  if(GreaterThan(Local(0),10)) CreateObject(KA3A,3000,470,-1);

  if(GreaterThan(Local(0),12)) CreateObject(KB3A,3095,550,-1);
  if(GreaterThan(Local(0),13)) CreateObject(KS3A,2890,490,-1);

  SetPosition(Var(6),Var(7));
  return(1);

WhileFight:
  if(Not(FindObject(KS3A,-220,-80,450,280))) 
   if(Not(FindObject(KB3A,-220,-80,450,280)))
    if(Not(FindObject(KA3A,-220,-80,450,280)))  Call("Ende");
  return(1);

Ende:
  Message("Ihr habt eure Gegner besiegt. |Hier ist euer Geld.");
  SetLocal(9,0);
  SetLocal(9,0,FindObject(FT3A,-200,-100,150,200));

  CastObjects(GS3A,Mul(Local(0),5),10,0,0);


  while(SetVar(1,FindObject(KT3A,-220,-80,450,280))) RemoveObject(Var(1));

  SetAction("Los");
  return(1);


