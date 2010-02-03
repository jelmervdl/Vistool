import java.io.IOException;
import java.io.UnsupportedEncodingException;

import com.kalooga.crawl.conf.KaloogaConf; 
import com.kalooga.crawl.store.GalleryitemsReader;
import com.kalooga.crawl.store.proxy.FactoryProxy;

import org.apache.lucene.store.Directory;

public class ImageLoaderByHash {
	private FactoryProxy proxy;
	private GalleryitemsReader reader;
	
	public ImageLoaderByHash(String galleryHash){
		this();
		
		//init with a gallery url
		reader = proxy.getReaderByHash(galleryHash);
	}

	public ImageLoaderByHash(){
		KaloogaConf.getConf().set( "items.proxy.host", "devserver1.kalooga.com" );
		KaloogaConf.getConf().set( "items.proxy.port", "8008" );
		proxy = new FactoryProxy();
	}

	public String[] getGallery(String galleryHash){
		//String domain = "domain";
		//System.out.println(itemsReader.getThumbImagesHashes());
		//for (int i = 0; i < imageHashes.length();){
		//}
		
		//byte[] thumbBytes = itemsReader.getImageThumbByHashTypeL(imageHashes[0]);
		return (proxy.getReaderByHash(galleryHash)).getThumbImagesHashes().split(" ");
	}
	
	public String[] getGallery(){
		//String domain = "domain";
		//System.out.println(itemsReader.getThumbImagesHashes());
		//for (int i = 0; i < imageHashes.length();){
		//}
		
		//byte[] thumbBytes = itemsReader.getImageThumbByHashTypeL(imageHashes[0]);
		return reader.getThumbImagesHashes().split(" ");
	}
	
	public byte[] getImage(String imageHash){
		// returns a byte array with the bytes in jpg format.
		try{
			return reader.getImageThumbByHashTypeL(imageHash);
		}
		catch (Exception e) {
			System.out.println(" caught a " + e.getClass() +
					"\n with message: " + e.getMessage());
			return null;
		}	
	}
	
	public byte[] getImage(){
		// does NOT work:
		//return this.getImage("83d7869c1e3483f7ea07eb75b7bdb8c388cafff1");
		//return this.getImage("c4de18c40218c23f2a13b2997008da3bca71d5a9");
		return null;
	}
	
	public byte[] getImageByLongHash(String longHash){
		String galleryHash = longHash.substring(0, 40);
		String imageHash = longHash.substring(40);
		
		return proxy.getReaderByHash(galleryHash).getImageThumbByHashTypeL(imageHash);
	}

	public String getImageString(String imageHash){
		return new String(this.getImage(imageHash));
	}
	
	public String getImageStringByLongHash(String longHash){
		try {
			return new String(this.getImageByLongHash(longHash), "ISO-8859-1");
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
	}
	
	public String[] getImageUrlsByCaption(String galleryHash, String keyword){
		LuceneAccess luceneAccess = new LuceneAccess();
		Directory captionDir = proxy.getReaderByHash(galleryHash).getCaptionIndex();
		return luceneAccess.getImageUrlsByCaptionFromDir(captionDir, keyword); 
	}
}
