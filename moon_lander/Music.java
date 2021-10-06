package main.moon_lander;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;


public class Music {
	
	private static Clip clip;
	
	public static void playMusic(String pathName, boolean isLoop) {
		try {
			clip = AudioSystem.getClip();
			File audioFile = new File(pathName);
			AudioInputStream ais = AudioSystem.getAudioInputStream(audioFile);
			clip.open(ais);
			clip.start();
			if(isLoop) {
				clip.loop(Clip.LOOP_CONTINUOUSLY);
			}
		}catch(LineUnavailableException e) {
			e.printStackTrace();
		}
		catch(UnsupportedAudioFileException e) {
			e.printStackTrace();
		}
		catch(IOException e) {
			e.printStackTrace();
		}
	}


 
}
