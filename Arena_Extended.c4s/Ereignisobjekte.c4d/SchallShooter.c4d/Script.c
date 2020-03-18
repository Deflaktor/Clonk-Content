#strict

Initialize:
  SetOwner(-1);
  SetAction("LittleBlast");
  return(1);

Action:
//CastObjects(FF3V,1,30);
//CastObjects(SHFT,1,50);
//if (Not(Random(3))) 
Exit(CreateContents(_SFN),0,0,0,Sin(Local(3),8),Cos(Local(3),8));
SetLocal(3,Sum(Local(3),12));
if (GreaterThan(Local(3),1440))
SetAction("LittleBlast2");
return(1);

Action2:
CastObjects(_SFN,5,100);
SetLocal(4,Sum(Local(4),1));
if (GreaterThan(Local(4),40))
return(Remove());
return(1);


Remove:
  CastObjects(_SFN,100,1000);
  Explode(50);
  RemoveObject();
  return(1);
