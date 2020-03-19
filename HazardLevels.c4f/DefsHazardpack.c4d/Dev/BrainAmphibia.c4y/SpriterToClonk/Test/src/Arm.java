import java.awt.Graphics2D;

public class Arm extends Part {

  private final int width = 16;

  private final int height = 64;

  public Arm() {
    super();
    this.originX = 8;
    this.originY = 32;
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
    // TODO Auto-generated method stub

  }
}
