import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

/*import java.awt.Frame;
import java.awt.Graphics2D;
//import java.awt.Rectangle;
import java.awt.Window;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
*/

public class imageHandling {
	byte [] getImage( String str ) {
		System.out.println("Image handling program 2009 jul 29");

		//ImageLoader loader = new ImageLoader();
		LuceneAccess luceneAccess = new LuceneAccess();
		//System.out.println("aap1");
		String[] galleries = luceneAccess.getTop("ferrari", 10);
		
		ImageLoaderByHash loader = new ImageLoaderByHash(galleries[0]);
		
		// get images of first gallery
		String[] imageHashList = loader.getGallery();
		// get first image of first gallery
		//		byte[] image = imageLoader.getImage(imageHashList[0]);
		byte[] image = loader.getImageByLongHash(galleries[0]+imageHashList[0]);
		// System.out.println(image.length);
		return image;
	}
	public static void main( String[] args ) {
		System.out.println("Image handling program 2009 jul 29");

		//ImageLoader loader = new ImageLoader();
		LuceneAccess luceneAccess = new LuceneAccess();
		System.out.println("aap1");
		String[] galleries = luceneAccess.getTop("barcelone", 10);
		ImageLoaderByHash loader = new ImageLoaderByHash(galleries[0]);
		
		// get images of first gallery
		String[] imageHashList = loader.getGallery();
		// get first image of first gallery
		//		byte[] image = imageLoader.getImage(imageHashList[0]);
		byte[] image = loader.getImageByLongHash(galleries[0]+imageHashList[0]);
		System.out.println(image.length);
		try {
			FileOutputStream fos = new FileOutputStream("aap.jpg");
			fos.write(image);
			fos.close(); 
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		/*
		BufferedImage image = null;
		try {
			image = ImageIO.read(new File("thumb.jpg"));
		} catch (IOException e) {
			System.out.println("Error reading file");
		}
		System.out.println(image.getWidth() + " " + image.getHeight());
		
		//Frame frame = new Frame("Image");
		//Rectangle bounds = gc.getBounds();
		//f.setLocation(10 + bounds.x, 10 + bounds.y);

		
		//Window windows = new Window(frame);
        //Rectangle bounds = gc.getBounds();
        //w.setLocation(10 + bounds.x, 10 + bounds.y);

		//frame.setVisible(true);

		JFrame jFrame = new JFrame("Thumb");  

		jFrame.setBounds(0, 0, image.getWidth(), image.getHeight());
		JImagePanel jImagePanel = new JImagePanel(image,0,0);
		jFrame.add(jImagePanel);
		jFrame.setVisible(true);
		
		// Get the surfaces Graphics object
		Graphics2D graphics2d = (Graphics2D)jFrame.getRootPane().getGraphics();
		*/ 
		
		// Now draw the image
		//graphics2d.drawString("Thumb", 10, 10);
		//graphics2d.drawImage(image, null, 10, 10);  
		//graphics2d.drawString("Thumb2", 10, 30);
		//graphics2d.drawImage(image, null, 0, 10);
		
		//JLabel label = new JLabel(icon);
		//JFrame f = new JFrame();
	}
}
