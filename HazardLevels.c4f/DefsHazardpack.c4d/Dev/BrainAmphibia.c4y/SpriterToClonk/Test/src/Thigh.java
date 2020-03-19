import java.awt.Graphics2D;

public class Thigh extends Part {

  private final int width = 22;

  private final int height = 48;

  public Thigh() {
    super();
    this.originX = 12;
    this.originY = 24;
  }

  @Override
  public void paint(Graphics2D g) {
    if (this.image != null) {
      g.drawImage(this.image, this.x - this.originX, this.y - this.originY, this.width, this.height, null);
    }
    g.drawRoundRect(this.x - this.originX, this.y - this.originY, this.width, this.height, 10, 50);
  }

  @Override
  public void update() {
    // TODO Auto-generated method stub

  }
}
