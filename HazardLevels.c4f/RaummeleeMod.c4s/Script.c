
#strict

HostileAnimals:
  return(1);

RemoveBodies:
  while(Var(0)=FindObject(_GTT))
    RemoveObject(Var(0));
  return(1);
  
Initialize:
  Global(0)=2;
  CreateObject(_TP1,600,3354);
  CreateObject(_TP2,666,1930);
  CreateObject(_RDR,782,3391);
  CreateObject(_RDR,1184,3391);
  CreateObject(_WEL,600,3200);
  CreateObject(_GER,221,860);
  CreateObject(_GER,1315,3228);
  CreateObject(_GER,1555,1438);
  CreateObject(_VEN,1354,3194);
  CreateObject(_SHZ,1238,3347);
  CreateObject(_SHZ,1476,3347);
  CreateObject(_WEL,982,3383);
  CreateObject(_ANT,701,1933);
  CreateObject(_SCM,1359,3259);
  CreateObject(_CRT,476,3371);
  CreateObject(_CRT,708,3371);
  CreateObject(_LCK,825,3390);
  CreateObject(_LCK,1125,3390);
  CreateObject(_DK8,540,1830);
  CreateObject(_DK9,870,1830);
  CreateObject(_LOC,542,1887);
  CreateObject(_LOC,810,1887);
  CreateObject(_LOC,573,3362);
  CreateObject(_LOC,1328,3336);
  CreateObject(_HGG,562,1943);
  CreateObject(_HGG,721,1943);
  CreateObject(_HGG,880,1943);

   //RelaunchBot();
   ScriptGo(1);
return(1);

Script5:
  RemoveObject(FindObject(_REV,0,0,0,0,0,0,0,NoContainer()));
  RemoveObject(FindObject(_GTT));
  return(goto(1));

DestructableLandscape:
  return(1);

DeployPlayer:
  while(true) {
    var x,y;
	x = 20 + Random(LandscapeWidth()-20);
	y = 20 + Random(LandscapeHeight()/2-20);
	if(!GBackSolid(x,y)) {
	  SetPosition(x, y, GetCrew(Par(0)));
	  break;
	}
  }
  return(1);
  
  
RelaunchBot:
  Var(0)=CreateObject(HK00,50,-50,-1);
  while(true) {
    var x,y;
	x = 20 + Random(LandscapeWidth()-20);
	y = 20 + Random(LandscapeHeight()/2-20);
	if(GetMaterial(x,y)==Material("Wall")) {
	  SetPosition(x, y, Var(0));
	  break;
	}
  }
  return(1);
  
  
MainEnergySupply:
  return(1);

