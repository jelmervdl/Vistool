import java.awt.image.BufferedImage;
//import java.awt.image.DataBufferByte;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class ImageLoader {
	protected int width;
	protected int[] imageData;

	public ImageLoader(String fileName){
		System.out.println("ImageLoader constructor, 2009 jul 29 5:26");
		//int[] imageData = null;
		
		BufferedImage bufferedImage = null;
		try {
			bufferedImage = ImageIO.read(new File(fileName));
		} catch (IOException e) {	
		}
		System.out.println("width x height: " + bufferedImage.getWidth() + " " + bufferedImage.getHeight());
		//System.out.println("numBanks: " + bufferedImage.getRaster().getDataBuffer().getNumBanks());
		System.out.println(bufferedImage.getData().getDataBuffer().getSize());
		
		width = bufferedImage.getWidth();
		//System.out.println(bufferedImage.toString());
		
		//System.out.println(bufferedImage.getData().);

		imageData = bufferedImage.getData().getPixels(0, 0, bufferedImage.getWidth(), bufferedImage.getHeight(), (int[])null);
		//int[] imageIntData = bufferedImage.getRGB(0, 0, bufferedImage.getWidth(), bufferedImage.getHeight(), null, 0, bufferedImage.getWidth());
		/*for (int i = 0; i < imageData.length; i++){
			System.out.print(imageData[i]);
			System.out.print(" ");
			if (((i+1) % 3) == 0 ) {
				System.out.print(" ");
			}
		}*/
		System.out.println();
	}
	
	public ImageLoader(){
		this("9x9.png");
		
	}
	
	public int[] getData(){
		return imageData;
	}
	
	public int getWidth(){
		return width;
	}
}
