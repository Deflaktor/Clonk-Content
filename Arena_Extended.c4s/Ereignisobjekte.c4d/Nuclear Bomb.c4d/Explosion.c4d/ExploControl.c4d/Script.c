/*-- Explosionssteuerung --*/

#strict

local exec_counter; // Skriptzähler für die Funktion DetonateExec()

protected func Initialize()
  {
  // Druckwelle erzeugen (nur wenn Spiel im 16Bit-Modus) und Action!
  ObjectCall(CreateObject(FXPW,1,1,GetOwner()),"Activate",this());
  SetAction("Detonate");
  return(1);
  }

/* Die Explosion */

private func DetonateExec()
  {
  // Hilfsvariablen
  var x;
  var y;
  var z;
  var obj;
  // Zähler erhöhen
  exec_counter++;
  // kleine Hauptexplosion im Zentrum und "Bombensplitter"
  if(exec_counter==1)
    {
    Explode(40,CreateObject(PRNT,0,0));
    // Nach links fliegende Bombensplitter
    x = 40;
    while(x>=0)
      {
     // obj = CreateObject(NCPR,-10,((x*2)+40)/-1);
     // SetXDir(-200,obj);
      x--;
      }
    // Nach rechts fliegende Bombensplitter
    x = 40;
    while(x>=0)
      {
     // obj = CreateObject(NCPR,+10,((x*2)+40)/-1);
     // SetXDir(+200,obj);
      x--;
      }
    // Geräusch
    Sound("MegaExplosion");
    Sound("HEADCRAS");
    }
  if(exec_counter==2)
    {
    Explode(80,CreateObject(PRNT,0,0));
    Explode(40,CreateObject(PRNT,-10,-5));
    Explode(40,CreateObject(PRNT,10,-5));
    Explode(40,CreateObject(PRNT,0,-60));
    }
  if(exec_counter==3)
    {
    Explode(100,CreateObject(PRNT,0,0));
    Explode(40,CreateObject(PRNT,-20,25));
    Explode(40,CreateObject(PRNT,20,25));
    Explode(40,CreateObject(PRNT,0,-90));
    }
  if(exec_counter==5)
    {
    Explode(130,CreateObject(PRNT,0,0));
    Explode(40,CreateObject(PRNT,-10,-110));
    Explode(40,CreateObject(PRNT,10,-110));
    Explode(40,CreateObject(PRNT,-50,0));
    Explode(40,CreateObject(PRNT,50,0));
    }
  if(exec_counter==6)
    {
    Explode(80,CreateObject(PRNT,0,0));
    Explode(40,CreateObject(PRNT,-10,-120));
    Explode(50,CreateObject(PRNT,0,-150));
    Explode(40,CreateObject(PRNT,10,-120));
    Explode(45,CreateObject(PRNT,-70,0));
    Explode(45,CreateObject(PRNT,70,0));
    Smoke(0,0,40);
    }
  if(exec_counter==8)
    {
    Explode(30,CreateObject(PRNT,0,0));
    Explode(50,CreateObject(PRNT,-30,-165));
    Explode(60,CreateObject(PRNT,-10,-180));
    Explode(60,CreateObject(PRNT,10,-180));
    Explode(50,CreateObject(PRNT,30,-165));
    Explode(55,CreateObject(PRNT,-100,0));
    Explode(55,CreateObject(PRNT,100,0));
    Smoke(0,0,80);
    Smoke(-10,-5,40);
    Smoke(10,-5,40);
    Smoke(0,-60,40);
    }
  if(exec_counter==10)
    {
    Explode(60,CreateObject(PRNT,0,0));
    Explode(60,CreateObject(PRNT,-50,-220));
    Explode(80,CreateObject(PRNT,-15,-240));
    Explode(80,CreateObject(PRNT,15,-240));
    Explode(60,CreateObject(PRNT,50,-220));
    Explode(65,CreateObject(PRNT,-120,0));
    Explode(65,CreateObject(PRNT,120,0));
    Smoke(0,0,100);
    Smoke(-20,25,40);
    Smoke(20,25,40);
    Smoke(0,-90,40);
    }
  if(exec_counter==11)
    {
    Explode(90,CreateObject(PRNT,0,-250));
    Explode(70,CreateObject(PRNT,-145,0));
    Explode(70,CreateObject(PRNT,145,0));
    Smoke(0,0,130);
    Smoke(-10,-110,40);
    Smoke(10,-110,40);
    Smoke(-50,0,40);
    Smoke(50,0,40);
    }
  if(exec_counter==12)
    {
    Explode(70,CreateObject(PRNT,-65,-173));
    Explode(90,CreateObject(PRNT,-30,-280));
    Explode(90,CreateObject(PRNT,30,-280));
    Explode(70,CreateObject(PRNT,65,-173));
    Explode(70,CreateObject(PRNT,-175,0));
    Explode(70,CreateObject(PRNT,175,0));
    Smoke(0,0,80);
    Smoke(-10,-120,10);
    Smoke(0,-150,50);
    Smoke(10,-120,10);
    Smoke(-70,0,45);
    Smoke(70,0,45);
    }
  if(exec_counter==14)
    {
    Explode(60,CreateObject(PRNT,0,0));
    Explode(80,CreateObject(PRNT,-80,-280));
    Explode(95,CreateObject(PRNT,-45,-300));
    Explode(95,CreateObject(PRNT,45,-300));
    Explode(80,CreateObject(PRNT,80,-280));
    Explode(100,CreateObject(PRNT,0,-260));
    Smoke(0,0,30);
    Smoke(-30,-165,50);
    Smoke(-10,-180,10);
    Smoke(10,-180,10);
    Smoke(30,-165,50);
    Smoke(-100,0,55);
    Smoke(100,0,55);
    }
  if(exec_counter==17)
    {
    Explode(60,CreateObject(PRNT,0,0));
    Explode(90,CreateObject(PRNT,-85,-285));
    Explode(105,CreateObject(PRNT,-48,-310));
    Explode(105,CreateObject(PRNT,48,-310));
    Explode(90,CreateObject(PRNT,85,-285));
    Explode(110,CreateObject(PRNT,0,-270));
    Smoke(0,0,60);
    Smoke(-50,-220,60);
    Smoke(-15,-240,10);
    Smoke(15,-240,10);
    Smoke(50,-220,60);
    Smoke(-120,0,65);
    Smoke(120,0,65);
    }
  if(exec_counter==18)
    {
    Explode(120,CreateObject(PRNT,-85,-300));
    Explode(160,CreateObject(PRNT,0,-330));
    Explode(120,CreateObject(PRNT,85,-300));
    Smoke(0,-250,90);
    Smoke(-145,0,40);
    Smoke(145,0,40);
    }
  if(exec_counter==19)
    {
    Explode(130,CreateObject(PRNT,-95,-320));
    Explode(180,CreateObject(PRNT,0,-360));
    Explode(130,CreateObject(PRNT,95,-320));
    Smoke(-65,-173,70);
    Smoke(-30,-280,10);
    Smoke(30,-280,10);
    Smoke(65,-173,70);
    Smoke(-175,0,40);
    Smoke(175,0,40);
    }
  if(exec_counter==21)
    {
    Smoke(0,0,60);
    Smoke(-80,-280,80);
    Smoke(-45,-300,95);
    Smoke(45,-300,95);
    Smoke(80,-280,80);
    Smoke(0,-260,100);
    }
  if(exec_counter==23)
    {
    Smoke(0,0,60);
    Smoke(-85,-285,90);
    Smoke(-48,-310,105);
    Smoke(48,-310,105);
    Smoke(85,-285,90);
    Smoke(0,-270,110);
    }
  if(exec_counter==25)
    {
    Smoke(-85,-300,90);
    Smoke(0,-330,160);
    Smoke(85,-300,90);
    }
  if(exec_counter==27)
    {
    Smoke(-120,-320,90);
    Smoke(0,-360,180);
    Smoke(120,-320,90);
    }
  if(exec_counter==28)
    {
    // Objekte beschädigen
    // Entflammbares
    obj = 0;
    while(obj = FindObject(0,0,0,-1,-1,OCF_Inflammable(),0,0,NoContainer(),obj))
      if((x = ObjectDistance(this(),obj))<=300)
        if(PathFree(GetX(),GetY(),GetX(obj),GetY(obj))||GetCon(obj)<=40)
          if(GetY(obj)<=GetY(this())+280)
            if(!OnFire(obj))
              BlastObjects(GetX(obj),GetY(obj),x/4);
    // Gebäude
    obj = 0;
    while(obj = FindObject(0,0,0,-1,-1,0,0,0,NoContainer(),obj))
      if((x = ObjectDistance(this(),obj))<=300)
        if(PathFree(GetX(),GetY(),GetX(obj),GetY(obj))||GetCon(obj)<=40)
          if(GetY(obj)<=GetY(this())+280)
            if(!OnFire(obj))
              if(GetCategory(obj)&C4D_Structure()) 
                BlastObjects(GetX(obj),GetY(obj),x/4);
    MusicLevel(100-GameCall("MusicVolume"));
    }
  if(exec_counter==40)
    {
    RemoveObject(0);
    }
  return(1);
  }

