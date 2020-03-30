#strict

local ziel,newziel;

public Activate:

SetVar(1,Par());
if(Par(1))
  SetVar(1,Par(1));


while(SetVar(0,FindObject(0,0,0,-1,-1,OCF_CrewMember(),"Dead",0,NoContainer(),Var())))
       if(!Hostileto(GetOwner(Var()),GetOwner(Var(1))))
		if(ObjectDistance(Var(),Var(1))<300)
	         	return(Leben(Var()));

Sound("Error");	
PlayerMessage(GetOwner(Var(1)),"Kein Ziel in Reichweite!",Var(1));
DoMagicEnergy(GetValue(),Var(1));
RemoveObject();
return();


private func Leben(target){
  ziel=target;
  
   Sound("Magic1");
  SetAction("wait"); 
  return(1);}

private func los()
{
var newziel;
newziel=CreateObject(GetID(ziel),0,0,GetOwner(ziel));
ObjectSetAction(newziel,"KneelUp");
MakeCrewMember (newziel,GetOwner(ziel)); 
GrabObjectInfo (ziel,newziel); 
RedefineFromObj(ziel);
RemoveObject(ziel);
newziel->Redefine2();
RemoveObject();
}

private func anim()
{
SetPositionAt(ziel);
//CastParticles("MSpark", 10,100, 0,0, 100, 200, RGBa(200,0,0,0), RGBa(0,255,0,100));
CastParticles("MSpark", 10,100, 0,0, 100, 200, RGBa(0,0,255,100), RGBa(255,255,255,200));
//CastParticles("MSpark", 10,300, 0,0, 100, 200, RGBa(200,200,255,0), RGBa(255,255,255,27));
}


global func SetPositionAt(target,pobj)
{
return(SetPosition(GetX(target),GetY(target),pobj));
}


//geaendertes script von clonk

private func RedefineObjPhysical(szPhys,pobj)
  {
  // Physical-Werte ermitteln
  var physTo   = GetCurrentPhysical(szPhys,2,0,pobj);
  SetPhysical(szPhys,physTo, 2,newziel);
  // Fertig
  return(1);
  }

private func RedefineFromObj(obj)
  {
  // Physicals anpassen
  RedefineObjPhysical("Energy", obj);
  RedefineObjPhysical("Breath", obj);
  RedefineObjPhysical("Walk", obj);
  RedefineObjPhysical("Jump", obj);
  RedefineObjPhysical("Scale", obj);
  RedefineObjPhysical("Hangle", obj);
  RedefineObjPhysical("Dig", obj);
  RedefineObjPhysical("Swim", obj);
  RedefineObjPhysical("Throw", obj);
  RedefineObjPhysical("Push", obj);
  RedefineObjPhysical("Fight", obj);
  RedefineObjPhysical("Magic", obj);
  RedefineObjPhysical("Float", obj);
  if (GetRank()<4) RedefineObjPhysical("CanScale", obj);
  if (GetRank()<6) RedefineObjPhysical("CanHangle", obj);
  RedefineObjPhysical("CanDig", obj);
  RedefineObjPhysical("CanConstruct", obj);
  RedefineObjPhysical("CanChop", obj);
  RedefineObjPhysical("CanSwimDig", obj);
  RedefineObjPhysical("CorrosionResist", obj);
  RedefineObjPhysical("BreatheWater", obj);
 
  // Fertig
  return(1);
  }