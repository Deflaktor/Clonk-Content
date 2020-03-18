#strict
#include PRNT

Check:
  SetAction("Delay");
  return(1);

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);

Hit:
  Sound("RockHit*");
  Explode(15,CreateObject(PRNT,0,1));
  if(LessThan(GetXDir(this()),1)) SetXDir(Sub(GetXDir(this()),Random(5)));
  if(GreaterThan(GetXDir(this()),0)) SetXDir(Sum(GetXDir(this()),Random(5)));
  SetYDir(-40);
  if(Not(Random(3))) Explode(15);
  return(1);

//So wars vorher:
//  SetVar(0,Sub(Random(200),100));
//  SetVar(1,Sub(Random(200),100));
//  SetXDir(Var(0));
//  SetYDir(Var(1));

