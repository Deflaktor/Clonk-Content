import java.awt.Graphics2D;

public class Body extends Part {

  private final int width = 98;

  private final int height = 118;

  private boolean aimHead = false;

  private boolean aimLeft = false;

  private boolean aimRight = false;

  public Body() {
    super();
    this.originX = 49;
    this.originY = 59;
  }

  @Override
  public void paint(Graphics2D g) {
    if (this.image != null) {
      g.drawImage(this.image, this.x - this.originX, this.y - this.originY, this.width, this.height, null);
    }
    g.drawOval(this.x - this.originX, this.y - this.originY, this.width, this.height);
  }

  @Override
  public void update() {
    this.Local0 = ((this.Local0 + 1) % 360);
    this.Local1 = ((this.Local1 + 1) % 100);
    this.Local2 += 5;
    if (this.Local2 > 100) {
      this.Local2 = 100;
    }
    idle();
    if (this.aimHead) {
      lookAtTarget();
    }
    if (this.aimLeft) {
      aimAtTargetLeft();
    }
  }

  public void idle() {
    final int angle = Sin(this.Local0, 45);
    final int angle2 = Sin(this.Local0, 15);
    final int angle3 = Sin(this.Local0, 10);
    // Right Leg
    SetDir(this.dir, rightFoot);
    rightLeg.PlaceR(rightFoot, 15, -8, -angle2 + 180 - 40, -15, -15, this.dir, this.Local2);
    rightThigh.PlaceR(rightLeg, -5, -24, angle2 + 180 + 40, -10, -10, this.dir, this.Local2);
    rightKnee.Place(rightLeg, 5, -21, -angle2 + 180 - 40, -18, 15, this.dir, this.Local2);
    // Left Leg
    leftFoot.Place(rightFoot, 30, 0, 0, 0, 0, this.dir, this.Local2);
    leftLeg.PlaceR(leftFoot, 15, -8, -angle2 + 180 - 40, -15, -15, this.dir, this.Local2);
    leftThigh.PlaceR(leftLeg, -5, -24, angle2 + 180 + 40, -10, -10, this.dir, this.Local2);
    leftKnee.Place(leftLeg, 5, -21, -angle2 + 180 - 40, -18, 15, this.dir, this.Local2);
    // Body
    body.Place(rightThigh, 16, -32, angle2 + 180 + 40, -10, -10, this.dir, this.Local2);
    // Right Arm
    rightArm.PlaceR(body, -8, -20, angle3 + 15 + 10, -32, -32, this.dir, this.Local2);
    rightElbow.Place(rightArm, 0, 0, angle3 + 15, -32, -32, this.dir, this.Local2);
    rightForearm.PlaceR(rightElbow, 0, 0, angle3 + 15 + 45, -32, -32, this.dir, this.Local2);
    // Left Arm
    leftArm.PlaceR(body, 0, -32, angle3 + 15, -32, -32, this.dir, this.Local2);
    leftElbow.Place(leftArm, 0, 0, angle3 + 15, -32, -32, this.dir, this.Local2);
    leftForearm.PlaceR(leftElbow, 0, 0, angle3 + 15 + 45, -32, -32, this.dir, this.Local2);
    // Head
    neck.PlaceR(body, -30, -65, angle - 90 + 45, -10, -10, this.dir, this.Local2);
    head.PlaceR(neck, -30, -35, 0, 0, 0, this.dir, this.Local2);
  }

  public void lookAtTarget() {
    // System.out.println("Angle between (" + body.x + "," + body.y + ") and (" + tx + "," + ty + "): "
    // + Angle(body.x, body.y, tx, ty));
    final int angleMouth = (Angle(0, 0, head.mouthX, head.mouthY) + 360) % 90;
    final int angle1 = (AngleToTarget(this.x, this.y - 30, tx, ty, this.dir) - angleMouth + 90 + 45) % 360;
    final int angle2 = Sin(angle1 + 90, 45) - 30;
    // 360 = UP 270 = FORWARD 180 = DOWN 90 = BACKWARD
    // Head
    neck.PlaceR(body, -28, -48, angle2, 32, 32, this.dir, this.Local2);
    final int rX = Sin(angle2 + 180, -32);
    final int rY = -Cos(angle2 + 180, -32);
    head.PlaceR(neck, rX, rY, angle1, 0, 0, this.dir, this.Local2, head.jointX, head.jointY);
  }

  public void aimAtTargetLeft() {
    // System.out.println("Angle between (" + body.x + "," + body.y + ") and (" + tx + "," + ty + "): "
    // + Angle(body.x, body.y, tx, ty));
    final int angle1 = AngleToTarget(this.x, this.y, tx, ty, this.dir) + 180;
    final int angle3 = angle1 - Sin(angle1, 30) - 15;
    // 360 = UP 270 = FORWARD 180 = DOWN 90 = BACKWARD
    // Left Arm
    leftArm.PlaceR(body, 0, -32, angle3 + 15, -32, -32, this.dir, this.Local2);
    leftElbow.Place(leftArm, 0, 0, angle3 + 15, -32, -32, this.dir, this.Local2);
    leftForearm.PlaceR(leftElbow, 0, 0, angle1, -32, -32, this.dir, this.Local2);
  }

  public void aimAtTargetRight() {
    final int angle1 = AngleToTarget(this.x, this.y, tx, ty, this.dir) + 180;
    final int angle3 = angle1 - Sin(angle1, 30) - 15;
    // 360 = UP 270 = FORWARD 180 = DOWN 90 = BACKWARD
    leftArm.PlaceR(body, 0, -32, angle3 + 15, -32, -32, this.dir, this.Local2);
    leftElbow.Place(leftArm, 0, 0, angle3 + 15, -32, -32, this.dir, this.Local2);
    leftForearm.PlaceR(leftElbow, 0, 0, angle1, -32, -32, this.dir, this.Local2);
  }

  public void trigger() {
    this.aimHead = !this.aimHead;
    this.Local2 = 0;
  }

  public void head(boolean selected) {
    this.aimHead = selected;
    this.Local2 = 0;
  }

  public void leftArm(boolean selected) {
    this.aimLeft = selected;
    this.Local2 = 0;
  }

  public void rightArm(boolean selected) {
    this.aimRight = selected;
    this.Local2 = 0;
  }

}
