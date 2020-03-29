#strict

Initialize:
  MusicLevel(50);
  SoundLevel("Selfdestruct",50);
  SetLocal(0,60000);
  SetAction("Destructing");
  //SetPosition();
  return(1);

Destruction:
  if(Local(0) == 0) return(SetAction("Nothing"));
  var x;
  var y;

  Local(0)--;

  x=RandomX(10,LandscapeWidth()-10/*-GetX()*/);
  y=RandomX(50,LandscapeHeight()-10/*-GetY()*/);

  if(GetMaterial(x,y) != Material("Sky") && GetMaterial(x,y) != Material("Earth")) { 
    Explode(20+Random(20),CreateObject(WOOD,x,y));
   // CastPXS("Earth",100,100,x,y);
  }

  return(1);


Remove:
  SoundLevel("Selfdestruct",0);
  return(RemoveObject());