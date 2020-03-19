package de.def;

import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Iterator;

import com.brashmonkey.spriter.Animation;
import com.brashmonkey.spriter.Data;
import com.brashmonkey.spriter.Entity;
import com.brashmonkey.spriter.Entity.CharacterMap;
import com.brashmonkey.spriter.FileReference;
import com.brashmonkey.spriter.Loader;
import com.brashmonkey.spriter.Mainline.Key;
import com.brashmonkey.spriter.Player;
import com.brashmonkey.spriter.Player.PlayerListener;
import com.brashmonkey.spriter.SCONReader;
import com.brashmonkey.spriter.Timeline;
import com.brashmonkey.spriter.Timeline.Key.Object;

public class Convert implements PlayerListener {

	boolean animationFinished;
	Player player;
	MyDrawer drawer;

	public static void main(String[] args) throws IOException {
		new Convert();
	}

	public Convert() throws IOException {
		String json = new String(Files.readAllBytes(Paths.get("../../animation_002.scon")), StandardCharsets.UTF_8);

		SCONReader reader = new SCONReader(json);
		Data data = reader.getData();
		Loader<Img> loader = new Loader<Img>(data) {
			@Override
			protected Img loadResource(FileReference ref) {
				return new Img(data.getFile(ref));
			}
		};
		loader.load(new File(""));
		Entity entity = data.getEntity("Entity");
		player = new Player(entity);
		
		drawer = new MyDrawer(loader);
	}
	
	public void convert() {
		player.addListener(this);
		player.speed = 15;
		for (int i = 0; i < player.getEntity().animations(); i++) {
			player.setAnimation(i);
			player.setTime(0);
			animationFinished = false;
			while (!animationFinished) {
				player.update();
				draw(player.objectIterator(), player.characterMaps);
			}
		}
		player.flipX();
	}
	
	public Player getPlayer() {
		return player;
	}
	
	public MyDrawer getDrawer() {
		return drawer;
	}
	
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

	private void draw(Object object) {
		System.out.println(object.pivot.x + ", " + object.pivot.y);
	}

	@Override
	public void animationFinished(Animation animation) {
		animationFinished = true;
	}

	@Override
	public void animationChanged(Animation oldAnim, Animation newAnim) {
		// TODO Auto-generated method stub

	}

	@Override
	public void preProcess(Player player) {
		// TODO Auto-generated method stub

	}

	@Override
	public void postProcess(Player player) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mainlineKeyChanged(Key prevKey, Key newKey) {
		// TODO Auto-generated method stub

	}

}
