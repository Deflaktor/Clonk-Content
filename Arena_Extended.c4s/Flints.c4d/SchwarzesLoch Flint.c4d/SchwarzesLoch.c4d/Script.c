#strict

Initialize:
SetAction("Blast");
return(1);

CheckSog:
  if(GetMaterial(GetX(Par(0)),GetY(Par(0)))==Material("Earth"))
    return(1);
  //if (BitAnd(OCF_CrewMember(),GetOCF(Par(0))))
  Jump(Par(0));
  SetVar(1,Sub(GetX(),GetX(Par(0))));
  SetVar(2,Sub(GetY(),GetY(Par(0))));
  SetSpeed(Div(Var(1),2),Div(Var(2),2)-5,Par(0));
  return(1);

Activity:
  Local(3)++;
  if(Local(3)>=70)
    return(Remove());

  DigFree(GetX(),GetY(),1*GetCon());
  
  while(SetVar(0,FindObject(0,-1*GetCon(),-1*GetCon(),2*GetCon(),2*GetCon(),0,0,0,NoContainer(),Var(0))))
    CheckSog(Var(0));

  while (SetVar(1,FindObject(0,-25,-30,50,60,0,0,0,0,Var(1))))
    if (Not(Equal(Var(1),this()))) {
      if (GetID(Var(1))==GetID()||GetID(Var(1))==SLGR) {
        //CastParticles("FSpark", Random(40),100, 0,0, (Random(40)+2000), 150, RGBa(255,255,0,0), RGBa(255,127,0,255));
        Sound("Energize");

        if(GetID(Var(1))==GetID())
          Local(3)=Min(Local(3), Local(3,Var(1)));
        else
          Local(3)=Max(0, Local(3)-20);

        if(GetCon()<301) {
          if(GetID(Var(1))==SLGR)
            DoCon( Min(50, 300-GetCon() ));
          else
            DoCon( Min(GetCon(Var(1)), 300-GetCon() ));

      }

      RemoveObject(Var(1));

      SetXDir();
      SetYDir();
      return(1);
    }

    if (GetCategory(Var(1))==1||GetID(Var(1))==BNMR||GetID(Var(1))==GKKE||GetID(Var(1))==_RBL||GetID(Var(1))==SURR||GetID(Var(1))==BLOW||GetID(Var(1))==_LIV)
      return(1);
  
    if(!ObjectCall(Var(1),"Destroy",GetOwner())) {
      Sound("Saug");
      CreateParticle("PxSpark",0,6,0,0,150,RGBa(100,100,180,100));
      RemoveObject(Var(1));
    }
  }
  return(1);

Remove:
  ObjectCall(CreateObject(SW3V,0,0,GetOwner()),"Init",GetCon());
  return(RemoveObject());