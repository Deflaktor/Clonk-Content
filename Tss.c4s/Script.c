#strict

static debugmode, catastrophies, players;

Initialize:
  SetWind(100);
  MusicLevel(40);
  ScriptGo(1);

  var hardmode = false;
  if(FindObject(MGPL))
    hardmode = true;

  if(hardmode) {
    if (!GetProductionOk()) {
      Message("Super Hard Modus kann nicht gespielt werden,|wenn mehr als 5 Flints und mehr als 5 Baumsamen nachgeliefert werden.|Außerdem dürfen nur folgende Objekte nachgeliefert werden:|Flagge, Bausatz, Leitungsbausatz, Lehm, Beton, Flüssiggranit, Stein, Gold, Clonks, Brücke.|Super Hard Modus wird deaktiviert.");
      RemoveObject(FindObject(MGPL));
      hardmode = false;
    }
  }
  if(hardmode) {
    var obj;
    while(obj=FindObject(FLNT)) RemoveObject(obj);
    while(obj=FindObject(LOAM)) RemoveObject(obj);
    while(obj=FindObject(FMEG)) RemoveObject(obj);
    while(obj=FindObject(MEGG)) RemoveObject(obj);
    while(obj=FindObject(ZAPN)) RemoveObject(obj);
    if(!FindObject(TACC)) CreateObject(TACC,0,0,-1);
    if(!FindObject(TKNW)) CreateObject(TKNW,0,0,-1);
	if(!FindObject(HBM_)) CreateObject(HBM_,0,0,-1);
	if(!FindObject(_TAC)) CreateObject(_TAC,0,0,-1);
  }
  return(1);

ProductionNotOk:
  if(!Par(1))
    return(0);
 // Log(Format("%i=%d",Par(0),Par(1)));
  var l = ProductionID(-1);
  for (var i = 0; i < l; i++) {
    if(Par(0) == ProductionID(i))
      if(Par(1) > ProductionCount(i))
        return(1);
  }
  return(0);
  
GetProductionOk:
  var i=100*2;
  while(i-=2) {
    var id, count, j = 4;
    while(j) {
      count=GetScenarioVal("HomeBaseProduction", Format("Player%d",j), i+1);
      id=GetScenarioVal("HomeBaseProduction", Format("Player%d",j), i);
      if(ProductionNotOk(id,count))
        return(0);
      j--;
    }
  }  
  return(1);
  
SetupHomeBaseMaterial:
  var iPlr = Par(0);
  var i, id = 1;
  while(id) {
    var count;
	id = GetHomebaseMaterial(iPlr,0,i,C4D_Vehicle()|C4D_Object()|C4D_Living());
	count = GetHomebaseMaterial(iPlr, id);
	if(id)
	  DoHomebaseMaterial(iPlr,id,-count);
	i++;
  }
  for(i=0;i<BuyID(-1);i++) {
    DoHomebaseMaterial(iPlr,BuyID(i),BuyCount(i));
  }
  return(1);

InitializePlayer:
  if(!FrameCounter())
    players++;
  else
    return(Laufzeitbeitritt(Par(0)));
	
  SetupHomeBaseMaterial(Par(0));
  var hardmode = false;
  if(FindObject(MGPL))
    hardmode = true;
  // Minimales Startkapital
  if(!hardmode)
    SetVar(1,GetWealth(Par(0)));
  if(!hardmode || players==1)
    SetWealth(Par(0),Var(1)*2+150);
  else if(hardmode && players>1)
    SetWealth(Par(0), 0);

  var obj, categories;
  while(obj=FindObjectOwner(0,Par(0),0,0,0,0,OCF_CrewMember(),0,0,obj)) 
    if(Contained(obj)) Contained(obj)->Exit(obj,0,GetDefBottom(Contained(obj))-GetY(Contained(obj)));
  obj=0;
  categories = C4D_Structure()|C4D_Vehicle()|C4D_Object();
  if(hardmode)
    while(obj=FindObjectOwner(0,Par(0),0,0,0,0,0,0,0,obj)) 
      if(GetCategory(obj)&categories)
        RemoveObject(obj);

  var x,y;
  if(GetHiRank(Par(0))) {
    x = GetX(GetHiRank(Par(0)));
    y = GetY(GetHiRank(Par(0)));
  } else {
    SetVar(3,PlaceAnimal(WIPF));
    x = GetX(Var(3));
    y = GetY(Var(3));
    RemoveObject(Var(3));
  }
  x = Max(50,Min(x, LandscapeWidth()-150));
  if(hardmode&&players>=2) {
    x=GetX(GetHiRank(0))-10+Random(20);
	y=GetY(GetHiRank(0))-10;
	for(var i=0;i<GetCrewCount(Par(0));i++)
	  SetPosition(x+Random(10-5),y,GetCrew(Par(0),i));
  }
  // Mindestens 4 Clonks
  if(players==1||!hardmode) {
    while (GetCrewCount(Par(0)) < 4) MakeCrewMember(CreateObject(CLNK,x,y,Par(0)),Par(0));
  } else if(players==2) {
    while (GetCrewCount(Par(0)) < 2) MakeCrewMember(CreateObject(CLNK,x,y,Par(0)),Par(0));
	
	var flag, tent, cont;
	flag = FindObjectOwner(FLAG, 0);
	Exit(flag);
	tent = FindObjectOwner(TENP, 0);
	Exit(tent);
	cont=Contents(0,GetNHiRank(0,0));
	Exit(cont);
	Enter(GetNHiRank(0,0), tent);
	if(!Contained(cont)) RemoveObject(cont);
	cont=Contents(0,GetNHiRank(0,1));
	Exit(cont);
	Enter(GetNHiRank(0,1), flag);
	if(!Contained(cont)) RemoveObject(cont);
	
	while (GetCrewCount(0) > 2) RemoveObject(GetNHiRank(0,GetCrewCount(0)-1));
	while (GetCrewCount(Par(0)) > 2) RemoveObject(GetNHiRank(Par(0),GetCrewCount(Par(0))-1));

	CreateObject(LOAM,0,0,-1)->Enter(GetCrew(Par(0),0));
	CreateObject(LOAM,0,0,-1)->Enter(GetCrew(Par(0),1));
	
  } else if(players==3) {
    while (GetCrewCount(Par(0)) < 1) MakeCrewMember(CreateObject(CLNK,x,y,Par(0)),Par(0));
	while (GetCrewCount(0) > 2) RemoveObject(GetNHiRank(0,GetCrewCount(0)-1));
	while (GetCrewCount(1) > 1) RemoveObject(GetNHiRank(1,GetCrewCount(1)-1));
	while (GetCrewCount(Par(0)) > 1) RemoveObject(GetNHiRank(Par(0),GetCrewCount(Par(0))-1));
	
	CreateObject(LOAM,0,0,-1)->Enter(GetCrew(Par(0),0));
  } else if(players==4) {
    while (GetCrewCount(Par(0)) < 1) MakeCrewMember(CreateObject(CLNK,x,y,Par(0)),Par(0));
	
	var flag, tent;
	flag = FindObjectOwner(FLAG, 0);
	Exit(flag);
	Enter(GetNHiRank(0,0),flag);
	
	tent = FindObjectOwner(TENP, 0);
	Exit(tent);
	SetOwner(Par(0), tent);
	
	while (GetCrewCount(0) > 1) RemoveObject(GetNHiRank(0,GetCrewCount(0)-1));
	while (GetCrewCount(1) > 1) RemoveObject(GetNHiRank(1,GetCrewCount(1)-1));
	while (GetCrewCount(2) > 1) RemoveObject(GetNHiRank(2,GetCrewCount(2)-1));
	while (GetCrewCount(Par(0)) > 1) RemoveObject(GetNHiRank(Par(0),GetCrewCount(Par(0))-1));
	
	Enter(GetNHiRank(Par(0),0), tent);
  } else {
    while (GetCrewCount(Par(0)) < 1) MakeCrewMember(CreateObject(CLNK,x,y,Par(0)),Par(0));
	while (GetCrewCount(Par(0)) > 1) RemoveObject(GetNHiRank(Par(0),GetCrewCount(Par(0))-1));
  }
  
  if(players==1 || !hardmode) {
    // Wenn kein Luftschiff da, muss es Windrad + Werkstatt mit Inhalt geben
    if(!FindObjectOwner(BLMP,Par(0))) {
      SetVar(3,0);
      // Windrad erzeugen
      if(!SetVar(1,FindObjectOwner(WMIL,Par(0)))) {
        SetVar(1,CreateConstruction(WMIL,x,y+10,Par(0),100,1,0));
        SetVar(3,1);
      }
      // Werkstatt erzeugen
      if(!SetVar(2,FindObjectOwner(WRKS,Par(0)))) {
        SetVar(2,CreateConstruction(WRKS,x+49,y+10,Par(0),100,1,0));
        SetVar(3,1);
      }
      // Stromversorgung
      if(Var(3))
        ObjectSetAction(CreateObject(PWRL,0,0,Par(0)), "Connect", Var(1), Var(2));
  
      // Sägemühle erzeugen
      if(!SetVar(4,FindObjectOwner(SAWM,Par(0)))) {
        SetVar(4,CreateConstruction(SAWM,x+49+72,y+10,Par(0),100,1,0));
        SetVar(3,1);
      }
      // Stromversorgung
      if(Var(3))
        ObjectSetAction(CreateObject(PWRL,0,0,Par(0)), "Connect", Var(1), Var(4));
  
      // Luftschiff muss herstellbar sein
      SetPlrKnowledge(Par(0),BLMP);
      // Komponente für Luftschiff
      for(var i=1;i<=6;i++) 
        CreateObject(METL,0,0,-1)->Enter(Var(2));
      for(var i=1;i<=8;i++)
        CreateObject(WOOD,0,0,-1)->Enter(Var(2));
    }
	
    // Kein Zeltpack? -> Erzeugen
    if(!FindObjectOwner(TENP,Par(0)))
      CreateObject(TENP,0,0,Par(0));
    Enter(GetNHiRank(Par(0),0),FindObjectOwner(TENP,Par(0)));
  
    // Keine Flagge? -> Erzeugen
    if(!FindObjectOwner(FLAG,Par(0)))
      CreateObject(FLAG,0,0,Par(0));
    Enter(GetNHiRank(Par(0),1),FindObjectOwner(FLAG,Par(0)));
    
    Var(2)=0;
    // Kein Lehm? -> Erzeugen
    if(SetVar(2,FindObjectOwner(LOAM,Par(0),0,0,0,0,0,0,0,Var(2)))) {
      Enter(GetNHiRank(Par(0), 2),Var(2));
      if(!SetVar(2,FindObjectOwner(LOAM,Par(0),0,0,0,0,0,0,0,Var(2)))) {
        SetVar(2,CreateObject(LOAM,0,0,-1));
      }
      Enter(GetNHiRank(Par(0), 3),Var(2));
    } else {
      SetVar(2,CreateObject(LOAM,0,0,-1));
      Enter(GetNHiRank(Par(0), 2),Var(2));
      if(!SetVar(2,FindObjectOwner(LOAM,Par(0),0,0,0,0,0,0,0,Var(2)))) {
        SetVar(2,CreateObject(LOAM,0,0,-1));
      }
      Enter(GetNHiRank(Par(0), 3),Var(2));
    }
  }
  
  // Alle Gebäude haben keinen Besitzer! 
  //   (Wir verlieren sonst Siedlungspunkte wenn sie draufgehen)
  SetVar(2,0);
  while (SetVar(2,FindObject(0,0,0,0,0,0,0,0,NoContainer(),Var(2))))
    if(!(GetCategory(Var(2))&C4D_Living()) && GetID(Var(2))!=FLAG && GetOwner()==Par(0))
      SetOwner(-1,Var(2));

  // Einfacher Start? Baue eine Hütte in der Luft!
  if(FindObject(_EYS)&&(players==1 || !hardmode))
    CreateObject(HUT2,x,100,Par(0));
  
  return(1);
  

Laufzeitbeitritt:
  var hardmode = false;
  if(FindObject(MGPL))
    hardmode = true;
	
  // Minimales Startkapital
  SetVar(0,FrameCounter()/100);
  if(Var(0)>150)
    SetVar(0,150);
  if(!hardmode)
    SetVar(1,GetWealth(Par(0)));
  SetWealth(Par(0),Var(1)*2+150-Var(0));

  if(FindObject(TACC))
    SetWealth(Par(0),0);
  
  var obj, categories;
  while(obj=FindObjectOwner(0,Par(0),0,0,0,0,OCF_CrewMember(),0,0,obj)) 
    if(Contained(obj)) Contained(obj)->Exit(obj,0,GetDefBottom(Contained(obj))-GetY(Contained(obj)));
  obj=0;
  categories = C4D_Structure()|C4D_Vehicle()|C4D_Object();
  if(hardmode)
    while(obj=FindObjectOwner(0,Par(0),0,0,0,0,0,0,0,obj)) 
      if(GetCategory(obj)&categories)
        RemoveObject(obj);
		
  if(hardmode)
    while (GetCrewCount(Par(0)) > 1) RemoveObject(GetNHiRank(Par(0),GetCrewCount(Par(0))-1));
  
  var x,y;
  for (var i,j=GetPlayerCount(); j; ++i)
    if (GetPlayerName(i)) {
	  if(i!=Par(0)) {
      var pCursor = GetHiRank(i);
      if (pCursor) {
	    x=GetX(pCursor);
		y=GetY(pCursor);
		break;
	  }
	  }
      --j;
  }
  if(x)
    SetPosition(x,y-10,GetHiRank(Par(0)));
  
  return(1);

GetNHiRank:
  var crew, i = Par(1);
  crew = GetHiRank(Par(0));
  while(i) {
    SetAlive(0, crew);
	crew = GetHiRank(Par(0));
	i--;
  }
  for(i=0;i<GetCrewCount(Par(0));i++)
    SetAlive(1, GetCrew(Par(0),i));
  return(crew);
  
DebugMode:
  var x, y, startx;
  startx=LandscapeWidth()/2;
  x=startx;
  y=300;
  x+=DebugCreate(WRKS,x,y,Par(0));
  x+=DebugCreate(FNDR,x,y,Par(0));
  x+=DebugCreate(SAWM,x,y,Par(0));
  x+=DebugCreate(HUT3,x,y,Par(0));
  x+=DebugCreate(WMIL,x,y,Par(0));
  x+=DebugCreate(ANVL,x,y,Par(0));
  x+=DebugCreate(RSRC,x,y,Par(0));
  x+=DebugCreate(CHEM,x,y,Par(0));
  var finalx = x;
  y-=25;
  DrawMaterialQuad("Earth-Flat", startx-50, y, finalx-50, y, finalx-50, y+3, startx-50, y+3);
  CreateObject(PWRL)->SetAction("Connect",FindObjectOwner(WMIL,Par(0)),FindObjectOwner(WRKS,Par(0)));
  CreateObject(PWRL)->SetAction("Connect",FindObjectOwner(WMIL,Par(0)),FindObjectOwner(SAWM,Par(0)));
  CreateObject(PWRL)->SetAction("Connect",FindObjectOwner(WMIL,Par(0)),FindObjectOwner(RSRC,Par(0)));
  CreateObject(PWRL)->SetAction("Connect",FindObjectOwner(WMIL,Par(0)),FindObjectOwner(CHEM,Par(0)));
  x=startx;
  y=150;
  while(x<finalx) {
    x+=DebugCreate(BRDM,x,y,Par(0));
  }
  return(1);

DebugCreate:
  var id = Par(0);
  var x = Par(1);
  var y = Par(2);
  var owner = Par(3);
  var width = GetDefWidth(id);
//  var height = GetDefHeight(id);
  var ox = GetDefOffset(id,0);
  var oy = GetDefOffset(id,1);
  CreateObject(id, x+ox, y+oy, owner);
  if(id==BRDM)
    CreateObject(_LNR, x+ox, y+oy-10, owner);
  debugmode = true;
  return(width);


Script400:
  var hardmode = false;
  if(FindObject(MGPL))
    hardmode = true;
  var repeat = 100*LandscapeWidth()/3750;

  // Falls ein Spieler eliminiert wird und es keine Flaggen mehr gibt
  var flag;
  if(hardmode) {
    var hasowner = false;
	var obj;
    while(obj=FindObject(FLAG,0,0,0,0,0,0,0,0,obj)) {
	  if(GetOwner(obj)!=-1) {
	    hasowner = true;
		break;
	  }
	}
	if(!hasowner) {
	  flag=FindObject(FLAG);
	  if(!flag)
	    flag=CreateObject(FLAG,0,0,-1);
	}
  }
  
  // Diese Map ist schwer, die Clonks sollen mehr EXP bekommen.
  var exp = 0;
  if(FindObject(ENRG))
    exp++;
  if(FindObject(CNMT))
    exp++;
  if(hardmode)
    exp=(exp+1)*2;
  for (var i,j=GetPlayerCount(); j; ++i)
    if (GetPlayerName(i))  {
	  // Eine neue Flagge muss kreiert werden?
	  if(flag) {
	    SetOwner(i,flag);
	    flag->Enter(GetHiRank(i));
	  }
      // Aber nur, wenn sie sich bewegen!
      if(Global(i)!=GetX(GetCursor(i)))
        DoCrewExp(exp, GetCursor(i));
      SetGlobal(i,GetX(GetCursor(i)));
      --j;
    }
  // --- Katastrophen ---
  var i;
  for(i = repeat+catastrophies; i>=100; i-=100) {
    // Vulkanausbruch
    LaunchVolcano(Random (LandscapeWidth()-1));
    // Meteoriten (Erst nach 10 min im Spiel, wenn man sich eingelebt hat)
    if((!Random( Max( 2, (72000-FrameCounter())/10000 )) || hardmode)&&(FrameCounter()>18000 || debugmode))
      SetSpeed(-20+Random(40),40,CreateObject(METO,Random(LandscapeWidth())));
    // Hardmode Blitze
    var frame = 95000;
    var rate = 3;
    if(FrameCounter()>3*frame/2)
      rate = 2;
    if(FrameCounter()>2*frame||debugmode)
      rate = 1;
    if(hardmode && !Random(rate) && (FrameCounter()>frame || debugmode))
      LaunchLightning(Random(LandscapeWidth()), 0, -20, 41, +5, 15);
  }
  catastrophies = i;
  MusicLevel(40);
  goto(380);
  return(1);

Script500:
  GameOver();
  return(1);

Allwissenheit:
  while (SetVar(0,GetDefinition(SetVar(1,Var(1)+1))))
    if(GetCategory(0, Var(0)) & C4D_Knowledge())
      SetPlrKnowledge(0, Var(0));
  if(Var(1)=FindObject(CNMT)) RemoveObject(Var(1));
  return(1);

OnGoalsFulfilled:
  // Gewonnen =) Alle Clonks kriegen massig EXP
  for (var i,j=GetPlayerCount(); j; ++i)
    if (GetPlayerName(i))  {
      var k=GetCrewCount(i); while (k--) DoCrewExp(1000,GetCrew(i, k));
      --j;
    }
  Sound("Trumpet",1);
  Message("Alle Ziele erfüllt! Herzlichen Glückwunsch!");
  goto(495);
  return(1);
  

ProductionID:
  var i=Par(0);
  if(!i--) return(8P51);
  if(!i--) return(FLNT);
  if(!i--) return(CNKT);
  if(!i--) return(LNKT);
  if(!i--) return(LOAM);
  if(!i--) return(CNCR);
  if(!i--) return(LIQG);
  if(!i--) return(FLAG);
  if(!i--) return(ROCK);
  if(!i--) return(GOL1);
  if(!i--) return(CLNK);
  if(!i--) return(BRDG);
  return(-i-1);

ProductionCount:
  var i=Par(0);
  if(!i--) return(10);
  if(!i--) return(5);
  return(5000);

BuyID:
  var i=Par(0);
  if(!i--) return(CNKT);
  if(!i--) return(LNKT);
  if(!i--) return(LOAM);
  if(!i--) return(WOOD);
  if(!i--) return(METL);
  if(!i--) return(CNCR);
  if(!i--) return(LIQG);
  if(!i--) return(FLAG);
  if(!i--) return(8P51);
  if(!i--) return(ROCK);
  if(!i--) return(ORE1);
  if(!i--) return(CLNK);
  if(!i--) return(BRDG);
  if(!i--) return(LORY);
  if(!i--) return(GLAS);
  if(!i--) return(SODA);
  if(!i--) return(SAND);
  return(-i-1);

BuyCount:
  var i=Par(0);
  if(!i--) return(5);
  if(!i--) return(8);
  if(!i--) return(20);
  if(!i--) return(25);
  if(!i--) return(10);
  if(!i--) return(10);
  if(!i--) return(10);
  if(!i--) return(3);
  if(!i--) return(15);
  if(!i--) return(10);
  if(!i--) return(15);
  if(!i--) return(5);
  if(!i--) return(2);
  if(!i--) return(1);
  if(!i--) return(1);
  if(!i--) return(1);
  if(!i--) return(1);
  return(0);
