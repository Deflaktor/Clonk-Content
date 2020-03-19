import java.awt.Graphics2D;

public class Foot extends Part {

  private final int width = 48;

  private final int height = 16;

  public Foot() {
    super();
    this.originX = 24;
    this.originY = 8;
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
