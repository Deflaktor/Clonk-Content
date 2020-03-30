//vom major}

#strict

public Activate:
 Sound("Magic1");
  SetLocal(1,Par());
  while( SetVar(0,FindObject(0,-500,-500,1000,1000,OCF_CrewMember(),0,0,NoContainer(),Var())))
       if(Hostileto(GetOwner(Var()),GetOwner(Par())))
   	  dmg(Var());       
  


DoEnergy(+Local(),Par());
return(RemoveObject());


private func dmg(target)
{
  SetLocal(0,Local()+20);
  DoEnergy(-20,target);
//DrawParticleLine("MSpark", 0, 0, GetX(target)-GetX(), GetY(target)-GetY(), 20, 100,RGBa(255,50,50,50), RGBa(50,255,50,100), -10);
  DrawParticleLine ("MSpark",0,0,GetX(target)-GetX(),GetY(target)-GetY(), 20,100,RGBa(200,RandomX(50,100),RandomX(0,100),50),RGBa(255,RandomX(0,50),RandomX(0,50),50),-10); 

  CastParticles("MSpark", 50,50, GetX(target)-GetX(),GetY(target)-GetY(), 20, 70, RGB(200), RGB(255));
  CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 1000, RGBa(255,150,50,100));
  }


         