//von major}

#strict

public Activate:
 Sound("Treedown");
   while( SetVar(0,FindObject(0,-300,-300,600,600,OCF_Chop(),0,0,NoContainer(),Var())))
         chp(Var());

 
return(RemoveObject());

private func chp(target)
{
  if(!ObjectCall(target,"IsStanding"))
	return();
  ObjectCall(target,"ChopDown");
  CastParticles("MSpark", 50,150, GetX(target)-GetX(),GetY(target)-GetY(), 20, 50, RGB(255), RGB(255));
  CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-25, 1000, RGBa(50,255,250,100));
 return(1); 
 }


         