// Obsolete, because simple byte[]'s are used to store the jpg data
public class SimpleImage {

	// -1 means undefined
	public int width;
	
	public byte[] data;
	public SimpleImage(byte[] dataParam, int widthParam){
		data = dataParam;
		width = widthParam;
	}
}
