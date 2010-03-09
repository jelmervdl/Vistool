import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Collection;
import java.util.List;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.Searcher;
import org.apache.lucene.search.TopDocCollector;
import org.apache.lucene.store.Directory;

public class LuceneAccess {
	
	public LuceneAccess(){
	}
	
	public String[] getTop(String queryString, int topNumber, String indexName){
		try {
			Searcher searcher = new IndexSearcher(indexName);
			Analyzer analyzer = new StandardAnalyzer();

			QueryParser queryParser = new QueryParser("captions", analyzer);
			Query query = queryParser.parse(queryString);
			System.out.println("Searching for: " + query.toString("captions"));

			TopDocCollector collector = new TopDocCollector(topNumber);
			searcher.search(query, collector);
			ScoreDoc[] hits = collector.topDocs().scoreDocs;
			String[] urlHashList = new String[topNumber];
			for (int i = 0; i < hits.length; i++) {
				int docId = hits[i].doc;
				//Document d = searcher.doc(docId);
				String urlHash = searcher.doc(docId).get("urlhash");
				//System.out.println(urlHash);
				urlHashList[i] = urlHash;
			}
			    
			//System.out.println(hits.length + " total matching documents");
			
			return urlHashList;
			
		} catch (Exception e) {
			System.out.println(" caught a " + e.getClass() +
					"\n with message: " + e.getMessage());
			return null;
		}
	}
	
	public String[] getTop(String queryString, int topNumber){
		return getTop(queryString, topNumber, "label-index-subset");
	}

	public String[] getTop(String queryString){
		return getTop(queryString, 1);
	}

	public String[] getTop(String queryString, String indexName){
		return getTop(queryString, 1, indexName);
	}
	
	// getting captions to each image
	public String[] getImageUrlsByCaptionFromDir(Directory captionDir, String keyword){
		try {
			IndexReader reader = IndexReader.open(captionDir);
			int total = reader.maxDoc();
			
			Searcher searcher = new IndexSearcher(captionDir);
			Analyzer analyzer = new StandardAnalyzer();
			QueryParser queryParser = new QueryParser("caption", analyzer);
			Query query = queryParser.parse(keyword);
			TopDocCollector collector = new TopDocCollector(total);
			searcher.search(query, collector);
			ScoreDoc[] hits = collector.topDocs().scoreDocs;
			String[] urlHashList = new String[hits.length];
			System.out.println("getUrlsByCaption: " + hits.length);
			for (int i = 0; i < hits.length; i++) {
				int docId = hits[i].doc;
				urlHashList[i] = searcher.doc(docId).get("digest");
				System.out.println("getUrlsByCaption: " + urlHashList[i]);
			}
			return urlHashList;
		} catch (Exception e) {
			System.out.println(" caught a " + e.getClass() +
					"\n with message: " + e.getMessage());
			return null;
		}
	}

	public void test(){
		System.out.println("Testing lucene access.");
		
		try {
			Searcher searcher = new IndexSearcher("label-index-subset");
			Analyzer analyzer = new StandardAnalyzer();
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			
			System.out.println("Query: ");
			String line = in.readLine();

			QueryParser queryParser = new QueryParser("captions", analyzer);
			Query query = queryParser.parse(line);
			System.out.println("Searching for: " + query.toString("captions"));

			//Query query = QueryParser.parse(line);
			/*
			//Hits hits = searcher.search(query);
			final int[] n_hits = new int[1]; // array instead of int
			final Vector hits = new Vector();
			searcher.search(query, new HitCollector() {
				public void collect(int doc, float score) {
					System.out.println(doc);
					hits.add(doc);
				}
			});
			System.out.println("Hits: " + hits.size());
			*/
			TopDocCollector collector = new TopDocCollector(99999);
			searcher.search(query, collector);
			ScoreDoc[] hits = collector.topDocs().scoreDocs;
			System.out.println(hits.length);
			for (int i = 0; i < hits.length; i++) {
				int docId = hits[i].doc;
				Document d = searcher.doc(docId);
				System.out.println(d.get("urlhash"));
			}
			    
			//System.out.println(hits.length() + " total matching documents");
			
		} catch (Exception e) {
			System.out.println(" caught a " + e.getClass() +
					"\n with message: " + e.getMessage());
		}
	}
}
