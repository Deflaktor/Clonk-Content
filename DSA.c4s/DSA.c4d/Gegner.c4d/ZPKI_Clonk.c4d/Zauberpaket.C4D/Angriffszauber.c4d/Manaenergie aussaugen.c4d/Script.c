//vom major}

#strict

public Activate:
 Sound("Magic1");
  SetLocal(1,Par());
if(Par(1))
SetLocal(1,Par(1));

  while( SetVar(0,FindObject(0,-500,-500,1000,1000,OCF_CrewMember(),0,0,NoContainer(),Var())))
        if(Hostileto(GetOwner(Var()),GetOwner(Par())))
   	           dmg(Var());

DoMagicEnergy(Local(),Local(1));
return(RemoveObject());


private func dmg(target)
{
if(GetMagicEnergy(target)==0)
  target=FindContents(HTZ0,target); 
	if(!target)	
		return();  

SetLocal(0,Local()+35);
  DoMagicEnergy(-35,target);
  DrawParticleLine ("MSpark",0,0,GetX(target)-GetX(),GetY(target)-GetY(), 20,100,RGBa(0,RandomX(0,100),RandomX(200,255),50),RGBa(25,0,255,50),-10); 

  CastParticles("MSpark", 50,50, GetX(target)-GetX(),GetY(target)-GetY(), 20, 50, RGB(200), RGB(255));
  CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 1000, RGBa(0,25,255,100));
return(1); 
 }


         