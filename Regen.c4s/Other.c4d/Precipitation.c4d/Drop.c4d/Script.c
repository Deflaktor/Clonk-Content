#strict

Initialize:
  // SetRDir(10);
  SetXDir(GetWind()*2);
  Local(0)=50+Random(25);
  return(1);
  
Check:
  SetXDir(GetWind()*2);
  SetYDir(Local(0));
  if(Random(5))
  DrawTransform();
  if(InLiquid())
    Hit();
  return(1);
  
Hit:
  if(GetX()<10||GetX()>LandscapeWidth()-10)
    return(1);
  else
    CastPXS("Water",20,30);
  RemoveObject();
  return(1);
  
  
private func DrawTransform()
{	// draw line
    var r = Angle(0,0,GetXDir(),GetYDir())/2;
	var w = 1;
	var l = -Distance(0,0,GetXDir(),GetYDir())/10;
	SetR(r);
	
	var iPosi = 0;

	//var cl = BoundBy( l-iPosi, 0, l);
	//cl = l*GetActMapVal("Facet","Laser",0,3)/GetActMapVal("Facet",GetAction(),0,3);

	var fsin = -Sin(r, 1000), fcos = Cos(r, 1000);

	var xoff = 0;
	var yoff = 0;

	var width = +fcos*w/2, height = +fcos*l;
	var xskew = +fsin*l, yskew = -fsin*w/2;

	var xadjust = +fcos*xoff + fsin*yoff +fsin*iPosi;
	var yadjust = -fsin*xoff + fcos*yoff +fcos*iPosi;

	// set matrix values
	SetObjDrawTransform ( width, xskew, xadjust, yskew, height, yadjust );
	
}