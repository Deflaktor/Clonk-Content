//vom major}

#strict

public Activate:
 Sound("Magic1");
  DoEnergy(+100,Par(0));
  while( SetVar(0,FindObject(0,-500,-500,1000,1000,OCF_CrewMember(),0,0,NoContainer(),Var())))
       if(!Hostileto(GetOwner(Var()),GetOwner(Par())))
          Heal(Var());

while(SetVar(0,FindObject(HZA5,-500,-500,1000,1000,0,0,0,NoContainer(),Var())))
       if(!Hostileto(GetOwner(Var()),GetOwner(Par())))
		 gegengift(Var());

return(RemoveObject());


private func Heal(target)
{
  
  DoEnergy(+100,target);
  CastParticles("MSpark", 50,50, GetX(target)-GetX(),GetY(target)-GetY(), 20, 50, RGB(255), RGB(255));
  CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 1000, RGBa(255,50,50,100));
  }


private func gegengift(target)
{
  
  RemoveObject(target);
  CastParticles("MSpark", 50,50, GetX(target)-GetX(),GetY(target)-GetY(), 20, 50, RGB(255), RGB(255));
  CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 1000, RGBa(50,50,255,100));
  }


         