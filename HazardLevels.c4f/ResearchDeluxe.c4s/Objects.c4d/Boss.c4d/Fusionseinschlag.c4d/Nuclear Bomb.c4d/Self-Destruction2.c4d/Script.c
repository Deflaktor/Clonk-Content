#strict

Initialize:
  MusicLevel(50);
  SoundLevel("Selfdestruct",50);
  SetLocal(0,60000);
  SetAction("Destructing");
  SetPosition();
  return(1);

Destruction:
  if(Local(0) == 0) return(SetAction("Nothing"));
  var x;
  var y;

  Local(0)--;
  x=RandomX(10,LandscapeWidth()-10-GetX());
  y=RandomX(50,LandscapeHeight()-10-GetY());
  SetVar(0,x);
  SetVar(1,y);

  if(GetMaterial(x,y) != Material("Sky")  && GetMaterial(x,y) != Material("Earth")) 
  if(Distance( Var() , Var(1) , GetX(GetHiRank(Local(1))) , GetY(GetHiRank(Local(1))) )<1100) { 
    Explode(20+Random(20),CreateObject(_WP4,x,y));
    CastPXS("Earth",100,100,x,y);
  }

  Local(1)++;
  if(Local(1)>GetPlayerCount()-1)
    Local(1)=0;

return(1);


Remove:
  SoundLevel("Selfdestruct",0);
  return(RemoveObject());