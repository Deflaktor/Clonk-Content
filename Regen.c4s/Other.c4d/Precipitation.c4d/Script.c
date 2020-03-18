#strict

local iMat, iLength, iStrength;

func Precipitation()
{
  
  //if (Random(1) > iStrength) return(0);
  var mat = Material("Water");
  // var mat = iMat;
  if (GetTemperature()<0) {
    if (mat==Material("Water")||mat==Material("Rain")) 
      mat=Material("Snow");
  }

  var vx = GetWind(0, 3) * 5, vy = 100;

  InsertMaterial(mat, Random(LandscapeWidth()) - GetX(), -GetY(), vx, vy);
  InsertMaterial(mat, Random(LandscapeWidth()) - GetX(), -GetY(), vx, vy);
  InsertMaterial(mat, Random(LandscapeWidth()) - GetX(), -GetY(), vx, vy);
  InsertMaterial(mat, Random(LandscapeWidth()) - GetX(), -GetY(), vx, vy);
  InsertMaterial(mat, Random(LandscapeWidth()) - GetX(), -GetY(), vx, vy);
  
  //if(!GBackLiquid(LandscapeWidth()/2 - GetX(),-GetY() + 100))
  //  CreateObject(DROP, Random(LandscapeWidth()) - GetX(), -GetY(), -1);

}

static iMatWater;

global func Splash(int iX, int iY, int iLSPosX, int iLSPosY, int iXDir, int iYDir, int iPxsMat, int iLsMat, int iEvent) {
  if(iX<10||iY>LandscapeWidth()-10)
    return(1);
  CastPXS("Water",5,30, iX, iY);
  return(1);
}

 /* if(iLsMat==iMatWater)
    CastPXS("Water",5,0, iX, iY+1);
  else*/

func Movement()
{
  SetXDir(BoundBy(GetWind(0, 3), -100, 100));
  if (GetX() > LandscapeWidth()-20) 
    SetPosition(25,-1);
  if (GetX() < 20) 
    SetPosition(LandscapeWidth()-25,-1);
}

func Activate(inMat, inLength, inStrength)
{
  iMatWater = Material("Water");
  SetAction("Process");
  iMat = inMat; iLength = inLength; iStrength = inStrength;
  return(1);                                      
}

protected func UpdateTransferZone()
  {
  // hack: Locals alter Spielstände aktualisieren
  if (Local(1))
    {
    iMat = Local();
    iLength = Local(1);
    iStrength = Local(2);
    }
  }
