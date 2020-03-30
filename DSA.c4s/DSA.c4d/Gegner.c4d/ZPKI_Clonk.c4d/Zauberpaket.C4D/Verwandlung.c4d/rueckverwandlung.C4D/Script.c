//Author wie immer Major aber das hier liest ja eh niemand also was solls}
#strict


Activate:

while(SetVar(0,FindObject(0,-500,-500,1000,1000,0,0,0,NoContainer(),Var())))
       if(Hostile(GetOwner(Var()),GetOwner(Par())))
          if(ObjectCall(Var(),"isVerwClonk"))
             rs(Var());
 
return();


private func rs(target)
{
ObjectCall(target,"rechange");
CastParticles("MSpark", 45,55, GetX(target)-GetX(),GetY(target)-GetY(), 28, 35, RGB(100), RGB(255));
CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 1000, RGBa(10,50,255,100));

}