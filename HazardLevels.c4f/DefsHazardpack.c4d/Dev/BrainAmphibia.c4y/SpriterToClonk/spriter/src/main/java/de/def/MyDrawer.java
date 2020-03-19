package de.def;

import java.awt.Color;
import java.awt.Graphics2D;
import java.util.Iterator;

import com.brashmonkey.spriter.Drawer;
import com.brashmonkey.spriter.Loader;
import com.brashmonkey.spriter.Player;
import com.brashmonkey.spriter.Timeline;
import com.brashmonkey.spriter.Entity.CharacterMap;
import com.brashmonkey.spriter.Timeline.Key.Object;

public class MyDrawer extends Drawer<Img> {

	private Graphics2D g;
	public int S = 400; 

	public MyDrawer(Loader<Img> loader) {
		super(loader);
	}

	public void setGraphics(Graphics2D g) {
		this.g = g;
	}

	@Override
	public void setColor(float r, float g, float b, float a) {
		this.g.setColor(new Color(r, g, b, a));
	}

	@Override
	public void line(float x1, float y1, float x2, float y2) {
		g.drawLine((int) x1, S-(int) y1, (int) x2, S-(int) y2);
	}

	@Override
	public void rectangle(float x, float y, float width, float height) {
		g.drawRect((int) x, S-(int) y, (int) width, (int) height);
	}

	@Override
	public void circle(float x, float y, float radius) {
		g.drawOval((int) (x - radius), S-(int) (y - radius), (int) radius * 2, (int) radius * 2);
	}

	@Override
	public void draw(Object object) {
	}
	
	@Override
	public void draw(Player player) {
		draw(player.objectIterator(), player.characterMaps);
		drawBones(player);
		drawBoxes(player);
		drawPoints(player);
	}

	/**
	 * Draws the objects the given iterator is providing with the given character map. 
	 * @param it the iterator iterating over the objects to draw
	 * @param map the character map to draw
	 */
	public void draw(Iterator<Timeline.Key.Object> it, CharacterMap[] maps){
		while(it.hasNext()){
			Timeline.Key.Object object = it.next();
			if(object.ref.hasFile()){
				if(maps != null){
					for(CharacterMap map: maps)
						if(map != null)
							object.ref.set(map.get(object.ref));
				}
			}
			this.draw(object);
		}
	}
}
