/*-- Randomator --*/

#strict
#include _WOM

IsWeapon:
  return(ShortRangeWeapon()|MiddleRangeWeapon());

public MinRange:
  return(10);

public MaxRange:
  return(200);

SelectionSound:
  Sound("Random");
  return(1);
  
/* Ammo ID */  
GetAmmoID:
  var i = Random(13);
  if (i==0){
    Sound("Purge1");
    return(_AM4);}
  if (i==1){
    Sound("ShotShot");
    return(C_S5);}
  if (i==2){
    Sound("LaserShot1");
    return(_EGM);}
  if (i==3){
    if(GameCall("NoHotlaser")) return(GetAmmoID());
    Sound("LaserShot1");
    return(_HLS);}
  if (i==4){
    Sound("PGFire");
    return(RAM2);}
  if (i==5){
    Sound("Wheet");
    return(_AM9);}
  if (i==6){
    Sound("LaserMGShot");
    return(_AM0);}
  if (i==7){
    Sound("LaserShot1");
    return(_PS3);}
  if (i==8){
    Sound("Shot1");
    return(_AM7);}
  if (i==9){
    Sound("LaserShot1");
    return(_LS2);}
  if (i==10){
    Sound("LaserShot1");
    return(GBK2);}
  return(0);
  

/* Feuern */
Shot:
  if(!Par(0)&&Random(2)) {
   while(SetVar(2,FindObject(0,-100,-100,200,200,0,0,0,NoContainer(),Var(2))))
    if(Or(
          BitAnd(GetOCF(Var(2)),OCF_CrewMember()),
          BitAnd(GetOCF(Var(2)),OCF_Living()),
          Equal(GetID(Var(2)),_DRN)
          ))
      // Gehört nicht dem Spieler
      if(GetHostile(Var(2), Contained()))
        // Lebt noch
        if(GetAlive(Var(2)))
          // Zappen!
          return(ObjectCall(CreateObject(_LSR,0,0,-1), "Launch",this(),Var(2)));
  }
  if(!Par(0)) {
    // Blitze abfeuern
    var obj;
	var rnd = Random(3);
	if(rnd==0) obj=CreateContents(LGTS);
	if(rnd==1) obj=CreateContents(LGTR);
	if(rnd==2) obj=CreateContents(LGTB);
	SetOwner(GetOwner(Contained()), obj);
    Exit(obj, Par(1)*24-12,0,0, 0,0,0 );
    if(Par(1)==DIR_Left())
      obj->Launch(GetX()-10,GetY()-1,1800);
    if(Par(1)==DIR_Right())
      obj->Launch(GetX()+10,GetY()-1,0);
    // Sound
    Sound("Electric");
    return(1);
  }
  // Ammo abfeuern
  Exit(Par(0), Par(1)*24-12,0,0, 0,0,0 );
  ObjectCall(Par(0),"Launch",Par(1));
  return(1);

