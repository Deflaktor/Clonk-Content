import java.awt.Graphics2D;

public class Head extends Part {

  private final int width = 126;

  private final int height = 96;

  public final int jointX = 35;

  public final int jointY = 40;

  public final int mouthX = -44;

  public final int mouthY = 30;

  public Head() {
    super();
    this.originX = 63;
    this.originY = 48;
  }

  @Override
  public void paint(Graphics2D g) {
    if (this.image != null) {
      g.drawImage(this.image, this.x - this.originX, this.y - this.originY, this.width, this.height, null);
    }
    g.drawOval(this.x - this.originX, this.y - this.originY, this.width, this.height);
    g.drawOval(this.x + this.mouthX, this.y + this.mouthY, 5, 5);
    g.drawOval(this.x + this.jointX, this.y + this.jointY, 5, 5);
  }

  @Override
  public void update() {
    // TODO Auto-generated method stub

  }
}
