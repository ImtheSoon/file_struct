package main.moon_lander;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.event.KeyEvent;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.URL;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;

/**
 * Actual game.
 * 
 * @author www.gametutorial.net
 */

public class Game {

    /**
     * The space rocket with which player will have to land.
     */
    private PlayerRocket playerRocket;
    
    /**
     * Landing area on which rocket will have to land.
     */
    private LandingArea landingArea;
    
    /**
     * Game background image.
     */
    private BufferedImage backgroundImg;
    
    /**
     * Red border of the frame. It is used when player crash the rocket.
     */
    private BufferedImage redBorderImg;
    
    private BufferedImage backgroundEarthImg;
    
    private BufferedImage backgroundSpaceImg;

    public Game()
    {
        Framework.gameState = Framework.GameState.GAME_CONTENT_LOADING;
        
        Thread threadForInitGame = new Thread() {
            @Override
            public void run(){
                // Sets variables and objects for the game.
                Initialize();
                // Load game files (images, sounds, ...)
                LoadContent();
                Music.playMusic("src/resources/musics/backgroundmusic.wav",true);
                Framework.gameState = Framework.GameState.PLAYING_EARTH;
            }
        };
        threadForInitGame.start();
    }
    
    
   /**
     * Set variables and objects for the game.
     */
    private void Initialize()
    {
        playerRocket = new PlayerRocket();
        landingArea  = new LandingArea();
        
    }
    
    /**
     * Load game files - images, sounds, ...
     */
    private void LoadContent()
    {
        try
        {
            URL backgroundImgUrl = this.getClass().getClassLoader().getResource("background.jpg");
            backgroundImg = ImageIO.read(backgroundImgUrl);
            URL backgroundEarthImgUrl = this.getClass().getClassLoader().getResource("background_earth.jpg");
            backgroundEarthImg = ImageIO.read(backgroundEarthImgUrl);
            URL backgroundSpaceImgUrl = this.getClass().getClassLoader().getResource("background_space.jpg");
            backgroundSpaceImg = ImageIO.read(backgroundSpaceImgUrl);
            
            
            URL redBorderImgUrl = this.getClass().getClassLoader().getResource("red_border.png");
            redBorderImg = ImageIO.read(redBorderImgUrl);
            
            
        }
        catch (IOException ex) {
            Logger.getLogger(Game.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
    /**
     * Restart game - reset some variables.
     */
    public void RestartGame()
    {
        playerRocket.ResetPlayer();
    }
    
    
    /**
     * Update game logic.
     * 
     * @param gameTime gameTime of the game.
     * @param mousePosition current mouse position.
     */
    public void UpdateGame(long gameTime, Point mousePosition)
    {
        // Move the rocket
        playerRocket.Update();
        if(Canvas.keyboardKeyState(KeyEvent.VK_P))
        	playerRocket.Pause();
        if(Canvas.keyboardKeyState(KeyEvent.VK_R))
        	playerRocket.Resume();
      
        
        // Checks where the player rocket is. Is it still in the space or is it landed or crashed?
        // First we check bottom y coordinate of the rocket if is it near the landing area.
        if(Framework.gameState==Framework.GameState.PLAYING_MOON) {
        if(playerRocket.y + playerRocket.rocketImgHeight - 10 > landingArea.y)
        {
            // Here we check if the rocket is over landing area.
            if((playerRocket.x > landingArea.x) && (playerRocket.x < landingArea.x + landingArea.landingAreaImgWidth - playerRocket.rocketImgWidth))
            {
                // Here we check if the rocket speed isn't too high.
                if(playerRocket.speedY <= playerRocket.topLandingSpeed)
                    playerRocket.landed = true;
                else
                    playerRocket.crashed = true;
            }
            else
                playerRocket.crashed = true;
                
            Framework.gameState = Framework.GameState.GAMEOVER;
        }
        
        }
        if(Framework.gameState==Framework.GameState.PLAYING_EARTH) {
        	if(playerRocket.y<-70) {
        		playerRocket.y=(int)(Framework.frameHeight * 0.9);
        		Framework.gameState = Framework.GameState.PLAYING_SPACE;
        		
        	}
        	
        }
        if(Framework.gameState==Framework.GameState.PLAYING_SPACE) {
        	if(playerRocket.y<-70) {
        		Framework.gameState = Framework.GameState.PLAYING_MOON;
        		playerRocket.y=0;
        		playerRocket.speedY=0;
        	}
        	
        }
    }
    
    /**
     * Draw the game to the screen.
     * 
     * @param g2d Graphics2D
     * @param mousePosition current mouse position.
     */
    public void Draw(Graphics2D g2d, Point mousePosition)
    {
        g2d.drawImage(backgroundImg, 0, 0, Framework.frameWidth, Framework.frameHeight, null);
        
        landingArea.Draw(g2d);
        
        playerRocket.Draw(g2d);
    }
    public void DrawEarth(Graphics2D g2d, Point mousePosition)
    {
        g2d.drawImage(backgroundEarthImg, 0, 0, Framework.frameWidth, Framework.frameHeight, null);
        
        playerRocket.Draw(g2d);
    }
    public void DrawSpace(Graphics2D g2d, Point mousePosition)
    {
        g2d.drawImage(backgroundSpaceImg, 0, 0, Framework.frameWidth, Framework.frameHeight, null);
        
        playerRocket.Draw(g2d);
    }
    public void DrawPause(Graphics2D g2d, Point mousePosition)
    {
        g2d.drawString("The game has been paused", Framework.frameWidth / 2 - 100, Framework.frameHeight / 3);
        
        playerRocket.Draw(g2d);
    }
    /**
     * Draw the game over screen.
     * 
     * @param g2d Graphics2D
     * @param mousePosition Current mouse position.
     * @param gameTime Game time in nanoseconds.
     * @param pauseTime 
     */
    public void DrawGameOver(Graphics2D g2d, Point mousePosition, long gameTime, long pauseTime)
    {
        Draw(g2d, mousePosition);
        
        g2d.drawString("Press space or enter to restart.", Framework.frameWidth / 2 - 100, Framework.frameHeight / 3 + 70);
        
        if(playerRocket.landed)
        {
            g2d.drawString("You have successfully landed!", Framework.frameWidth / 2 - 100, Framework.frameHeight / 3);
            g2d.drawString("You have landed in " + (gameTime) / Framework.secInNanosec + " seconds.",Framework.frameWidth / 2 - 100, Framework.frameHeight / 3 + 20);
            g2d.drawString("You paused " + (pauseTime) / Framework.secInNanosec + " seconds.",Framework.frameWidth/ 2 - 100, Framework.frameHeight / 3 + 40);
        }
        else
        {
            g2d.setColor(Color.red);
            g2d.drawString("You have crashed the rocket!", Framework.frameWidth / 2 - 95, Framework.frameHeight / 3);
            g2d.drawImage(redBorderImg, 0, 0, Framework.frameWidth, Framework.frameHeight, null);
        }
    }
}
