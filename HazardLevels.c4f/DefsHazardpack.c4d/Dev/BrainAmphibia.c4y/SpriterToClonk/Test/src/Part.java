import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

import javax.imageio.ImageIO;

public abstract class Part extends Commons {
  public static Body body;

  public static Head head;

  public static Neck neck;

  public static Knee rightKnee;

  public static Leg rightLeg;

  public static Thigh rightThigh;

  public static Foot rightFoot;

  public static Knee leftKnee;

  public static Leg leftLeg;

  public static Thigh leftThigh;

  public static Foot leftFoot;

  public static Arm leftArm;

  public static Elbow leftElbow;

  public static Forearm leftForearm;

  public static Arm rightArm;

  public static Elbow rightElbow;

  public static Forearm rightForearm;

  public static int tx, ty;

  public int originX, originY;

  public int previousR;

  protected BufferedImage image;

  public Part() {
    this.Local2 = 100;
    try {
      this.image = ImageIO.read(getClass().getClassLoader().getResourceAsStream(getClass().getSimpleName() + ".png"));
    } catch (final Exception e) {
      // e.printStackTrace();
    }
  }

  public void paintDo(Graphics2D g) {
    final double theta = this.r / 360d * 2 * Math.PI;
    g.translate(250, 250);
    if (GetDir() == DIR_Right()) {
      g.scale(-1, 1);
    }
    // g.rotate(-theta);
    g.rotate(theta, this.x, this.y);
    paint(g);
    g.drawLine(this.x - 1, this.y, this.x + 1, this.y);
    g.drawLine(this.x, this.y - 1, this.x, this.y + 1);
    g.rotate(-theta, this.x, this.y);
    if (GetDir() == DIR_Right()) {
      g.scale(-1, 1);
    }
    // g.rotate(theta);
    g.translate(-250, -250);
  }

  public abstract void paint(Graphics2D g);

  public abstract void update();

  public static void init() {
    body = new Body();
    head = new Head();
    neck = new Neck();
    rightKnee = new Knee();
    rightLeg = new Leg();
    rightThigh = new Thigh();
    rightFoot = new Foot();
    leftKnee = new Knee();
    leftLeg = new Leg();
    leftThigh = new Thigh();
    leftFoot = new Foot();
    rightArm = new Arm();
    rightElbow = new Elbow();
    rightForearm = new Forearm();
    leftArm = new Arm();
    leftElbow = new Elbow();
    leftForearm = new Forearm();
  }

  public static void updateAll() {
    body.update();
    head.update();
    neck.update();
    rightKnee.update();
    rightLeg.update();
    rightThigh.update();
    rightFoot.update();
    leftKnee.update();
    leftLeg.update();
    leftThigh.update();
    leftFoot.update();
    rightArm.update();
    rightElbow.update();
    rightForearm.update();
    leftArm.update();
    leftElbow.update();
    rightForearm.update();
  }

  public static void paintAll(Graphics2D g2) {
    rightLeg.paintDo(g2);
    rightThigh.paintDo(g2);
    rightFoot.paintDo(g2);
    rightKnee.paintDo(g2);
    rightArm.paintDo(g2);
    rightElbow.paintDo(g2);
    rightForearm.paintDo(g2);
    neck.paintDo(g2);
    body.paintDo(g2);
    head.paintDo(g2);
    leftLeg.paintDo(g2);
    leftThigh.paintDo(g2);
    leftFoot.paintDo(g2);
    leftKnee.paintDo(g2);
    leftArm.paintDo(g2);
    leftElbow.paintDo(g2);
    leftForearm.paintDo(g2);
  }

  // Place only
  protected Part Place(Part origin, int rX, int rY, int angle, int lengthX, int lengthY, int mirror, int percentage) {
    return Place(origin, rX, rY, angle, lengthX, lengthY, mirror, percentage, 0, 0);
  }

  protected Part Place(Part origin,
                       int rX,
                       int rY,
                       int angle,
                       int lengthX,
                       int lengthY,
                       int mirror,
                       int percentage,
                       int anchorx,
                       int anchory) {
    angle = InterpolateAngle(this.previousR, angle, percentage);
    this.previousR = angle;
    final int length = (int)Math.sqrt(anchorx * anchorx + anchory * anchory);
    if (anchorx != 0 || anchory != 0) {
      final int angleAnchor = (Angle(0, 0, anchorx, anchory) + 360) % 90;
      angle -= angleAnchor;
    }
    SetYDir(0, this);
    rX += Sin(angle, lengthX + length);
    rY -= Cos(angle, lengthY + length);
    if (mirror > 0) {
      // rX *= -1;
      SetDir(DIR_Right(), this);
    } else {
      SetDir(DIR_Left(), this);
    }

    SetPosition(GetX(origin) + rX, GetY(origin) + rY, this);
    return this;
  }

  protected int Interpolate(int v1, int v2, int percentage) {
    if (percentage == 100) {
      return v2;
    }
    return (v1 * (100 - percentage) + v2 * percentage) / 100;
  }

  protected int InterpolateAngle(int a1, int a2, int percentage) {
    if (percentage == 100) {
      return a2;
    }
    final int diff = (((((a2 - a1) % 360) + 540) % 360) - 180);
    return a1 + diff * percentage / 100;
  }

  // Place and rotate
  protected Part PlaceR(Part origin, int rX, int rY, int angle, int lengthX, int lengthY, int mirror, int percentage) {
    return PlaceR(origin, rX, rY, angle, lengthX, lengthY, mirror, percentage, 0, 0);
  }

  protected Part PlaceR(Part origin,
                        int rX,
                        int rY,
                        int angle,
                        int lengthX,
                        int lengthY,
                        int mirror,
                        int percentage,
                        int anchorx,
                        int anchory) {
    if (mirror > 0) {
      // angle = InterpolateAngle(this.previousR, -angle, percentage);
      angle = InterpolateAngle(this.previousR, angle, percentage);
    } else {
      angle = InterpolateAngle(this.previousR, angle, percentage);
    }
    SetR(angle, this);
    this.previousR = angle;
    return Place(origin, rX, rY, angle, lengthX, lengthY, mirror, 100, anchorx, anchory);
  }

  protected int AngleToTarget(int sx, int sy, int tx, int ty, int mirror) {
    if (mirror > 0) {
      return -Angle(sx, sy, tx, ty);
    } else {
      return Angle(sx, sy, tx, ty);
    }
  }

}
