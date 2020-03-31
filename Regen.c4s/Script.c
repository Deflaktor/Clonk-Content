/*-- Regen --*/

#strict

static wave, seed, knowsOven, knowsDynamo, knowsWizard, knowsAltar, knowsSmallCastle, knowsCastle, gaveMaterial;

protected func Initialize() {
  seed=137;
  // Spielziel setzen
  FindObject(RMOB)->AddType(SHEL, 0);
  Sound("@Rain.ogg", 1,0,20,0,1);
  SetSkyParallax (1, 0, 0, 0, 0,  SkyPar_Keep() ,  SkyPar_Keep() ); 
  var tunnel = Material("Tunnel");
  // Vegetation
  for(var i=0;i<50;) if(PlaceInMat(tunnel, _VEG, 1)) i++;
  for(var i=0;i<15;) if(PlaceInMat(tunnel, S_RN)) i++;
  for(var i=0;i<15;) if(PlaceInMat(tunnel, SWEB)) i++;
  for(var i=0;i<20;) if(PlaceInMat(tunnel, _STA, 1, 0, -19,-60,-4)) i++;
  for(var i=0;i<5;) if(PlaceInMat(tunnel, IDOL)) i++;
  for(var i=0;i<1;) if(PlaceInMat(tunnel, GIDL)) i++;
  for(var i=0;i<10;) if(PlaceInMat(tunnel, BCRS, 1, 15)) i++;
  // Buildings
  for(var i=0;i<1;) if(Var(0)=PlaceInMat(tunnel, CSB1, 0, 40)) {
    RemoveObject(Var(0)->FindObject(Var(0)->BasementID(),-100,0,200,100));
    i++;
  }
  for(var i=0;i<1;) if(PlaceInMat(tunnel, HTB1)) i++;
  for(var i=0;i<2;) if(PlaceInMat(tunnel, HUT1, 0, 20)) i++;
  for(var i=0;i<1;) if(Var(0)=PlaceInMat(tunnel, OVEN, 0, 20)) {
    Var(0)->CreateContents(WOOD);
    Var(0)->CreateContents(WOOD);
    i++;
  }
  for(var i=0;i<1;) if(PlaceInMat(tunnel, ANVL, 1, 20)) i++;
  for(var i=0;i<4;) if(PlaceInMat(tunnel, IDLS)) i++;
  for(var i=0;i<1;) if(PlaceInMat(tunnel, TWB1)) i++;
  // Mushrooms
  for(var i=0;i<10;) if(PlaceInMat(tunnel, MUSH)) i++;
  // Animals
  for(var i=0;i<6;) if(PlaceInMat(tunnel, WIPF,0,15)) i++;
  for(var i=0;i<5;) if(PlaceInMat(tunnel, SNKE,0,15)) i++;
  for(var i=0;i<5;) if(PlaceInMat(tunnel, MONS,0,20)) i++;
  for(var i=0;i<2;) if(PlaceInMat(tunnel, FMNS,0,20)) i++;
  // Skeletons
  for(var i=0;i<5;) if(PlaceInMat(tunnel, KIL1,1,20)) i++;
  for(var i=0;i<4;) if(Var(0)=PlaceInMat(tunnel, KIL1, 1, 20)) {
    Var(0)->SetWeapID(FLT_);
    i++;
  }
  for(var i=0;i<35;) if(PlaceInMat(tunnel, BONE)) i++;
  for(var i=0;i<10;) if(Var(0)=PlaceInMat(tunnel, BONE, 1, 20)) {
    Var(0)->SetUndead(1);
    i++;
  }
  // Chests
  for(var i=0;i<15;) if(Var(0)=PlaceInMat(tunnel, CHST, 1)) {
    // One chest has Ultra Flint
    if(i==11)
      Var(0)->CreateContents(_UFL);
    else {
      if(i==9) CreateContents(_CPL,Var(0))->SetID(SAWM);
      if(i>=7&&i<=8) CreateContents(_CPL,Var(0))->SetID(OVEN);
      if(i>=5&&i<=6) CreateContents(_CPL,Var(0))->SetID(WTWR);
      if(i>=3&&i<=4) CreateContents(_CPL,Var(0))->SetID(ALTR);
      if(i==2) CreateContents(_CPL,Var(0))->SetID(CST2);
      if(i==1) CreateContents(_CPL,Var(0))->SetID(CST1);
      // Bummerang
      if(i==0) CreateContents(_BMR,Var(0));
      PutContentsInChests(Var(0));
    }
    i++;
  }
  // 5 empty chests
  for(var i=0;i<5;) if(PlaceInMat(tunnel, CHST, 1)) i++;
  // Doughpots
  for(var i=0;i<5;) if(PlaceInMat(tunnel, DPOT, 1, 20)) i++;
  // Lorrys
  for(var i=0;i<4;) if(Var(0)=PlaceInMat(tunnel, LORY, 1, 20)) {
    if(Chance(40)) {
      Var(0)->CreateContents(BONE);
      Var(0)->CreateContents(BONE);
      Var(0)->CreateContents(SKUL);
    }
    if(Chance(5)) Var(0)->CreateContents(LNKT);
    if(Chance(20)) Var(0)->CreateContents(WOOD);
    if(Chance(15)) Var(0)->CreateContents(COAL);
    if(Chance(5)) Var(0)->CreateContents(CRYS);
    if(Chance(10)) Var(0)->CreateContents(STFN);
    if(Chance(30)) Var(0)->CreateContents(SFLN);
    i++;
  }
  for(var i=0;i<2;) if(Var(0)=PlaceInMat(tunnel, WLRY, 1, 20)) {
    if(Chance(40)) {
      Var(0)->CreateContents(BONE);
      Var(0)->CreateContents(BONE);
      Var(0)->CreateContents(SKUL);
    }
    if(Chance(5)) Var(0)->CreateContents(CNKT);
    if(Chance(20)) Var(0)->CreateContents(WOOD);
    if(Chance(15)) Var(0)->CreateContents(COAL);
    if(Chance(5)) Var(0)->CreateContents(CRYS);
    if(Chance(30)) Var(0)->CreateContents(STFN);
    if(Chance(10)) Var(0)->CreateContents(SFLN);
    i++;
  }
  
  ScriptGo(1);
  return(1);
}

protected func PutContentsInChests(object chest) {
  var val;
  // every fourth chest is empty
  if(Chance(25)) return(chest);
  // 50% chance of food
  if(Chance(50)) {
    val = Roll(1,4);
    chest->CreateContents(GetFoodId(val));
  }
  val = Roll(0,4);
  for(var i=0;i<val;i++)
    chest->CreateContents(GOLD);
  if(Chance(30)) chest->CreateContents(METL);
  if(Chance(10)) {
    val = Roll(1,4);
    if(val==1) chest->CreateContents(EFLN);
    if(val==2) chest->CreateContents(TRP1);
    if(val==3) chest->CreateContents(ADM3);
  }
  if(Chance(10)) chest->CreateContents(SFLN);
  if(Chance(12)) chest->CreateContents(STFN);
  if(Chance(15)) chest->CreateContents(TFLN);
  if(Chance(15)) chest->CreateContents(FLNT);
  if(Chance(10)) chest->CreateContents(CNKT);
  if(Chance(10)) chest->CreateContents(WBRL);
  if(Chance(12)) chest->CreateContents(BARL);
  if(Chance(10)) chest->CreateContents(TENP);
  if(Chance(15)) chest->CreateContents(_BMR);
  if(Chance(20)) chest->CreateContents(PFIS);
  if(Chance(20)) chest->CreateContents(PSTO);
  if(Chance(10)) {
    chest->CreateContents(BONE);
    chest->CreateContents(BONE);
    chest->CreateContents(SKUL);
  }
  if(!chest->FindContents(_CPL)&&Chance(35)) {
    var obj = CreateContents(_CPL,chest);
    val = Roll(1,6);
    if(val==1) obj->SetID(BAS7);
    if(val==2) obj->SetID(DRCK);
    if(val==3) obj->SetID(HUT1);
    if(val==4) obj->SetID(SGNL);
    if(val==5) obj->SetID(GIDL);
    if(val==6) obj->SetID(IDOL);
  }
  return(chest);
}

protected func GetFoodId(int type) {
  if(type==1)
    return(BRED);
  if(type==2)
    return(COKI);
  if(type==3)
    return(MUSH);
  if(type==4)
    return(PHEA);
  return(0);
}

protected func Chance(int percentage) {
  //seed = (seed*9)/1000+(seed*9)%1000;
  var rand = Random(100);//seed/10;
  if(rand<percentage)
    return(true);
  return(false);
}

protected func Roll(int min, int max) {
  //seed = (seed*9)/1000+(seed*9)%1000;
  var rand = Random(1000);//seed;
  return(min+rand*(max-min+1)/1000);
}


protected func InitializePlayer(int iPlr) {
   var obj,clonk,item;
   while(obj=FindObjectOwner(0,iPlr)) RemoveObject(obj);
   for(var i=0;i<10;i++) {
     obj = TryIt();
     if(obj)
       break;
   }
   if(!obj)
     obj=CreateObject(BUSH,LandscapeWidth()/2,100);
   clonk = CreateObject(CLNK,GetX(obj),GetY(obj),iPlr);
   item = CreateObject(TENP,0,0,iPlr);
   item->Enter(clonk);
   MakeCrewMember(clonk,iPlr);
   clonk->DoEnergy(1000);
   clonk = CreateObject(CLNK,GetX(obj),GetY(obj),iPlr);
   item = CreateObject(FLAG,0,0,iPlr);
   item->Enter(clonk);
   MakeCrewMember(clonk,iPlr);
   clonk->DoEnergy(1000);
   RemoveObject(obj);
   
   if(knowsOven)
     SetPlrKnowledge(iPlr, OVEN);
   if(knowsDynamo)
     SetPlrKnowledge(iPlr, DYNM);
   if(knowsWizard)
     SetPlrKnowledge(iPlr, WTWR);
   if(knowsAltar)
     SetPlrKnowledge(iPlr, ALTR);
   if(knowsSmallCastle)
     SetPlrKnowledge(iPlr, CST1);
   if(knowsCastle)
     SetPlrKnowledge(iPlr, CST2);
   return(_inherited(iPlr));
}

private func TryIt() {
  var obj = PlaceVegetation(BUSH,0,0,LandscapeWidth(),LandscapeHeight(),100000);
  if(obj)
    if(obj->GetMaterial()==Material("Sky"))
      return(obj);
  RemoveObject(obj);
  return(0);
}

private func PlaceInMat(int mat, id pId, bool noNearby, int needsPlace, int placement, int freeSpace, int yOffset) {
  var obj = PlaceAnimal(pId);
  if(obj) 
    if(obj->GetMaterial()==mat) {
      if(noNearby) if(obj->FindObject(pId,-50,-50,100,100)) { RemoveObject(obj); return(0); }
      if(!needsPlace&&!placement) return(obj);
      else {
        if(needsPlace&&
           obj->GetMaterial(-needsPlace,-5)==mat&&
           obj->GetMaterial(needsPlace,-5)==mat&&
           obj->GetMaterial(0,-needsPlace)==mat)
          return(obj);
        if(placement) {
          var dir = 3; if(placement<0) dir = -3;
          // there needs to be some free space
          //if(GetTunnelHeight(GetX(obj),GetY(obj))<freeSpace) return(0);
          if(obj->GBackSolid(0,freeSpace)||obj->GBackSolid(0,freeSpace/2)) {
            RemoveObject(obj);
            return(0);
          }
          for(var i=1;i<100;i++) {
            if(obj->GBackSolid(0,i*dir+placement)) {
              obj->SetPosition(GetX(obj),GetY(obj)+i*dir+yOffset);
              return(obj);
            }
          }
        }
      }
    }
  RemoveObject(obj);
  return(0);
}

private func GetTunnelHeight(int iX, int iY) {
  var topY = 0;
  var bottomY = LandscapeHeight();
  var overflow=true;
  for(var i=1;i<100;i++) {
      if(GBackSolid(iX,iY-i*3)) {
        topY=iY-i*3;
        overflow=false;
        break;
      }
  }
  if(overflow) return(0);
  overflow=true;
  for(var i=1;i<100;i++) {
      if(GBackSolid(iX,iY-i*3)) {
        bottomY=iY+i*3;
        overflow=false;
        break;
      }
  }
  if(overflow) return(0);
  return(bottomY-topY);
}

Script5:
  LaunchVolcano(Random(LandscapeWidth())); 
  return(1);
  
Script9:
  LaunchVolcano(Random(LandscapeWidth())); 
  while(ObjectCount(RCKF)<45) CreateObject(RCKF,10,10,-1);
  return(1);


  
Script1200:
  CreateEnemy();
  //DoHomeBaseMaterialAll(WLRY,1);
  return(1);
  
Script2200:
  if(!gaveMaterial) {
    CreateEnemy();
    //DoHomeBaseMaterialAll(LORY,1);
    DoHomeBaseMaterialAll(ACT3,1);
    DoHomeBaseMaterialAll(BRED,1);
    DoHomeBaseMaterialAll(CTW7,1);
    gaveMaterial=true;
  }
  goto(10000-800);
  return(1);
  
Script10000:
  if(!CreateEnemy()) return(goto(10000-30));
  wave++;
  // LaunchEarthquake(Random(LandscapeWidth()),RandomX(LandscapeHeight()/2,LandscapeHeight()));
  goto(Max(5000,10000-600));
  return(1);
  
protected func CreateEnemy() {
  // cache id for performance
  var tunnel = Material("Tunnel");
  // select random clonk
  var obj = GetRandomClonk();
  // if(!obj) obj = GetRandomClonk();
  if(!obj) return(0);
  // random location around clonk but not too close
  var x,y;
  var enemy = 0;
  var type = (seed++)%2;
  var count = Min(2,wave/25+1);
  if(wave>30) {
    type=2;
    count++;
    if(Random(2))
      count = Random(count+1);
  }
  for(var i=0;i<1000;i++) {
    if(count<=0)
      break;
    x = RandomX(GetX(obj)-50,GetX(obj)+50);
    y = RandomX(GetY(obj)-30,GetY(obj)+10);
    if(!GBackSemiSolid(x,y)&&
       !GBackSemiSolid(x,y-20)&&
       !GBackSemiSolid(x-5,y-5)&&
       !GBackSemiSolid(x+5,y-5)&&
       Distance(GetX(obj),GetY(obj),x,y)>10&&
       PathFree(x,y,GetX(obj),GetY(obj))) {
      if(type==0||(type==2&&Random(2))) {
        enemy=CreateObject(_DFA,x,y,-1);
        enemy->SetBlast(BoundBy(wave/2,10,20));
        count--;
        if(FindObject(ALTR))
          if(enemy->ObjectDistance(enemy->FindObject(ALTR,0,0,-1,-1))<1000) {
            RemoveObject(enemy);
            if(type==2) count++;
          }
          if(FindObject2(Find_ID(FLAG), enemy->Find_Distance(200), Find_Action("FlyBase"))) {
            RemoveObject(enemy);
            if(type==2) count++;
          }
      } 
      if(type==1||(type==2&&Random(2))) {
        enemy=CreateObject(KIL1,x,y,-1);
        enemy->SetAction("Walk");
        enemy->SetNotEternal(1);
        if(Random(2)&&wave>25)
          enemy->SetWeapID(FLT_);
        if(Random(2)&&wave>40)
          enemy->SetWeapID(FLNT);
        count--;
        if(FindObject(ALTR))
          if(enemy->ObjectDistance(enemy->FindObject(ALTR,0,0,-1,-1))<1000) {
            RemoveObject(enemy);
            if(type==2) count++;
          }
          if(enemy) {
            if(FindObject2(Find_ID(FLAG), enemy->Find_Distance(200), Find_Action("FlyBase"))) {
               RemoveObject(enemy);
               if(type==2) count++;
            }
          }
      }
    }
  }
  return(enemy);
}

protected func GetRandomClonkNoContainer() {
  var clonks = ObjectCount(0,0,0,0,0,OCF_CrewMember(),0,0,NoContainer());
  var rand = Random(clonks);
  var obj;
  while(obj=FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,NoContainer(),obj))
    if(rand==0) break; 
    else rand--;
  if(!obj) return(0);
  if(obj->GBackSemiSolid())
    return(0);
  return(obj);
}

protected func GetRandomClonk() {
  var clonks = ObjectCount(0,0,0,0,0,OCF_CrewMember(),0,0,0);
  var rand = Random(clonks);
  var obj;
  while(obj=FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,0,obj))
    if(rand==0) break; 
    else rand--;
  if(obj->GBackSemiSolid())
    return(0);
  return(obj);
}

protected func DoHomeBaseMaterialAll(id idID, int iChange) {
  for (var i,j=GetPlayerCount(); j; ++i)
    if (GetPlayerName(i)) {
      DoHomebaseMaterial(i,idID,iChange);
      --j;
    }
}
