public abstract class Commons {
  public int x, y, r;

  public int Local0, Local1, Local2, Local3, Local4, Local5;

  public int dir;

  public void SetPosition(int x, int y, Part obj) {
    obj.x = x;
    obj.y = y;
  }

  public void SetDir(int dir, Part obj) {
    obj.dir = dir;
  }

  public int GetDir() {
    return this.dir;
  }

  public int GetY(Part origin) {
    if (origin == null) {
      return this.y;
    }
    return origin.y;
  }

  public int GetX(Part origin) {
    if (origin == null) {
      return this.x;
    }
    return origin.x;
  }

  public int GetR(Part obj) {
    if (obj == null) {
      return this.r;
    }
    return obj.r;
  }

  public int GetX() {
    return this.x;
  }

  public int GetY() {
    return this.y;
  }

  public int DIR_Left() {
    return 0;
  }

  public int DIR_Right() {
    return 1;
  }

  public int Cos(int angle, int lengthY) {
    return (int)(Math.cos(angle * Math.PI * 2d / 360d) * lengthY);
  }

  public int Sin(int angle, int lengthX) {
    return (int)(Math.sin(angle * Math.PI * 2d / 360d) * lengthX);
  }

  public int Angle(int iX1, int iY1, int iX2, int iY2) {
    return (int)(360 + 90 + Math.atan2((iY2 - iY1), (iX2 - iX1)) * 360d / Math.PI / 2d) % 360;
  }

  public void SetYDir(int yDir, Part obj) {
    // nothing
  }

  public void SetR(int r, Part obj) {
    obj.r = r;
  }
}
