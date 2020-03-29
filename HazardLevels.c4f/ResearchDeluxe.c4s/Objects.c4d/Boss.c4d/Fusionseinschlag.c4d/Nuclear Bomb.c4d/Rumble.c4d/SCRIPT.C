#strict

local target,time,strength,angle;

global func Rumble(x,y,wdt,hgt,tim,str) { //strength=0 für standardrumble
  var obj,i;
  while(obj=FindObject(0,x,y,wdt,hgt,OCF_CrewMember(),0,0,0,obj)) { i=1;
    if(!RumbleTarget(obj))
      CreateObject(_RMB,GetX(obj),GetY(obj),GetOwner(obj))->_RMB::StartRumbling(obj,tim,str);
    else RumbleTarget(obj)->_RMB::NewRumbling(tim,str);
    }
  return(i==1);
}

global func RumbleObject(obj,tim,str) { //strength=0 für standardrumble
  if(!obj || !(GetOCF(obj)&OCF_CrewMember())) return();
  if(!RumbleTarget(obj))
    CreateObject(_RMB,GetX(obj),GetY(obj),GetOwner(obj))->_RMB::StartRumbling(obj,tim,str);
  else RumbleTarget(obj)->_RMB::NewRumbling(tim,str);
  return(1);
}

global func RumbleTarget(obj) {
  var rumble;
  while(rumble=FindObject(_RMB,0,0,0,0,0,0,0,0,rumble))
    if(LocalN("target",rumble)==obj) return(rumble);}

func StartRumbling(obj,tim,str) {
	if(!str) strength=63;
	target=obj;
	time=tim;
	strength=str;
	SetPlrViewRange(1);
  	SetAction("Rumble");
}

func NewRumbling(tim,str) {
	if(!str) strength=63;
	time=tim;
	strength=str;
  	SetAction("Idle");
  	SetAction("Rumble");
}

//Timer
func Rumbling() {
  if(GetActTime()<2) return();
  if(GetActTime()>time) return(Remove());
  if(!target) return(Remove());
  angle=(angle+RandomX(90,180))%360; 
  var ldt=LandscapeWidth();
  var lgt=LandscapeHeight();
  SetPosition(
	BoundBy( BoundBy(GetX(target),
			BoundBy(strength,400,ldt/2),
			BoundBy(ldt-strength,ldt/2,ldt-400))
			+Sin(angle,strength)
		,1,ldt-1),
	BoundBy( BoundBy(GetY(target),
			BoundBy(strength,200,lgt/2),
			BoundBy(lgt-strength,lgt/2,lgt-200))
			+Cos(angle,-strength)
		,1,lgt-1));

  if(GetCursor(GetOwner())==target) SetPlrView(GetOwner(),this());
}

func Remove() {SetPlrView(GetOwner(),GetCursor(GetOwner())); RemoveObject();}

DestroyIt:
  return(1);
