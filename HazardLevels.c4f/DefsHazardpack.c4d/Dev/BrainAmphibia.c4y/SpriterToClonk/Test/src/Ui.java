import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

/*
 * icon Systemhaus GmbH
 * www.icongmbh.de
 */

/**
 * 
 *
 */

public class Ui extends JFrame {

  public static JPanel contentPane;

  /**
   * Launch the application.
   */
  public static void main(String[] args) {
    Part.init();
    EventQueue.invokeLater(new Runnable(){
      @Override
      public void run() {
        try {
          final Ui frame = new Ui();
          frame.setVisible(true);
        } catch (final Exception e) {
          e.printStackTrace();
        }
      }
    });
    new Thread(new Runnable(){
      @Override
      public void run() {
        while (true) {
          try {
            Thread.sleep(1000 / 37);
          } catch (final InterruptedException e) {
            e.printStackTrace();
          }
          Part.updateAll();
          if (Ui.contentPane != null) {
            Ui.contentPane.repaint();
          }
        }
      }
    }).start();
  }

  /**
   * Create the frame.
   */
  public Ui() {
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
   // setBounds(-400, 840, 400, 340);
    Ui.contentPane = new JPanel(){
      @Override
      protected void paintComponent(Graphics g) {
        final Graphics2D g2 = (Graphics2D)g;
        super.paintComponent(g);
        Part.paintAll(g2);
      }
    };
    Ui.contentPane.addMouseMotionListener(new MouseMotionAdapter(){
      @Override
      public void mouseMoved(MouseEvent e) {
        Part.tx = e.getX() - 250;
        Part.ty = e.getY() - 250;
      }
    });
    Ui.contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
    Ui.contentPane.setLayout(new BorderLayout(0, 0));
    final JPanel panel = new JPanel();
    Ui.contentPane.add(panel, BorderLayout.SOUTH);
    final JCheckBox checkbox1 = new JCheckBox("Head");
    checkbox1.addActionListener(new ActionListener(){

      @Override
      public void actionPerformed(ActionEvent e) {
        Part.body.head(checkbox1.isSelected());
      }
    });
    panel.add(checkbox1);
    final JCheckBox checkbox2 = new JCheckBox("Left Arm");
    checkbox2.addActionListener(new ActionListener(){

      @Override
      public void actionPerformed(ActionEvent e) {
        Part.body.leftArm(checkbox2.isSelected());
      }
    });
    panel.add(checkbox2);
    final JCheckBox checkbox3 = new JCheckBox("Right Arm");
    checkbox3.addActionListener(new ActionListener(){

      @Override
      public void actionPerformed(ActionEvent e) {
        Part.body.rightArm(checkbox3.isSelected());
      }
    });
    panel.add(checkbox3);
    final JButton button = new JButton("Flip");
    button.addActionListener(new ActionListener(){
      @Override
      public void actionPerformed(ActionEvent e) {
        if (Part.body.GetDir() == 0) {
          Part.body.SetDir(1, Part.body);
        } else {
          Part.body.SetDir(0, Part.body);
        }
      }
    });
    panel.add(button);
    setContentPane(Ui.contentPane);
  }
}
