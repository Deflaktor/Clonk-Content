//Locals  0Owner   1KI   2Counter
#strict

local angle1, angle2;

Initialize:
Start();
return(1);

	Start:
ObjectCall(CreateObject(FXPW,1,1),"Activate",this());
SetLocal(0,0);
SetLocal(1,175);
ObjectCall(CreateObject(EXPL),"Launch",60);
Sound("RDHit");
SetAction("Los");
return(1);

	Remove:  //fette Explosion am schluss
while(LessThan(Local(2),10)) FinalEXPL();
return(RemoveObject());

	FinalEXPL:
ObjectCall(CreateObject(EXPL,Random(160)-80, Random(150)-25),"Launch",60);
SetLocal(2,Sum(Local(2),1));
return(1);


	Explosion:  //Explosionen in der mitte der Explosionskette
// Wird 35 mal aufgerufen
/*var x, y;
angle1+=15;
Local(0)+=15;
Local(1)-=15;
if(Local(0)>=175) {
  var temp=Local(0);
  Local(0)=Local(1);
  Local(1)=temp;
}
for(var i=-90;i<=180;i+=90) {
  x = Sin(angle1+i, Local(0));
  y = -Cos(angle1+i, Local(0));
  ObjectCall(CreateObject(EXPL,x,y),"Launch",40);
}
for(var i=-90;i<=180;i+=90) {
  x = Sin(angle1+i, Local(1));
  y = -Cos(angle1+i, Local(1));
  ObjectCall(CreateObject(EXPL,x,y),"Launch",40);
}
for(var i=-90;i<=180;i+=90) {
  x = Sin(angle1+i, Local(0));
  y = -Cos(angle1+i, Local(1));
  ObjectCall(CreateObject(EXPL,x,y),"Launch",40);
}
for(var i=-90;i<=180;i+=90) {
  x = Sin(angle1+i, Local(1));
  y = -Cos(angle1+i, Local(0));
  ObjectCall(CreateObject(EXPL,x,y),"Launch",40);
}*/
ObjectCall(CreateObject(EXPL,Random(60)-30, Random(60)-30),"Launch",40);
ObjectCall(CreateObject(EXPL,Random(120)-60, Random(200)-100),"Launch",40);
ObjectCall(CreateObject(EXPL,Random(180)-90, Random(300)-200),"Launch",40);
ObjectCall(CreateObject(EXPL,Random(240)-120, Random(120)-60),"Launch",40);
ObjectCall(CreateObject(EXPL,Random(300)-150, Random(300)-200),"Launch",40);

  while(SetVar(0,FindObject(0,-400,-400,800,800,OCF_CrewMember(),0,0,NoContainer(),Var(0))))
  if(GetOwner(Var(0))==-1||GetOwner(Var(0))==GetOwner()||Hostile(GetOwner(),GetOwner(Var(0))))
  if(PathFree(GetX(),GetY(),GetX(Var(0)),GetY(Var(0))))
  FlyHim(300,Var(0));
return(1);

FlyHim:
  Fling( Par(1),
         Div( Sub(GetX(Par(1)),GetX(this())) , Div(Par(0),7) ),
         Div( Sub(GetY(Par(1)),GetY(this())) , Div(Par(0),7) )
        );
DoEnergy(-5,Par(1));
return(1);

/*
BlastHim:
var obj;
    obj = 0;
    while(obj = FindObject(0,0,0,-1,-1,OCF_Inflammable(),0,0,NoContainer(),obj))
      if((x = ObjectDistance(this(),obj))<=800)
        if(PathFree(GetX(),GetY(),GetX(obj),GetY(obj))||GetCon(obj)<=40)
          if(GetY(obj)<=GetY(this())+280)
            if(!OnFire(obj))
              BlastObjects(GetX(obj),GetY(obj),x/4);
return(1);*/