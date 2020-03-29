
#strict

Launch:
//  SetClrModulation(RGBa(255,255,255,80));

  DoCon(Par(0)*100/20-100);

  SetPosition(GetX(),GetY()+32*GetCon()/100);

  ObjectSetAction(SetVar(0,CreateObject(_FX3)),"Justify",this());
  ObjectCall(Var(0),"Resize",GetCon());

  SetLocal(0,Par(0));

  BlastObjects(GetX(),GetY(),Local(0));

Local(1)=2;

var i;
for(i=0;i<2;i++)
{  

  if(Equal(GetMaterial(Local(1)),Material("Earth"))) 
    CastPXS("Earth",10*GetCon()/10,10*GetCon()/15); 
  if(Equal(GetMaterial(Local(1)),Material("Earth"))) 
    break;
  if(Equal(GetMaterial(Local(1)),Material("Sand")))  
    CastPXS("Sand",10*GetCon()/10,10*GetCon()/15);
  if(Equal(GetMaterial(Local(1)),Material("Sand")))  
    break;
  if(Equal(GetMaterial(Local(1)),Material("FlySand")))  
    CastPXS("FlySand",10*GetCon()/10,10*GetCon()/15);
  if(Equal(GetMaterial(Local(1)),Material("FlySand")))  
    break;  
  if(Equal(GetMaterial(Local(1)),Material("Snow"))) 
    CastPXS("Snow",10*GetCon()/10,10*GetCon()/15);
  if(Equal(GetMaterial(Local(1)),Material("Snow"))) 
    break;
  if(Equal(GetMaterial(Local(1)),Material("Ice")))  
    CastPXS("Ice",10*GetCon()/10,10*GetCon()/15);
  if(Equal(GetMaterial(Local(1)),Material("Ice")))  
    break;
  if(Equal(GetMaterial(Local(1)),Material("Coal"))) 
    CastPXS("Coal",10*GetCon()/10,10*GetCon()/15);
  if(Equal(GetMaterial(Local(1)),Material("Coal"))) 
    break; 
  if(Equal(GetMaterial(Local(1)),Material("Sulphur")))  
    CastPXS("Sulphur",10*GetCon()/10,10*GetCon()/15);
  if(Equal(GetMaterial(Local(1)),Material("Sulphur")))  
    break;
  if(Equal(GetMaterial(Local(1)),Material("Ashes"))) 
    CastPXS("Ashes",10*GetCon()/10,10*GetCon()/15);
  if(Equal(GetMaterial(Local(1)),Material("Ashes"))) 
    break;
  if(Equal(GetMaterial(Local(1)),Material("FlyAshes"))) 
    CastPXS("FlyAshes",10*GetCon()/10,10*GetCon()/15);
  if(Equal(GetMaterial(Local(1)),Material("FlyAshes"))) 
    break; 

Local(1)=-1;
}

  DigFree(GetX(),GetY(),Local(0));
  Sound(Format("Blast%d",BoundBy((Local(0)/10)-1,1,3)));

  return(1);
Initialize:
  SetAction("Blast");
  SetLocal(0,64);
  return(1); 
Remove:
  RemoveObject();
  return(1);