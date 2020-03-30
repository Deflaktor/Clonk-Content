//vom major}

#strict

public Activate:
 Sound("Magic1");
  DoEnergy(+100,Par(0));
  while( SetVar(0,FindObject(TRE1,-500,-500,1000,1000,0,0,0,NoContainer(),Var())))
         Heal(Var(),C4Id("TRB1"));

 while( SetVar(0,FindObject(TRE2,-500,-500,1000,1000,0,0,0,NoContainer(),Var())))
         Heal(Var(),C4Id("TRB2"));

 while( SetVar(0,FindObject(TRE3,-500,-500,1000,1000,0,0,0,NoContainer(),Var())))
         Heal(Var(),C4Id("TRB3"));

while( SetVar(0,FindObject(BUSH,-500,-500,1000,1000,0,0,0,NoContainer(),Var())))
         Heal(Var(),C4Id("BUSB"));

while( SetVar(0,FindObject(PLM1,-500,-500,1000,1000,0,0,0,NoContainer(),Var())))
         Heal(Var(),C4Id("PLB1"));

while( SetVar(0,FindObject(PLM2,-500,-500,1000,1000,0,0,0,NoContainer(),Var())))
         Heal(Var(),C4Id("PLB2"));

return(RemoveObject());

private func Heal(target,cto)
{
  
  ChangeDef(cto,target);
  CastParticles("MSpark", 50,50, GetX(target)-GetX(),GetY(target)-GetY(), 20, 50, RGB(255), RGB(255));
  CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 1000, RGBa(255,255,50,100));
  }


         