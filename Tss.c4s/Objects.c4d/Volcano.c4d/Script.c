/* Vulkan */
#strict

local iWidth,iXDir;
local iStrength, iLiveTime;
local OldX, OldY;

/* Ausbruch */ 

func Advance() {
  var obj, advancex=Random(11)-5+iXDir, advancey=Random(8)-12;
	var xdir, ydir;

   	// Verzweigungen
	if(!Random(30)) Branch();

  if(!InGround()) {
		SetAction("Discharge");
		/*for(var i=0; i<Max(3,iWidth/3); i++) 
		  CreateParticle("LavaGlow",GetX()-iWidth/2+Random(iWidth),GetY()+5-Random(20),0,0,100+Random(50+2*iWidth),RGBa(255,255,255,50));*/
			xdir=30-Random(60);
			ydir=-20-Random(50)-iWidth/2;
	} else {
		xdir=(GetX()-OldX)*10;
		ydir=(GetY()-OldY)*10;
	}
	// Objekte mitschleudern
	while(obj=FindObject(0,Max(OldX,GetX())-Min(OldX,GetX())-iWidth/2,0,iWidth+Abs(OldX-GetX()),OldY-GetY(),OCF_Collectible(),0,0,0,obj)) {
		SetYDir(ydir, obj);
	  SetXDir(xdir, obj);
	}
	
  OldX=GetX();
  OldY=GetY();
  SetPosition(GetX()+advancex,GetY()+advancey);
	if(iWidth>5) 
		if(!Random(3)) Sound("Lava*");
	
	if(iWidth>10) {
		//CreateParticle("LavaGlow",-iWidth/2+Random(iWidth),+5-Random(20),0,0,100+Random(50+2*iWidth),RGBa(255,255,255,50));
		//if(!Random(10)) ShakeViewPort(10+Random(iWidth),this());
	}

  //if(!InMoonstone(advancex, advancey, iWidth)) {

    if(!DrawLava(advancex, advancey, iWidth))
      DrawLine(OldX,OldY,GetX(),GetY());
    
//    DrawMaterialQuad("Lava-Flat",
//      GetX()-iWidth/2, GetY(),GetX()+iWidth/2, GetY(),
//      OldX+iWidth/2,OldY,OldX-iWidth/2,OldY,1);

  //}

  if(Local(1))
    DrawMoonstone(advancex, advancey, iWidth);

  BlastObjects (GetX()-iWidth/2+Random(iWidth),GetY(),Max(10,iWidth+Random(10)));
  if(!InBounds()) return(Remove());
  DecreaseSize();
}

/* Zeichenfunktionen f¸r die Kokelerde */

func DrawLine(x1, y1, x2, y2) {
  var colr, coll,x,y, i,dist=Distance(x1,y1,x2,y2);
	var wdt, max=90; // max. Ankokelung
  i=dist;
  while(i>=0) {
    x=x2+((x1-x2)*i)/dist-GetX();
    y=y2+((y1-y2)*i)/dist-GetY();
    if(GBackSolid(x+iWidth/2+2,y)) {
			wdt=Min(1+iWidth,3+Random(4));
			colr=GetMaterialColorX(GetMaterial(x+iWidth/2+2,y),0);
			DrawXGradient(x+iWidth/2,y,colr,wdt,max,1);
    }
    if(GBackSolid(x-iWidth/2-2,y)) {
			wdt=Min(1+iWidth,3+Random(4));
			coll=GetMaterialColorX(GetMaterial(x-iWidth/2-2,y),0);
			DrawXGradient(x-iWidth/2,y,coll,wdt,max,0);
    }
    i--;
  }
}

func DrawXGradient(x, y, col, wdt, max, dir) {
	dir=-1+2*dir;
	var fact=max/wdt;
	for(var i=1; i<=wdt; i++) SetLandscapePixel(x+i*dir,y,DarkenRGB(max-i*fact,col));
}

func DarkenRGB(amm,val) {
  return(LightenRGB(-amm,val));
}

func LightenRGB(amm, val) {
  var red=GetRGBValue(val, 1), green=GetRGBValue(val,2),blue=GetRGBValue(val,3);
  val=SetRGBaValue(val,BoundBy(red+(amm*red)/100,0,255),1);
  val=SetRGBaValue(val,BoundBy(green+(amm*green)/100,0,255),2);
  val=SetRGBaValue(val,BoundBy(blue+(amm*blue)/100,0,255),3);
  return(val);
}

/* Eruption */ 

func CastLava() {
  // Hoehle die sich mit Lava vollfuellt?
  if(InGround()) {
    iLiveTime-=GetActTime();
    return(SetAction("Advance"));
  }
  // Vulkane lassen alle Fl¸ssigkeiten verdampfen
  if(GBackLiquid(0,-2) && GetMaterial(0,-2)!=Material("Lava") && GetMaterial(0,-2)!=Material("DuroLava")) 
   for(var i; i<5; i++) ExtractLiquid(0,-2);
  // dicke Rauchschwaden
  for(var i=1+Random(3); i>=0; i--) {
		Smoke(-iWidth / 2 + Random(iWidth), +15, 10 + Random(iWidth / 2), HSL2RGB(RGB(38, 200, 100))); 
		//if(!Random(3)) Smoke(-iWidth/2+Random(iWidth), +15, 3+Random(4),HSL2RGB(RGB(38,200+Random(55),100))); 
	}
  // ggf. hoeher casten
  while(GBackSolid(0,0) && GetY()) SetPosition(GetX(),GetY()-1);
  // rausrinnen
  for(var i=3+Random(5); i>0; i--) InsertMaterial(Material("Lava"),0,0);
  // rumspritzen
  if (!Random(2))
  {
  	var y_diff;
  	while(GetMaterial(0,y_diff)==Material("Lava")) y_diff--;
  	CastPXSX("Lava", Max(iWidth/2,5), Max(50, iWidth) + Random(50), -iWidth/2 + Random(iWidth), y_diff - 1, 270 + 10 - Random(21), 20 + Random(30));
  }  
  // mit Lavaklumpen um sich werfen
    if(iWidth>10)
      if(!Random(5)) {
        CastObjectsX(LAVA,1,Max(40,iWidth)+Random(30),-iWidth/2+Random(iWidth),0,270,50,"LavaCast");
	Sound("Discharge");
	BlastObjects (GetX()-iWidth/2+Random(iWidth),GetY(),Max(40,iWidth+Random(10)));
	//if(!Random(5))	ShakeViewPort(10+Random(20)+Random(iWidth),this());
      }
  if(GetActTime()>iLiveTime) {
    //Log("my time is running out aarrgh...........*plop*");
    Remove(); 
  }
}

/* Callback of CastObjectsX */
func LavaCast(obj) {
  //LocalN("mat",obj)="Lava";
  DoCon(-50+Random(5*iWidth)+iWidth/2,obj);
}

/* Aktivierung des Vulkans */
func Activate(iX,iY,iStr,iM,iXD,iTime) {
  AddVertex(iX,iY);
  iWidth=iStr;
  iXDir=iXD;
	SetPosition(iX,iY);
  if(iTime) iLiveTime=iTime;
  else iLiveTime=200+2*iWidth;
  if(!InGround()) return(Remove());
  SetAction("Advance");
  if(!Random(5)) Sound("Lava*");
  // unteres Ende abrunden
  /*if(!InMoonstone(-2,2,iWidth))
  DrawMaterialQuad("Lava-Flat",
    iX-iWidth/2,iY,
    iX+iWidth/2,iY,
    iX+Random(iWidth/2),iY+iWidth/4+Random(iWidth/4),
    iX-Random(iWidth/2),iY+iWidth/4+Random(iWidth/4),
    1);*/
  return(1);
}

/* Vulkanader abspalten */

private func Branch() {
  var pVolcano=CreateObject(FXV1,0,0,-1);
  var iStr=Random(iWidth);
  var iXDir=2+Random(4);
  iXDir=(1-2*Random(2))*iXDir;
  pVolcano->FXV1::Activate(-iWidth/2+GetX()+iStr/2,GetY(),iStr,Material("Lava"),iXDir);
  //SetVertex(iLastVertex,0,GetVertex(iLastVertex,0)+iStr/2);
  iWidth-=iStr;
}

/* Vulkanader verkleinern */

private func DecreaseSize() {
  if(Random(5)) return();
  if(--iWidth<=0) Remove();
}


/* Pr¸fungen */

private func InGround() {
  // letzter Vertex in festem Material -> im Untergrund
  //return(0);
  if (GBackSolid(0,-10)) return(1);
  if (GBackLiquid(0,-10)) return(1);
  return(0);
  // letzter Vertex im Material was gecastet wird -> im Untergrund
  if (GetMaterial(0,-10) == Material("Lava") || GetMaterial(0,-10)==Material("DuroLava")) return(1);
  // ansonsten nicht im Untergrund
  return(0);
}

private func InMoonstone(int iAdvanceX, int iAdvanceY, int iWidth) {
  var left, right, c, step = 2;
  left = -iAdvanceX-iWidth/2;
  right = -iAdvanceX+iWidth/2;
  iWidth = Max(iWidth, 6);
  iAdvanceY = Min(iAdvanceY, -2);
  for(var y=-iAdvanceY;y>=-2;y-=step) {
    var shift = c*iAdvanceX/iAdvanceY;
    for(var x=left-1-shift;x<=right+1-shift;x+=step) {
      if (GetMaterial(x,y) == Material("Moonstone")) 
        return(1); 
   // else
   //   DrawMaterialQuad ("Lava", x+GetX(), y+GetY(), x+GetX(), y+GetY(), x+GetX()+1, y+GetY()+1, x+GetX(), y+GetY());
    }
    c+=step;
  }
  return(0);
}

private func DrawMoonstone(int iAdvanceX, int iAdvanceY, int width) {
  if(!iAdvanceX&&!iAdvanceY&&!width) {
    iAdvanceX=Random(11)-5+iXDir;
    iAdvanceY=Random(8)-12;
    width=iWidth;
  }
    DrawMaterialQuad("Lava",
      GetX()-width/2, GetY(),GetX()+width/2, GetY(),
      GetX()-iAdvanceX+width/2,GetY()-iAdvanceY,GetX()-iAdvanceX-width/2,GetY()-iAdvanceY,1);
  var left, right, c, step = 1;
  left = -iAdvanceX-width/2;
  right = -iAdvanceX+width/2;
  
  //width = Max(width, 6);
  //iAdvanceY = Min(iAdvanceY, -2);
  for(var y=-iAdvanceY;y>=0;y-=step) {
    var shift = c*iAdvanceX/iAdvanceY;
    for(var x=left-shift-1;x<=right-shift+1;x+=step) {
      DrawMaterialQuad ("Rock", x+GetX(), y+GetY(), x+GetX(), y+GetY(), x+GetX()+1, y+GetY()+1, x+GetX(), y+GetY());
    }
    c+=step;
  }
  Local(1)=0;
  return(1);
}

private func DrawLava(int iAdvanceX, int iAdvanceY, int width) {
  if(!iAdvanceX&&!iAdvanceY&&!width) {
    iAdvanceX=Random(11)-5+iXDir;
    iAdvanceY=Random(8)-12;
    width=iWidth;
  }
  var ret = 0;
  var left, right, c, step = 1;
  left = -iAdvanceX-width/2;
  right = -iAdvanceX+width/2;
  
  for(var y=-iAdvanceY;y>=0;y-=step) {
    var shift = c*iAdvanceX/iAdvanceY;
    for(var x=left-shift;x<=right-shift;x+=step) {
      if (GetMaterial(x,y) != Material("Moonstone")) 
        DrawMaterialQuad ("Lava-Flat", x+GetX(), y+GetY(), x+GetX(), y+GetY(), x+GetX()+1, y+GetY()+1, x+GetX(), y+GetY(), 1);
      else 
        ret = 1;
    }
    c+=step;
  }
  Local(1)=0;
  return(ret);
}

private func InBounds() {
  // auﬂerhalb der Landschaft
  if(GetX()+iWidth/2<0) return(0);
  if(GetX()-iWidth/2>LandscapeWidth()) return(0);
  if (!Inside(GetY(),0,LandscapeHeight())) return(0);
  // nicht auﬂerhalb der Landschaft
  return(1);
}

private func Remove() { 
  RemoveObject(); 
}