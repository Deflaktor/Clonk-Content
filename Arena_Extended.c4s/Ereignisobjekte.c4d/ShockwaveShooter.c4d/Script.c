#strict


Initialize:
SetAction("LittleBlast");
if(!Random(4))
  Local(0) = TSFT;
else
  Local(0) = SHFT;
return(1);

Action:
//CastObjects(FF3V,1,30);
//CastObjects(SHFT,1,50);
//if (Not(Random(3))) 
//for (var i = 0; i < 48; i+=36)
Exit(CreateContents(Local(0)),0,0,0,Sin(Local(3),8),Cos(Local(3),8));
SetLocal(3,Sum(Local(3),12));
if (GreaterThan(Local(3),720))
return(Remove());
return(1);

Remove:
  Explode(50);
  RemoveObject();
  return(1);
