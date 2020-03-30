Initialize:
  return(1);

RejectCollect:
  if(Equal(Par(0),_ZKI)) return(0);
  if(Equal(Par(0),_ZKR)) return(0);
  if(Equal(Par(0),_ZKH)) return(0);
  Sound("Crystal*");
  return(1);

BurnBabyBurn:
 if(Equal(Local(0),0))
  if(FindContents(_ZKI))
     if(FindContents(_ZKR))
        if(FindContents(_ZKH))
         Call("FreudeHerrscht");
  return(1);

FreudeHerrscht:
  SetLocal(0,101901);
  SetAction("pojhngDjhNC");
  return(1);

Tataa:
  SetLocal(1,1);
  Message("Der Zauberstab ist nun Euer",this());
  CreateObject(ZS3A);
  SetLocal(8,1,FindObject(FT33,-5000,-3000,10000,6000));
  return(1);

Sparkle:
  SetVar(1,Sum(Random(6),-2));
  SetVar(2,Sum(Random(4),-1));
  CastObjects(SPRK,3,20,Var(1),Var(2));
  if(GreaterThan(GetActTime(),130))  if(Not(Local(1))) Call("Tataa");
  if(GreaterThan(GetActTime(),150))  SetAction("idle");
  return(1);


