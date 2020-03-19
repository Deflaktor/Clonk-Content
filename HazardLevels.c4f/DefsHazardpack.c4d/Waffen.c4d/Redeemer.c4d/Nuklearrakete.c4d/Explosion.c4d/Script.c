/*-- Explosionssteuerung --*/

#strict

local exec_counter; // Skriptzähler für die Funktion DetonateExec()

protected func Initialize()
  {
  // Druckwelle erzeugen (nur wenn Spiel im 16Bit-Modus) und Action!
  ObjectCall(CreateObject(FXPW,1,1),"Activate",this());
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
    }
  if(exec_counter==2)
    {
    ObjectCall(CreateObject(EXPL,0,0),"Launch",80);
    ObjectCall(CreateObject(EXPL,-10,-5),"Launch",40);
    ObjectCall(CreateObject(EXPL,10,-5),"Launch",40);
    ObjectCall(CreateObject(EXPL,0,-60),"Launch",40);
    }
  if(exec_counter==3)
    {
    ObjectCall(CreateObject(EXPL,0,0),"Launch",100);
    ObjectCall(CreateObject(EXPL,-20,25),"Launch",40);
    ObjectCall(CreateObject(EXPL,20,25),"Launch",40);
    ObjectCall(CreateObject(EXPL,0,-90),"Launch",40);
    }
  if(exec_counter==5)
    {
    ObjectCall(CreateObject(EXPL,0,0),"Launch",130);
    ObjectCall(CreateObject(EXPL,-10,-110),"Launch",40);
    ObjectCall(CreateObject(EXPL,10,-110),"Launch",40);
    ObjectCall(CreateObject(EXPL,-50,0),"Launch",40);
    ObjectCall(CreateObject(EXPL,50,0),"Launch",40);
    }
  if(exec_counter==6)
    {
    ObjectCall(CreateObject(EXPL,0,0),"Launch",80);
    ObjectCall(CreateObject(EXPL,-10,-120),"Launch",40);
    ObjectCall(CreateObject(EXPL,0,-150),"Launch",50);
    ObjectCall(CreateObject(EXPL,10,-120),"Launch",40);
    ObjectCall(CreateObject(EXPL,-70,0),"Launch",45);
    ObjectCall(CreateObject(EXPL,70,0),"Launch",45);
    Smoke(0,0,40);
    }
  if(exec_counter==8)
    {
    ObjectCall(CreateObject(EXPL,0,0),"Launch",30);
    ObjectCall(CreateObject(EXPL,-30,-165),"Launch",50);
    ObjectCall(CreateObject(EXPL,-10,-180),"Launch",60);
    ObjectCall(CreateObject(EXPL,10,-180),"Launch",60);
    ObjectCall(CreateObject(EXPL,30,-165),"Launch",50);
    ObjectCall(CreateObject(EXPL,-100,0),"Launch",55);
    ObjectCall(CreateObject(EXPL,100,0),"Launch",55);
    Smoke(0,0,80);
    Smoke(-10,-5,40);
    Smoke(10,-5,40);
    Smoke(0,-60,40);
    }
  if(exec_counter==10)
    {
    ObjectCall(CreateObject(EXPL,0,0),"Launch",60);
    ObjectCall(CreateObject(EXPL,-50,-220),"Launch",60);
    ObjectCall(CreateObject(EXPL,-15,-240),"Launch",80);
    ObjectCall(CreateObject(EXPL,15,-240),"Launch",80);
    ObjectCall(CreateObject(EXPL,50,-220),"Launch",60);
    ObjectCall(CreateObject(EXPL,-120,0),"Launch",65);
    ObjectCall(CreateObject(EXPL,120,0),"Launch",65);
    Smoke(0,0,100);
    Smoke(-20,25,40);
    Smoke(20,25,40);
    Smoke(0,-90,40);
    }
  if(exec_counter==11)
    {
    ObjectCall(CreateObject(EXPL,0,-250),"Launch",90);
    ObjectCall(CreateObject(EXPL,-145,0),"Launch",70);
    ObjectCall(CreateObject(EXPL,145,0),"Launch",70);
    Smoke(0,0,130);
    Smoke(-10,-110,40);
    Smoke(10,-110,40);
    Smoke(-50,0,40);
    Smoke(50,0,40);
    }
  if(exec_counter==12)
    {
    ObjectCall(CreateObject(EXPL,-65,-173),"Launch",70);
    ObjectCall(CreateObject(EXPL,-30,-280),"Launch",90);
    ObjectCall(CreateObject(EXPL,30,-280),"Launch",90);
    ObjectCall(CreateObject(EXPL,65,-173),"Launch",70);
    ObjectCall(CreateObject(EXPL,-175,0),"Launch",70);
    ObjectCall(CreateObject(EXPL,175,0),"Launch",70);
    Smoke(0,0,80);
    Smoke(-10,-120,10);
    Smoke(0,-150,50);
    Smoke(10,-120,10);
    Smoke(-70,0,45);
    Smoke(70,0,45);
    }
  if(exec_counter==14)
    {
    ObjectCall(CreateObject(EXPL,0,0),"Launch",60);
    ObjectCall(CreateObject(EXPL,-80,-280),"Launch",80);
    ObjectCall(CreateObject(EXPL,-45,-300),"Launch",95);
    ObjectCall(CreateObject(EXPL,45,-300),"Launch",95);
    ObjectCall(CreateObject(EXPL,80,-280),"Launch",80);
    ObjectCall(CreateObject(EXPL,0,-260),"Launch",100);
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
    ObjectCall(CreateObject(EXPL,0,0),"Launch",60);
    ObjectCall(CreateObject(EXPL,-85,-285),"Launch",90);
    ObjectCall(CreateObject(EXPL,-48,-310),"Launch",105);
    ObjectCall(CreateObject(EXPL,48,-310),"Launch",105);
    ObjectCall(CreateObject(EXPL,85,-285),"Launch",90);
    ObjectCall(CreateObject(EXPL,0,-270),"Launch",110);
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
    ObjectCall(CreateObject(EXPL,-85,-300),"Launch",120);
    ObjectCall(CreateObject(EXPL,0,-330),"Launch",160);
    ObjectCall(CreateObject(EXPL,85,-300),"Launch",120);
    Smoke(0,-250,90);
    Smoke(-145,0,40);
    Smoke(145,0,40);
    }
  if(exec_counter==19)
    {
    ObjectCall(CreateObject(EXPL,-95,-320),"Launch",130);
    ObjectCall(CreateObject(EXPL,0,-360),"Launch",180);
    ObjectCall(CreateObject(EXPL,95,-320),"Launch",130);
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
      if((x = ObjectDistance(this(),obj))<=800)
        if(PathFree(GetX(),GetY(),GetX(obj),GetY(obj))||GetCon(obj)<=40)
          if(GetY(obj)<=GetY(this())+280)
            if(!OnFire(obj))
              BlastObjects(GetX(obj),GetY(obj),x/10);
    // Gebäude
    obj = 0;
    while(obj = FindObject(0,0,0,-1,-1,0,0,0,NoContainer(),obj))
      if((x = ObjectDistance(this(),obj))<=800)
        if(PathFree(GetX(),GetY(),GetX(obj),GetY(obj))||GetCon(obj)<=40)
          if(GetY(obj)<=GetY(this())+280)
            if(!OnFire(obj))
              if(GetCategory(obj)&C4D_Structure()) 
                BlastObjects(GetX(obj),GetY(obj),x/10);
    }
  if(exec_counter==40)
    {
   // Music("1.mid");
    RemoveObject(0);
    }
  return(1);
  }
