import java.awt.AlphaComposite;
import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.EventQueue;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.geom.GeneralPath;
import java.awt.image.BufferedImage;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class DaveTest2 {

	private JFrame frame;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					DaveTest2 window = new DaveTest2();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public DaveTest2() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 450, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		JPanel panel = new JPanel();
		panel.setLayout(new BorderLayout());

		frame.add(panel);

		JLabel label = new JLabel("<html><b>This is</b> a <i> TEST</i></html>");
		label.setFont(label.getFont().deriveFont(24.0f));
		panel.add(label, BorderLayout.NORTH);
		frame.setVisible(true);

		// Create an empty image
		final BufferedImage img = new BufferedImage(label.getWidth(),
				label.getHeight(), BufferedImage.TYPE_INT_ARGB);
		Graphics2D g2 = (Graphics2D) img.getGraphics();
		g2.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		// Paint text to an empty image
		g2.translate(0, 2);
		g2.setFont(label.getFont());
		label.setForeground(Color.BLACK);
		g2.translate(1, 0);
		label.paint(g2);
		g2.translate(-2, 0);
		label.paint(g2);
		g2.translate(1, 0);
		g2.translate(0, 1);
		label.paint(g2);
		g2.translate(0, -2);
		label.paint(g2);
		g2.translate(0, 1);
		label.setForeground(Color.WHITE);
		label.paint(g2);
		// Get the non transparent pixels
//		GeneralPath gp = getOutline(img);
//		
//		// Redraw on the non transparent pixels
//		g2.setStroke(new BasicStroke(2.5f));
//		g2.setPaint(Color.BLACK);
//		g2.draw(gp);
		
		// Redraw the text on top of it
		label.paint(g2);
		
		
		JPanel imgPanel = new JPanel() {
			private static final long serialVersionUID = 1L;
			protected void paintComponent(Graphics g) {
				Graphics2D g2 = (Graphics2D) g;
				AlphaComposite ac = AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.5f);
				g2.setComposite(ac);
				g2.drawImage(img, 0, 0, null);
			};
		};

		panel.add(imgPanel, BorderLayout.CENTER);

	}

	public static GeneralPath getOutline(BufferedImage bi) {
		// construct the GeneralPath
		GeneralPath gp = new GeneralPath();
		gp.moveTo(0, 0);

		boolean cont = false;
		for (int xx = 0; xx < bi.getWidth(); xx++) {
			for (int yy = 0; yy < bi.getHeight(); yy++) {
				if (new Color(bi.getRGB(xx, yy), true).getAlpha() >= 200) {
					if (cont) {
						gp.lineTo(xx, yy);
						gp.lineTo(xx, yy + 1);
						gp.lineTo(xx + 1, yy + 1);
						gp.lineTo(xx + 1, yy);
						gp.lineTo(xx, yy);
					} else {
						gp.moveTo(xx, yy);
					}
					cont = true;
				} else {
					cont = false;
				}
			}
			cont = false;
		}
		gp.closePath();
		return gp;
	}

}
