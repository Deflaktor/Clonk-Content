//von major}

#strict

public Activate:
 Sound("Magic1");
  
  while(SetVar(0,FindObject(ROCK,-500,-500,1000,1000,0,0,0,0,Var())))
       chx(Var());

return(RemoveObject());


private func chx(target)
{
  Var()=RandomX(-50,30);
  
  CastParticles("MSpark", 50,50, GetX(target)-GetX(),GetY(target)-GetY(), 20, 50, RGB(255), RGB(255));
  
  if(!Random(2))
   {
   CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 1000, RGBa(0,220+Var(),220+Var(),100));
     return(ChangeDef(GOLD,target));}

CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 1000, RGBa(100,100+Var(),180+Var(),100));

  ChangeDef(CRYS,target);
  return();

}

