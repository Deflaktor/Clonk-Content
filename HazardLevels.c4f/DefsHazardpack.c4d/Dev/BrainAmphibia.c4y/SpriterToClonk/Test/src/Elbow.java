import java.awt.Graphics2D;

public class Elbow extends Part {

  private final int width = 10;

  private final int height = 10;

  public Elbow() {
    super();
    this.originX = 5;
    this.originY = 5;
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
