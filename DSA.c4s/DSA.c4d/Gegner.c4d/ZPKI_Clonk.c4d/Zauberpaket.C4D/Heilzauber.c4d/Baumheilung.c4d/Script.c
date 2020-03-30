//vom major}

#strict

public Activate:
 Sound("Magic1");
  DoEnergy(+100,Par(0));
  while( SetVar(0,FindObject(TRB1,-500,-500,1000,1000,0,0,0,NoContainer(),Var())))
         Heal(Var(),C4Id("TRE1"));

 while( SetVar(0,FindObject(TRB2,-500,-500,1000,1000,0,0,0,NoContainer(),Var())))
         Heal(Var(),C4Id("TRE2"));

 while( SetVar(0,FindObject(TRB3,-500,-500,1000,1000,0,0,0,NoContainer(),Var())))
         Heal(Var(),C4Id("TRE3"));

while( SetVar(0,FindObject(BUSB,-500,-500,1000,1000,0,0,0,NoContainer(),Var())))
         Heal(Var(),C4Id("BUSH"));

while( SetVar(0,FindObject(PLB1,-500,-500,1000,1000,0,0,0,NoContainer(),Var())))
         Heal(Var(),C4Id("PLM1"));

while( SetVar(0,FindObject(PLB2,-500,-500,1000,1000,0,0,0,NoContainer(),Var())))
         Heal(Var(),C4Id("PLM2"));

return(RemoveObject());

private func Heal(target,cto)
{
  if(GetOCF(target)&OCF_OnFire())
	 Extinguish(target);
  ChangeDef(cto,target);
  CastParticles("MSpark", 50,50, GetX(target)-GetX(),GetY(target)-GetY(), 20, 50, RGB(255), RGB(255));
  CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 1000, RGBa(50,255,50,100));
  }


         