#strict
#include _POV

public func Dmg() {
  return(1);
}

/* Wird abgefeuert, Par(0) ist Schußrichtung */
public func Launch(int dir) {
  SetCon(10);
  if (dir == DIR_Left()) SetLocal(0,-250);
  if (dir == DIR_Right()) SetLocal(0,+250);
  SetAction("Travel");
  return(1);
}

/* Fliegt */
Travel:
  // Treffer-Überprüfung
  if(GetActTime()>1)
    while(SetVar(0,FindObject(0, -30,-30,60,70,0,0,0,NoContainer(),Var(0)))) Repel(Var(0));
  //if(CheckHit(-20,-20,40,40))
  //  return(Hit());
  // Bewegung
  SetXDir(Local(0));
  SetYDir(Local(1));
  
  //if(GetCon()>60) {
    var alpha = BoundBy((GetCon()-60)*8,150,255);
    SetClrModulation(RGBa(255,255,255,alpha));
  //} //else {
  var c = 20+Random(41);
  CreateParticle("PxSpark",0,-20*GetCon()/100, Local(0)/10, -10, c, RGBa(125, Random(100), 0, 100));
  CreateParticle("PxSpark",0,20*GetCon()/100, Local(0)/10, -10, c, RGBa(125, Random(100), 0, 100));
    //CreateObject(CKFL,0,-20*GetCon()/100);
	//CreateObject(CKFL,0,20*GetCon()/100);
  //}
  
  if(GetCon()<100) {
    DoCon(10);
  } else {
    RemoveObject();
  }
  return(1);
  
/* Treffer */
Hit:
  Sound("Thump1");
  while(SetVar(0,FindObject(0,-40,-40,80,80,OCF_Alive(),0,0,NoContainer(),Var(0)))) SonicHit(Var(0));
  RemoveObject();
  return(1);
  
SonicHit:
  DoEnergy(-Dmg()*5,Par(0));
  Fling(Par(0),Random(4)-2,-4-Random(10));
  return(1); 
    
Repel:
  if( GetOwner(Par(0))==GetOwner(Contained(GetActionTarget()))&&Contained(GetActionTarget()) )
    return(1);
  if(Par(0)==GetActionTarget())
    return(1);
  if(GetMass(Par(0))>=200)
    return(1);
  if(!(GetCategory(Par(0)) & C4D_Object()||GetCategory(Par(0)) & C4D_Living()))
    return(1);
  if(GetID(Par(0))==_HGG||GetID(Par(0))==_HG2)
    return(1);
  SetVar(1,Sub(GetX(),GetX(Par(0)))-Local(0)/4);
  SetVar(2,Sub(GetY(),GetY(Par(0)))+20);
 // if(GetID(Par(0))!=ST5B)
    DoEnergy(-Dmg(),Par(0));
  Fling(Par(0),0,-10);
  SetSpeed(-Var(1)*2+Random(2)-4,-Var(2)*2-10+Random(2)-4,Par(0));
  if(SEqual(GetAction(Par(0)),"Travel")) {
    SetLocal(0,-Var(1)*2,Par(0));
    SetLocal(1,-Var(2)*2,Par(0));
    if (Local(0,Par(0))<0) SetDir(DIR_Left(),Par(0));
    else SetDir(DIR_Right(),Par(0));
  }
  if(ObjectCall(Par(0),"IsProjectile"))
    SetOwner(GetOwner(Contained(GetActionTarget())),Par(0));
  return(1);