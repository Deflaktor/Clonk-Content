package de.def;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.EventQueue;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.io.IOException;

import javax.swing.DefaultComboBoxModel;
import javax.swing.DefaultListCellRenderer;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.ListCellRenderer;
import javax.swing.border.EmptyBorder;

import com.brashmonkey.spriter.Animation;

public class Ui extends JFrame {

	public static JPanel contentPane;
	public static Convert convert;

	/**
	 * Launch the application.
	 * 
	 * @throws IOException
	 */
	public static void main(String[] args) throws IOException {
		convert = new Convert();
		EventQueue.invokeLater(new Runnable() {
			@Override
			public void run() {
				try {
					final Ui frame = new Ui();
					frame.setSize(800, 600);
					frame.setLocationRelativeTo(null);
					frame.setVisible(true);

				} catch (final Exception e) {
					e.printStackTrace();
				}
			}
		});
		new Thread(new Runnable() {
			@Override
			public void run() {
				while (true) {
					try {
						Thread.sleep(1000 / 37);
					} catch (final InterruptedException e) {
						e.printStackTrace();
					}
					convert.player.update();
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
		Ui.contentPane = new JPanel() {
			@Override
			protected void paintComponent(Graphics g) {
				final Graphics2D g2 = (Graphics2D) g;
				super.paintComponent(g);
				g2.translate(100, 100);
				convert.drawer.setGraphics(g2);
				convert.drawer.draw(convert.player);
				g2.translate(-100, -100);
			}
		};
		Ui.contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		Ui.contentPane.setLayout(new BorderLayout(0, 0));
		final JPanel panel = new JPanel();
		Ui.contentPane.add(panel, BorderLayout.SOUTH);
		int count = convert.player.getEntity().animations();
		Animation[] animations = new Animation[count];
		for (int i = 0; i < animations.length; i++) {
			animations[i] = convert.player.getEntity().getAnimation(i);
		}
		final JComboBox<Animation> combobox = new JComboBox<Animation>(animations);
		combobox.setRenderer(new DefaultListCellRenderer() {
			@Override
			public Component getListCellRendererComponent(JList<?> list, Object value, int index, boolean isSelected,
					boolean cellHasFocus) {
				value = ((Animation) value).name;
				return super.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
			}
		});
		combobox.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				convert.player.setAnimation((Animation) combobox.getSelectedItem());
			}
		});
		panel.add(combobox);
		final JButton button = new JButton("Flip");
		button.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				convert.player.flipX();
			}
		});
		panel.add(button);
		setContentPane(Ui.contentPane);
	}
}
