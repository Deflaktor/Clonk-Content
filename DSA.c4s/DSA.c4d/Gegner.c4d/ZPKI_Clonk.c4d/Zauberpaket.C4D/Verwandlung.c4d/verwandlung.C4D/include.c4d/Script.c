#strict
rechange:
CastObjects(SPRK,3,10,0,-3);
ChangeDef(Local(11));
SetOwner(GetOwner());
SetPosition(GetX(),GetY()-2);
PrivateCall(this(),"Initialize");
return(1);

isVerwClonk:
return(1);