package de.def;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import javax.imageio.ImageIO;

public class Img {
	private BufferedImage image;

	public Img(com.brashmonkey.spriter.File file) {
		try {
			this.image = ImageIO.read(new FileInputStream(new File("../../" + file.name)));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
