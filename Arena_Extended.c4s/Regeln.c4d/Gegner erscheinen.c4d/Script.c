#strict

protected Initialize:
  SetAction("Initialize");
  // Position
  SetPosition();
  return(1);

Initialized:
  // Plazierungsfaktor ermitteln
  Local(0)=ObjectCount(GetID())+1;
  // Andere Objekte des gleichen Typs entfernen
  while(Var(1)=FindObject(GetID()))
    RemoveObject(Var(1));
  // Steuerungsaktion
  SetAction("Active");
  return(1);

DoFlints:
  if(Local(1)>150) {
    SetPosition(Random(LandscapeWidth()),0,CreateObject(KIL1));
    if(GetGodX()&&ObjectCount(KIL1)<2*(1+1*Local(0)/10))
      SetPosition(GetGodX(),0,CreateObject(KIL1));
    SetLocal(1);
  }
  if(Local(2)>200) {
    SetPosition(Random(LandscapeWidth()),0,CreateObject(KIK1));
    if(GetGodX()&&ObjectCount(KIK1)<2*(1+1*Local(0)/10))
      SetPosition(GetGodX(),0,CreateObject(KIK1));
    SetLocal(2);
  }
  
  if(Local(3)>300) {
    SetPosition(Random(LandscapeWidth()),0,CreateObject(DIL1));
    if(GetGodX()&&ObjectCount(DIL1)<2*(1+1*Local(0)/10))
      SetPosition(GetGodX(),0,CreateObject(DIL1));
    SetLocal(3);
  }
  
  if(Local(4)>800) {
    SetPosition(Random(LandscapeWidth()),0,CreateObject(KIL3));
    if(GetGodX()&&ObjectCount(KIL3)<2*(1+1*Local(0)/10))
      SetPosition(GetGodX(),0,CreateObject(KIL3));
    SetLocal(4);
  }
  
  if(Local(5)>6000) {
    SetPosition(Random(LandscapeWidth()),0,CreateObject(KIL4));
    SetLocal(5);
  }
   
  if(LessThan(ObjectCount(KIL1),1+1*Local(0)/10)) SetLocal(1,Local(1)+1*Local(0));
  if(LessThan(ObjectCount(KIK1),1+1*Local(0)/10)) SetLocal(2,Local(2)+1*Local(0));
  if(LessThan(ObjectCount(DIL1),1+1*Local(0)/10)) SetLocal(3,Local(3)+1*Local(0));
  if(LessThan(ObjectCount(KIL3),1+1*Local(0)/10)) SetLocal(4,Local(4)+1*Local(0));
  if(LessThan(ObjectCount(KIL4),1+1*Local(0)/10)) SetLocal(5,Local(5)+1*Local(0));
  return(1);
  
GetGodX:
  if(Var(0)=FindObject(MNTK)) {
    if(!Var(0)->GetNoRespawn()) {
      if(Var(0)=Var(0)->GetCurrentGod()) {
        return(GetX(Var(0)));
      }
    }
  }
  return(0);
