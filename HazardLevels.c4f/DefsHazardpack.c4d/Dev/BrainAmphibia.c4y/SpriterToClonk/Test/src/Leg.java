import java.awt.Graphics2D;

public class Leg extends Part {

  private final int width = 16;

  private final int height = 32;

  public Leg() {
    super();
    this.originX = 8;
    this.originY = 16;
  }

  @Override
  public void paint(Graphics2D g) {
    if (this.image != null) {
      g.drawImage(this.image, this.x - this.originX, this.y - this.originY, this.width, this.height, null);
    }
    g.drawRoundRect(this.x - this.originX, this.y - this.originY, this.width, this.height, 5, 5);
  }

  @Override
  public void update() {
    // TODO Auto-generated method stub

  }
}
