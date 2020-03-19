import java.awt.Graphics2D;

public class Forearm extends Part {

  private final int width = 14;

  private final int height = 64;

  public Forearm() {
    super();
    this.originX = 7;
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
