package as.mke.lavrun;

import java.io.*;
import java.nio.charset.Charset;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;
import java.util.zip.ZipInputStream;

public class ReadFile {
    public static InputStream readFile(String path,String filename) throws IOException {
       // String path = "F:\\*******\\201707\\78641695079026649.zip";
        ZipFile zf = new ZipFile(path);
		InputStream ine=null;
        InputStream in = new BufferedInputStream(new FileInputStream(path));
        Charset gbk = Charset.forName("utf8");
        ZipInputStream zin = new ZipInputStream(in,gbk);
        ZipEntry ze;
        while((ze = zin.getNextEntry()) != null){
			
			
			
		if(ze.getName().equals(filename)){
            //    BufferedReader br = new BufferedReader(
				ine=zf.getInputStream(ze);
					/*
                String line;
                while((line = br.readLine()) != null){
                    System.out.println(line.toString());
                }
              */
            }
            
			
			}
     //  zin.closeEntry();
    
	
	return ine;
	
	}
	
}
