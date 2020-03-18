
#strict

local died;
local killedBy;

GetValue:
  return(5);

SetMyColor:
  if(GetOwner()==-1)
    SetRandomColor();
  return(1);

CheckColorFree:
  for (var i,j=GetPlayerCount(); j; ++i)
    if (GetPlayerName(i)) {
      var pCursor = GetCrew(i);
      if (pCursor) 
        if(GetColorDw(pCursor)==GetColorDw())
          return(0);
      --j;
    }
  return(1);

SetRandomColor:
  var rnd;
  for(var i=0;i<100;i++) {
    rnd = Random(12);
    SetColor(rnd);
    if(CheckColorFree())
      return(1);
  }
  return(1);

Destroy:
  if(GetAction() S= "Dead") return(0);
  if(Par(0) == GetOwner()) return(0);
  SetWealth(Par(0),GetWealth(Par(0))+GetValue());
  while(SetVar(1,FindObject(SDCL,0,0,0,0,0,0,0,0,Var(1))))
    if(GetOwner(Var(1))==Par(0)) {
      SetLocal(0,Local(0,Var(1))+1,Var(1));
      SetLocal(1,Var(1));
    }
  return(0);

public Damaged:
 // Log(Format("Dead %d, by %d (alread died = %d)",GetEnergy(), Par(1),died));
  if(died) return(0);
  if(GetEnergy()-Par(0)<=0) {
    died = 1;
    if(Par(1) != GetOwner()) {
      killedBy = Par(1);
      died = 2;
      SetVar(1,FindObjectOwner(SDCL,Par(1)));
      if(Var(1))
        SetLocal(0,Local(0,Var(1))+1,Var(1));
    }
	Kill();
	return(1);
  }
  DoEnergy(-Par(0));
  return(0);

public Damage:
  //Log("Not Dead");
  if(GetAction() S= "Dead") return(Damaged(Par(0), Par(1)));
  //Bluten(Par(0));
  return(0);

public CatchBlow:
  if (SEqual(GetAction(),"Dead")) return(0);
  Bluten(Par(0));
  return(0);

Bluten:
  SetVar(0,Max(Par(0),8));
  CastObjectsX(BLUT, Var(0)/4, Var(0)/2,0,0,0,0,"ResizeBlut");
  Var(1) = Angle(0,0,GetXDir(),GetYDir());
  CastObjectsX(BLUT, Var(0)/4, Var(0)/2,0,0,Var(1),45,"ResizeBlut");
  return(1);
  
ResizeBlut:
  return(DoCon(GetCon()-100,Par(0)));