#strict

local dir, obj1, obj2, hasObj1, hasObj2, oneLost, speed, target1, target2;
func Movement() {
    // Reset one lost variable
	if(!obj1&&!obj2)
	  oneLost=0;
	// Find Contents  
    if(Contents()) {
	  if(!obj1) {
	    obj1=Contents();
		hasObj1=1;
		Exit(obj1);
	  }
	}
    if(Contents()) {
	  if(!obj2) {
	    obj2=Contents();
		hasObj2=1;
		Exit(obj2);
	  }
	}
	// Cant carry more than two objects
	while(Var(0)=Contents()) Exit(Var(0));
	// Move
	var x,y;
	if(dir==1) {
	  x=-speed;
      y=+speed;	  
	}
	if(dir==2)
	  y=+speed;
	if(dir==3) {
	  x=+speed;
      y=+speed;
	} 
	if(dir==4)
	  x=-speed;
	if(dir==6)
	  x=+speed;
	if(dir==7) {
	  x=+speed;
      y=-speed;
	}
	if(dir==8)
	  y=-speed;
	if(dir==9) {
	  x=-speed;
      y=-speed;
	}
	SetPosition(GetX()+x,GetY()+y);
	// Lost object1?
    if(obj1&&Contained(obj1)||!obj1&&hasObj1) {
	  obj1=0;
	  hasObj1=0;
	  oneLost=1;
	  if(target1) target1->Trigger();
	}
	// Lost object2?
    if(obj2&&Contained(obj2)||!obj2&&hasObj2) {
	  obj2=0;
	  hasObj2=0;
	  oneLost=1;
	  if(target2) target2->Trigger();
	}
	// If two objects, place them apart from each other
	var stayApartDistance = 5;
	if(!oneLost&&((obj1&&!obj2)||(!obj1&&obj2)))
	  stayApartDistance = 0;
	// Place objects on top
    if(obj1) {
	  SetPosition(GetX()-stayApartDistance, GetY()-6,obj1);
	  SetXDir(x, obj1);
	  SetYDir(y, obj1);
	}
    if(obj2) {
	  SetPosition(GetX()+stayApartDistance, GetY()-6,obj2);
	  SetXDir(x, obj2);
	  SetYDir(y, obj2);
	}
}

Destruction:
  if(obj1)
    RemoveObject(obj1);
  if(obj2)
    RemoveObject(obj2);
  return(1);
  
SetTarget1:
  if(!ObjectCall(Par(0),"IsTriggerable")) return(Message("Target not triggerable",this()));
  target1 = Par(0);
  return(1);
  
SetTarget2:
  if(!ObjectCall(Par(0),"IsTriggerable")) return(Message("Target not triggerable",this()));
  target2 = Par(0);
  return(1);

SetTargets:
  SetTarget1(Par(0));
  SetTarget2(Par(1));
  return(1);
  
SetTarget1AndStart:
  SetTarget1(Par(0));
  Start(Par(1));
  return(1);
  
SetTarget2AndStart:
  SetTarget2(Par(0));
  Start(Par(1));
  return(1);
  
Start:
  obj1=0;
  obj2=0;
  dir=Par(0);
  speed=Par(1);
  oneLost=0;
  if(!dir)
    dir=6;
  if(!speed)
    speed=2;
  return(1);
