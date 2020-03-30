//von major}

#strict

public Activate:
 Sound("Magic1");
 while( SetVar(0,FindObject(FRCA,-200,-200,400,400,0,0,0,NoContainer(),Var())))
         des(Var());

while( SetVar(0,FindObject(FBRG,-200,-200,400,400,0,0,0,NoContainer(),Var())))
         des(Var());

while( SetVar(0,FindObject(FRCS,-200,-200,400,400,0,0,0,NoContainer(),Var())))
         des(Var());

while( SetVar(0,FindObject(FRCW,-200,-200,400,400,0,0,0,NoContainer(),Var())))
         des(Var());

while(SetVar(0,FindObject(HZTR,-200,-200,400,400,0,0,0,NoContainer(),Var())))
         des(Var());

while( SetVar(0,FindObject(0,-200,-200,400,400,0,0,0,NoContainer(),Var())))
	if(GetCategory(Var())==131072)
         	dest(Var());


return(RemoveObject());

private func des(target)
{
  
  PrivateCall(target,"Destroy");
  CastParticles("MSpark", 50,50, GetX(target)-GetX(),GetY(target)-GetY(), 20, 50, RGB(25), RGB(255));
  CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 1000, RGBa(2,3,250,100));
  }

private func dest(target)
{
  PrivateCall(target,"rem");
  RemoveObject(target);
  CastParticles("MSpark", 50,50, GetX(target)-GetX(),GetY(target)-GetY(), 20, 50, RGB(25), RGB(255));
  CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 1000, RGBa(2,3,250,100));
  }


         